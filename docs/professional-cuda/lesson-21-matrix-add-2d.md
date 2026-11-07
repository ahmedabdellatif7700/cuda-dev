# Lesson 21 — Summing Matrices with a 2D Grid and 2D Blocks

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Organizing Parallel Threads |
| Subsection | Summing Matrices with a 2D Grid and 2D Blocks |
| Printed pages | 53–56 |
| Roadmap ID | 2.3.2 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Core idea

A 2D grid and 2D blocks distribute ownership independently along rows and columns.

**Code or evidence:** [matrix_add_2d.cu](../../src/matrix_add_2d.cu). A 7-by-3 matrix with block (4,2) needs grid (2,2). It launches 32 threads for 21 valid outputs, so edge checks are essential.

**Original lesson commit:** `62932e7`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Concept and code connection

Use AddMatrix2D: block (4,2), grid (ceil(7/4),ceil(3/2)) = (2,2). Each lane checks row and column before accessing index = row*width+column. Edge tiles contain inactive threads. At equal total threads, changing block aspect ratio changes how warps traverse rows and memory. The tiny display shape teaches ownership; larger matching shapes are needed for meaningful performance investigation.

## Expected observations

Compare grid/block dimensions, active lanes, memory sectors and Duration. Propose block-shape changes one at a time; do not select a winner from occupancy alone.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): AddMatrix2D. See the [handout](../ncu-profiling/lesson-21-matrix-add-2d.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
