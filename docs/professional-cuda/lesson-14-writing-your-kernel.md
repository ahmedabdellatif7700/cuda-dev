# Lesson 14 — Writing Your Kernel

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Introducing the CUDA Programming Model |
| Subsection | Writing Your Kernel |
| Printed pages | 37–38 |
| Roadmap ID | 2.1.5 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Concept and code connection

Write one thread’s operation and derive its global index. The scalar vector kernel assigns one output to one thread. The retained cyclic kernel loops with a grid stride. Each valid output must have a unique owner; avoid cross-thread writes to the same result. The current matrix kernels extend the same pattern with row-major index = row*width+column. Bounds tests belong before reads/writes, including the second element in pair variants.

## Expected observations

Read relevant PTX loads, add, store beside the statement. PTX virtual-register counts are not physical resource use.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): VectorAddScalar / VectorAddCyclic. See the [handout](../ncu-profiling/lesson-14-writing-your-kernel.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
