# Lesson 49 — Streams Events and Dependencies

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 6; section 6.1.
Printed section start: 268. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

A stream orders its own operations; independent streams permit concurrency but never guarantee it. Completion events establish ownership without requiring source timers.

## Current focused code

- `src/streamchunks.cu`
- `src/streamchunks.cpp`
- `src/main.cpp`

Kernel(s): StreamChunksKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 49 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Introducing Streams and Events (p. 268) | draw command DAGs and validate buffer ownership at completion points. [H,V] |
| CUDA Streams (p. 269) | compare ordered work in one stream with independent streams; verify identical outputs. [H] |
| Stream Scheduling (p. 271) | vary issue order and record events; explain why independent work need not overlap. [H] |
| Stream Priorities (p. 273) | query priority range and compare long/short work; treat priority as a scheduling hint. [H] |
| CUDA Events (p. 273) | use timing and dependency events; distinguish elapsed GPU intervals from CPU enqueue time. [T,H] |
| Stream Synchronization (p. 275) | compare event, stream, and device waits with the same required dependency graph. [H,V] |
| False Dependencies (p. 272) | Draw queue-induced ordering and compare independent versus accidentally ordered commands. [H] |
| Hyper-Q (p. 272) | Explain historical multiple work queues; test independent submissions without inferring physical queue counts. [H] |
| Creation and Destruction (p. 273) | Use checked event ownership, complete outstanding work, and exclude setup from steady timing. [H,V] |
| Recording Events and Measuring Elapsed Time (p. 274) | Bracket work in one stream and compare with synchronized wall time. [T,H] |
| Blocking and Non-Blocking Streams (p. 276) | Compare legacy default-stream interaction with explicit nonblocking streams. [H,V] |
| Implicit Synchronization (p. 276) | Identify book-listed implicit waits and test applicable calls in controlled sequences. [H] |
| Explicit Synchronization (p. 277) | Compare event, stream, and device completion with the same dependency requirement. [H,V] |
| Configurable Events (p. 278) | Compare timing-enabled, timing-disabled, and supported host-wait flags. [H,T] |


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
[matching handout](../ncu-profiling/lesson-49-streams-events-and-dependencies.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
