# Lesson 10 — CUDA Programming Structure

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Introducing the CUDA Programming Model |
| Subsection | CUDA Programming Structure |
| Printed pages | 25–26 |
| Roadmap ID | 2.1.1 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Concept and code connection

Read the chapter/programming-model introduction on pp. 23–25 first. CUDA exposes logical thread groups and memory spaces. Follow allocate → copy inputs → launch → copy output → release in the existing vector wrapper. A host function in a .cu file still runs on the CPU. The kernel is the __global__ function. Chapter 1 modules remain available; no duplicate kernel is needed.

## Expected observations

Distinguish host orchestration from device instructions. Capture geometry, not CPU allocation cost.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): VectorAddScalar. See the [handout](../ncu-profiling/lesson-10-cuda-programming-structure.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
