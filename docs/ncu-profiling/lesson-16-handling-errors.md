# Lesson 16 — Handling Errors: observation handout

Chapter 2 → Introducing the CUDA Programming Model → Handling Errors, printed pp. 40; roadmap 2.1.7.
See [lesson notes](../professional-cuda/lesson-16-handling-errors.md).

## Core idea

API errors, invalid launches, execution faults, and wrong answers are different failure classes with different evidence.

**Code or evidence:** [launch_errors.cu](../../exercises/chapter-02/launch_errors.cu). A zero-thread launch reports an argument error; a valid launch can complete successfully; an invalid device ID fails before useful GPU work.

**Original lesson commit:** `5fbcb3f`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Monitor and interpret

Kernel(s): **EmptyKernel in standalone exercise**.

Error messages and API status are the evidence here. An invalid launch may produce no kernel report. No performance conclusion follows.

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
