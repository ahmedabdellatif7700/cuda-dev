# Lesson 1 — Sequential and Parallel Programming

## Book location

| Field | Reference |
|---|---|
| Book | Cheng, Grossman, and McKercher, *Professional CUDA C Programming* (2014) |
| Chapter | 1 — Heterogeneous Parallel Computing with CUDA (starts p. 1) |
| Section | Parallel Computing (starts p. 2) |
| Subsection | Sequential and Parallel Programming (starts p. 3) |
| Reading | Printed p. 3; stop at Parallelism on p. 4. Read the introductions on pp. 1–2 first. |
| Roadmap ID | 1.1.1 — see [learning roadmap](cuda-learning-path.md) |
| Experiment | Scalar CUDA vector addition |
| Status | Build/run completed; small-grid screenshots discussed; size comparison pending |

The roadmap ID is our navigation label, not a section number printed in the book.

## Theory and GPU architecture

Each output `c[i] = a[i] + b[i]` depends only on input elements at index i.
A sequential CPU loop visits these outputs in order. The GPU assigns independent
outputs to threads, grouped in blocks that the GPU schedules on its SMs.
Parallel work still incurs launch, synchronization, and data-handling costs.
For example, A = [1, 2, 3] and B = [4, 5, 6] yield C = [5, 7, 9],
regardless of which GPU thread finishes first.

## Implementation

- `src/main.cpp`: create deterministic inputs and call `VectorAdd`.
- `src/vector_add.cu`: only the `VectorAddScalar` kernel and its launch wrapper.
- `src/vector_add.cpp`: allocation, input copies, call to the launch wrapper,
  and result copy. Contains no kernels or timers. The blocking result copy completes
  the GPU work.
- `include/VectorAdd.h`: the host interface using `std::span` and the device-pointer launch declaration.
- `include/CudaSupport.h`: existing checked CUDA calls and allocation ownership.

There are no timers, CUDA events, benchmark loops, or runtime-wrapper classes.
The kernel and host runtime operations live in separate files. CMake links
`CUDA::cudart` to expose CUDA runtime headers and linkage to the C++ wrapper.
The Makefile and its build/run workflow are unchanged.

## Experiment and correctness

Run 0, 1, 16, 31, 33, 257, 1,024, 65,536, and 4,194,307 elements with
256 threads/block. Empty input performs no launch. Each nonempty size launches
once, including sizes that exercise partial warps and blocks.

There is no CPU reference or numerical result comparison. CUDA API and launch
error checks remain. A `Completed` line reports that the GPU work and result copy
completed; it does not certify numerical correctness.

## Measurements

Kernel measurements belong to your `ncu-ui` workflow. The program only computes
results; it makes no CPU/GPU speedup claims.

## Expected GPU behavior

Each output is independent, so thread execution order does not affect the result.
Small inputs expose few blocks; larger inputs expose more parallel work.
A bounds check keeps threads in the final partial block from accessing beyond
an array. On Orin, CPU and GPU share physical DRAM while CUDA still provides
explicit allocation, copy, and synchronization semantics.

## Build and validation

Validated with `make clean build run` on 2026-11-01: Release build succeeded
using GNU C++ 13.3.0, CUDA 13.2.86, CMake 3.28.3, and architecture 87.
All nine input sizes completed with exit status 0. No numerical result checks
or performance measurements were performed. User profiling and discussion remain
pending; record target conditions with your captures.

## User profiling and discussion

Profile `VectorAddScalar` in `ncu-ui`, starting with Duration and Launch Statistics.
The nonempty sizes launch 1, 1, 1, 1, 2, 4, 256, and 16,385 blocks respectively.
Select the input of interest using the launch order and grid dimensions. There
are no warmup or timing launches. Empty input does not appear in the captures.
Kernel duration does not include the host allocation/copy pipeline. Share your
captures and collection settings so we can interpret the actual behavior together.

## Completion gate

- Explain why output elements are independent and where CPU/GPU work occurs.
- Explain allocation, copies, the kernel launch, and completion of the result copy.
- Run the input sizes and compare your profiling observations with the prediction.
- Discuss your kernel captures before advancing to **1.1.2 — Parallelism (p. 4)**.

Results and discussion: initial small-grid capture recorded below; larger-grid comparison pending.

## Profiling handout

See the [Nsight Compute profiling handout](../ncu-profiling/lesson-01-sequential-and-parallel-programming.md)
for the observation checklist, screenshot interpretation, and proposed code changes.
