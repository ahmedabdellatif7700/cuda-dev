# Lesson 8 — Is CUDA C Programming Difficult?: observation handout

Book: Chapter 1, Is CUDA C Programming Difficult?; printed pp. 20–21. Roadmap ID 1.4.
See [lesson notes](../professional-cuda/lesson-08-is-cuda-c-programming-difficult.md).

## Core idea

Efficient CUDA requires understanding both thread organization and memory locality, not merely translating syntax.

**Code or evidence:** [vector_add.cu](../../src/vector_add.cu). Adjacent thread indices read adjacent floats, demonstrating spatial locality. Single-pass addition has little reuse to justify shared-memory staging.

**Original lesson commit:** `3b2a2e0`. This note explains that lesson;
the current main may have advanced to a later experiment.

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
