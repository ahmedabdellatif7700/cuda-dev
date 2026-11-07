# Lesson 5 — Paradigm of Heterogeneous Computing: observation handout

Book: Chapter 1, Heterogeneous Computing; printed pp. 12–13. Roadmap ID 1.2.2.
See [lesson notes](../professional-cuda/lesson-05-paradigm-of-heterogeneous-computing.md).

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
