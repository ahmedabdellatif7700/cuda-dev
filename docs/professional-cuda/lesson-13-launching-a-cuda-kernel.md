# Lesson 13 — Launching a CUDA Kernel

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Introducing the CUDA Programming Model |
| Subsection | Launching a CUDA Kernel |
| Printed pages | 36 |
| Roadmap ID | 2.1.4 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Concept and code connection

The host syntax Kernel<<<grid, block>>>(arguments) submits device work. Launch is asynchronous with respect to the host; launch success does not establish completion. Use ceil division so partial final blocks exist, then bounds-check in the kernel. For 21 elements and 8 threads, launch 3 blocks and guard 3 extra threads. Legal block dimensions must also satisfy the total-thread limit. Tiny teaching blocks are not performance recommendations.

## Expected observations

Compare expected and captured launch geometry. Only compare performance at equal useful output count.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): VectorAddScalar / AddMatrix1D. See the [handout](../ncu-profiling/lesson-13-launching-a-cuda-kernel.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
