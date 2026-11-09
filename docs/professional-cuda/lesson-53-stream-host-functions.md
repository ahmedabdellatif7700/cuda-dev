# Lesson 53 — Stream Host Functions

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 6; section 6.5.
Printed section start: 295. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

A stream-ordered host function runs after prior work. It must not issue CUDA API calls or outlive data it references.

## Current focused code

- `src/callbackchunks.cu`
- `src/callbackchunks.cpp`
- `src/main.cpp`

Kernel(s): CallbackChunksKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 53 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Stream Callbacks (p. 295) | explain the legacy callback and implement a supported host-function continuation with no CUDA API calls inside it. [H,V] |


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
[matching handout](../ncu-profiling/lesson-53-stream-host-functions.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
