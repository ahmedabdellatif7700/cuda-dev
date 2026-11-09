# Lesson 50 — Concurrent Kernel Execution

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 6; section 6.2.
Printed section start: 279. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Kernels in independent nonblocking streams may overlap when resources and scheduling permit. A submission order is a dependency graph, not a measured overlap timeline.

## Current focused code

- `src/concurrentchunks.cu`
- `src/concurrentchunks.cpp`
- `src/main.cpp`

Kernel(s): ConcurrentChunksKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 50 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Concurrent Kernel Execution (p. 279) | pair resource-light kernels then resource-heavy kernels; predict resource contention. [O,H] |
| Concurrent Kernels in Non-NULL Streams (p. 279) | launch independent buffers in nonblocking streams; validate isolation and possible overlap. [H,O] |
| False Dependencies on Fermi GPUs (p. 281) | analyze the historical queue limitation, then test issue order on Orin without asserting Fermi behavior. [H] |
| Dispatching Operations with OpenMP (p. 283) | compare single-thread and multiple host dispatchers; use standard C++ threads locally if OpenMP is unavailable and retain the OpenMP tool-gated exercise. [H,T] |
| Adjusting Stream Behavior Using Environment Variables (p. 284) | compare supported connection settings in separate processes; validate runtime applicability and avoid assuming overlap. [H] |
| Concurrency-Limiting GPU Resources (p. 286) | independently raise registers, shared bytes, and blocks; predict less opportunity for co-residency. [O,H] |
| Blocking Behavior of the Default Stream (p. 287) | contrast legacy default, explicit nonblocking streams, and supported per-thread semantics. [H,V] |
| Creating Inter-Stream Dependencies (p. 288) | use record/wait events to enforce producer→consumer ordering without a global wait. [H,V] |


## How to work through it

For streams, the printed independent CPU sum is 4950 and chunk output is 2. No overlap claim is made without your timeline evidence. Default-stream, Fermi false-dependency, OpenMP dispatch and environment-variable topics are explicitly reading questions in the table; the current representative code uses four nonblocking streams and dependency-only events. For math, printed sine values cover input 1 only; error-domain/FP64 and fast-math sweeps remain numerical discussion exercises, not measured accuracy claims. Atomic input 1024 ones prints 1024. Record missing comparisons as pending.

The table records the book's questions/experiments, not a claim that every historical
variant was reproduced or optimized. The code is the representative implementation
specified above. Any external-hardware or missing-tool work is marked separately.
No source timers or automatic numerical comparisons are introduced. Read printed
outputs and reason about bounds/ownership; completion alone does not prove correctness.

## Build and observation

`make clean build run` and `make ptx` succeeded. No timers, numerical assertions, profiler collection or power-setting changes were made.

## Profiling and next step

You personally capture actual kernels in ncu-ui. The
[matching handout](../ncu-profiling/lesson-50-concurrent-kernel-execution.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
