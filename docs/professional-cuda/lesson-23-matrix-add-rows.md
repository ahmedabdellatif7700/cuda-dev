# Lesson 23 — Summing Matrices with a 2D Grid and 1D Blocks

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Organizing Parallel Threads |
| Subsection | Summing Matrices with a 2D Grid and 1D Blocks |
| Printed pages | 58–59 |
| Roadmap ID | 2.3.4 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Concept and code connection

Map blockIdx.y directly to one matrix row and use 1D threads across columns. Grid = (ceil(width/threads),height). For width 7, height 3, threads 4: grid (2,3), 6 blocks and 24 launched threads. Each row has one extra thread. This preserves explicit rows while keeping blocks 1D. Compare with the 32 threads in the 2D-block variant and 24 in the flat variant; same work does not imply identical inactive-thread patterns.

## Expected observations

Inspect block count, work per row and transaction patterns. Keep datatype and outputs fixed when comparing variants.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): AddMatrixRows. See the [handout](../ncu-profiling/lesson-23-matrix-add-rows.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
