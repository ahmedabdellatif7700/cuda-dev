# Lesson 21 — Summing Matrices with a 2D Grid and 2D Blocks: observation handout

Chapter 2 → Organizing Parallel Threads → Summing Matrices with a 2D Grid and 2D Blocks, printed pp. 53–56; roadmap 2.3.2.
See [lesson notes](../professional-cuda/lesson-21-matrix-add-2d.md).

## Monitor and interpret

Kernel(s): **AddMatrix2D**.

Compare grid/block dimensions, active lanes, memory sectors and Duration. Propose block-shape changes one at a time; do not select a winner from occupancy alone.

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
