# Lesson 56 — Tuning Math and Atomics

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 7; section 7.2.
Printed section start: 306. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Intrinsics and precision choices trade accuracy/domain behavior against instruction cost. Contention changes atomic behavior; addition order can change floating-point results.

## Current focused code

- `src/intrinsicsine.cu`
- `src/intrinsicsine.cpp`
- `src/main.cpp`

Kernel(s): IntrinsicSineKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 56 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Optimizing Instructions for Your Application (p. 306) | establish correctness/accuracy constraints before instruction tuning. [I,V] |
| Single-Precision vs. Double-Precision (p. 306) | benchmark equal algorithms and report absolute/relative error against a high-precision CPU reference. [C,I,V] |
| Standard vs. Intrinsic Functions (p. 309) | compare selected math and fast-math builds including special inputs; inspect SASS and numerical changes. [I,V] |
| Understanding Atomic Instructions (p. 315) | sweep same-address, distributed, and locally aggregated updates; predict contention scaling. [A] |
| Bringing It All Together (p. 322) | optimize a validated arithmetic/atomic workload with one independent change per step. [A,I,T] |
| Summary (p. 308) | Review this primitive’s accuracy, instruction, and performance tradeoffs before the next subsection. [I,V,T] |
| Visualizing Standard and Intrinsic Functions (p. 309) | Plot or tabulate error over a defined domain and correlate with instruction differences. [I,V] |
| Manipulating Instruction Generation (p. 311) | Compare normal and narrowly scoped fast-math/intrinsic variants, including FMA and special values. [I,V] |
| Summary (p. 315) | Review this primitive’s accuracy, instruction, and performance tradeoffs before the next subsection. [I,V,T] |
| From the Ground Up (p. 315) | Contrast an intentionally raced update with an atomic and a staged reduction in isolated runs. [A,V] |
| Built-In CUDA Atomic Functions (p. 317) | Test supported add/exchange/CAS and relevant type/scope semantics against deterministic invariants. [A,V] |
| The Cost of Atomic Operations (p. 318) | Sweep contention and useful work per update; report serialization trends. [A,T] |
| Limiting the Performance Cost of Atomic Operations (p. 319) | Aggregate within warp/block before global updates; count operations and resource costs. [A,S,O] |
| Atomic Floating-Point Support (p. 320) | Query supported types, validate tolerance and nondeterministic addition order, and explain CAS fallback historically. [A,V] |
| Summary (p. 321) | Review this primitive’s accuracy, instruction, and performance tradeoffs before the next subsection. [I,V,T] |


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
[matching handout](../ncu-profiling/lesson-56-tuning-math-and-atomics.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
