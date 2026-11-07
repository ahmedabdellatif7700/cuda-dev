# Lesson 23 — Summing Matrices with a 2D Grid and 1D Blocks: observation handout

Chapter 2 → Organizing Parallel Threads → Summing Matrices with a 2D Grid and 1D Blocks, printed pp. 58–59; roadmap 2.3.4.
See [lesson notes](../professional-cuda/lesson-23-matrix-add-rows.md).

## Core idea

A 2D grid with 1D blocks can dedicate each grid row to one matrix row.

**Code or evidence:** [matrix_add_rows.cu](../../src/matrix_add_rows.cu). With width 7, height 3, and 4 threads/block, grid (2,3) launches 24 threads; each row has one thread beyond its width.

**Original lesson commit:** `d9c9df1`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Monitor and interpret

Kernel(s): **AddMatrixRows**.

Inspect block count, work per row and transaction patterns. Keep datatype and outputs fixed when comparing variants.

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
