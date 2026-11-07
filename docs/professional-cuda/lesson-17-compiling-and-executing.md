# Lesson 17 — Compiling and Executing

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Introducing the CUDA Programming Model |
| Subsection | Compiling and Executing |
| Printed pages | 40–42 |
| Roadmap ID | 2.1.8 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Concept and code connection

Use the preserved Make → CMake → Ninja build. C++ is compiled as C++23; .cu sources use CUDA C++20 and architecture 87. The linked program contains host code and device images. make ptx generates intermediate operations; make asm also extracts final SASS. Keep Release for performance observations. With multiple functions/files, headers declare interfaces and separate device compilation/linking is already enabled. If nvcc is absent from PATH, export /usr/local/cuda-13.2/bin for the shell; do not install another toolkit automatically.

## Expected observations

Record compiler/target/revision with captures. Debug instrumentation changes instruction selection and performance.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): Current matrix kernels. See the [handout](../ncu-profiling/lesson-17-compiling-and-executing.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
