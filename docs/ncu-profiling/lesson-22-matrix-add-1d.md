# Lesson 22 — Summing Matrices with a 1D Grid and 1D Blocks: observation handout

Chapter 2 → Organizing Parallel Threads → Summing Matrices with a 1D Grid and 1D Blocks, printed pp. 57; roadmap 2.3.3.
See [lesson notes](../professional-cuda/lesson-22-matrix-add-1d.md).

## Monitor and interpret

Kernel(s): **AddMatrix1D**.

Compare with the same 21 outputs in AddMatrix2D. Small block sizes expose partial warps; no speed ranking is claimed from this teaching input.

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
