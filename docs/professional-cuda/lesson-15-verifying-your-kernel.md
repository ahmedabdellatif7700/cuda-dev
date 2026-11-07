# Lesson 15 — Verifying Your Kernel

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Introducing the CUDA Programming Model |
| Subsection | Verifying Your Kernel |
| Printed pages | 39 |
| Roadmap ID | 2.1.6 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Core idea

Successful launch/completion and fast execution do not prove numerical correctness.

**Code or evidence:** [matrix_add_2d.cu](../../src/matrix_add_2d.cu). For a 7-by-3 array with A = 0..20 and B = 10, inspect outputs 10..30. There is no automated reference comparison by user preference.

**Original lesson commit:** `f9cb9c8`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Concept and code connection

Verification asks whether results match the intended algorithm, not whether a launch finished. Typical methods are a CPU reference, known outputs, boundaries and appropriate floating-point tolerances. Per your preference, the program prints outputs and does not implement automated comparisons. For the 7-by-3 matrix, A = 0..20 and B = 10 gives sums 10..30. Inspect rows and partial tiles visually; this does not certify all outputs for all inputs. An indexing error may return plausible wrong numbers with no CUDA error. Numerical proof and profiler measurements are different evidence.

## Expected observations

ncu-ui cannot establish numerical correctness. No automatic reference checker is added; explicit coverage reasoning and visual observations are documented.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): AddMatrix2D. See the [handout](../ncu-profiling/lesson-15-verifying-your-kernel.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
