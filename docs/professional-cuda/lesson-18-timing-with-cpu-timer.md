# Lesson 18 — Timing with CPU Timer

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Timing Your Kernel |
| Subsection | Timing with CPU Timer |
| Printed pages | 43–46 |
| Roadmap ID | 2.2.1 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Concept and code connection

Read the timing introduction on p. 43 first. A CPU timer around only a launch often measures enqueue work, not GPU completion. A synchronized interval can measure completed work; including allocations/copies answers a different pipeline question. Events provide stream-ordered GPU intervals. We cover these definitions without adding timers, as requested. Kernel time from your ncu-ui capture is not total application latency; printed stage labels are not timestamps.

## Expected observations

Observe Duration and repeated-capture variation under comparable clocks. CPU latency and CUDA-event timing remain unmeasured, not silently inferred.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): Any selected kernel. See the [handout](../ncu-profiling/lesson-18-timing-with-cpu-timer.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
