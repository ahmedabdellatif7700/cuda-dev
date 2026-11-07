# Lesson 5 — Paradigm of Heterogeneous Computing: observation handout

Book: Chapter 1, Heterogeneous Computing; printed pp. 12–13. Roadmap ID 1.2.2.
See [lesson notes](../professional-cuda/lesson-05-paradigm-of-heterogeneous-computing.md).

## Core idea

Choose CPU or GPU work placement according to useful parallelism, control flow, data size, and movement cost.

**Code or evidence:** [combined_main.cpp](../../exercises/chapter-01/combined_main.cpp). The GPU performs independent additions; the CPU then sums the small returned array. This division demonstrates cooperation without proving a speedup.

**Original lesson commit:** `b0df87b`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Focus

Compare host preparation/consumption with the GPU addition. Capture `VectorAddScalar` only if useful; its geometry remains 2 blocks × 32 threads. The CPU sum is outside its kernel report. No overlap or CPU/GPU speedup is established.

## Record

- Kernel or source path examined: pending user discussion.
- Relevant PTX beside the implementation: identify only this lesson's operations.
- Actual capture and settings: pending, if applicable.
- Prediction versus observation: pending user discussion.

Do not run profilers automatically. Preserve the user-controlled ncu-ui workflow.
Host work, copy completion, and printed ordering cannot be explained by an isolated
kernel duration. PTX describes intermediate operations, not measured execution.
