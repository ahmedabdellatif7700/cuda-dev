# Lesson 17 — Compiling and Executing: observation handout

Chapter 2 → Introducing the CUDA Programming Model → Compiling and Executing, printed pp. 40–42; roadmap 2.1.8.
See [lesson notes](../professional-cuda/lesson-17-compiling-and-executing.md).

## Core idea

Host and device compilation/linking produce one executable while preserving distinct CPU and GPU execution paths.

**Code or evidence:** [Makefile](../../Makefile). make clean build run builds and executes; make ptx emits intermediate GPU operations; make asm additionally extracts final device instructions.

**Original lesson commit:** `ce6d1e1`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Monitor and interpret

Kernel(s): **Current matrix kernels**.

Record compiler/target/revision with captures. Debug instrumentation changes instruction selection and performance.

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
