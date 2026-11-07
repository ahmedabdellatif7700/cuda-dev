# Lesson 22 — Summing Matrices with a 1D Grid and 1D Blocks

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Organizing Parallel Threads |
| Subsection | Summing Matrices with a 1D Grid and 1D Blocks |
| Printed pages | 57 |
| Roadmap ID | 2.3.3 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Core idea

A flat 1D mapping can process an entire matrix when the operation does not depend on row boundaries.

**Code or evidence:** [matrix_add_1d.cu](../../src/matrix_add_1d.cu). The 21-element matrix with 8 threads/block needs 3 blocks. Flat addition needs no division into row and column inside the kernel.

**Original lesson commit:** `88ef1a3`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Concept and code connection

Flatten the entire matrix and launch ceil(width*height/threads) blocks. With 21 outputs and 8 threads, the grid has 3 blocks. Addition does not need row/column division: a single flat index is sufficient. A block can cross row boundaries safely because each output is independent. Keep dimensions in the host interface for comparison with the 2D mappings.

## Expected observations

Compare with the same 21 outputs in AddMatrix2D. Small block sizes expose partial warps; no speed ranking is claimed from this teaching input.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): AddMatrix1D. See the [handout](../ncu-profiling/lesson-22-matrix-add-1d.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
