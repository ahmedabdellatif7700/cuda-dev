# Lesson 6 — CUDA: A Platform for Heterogeneous Computing: observation handout

Book: Chapter 1, Heterogeneous Computing; printed pp. 14–16. Roadmap ID 1.2.3.
See [lesson notes](../professional-cuda/lesson-06-cuda-platform.md).

## Focus

Use the current kernel name to connect source → PTX → final SASS when needed. A PTX instruction need not map one-to-one to SASS. Read kernel register use from the capture rather than counting PTX virtual registers.

## Record

- Kernel or source path examined: pending user discussion.
- Relevant PTX beside the implementation: identify only this lesson's operations.
- Actual capture and settings: pending, if applicable.
- Prediction versus observation: pending user discussion.

Do not run profilers automatically. Preserve the user-controlled ncu-ui workflow.
Host work, copy completion, and printed ordering cannot be explained by an isolated
kernel duration. PTX describes intermediate operations, not measured execution.
