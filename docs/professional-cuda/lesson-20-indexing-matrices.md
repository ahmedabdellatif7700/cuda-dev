# Lesson 20 — Indexing Matrices with Blocks and Threads

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Organizing Parallel Threads |
| Subsection | Indexing Matrices with Blocks and Threads |
| Printed pages | 49–52 |
| Roadmap ID | 2.3.1 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Core idea

Row-major storage turns a two-dimensional coordinate into a unique flat array location.

**Code or evidence:** [matrix_add_2d.cu](../../src/matrix_add_2d.cu). At width 7, row 2 and column 3 map to index 17. Row and column bounds must both be satisfied before accessing that location.

**Original lesson commit:** `f96534d`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Concept and code connection

Read the section introduction on p. 49. A matrix is logically 2D but physically a flat row-major array. Derive row = blockIdx.y*blockDim.y+threadIdx.y, column = blockIdx.x*blockDim.x+threadIdx.x, then index = row*width+column. For width 7, row 2 and column 3 map to 17; output is 17+10=27. Coordinates outside width/height must exit. A square-only test can conceal swapped dimensions; use the 7-by-3 example.

## Expected observations

Grid (2,2) and block (4,2) launch 32 threads for 21 outputs. Trace coordinates before considering throughput.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): AddMatrix2D. See the [handout](../ncu-profiling/lesson-20-indexing-matrices.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
