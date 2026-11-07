# Lesson 12 — Organizing Threads: observation handout

Chapter 2 → Introducing the CUDA Programming Model → Organizing Threads, printed pp. 30–35; roadmap 2.1.3.
See [lesson notes](../professional-cuda/lesson-12-organizing-threads.md).

## Core idea

Thread coordinates are local until combined with block coordinates; multidimensional geometry is a logical indexing scheme.

**Code or evidence:** [thread_mapping.cu](../../src/thread_mapping.cu). In 1D, global = blockIdx.x * blockDim.x + threadIdx.x. For 2D local linearization, use x + blockDim.x * y.

**Original lesson commit:** `0d60fee`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Monitor and interpret

Kernel(s): **WriteThreadIndices / AddMatrix2D**.

Record grid and block in all dimensions, total threads and partial participation. Do not equate local ID with SM number.

For actual kernels: begin with Launch Statistics (grid/block dimensions), Duration,
and relevant Source/SASS or generated PTX. Inspect Occupancy and Memory Workload
Analysis only when they answer a concrete question. Record revision, input shape,
block size, tool/collection settings, clocks, and variation. Keep numerical correctness,
compiled PTX, and measured behavior as distinct forms of evidence.

## Change candidates

For matrix kernels, vary one launch dimension/shape at equal output count after
deriving the new indexing and bounds. For host API topics, inspect returned values
or messages rather than optimizing a nonexistent kernel. No code change or tool
suggestion is automatically a speedup; keep the baseline and ask what measurement
would distinguish competing explanations.

## Observation record

- Expected geometry or host API outcome: derive before capturing.
- Actual capture or command output: pending user discussion unless recorded in summary.
- Predicted versus observed behavior: pending.
- Proposed next change and acceptance criterion: pending.

You perform ncu-ui captures. No automatic profiling is run, and no kernel Duration
is presented as the whole pipeline cost.
