# Lesson 16 — Handling Errors

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Introducing the CUDA Programming Model |
| Subsection | Handling Errors |
| Printed pages | 40 |
| Roadmap ID | 2.1.7 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Concept and code connection

Separate host API errors, launch-configuration errors, asynchronous execution faults, and numerical logic errors. Existing launch wrappers use cudaGetLastError; a completion boundary can reveal later execution faults. Simple host wrappers intentionally omit most status checks per your preference, so a zero process exit alone is weak evidence. The isolated launch_errors exercise prints the error for a zero-thread block, then successful completion of a legal launch, then an invalid device ID. It does not intentionally corrupt memory or poison the device context.

## Expected observations

Error messages and API status are the evidence here. An invalid launch may produce no kernel report. No performance conclusion follows.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): EmptyKernel in standalone exercise. See the [handout](../ncu-profiling/lesson-16-handling-errors.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
