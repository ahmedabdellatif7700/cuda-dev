# Lesson 6 — CUDA: A Platform for Heterogeneous Computing: observation handout

Book: Chapter 1, Heterogeneous Computing; printed pp. 14–16. Roadmap ID 1.2.3.
See [lesson notes](../professional-cuda/lesson-06-cuda-platform.md).

## Core idea

CUDA is a complete programming platform; source language, runtime, driver, compiler, and tools serve different roles.

**Code or evidence:** [CMakeLists.txt](../../CMakeLists.txt). The host compiler builds C++ orchestration, nvcc compiles CUDA, and cudart supports runtime calls. PTX is intermediate code, not a profiling result.

**Original lesson commit:** `1e8f7c0`. This note explains that lesson;
the current main may have advanced to a later experiment.

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
