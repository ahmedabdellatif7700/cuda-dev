# Lesson 12 — Organizing Threads

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Introducing the CUDA Programming Model |
| Subsection | Organizing Threads |
| Printed pages | 30–35 |
| Roadmap ID | 2.1.3 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Core idea

Thread coordinates are local until combined with block coordinates; multidimensional geometry is a logical indexing scheme.

**Code or evidence:** [thread_mapping.cu](../../src/thread_mapping.cu). In 1D, global = blockIdx.x * blockDim.x + threadIdx.x. For 2D local linearization, use x + blockDim.x * y.

**Original lesson commit:** `0d60fee`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Concept and code connection

ThreadIdx is local within a block; blockIdx identifies a block; blockDim and gridDim hold dimensions. dim3 defaults unused components to 1. A 2D block is linearized as local = x + blockDim.x*y; in 3D add blockDim.x*blockDim.y*z. A block index is flattened similarly using grid dimensions. The earlier thread_mapping kernel shows the 1D case. Our 2D matrix kernel extends it independently along x/y. Logical coordinates describe ownership, not physical SM placement. For block (4,2), local coordinate (3,1) has linear ID 7. A grid (2,2) of these blocks launches 32 threads.

## Expected observations

Record grid and block in all dimensions, total threads and partial participation. Do not equate local ID with SM number.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): WriteThreadIndices / AddMatrix2D. See the [handout](../ncu-profiling/lesson-12-organizing-threads.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
