# Lesson 20 — Indexing Matrices with Blocks and Threads: observation handout

Chapter 2 → Organizing Parallel Threads → Indexing Matrices with Blocks and Threads, printed pp. 49–52; roadmap 2.3.1.
See [lesson notes](../professional-cuda/lesson-20-indexing-matrices.md).

## Core idea

Row-major storage turns a two-dimensional coordinate into a unique flat array location.

**Code or evidence:** [matrix_add_2d.cu](../../src/matrix_add_2d.cu). At width 7, row 2 and column 3 map to index 17. Row and column bounds must both be satisfied before accessing that location.

**Original lesson commit:** `f96534d`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Monitor and interpret

Kernel(s): **AddMatrix2D**.

Grid (2,2) and block (4,2) launch 32 threads for 21 outputs. Trace coordinates before considering throughput.

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
