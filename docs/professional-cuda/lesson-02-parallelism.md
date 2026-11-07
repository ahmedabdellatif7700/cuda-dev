# Lesson 2 — Parallelism

## Book location

| Field | Reference |
|---|---|
| Book | Cheng, Grossman, and McKercher, *Professional CUDA C Programming* (2014) |
| Chapter | 1 — Heterogeneous Parallel Computing with CUDA |
| Section | Parallel Computing (starts p. 2) |
| Subsection | Parallelism (printed pp. 4–5) |
| Roadmap ID | 1.1.2 — [learning roadmap](cuda-learning-path.md) |
| Experiment | Scalar baseline versus cyclic grid-stride vector addition |
| Status | Implementation prepared; user profiling pending |

Read through the data-partition figures and stop before Computer Architecture
on p. 6. Roadmap IDs are our navigation labels, not printed book numbering.

## Core idea

Data parallelism applies one operation to many data items; cyclic ownership lets a bounded set of threads cover a larger array.

**Code or evidence:** [vector_add_cyclic.cu](../../src/vector_add_cyclic.cu). With four threads, thread 1 owns indices 1, 5, 9. The stride is the total launched thread count, not the block size alone.

**Original lesson commit:** `ce01ba4`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Theory and GPU architecture

**Data parallelism:** apply the same operation to independent data items. Both
vector-add kernels do this. **Task parallelism:** perform different independent
functions concurrently. Running these two kernels sequentially does not demonstrate
concurrent task execution; streams and concurrency are covered later.

The book distinguishes contiguous block partitioning from cyclic partitioning.
A contiguous partition gives each worker a consecutive chunk; a cyclic partition
revisits chunks separated by the number of workers. A data-partition block is not
necessarily a CUDA thread block. The existing scalar kernel is a one-element-per-
thread baseline, not a general multi-element contiguous-chunk implementation.

For four conceptual threads and twelve elements:

| Thread | Contiguous partition (theory) | Cyclic partition |
|---|---|---|
| 0 | 0, 1, 2 | 0, 4, 8 |
| 1 | 3, 4, 5 | 1, 5, 9 |
| 2 | 6, 7, 8 | 2, 6, 10 |
| 3 | 9, 10, 11 | 3, 7, 11 |

For cyclic ownership, `first_index = blockIdx.x * blockDim.x + threadIdx.x` and
`grid_stride = gridDim.x * blockDim.x`. Thread `first_index` handles
`first_index, first_index + grid_stride, first_index + 2 * grid_stride, ...` while the index is below `element_count`.
Neighboring lanes still access neighboring elements during each iteration.

### Launch vocabulary: elements, threads, and blocks

An **element** is one array value. A **thread** is one execution of the kernel
body. A CUDA **thread block** groups threads, and a **grid** contains all blocks
in one launch. The GPU schedules blocks on its streaming multiprocessors (SMs);
launched threads need not all be resident at the same time.

| Code name | Meaning | Current setting |
|---|---|---|
| `element_count` | Number of values in each input and output array | Changes for each run |
| `threads_per_block` | Number of threads in one CUDA block; also called block size | 256 |
| `block_count` | Number of blocks launched; also called grid size for this 1D launch | Calculated in the launch wrapper |
| `max_blocks` | Upper limit we choose for the cyclic grid, not threads per block | 64 |
| `first_index` | Global index assigned to a thread at the start | `blockIdx.x * blockDim.x + threadIdx.x` |
| `grid_stride` | Total launched threads, and the jump between one thread's elements | `gridDim.x * blockDim.x` |

The launch syntax is `Kernel<<<block_count, threads_per_block>>>(...)`.
For example, 64 blocks with 256 threads/block launch 16,384 threads. That does
not limit the array to 16,384 elements: a thread can repeat work in a loop.

### What makes the kernel cyclic?

“Cyclic” describes data ownership, not a special CUDA kernel type. The usual
CUDA name for this implementation is a **grid-stride loop**:

```cpp
const auto first_index = std::size_t(blockIdx.x) * blockDim.x + threadIdx.x;
const auto grid_stride = std::size_t(gridDim.x) * blockDim.x;
for (auto index = first_index; index < element_count; index += grid_stride)
    output[index] = input_a[index] + input_b[index];
```

Read the loop in three steps:

1. Start at this thread's own global index.
2. Add the input values at that index and write the corresponding output.
3. Jump ahead by the total launched thread count; repeat while inside the array.

With 4 threads and 12 elements, thread 1 starts at index 1, then handles 5 and 9.
Its next index is 13, so it exits. Thread 2 handles 2, 6, and 10 independently.
Each thread's iterations run in sequence; different threads provide parallelism.
There is no barrier between iterations or global requirement that threads finish
one iteration together. Adjacent lanes executing the same iteration still access
adjacent elements, which suits coalesced memory access.

