# Lesson 8 — Is CUDA C Programming Difficult?: observation handout

Book: Chapter 1, Is CUDA C Programming Difficult?; printed pp. 20–21. Roadmap ID 1.4.
See [lesson notes](../professional-cuda/lesson-08-is-cuda-c-programming-difficult.md).

## Focus

Inspect the actual bounds control and global loads/store when relevant. Do not introduce shared memory to this one-pass addition without a reuse hypothesis. Low utilization for two blocks does not demonstrate a broken memory layout.

## Record

- Kernel or source path examined: pending user discussion.
- Relevant PTX beside the implementation: identify only this lesson's operations.
- Actual capture and settings: pending, if applicable.
- Prediction versus observation: pending user discussion.

Do not run profilers automatically. Preserve the user-controlled ncu-ui workflow.
Host work, copy completion, and printed ordering cannot be explained by an isolated
kernel duration. PTX describes intermediate operations, not measured execution.
