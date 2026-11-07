# Lesson 19 — Timing with nvprof: observation handout

Chapter 2 → Timing Your Kernel → Timing with nvprof, printed pp. 47–48; roadmap 2.2.2.
See [lesson notes](../professional-cuda/lesson-19-timing-with-nvprof.md).

## Core idea

Profiler kernel duration measures a different scope from application wall time, and collection conditions affect interpretation.

**Code or evidence:** [lesson-19-timing-with-nvprof.md](../../docs/ncu-profiling/lesson-19-timing-with-nvprof.md). Use ncu-ui instead of the historical nvprof workflow. Compare matched workloads/settings; do not call a kernel duration the full CPU/GPU pipeline cost.

**Original lesson commit:** `e5bd970`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Monitor and interpret

Kernel(s): **AddMatrix2D / AddMatrix1D / AddMatrixRows**.

Keep n, datatype, launch, precision and collection settings explicit. Compare actual hierarchy traffic before claiming DRAM saturation.

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
