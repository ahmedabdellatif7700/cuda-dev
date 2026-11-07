# Lesson 15 — Verifying Your Kernel: observation handout

Chapter 2 → Introducing the CUDA Programming Model → Verifying Your Kernel, printed pp. 39; roadmap 2.1.6.
See [lesson notes](../professional-cuda/lesson-15-verifying-your-kernel.md).

## Core idea

Successful launch/completion and fast execution do not prove numerical correctness.

**Code or evidence:** [matrix_add_2d.cu](../../src/matrix_add_2d.cu). For a 7-by-3 array with A = 0..20 and B = 10, inspect outputs 10..30. There is no automated reference comparison by user preference.

**Original lesson commit:** `f9cb9c8`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Monitor and interpret

Kernel(s): **AddMatrix2D**.

ncu-ui cannot establish numerical correctness. No automatic reference checker is added; explicit coverage reasoning and visual observations are documented.

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
