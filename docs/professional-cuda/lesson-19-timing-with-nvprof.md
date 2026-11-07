# Lesson 19 — Timing with nvprof

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Timing Your Kernel |
| Subsection | Timing with nvprof |
| Printed pages | 47–48 |
| Roadmap ID | 2.2.2 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Core idea

Profiler kernel duration measures a different scope from application wall time, and collection conditions affect interpretation.

**Code or evidence:** [lesson-19-timing-with-nvprof.md](../../docs/ncu-profiling/lesson-19-timing-with-nvprof.md). Use ncu-ui instead of the historical nvprof workflow. Compare matched workloads/settings; do not call a kernel duration the full CPU/GPU pipeline cost.

**Original lesson commit:** `e5bd970`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Concept and code connection

nvprof is the book’s historical profiler. Use your ncu-ui workflow for kernel Duration and launch/resource metrics. Replay and collection can perturb caches and concurrency; collection wall time is not kernel time. Inspect arithmetic intensity: one float addition reads two floats and writes one, or 12 logical bytes per output. Actual cache/DRAM bytes differ. A compute-to-byte argument suggests questions, not proof of a bottleneck. No old nvprof command or numeric Tesla result is assumed to match Orin.

## Expected observations

Keep n, datatype, launch, precision and collection settings explicit. Compare actual hierarchy traffic before claiming DRAM saturation.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): AddMatrix2D / AddMatrix1D / AddMatrixRows. See the [handout](../ncu-profiling/lesson-19-timing-with-nvprof.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