For a tail example, 4 threads and 10 elements give ownership {0,4,8}, {1,5,9},
{2,6}, and {3,7}. Some threads do one more addition. The loop condition stops
each thread before it accesses an invalid index. No thread shares an output
index with another thread.

### How the two kernels differ for our actual inputs

The scalar baseline computes one output per thread, guarded by a bounds check.
It needs `ceil(element_count / threads_per_block)` blocks. Integer arithmetic
implements that as `(element_count + threads_per_block - 1) / threads_per_block`.
The cyclic variant caps that calculated count at `max_blocks` and covers the
remaining elements by looping.

| At 65,536 elements | Scalar baseline | Cyclic variant |
|---|---:|---:|
| Threads/block | 256 | 256 |
| Blocks | 256 | 64 |
| Total launched threads | 65,536 | 16,384 |
| Outputs/thread | 1 | 4 |
| Total additions | 65,536 | 65,536 |

For cyclic thread 5, those four indices are 5, 16,389, 32,773, and 49,157.
Its next index is 65,541, beyond the array. Every other thread follows the same
rule from its own starting index.

This decouples array size from grid size. It can reuse threads and reduce block
scheduling work, but also adds loop instructions and can expose too little
parallel work if the grid cap is too small. It does not reduce the number of
required additions or output values. Only your matched profiling captures can
show whether it helps for a particular input and launch configuration.

### Reading the book's 2D partition examples

The figures also show 2D partitioning: chunks along rows, chunks along both
axes, and cyclic chunks along one axis. Sketch row/column ownership before
flattening to row-major indices. Alternative x/y and two-axis cyclic patterns
remain part of Chapter 1 exercise 1; this lesson's implementation stays 1D.

## Implementation

- `src/main.cpp`: run scalar then cyclic addition for one selected input size
  (currently 65,536). Inputs contain 1 and 2, so the displayed sums should be 3.
  Keep 256 threads/block; set the cyclic grid cap to 64 blocks. After each call,
  print the first eight returned values (or all values for smaller arrays). Empty
  input prints only the variant label. This is an output preview, not an automated result check.
- `src/vector_add.cu`: unchanged scalar kernel and launch wrapper.
- `src/vector_add_cyclic.cu`: separate cyclic kernel and launch wrapper.
- `src/vector_add.cpp`: two plain host functions with explicit allocation, copy, and launch steps.
  Their straightforward repetition keeps each path easy to read; no templates or
  lambdas are used. The host interface accepts ordinary vector references.
- `include/VectorAdd.h`: declarations for both operations and launch wrappers.

The cyclic launch uses `min(ceil(element_count / threads_per_block), max_blocks)`. The 64-block cap
is an experiment setting, not a claimed optimum for Orin. Blocks are distributed
by the GPU scheduler; the program does not pin eight blocks to each SM.

## Experiment and correctness

Use identical input arrays and 256 threads/block for both variants. The program
runs one size, 65,536, with no size sweep or printing helper. To explore other
sizes, change `element_count` in `main.cpp`: 0, 1, 16, 31, 33, 257, 1,024, or
4,194,307. Each host call owns separate
device buffers and performs its own input and output copies. The host output
buffer is reused. No timers or numerical result comparisons are included.

Reason about coverage: every valid index has exactly one remainder modulo stride,
so one cyclic thread owns it. The loop condition handles short inputs and tails.
Empty arrays launch neither kernel. CUDA error handling remains; completion logs
establish successful execution, not numerical correctness.

## Measurements and expected GPU behavior

You collect kernel evidence in `ncu-ui`. For sizes up to 1,024, both variants use
the same grid size. At 65,536 elements the baseline has 256 blocks and cyclic has
64; at 4,194,307 elements they have 16,385 and 64. The cyclic threads perform more
work each, with loop/indexing overhead and potentially different resource usage.
Fewer launched threads does not mean less output data or guaranteed lower time.

## Build and validation

`make clean build run` completed successfully on 2026-11-01 (exit status 0).
Both variants completed all nine input sizes; empty input launched no kernel.
Configuration: Release, GNU C++ 13.3.0, CUDA 13.2.86, CMake 3.28.3, architecture 87.
The simplified single-size main is also checked with the same command; its
output previews contain eight values of 3 for each variant. No numerical result
comparisons or automated profiler captures are performed.

## User profiling and discussion

Follow the [lesson 2 profiling handout](../ncu-profiling/lesson-02-parallelism.md).
Capture the actual `VectorAddScalar` and `VectorAddCyclic` kernels at matching
input sizes. Discuss work distribution before considering optimization.

## Completion gate

- Distinguish data parallelism from task parallelism.
- Explain contiguous and cyclic ownership, including the 2D figures.
- Derive cyclic indices for a small input and explain unique ownership and tails.
- Explain how a capped grid can process more elements than it launches threads.
- Interpret your matched kernel captures before advancing to **1.1.3 — Computer
  Architecture (p. 6)**.
