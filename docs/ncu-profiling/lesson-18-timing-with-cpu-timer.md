# Lesson 18 — Timing with CPU Timer: observation handout

Chapter 2 → Timing Your Kernel → Timing with CPU Timer, printed pp. 43–46; roadmap 2.2.1.
See [lesson notes](../professional-cuda/lesson-18-timing-with-cpu-timer.md).

## Core idea

An elapsed interval is meaningful only when its start, completion boundary, and included work are defined.

**Code or evidence:** [vector_add.cpp](../../src/vector_add.cpp). Timing only host submission differs from timing completed GPU work or allocation/copy/compute together. No source timer is added; this lesson is conceptual.

**Original lesson commit:** `ab4621b`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Monitor and interpret

Kernel(s): **Any selected kernel**.

Observe Duration and repeated-capture variation under comparable clocks. CPU latency and CUDA-event timing remain unmeasured, not silently inferred.

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
