# Lesson 32 — Reduction and Divergence

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 3; section 3.4.
Printed section start: 104. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

A reduction combines independent inputs through dependent stages. Neighbor and interleaved active-lane patterns can do the same sum with different control activity; barriers must be reached by every block thread.

## Current focused code

- `src/neighborreduce.cu`
- `src/neighborreduce.cpp`
- `src/main.cpp`
- `src/interleavedreduce.cu`
- `src/interleavedreduce.cpp`

Kernel(s): NeighborReduceKernel, InterleavedReduceKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 32 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Avoiding Branch Divergence (p. 104) | keep a reduction baseline while changing the active-lane pattern. [D] |
| The Parallel Reduction Problem (p. 104) | define sum identity, partial blocks, and multistage completion; validate against a wide CPU accumulator. [V,L] |
| Divergence in Parallel Reduction (p. 106) | implement neighbor-pair reduction with legal synchronization and padded identities. [D,W] |
| Improving Divergence in Parallel Reduction (p. 110) | reorganize active lanes contiguously; compare branch activity at equal size. [D,I] |
| Reducing with Interleaved Pairs (p. 112) | compare the book’s interleaved-pair formulation with neighbor pairs; verify indexing and instruction cost. [D,I] |


## How to work through it

Inputs are 1.0f; reductions print 256. The branch exercise has two numerical paths, so it does not isolate divergence cost from arithmetic effects. Modify only the predicate (lane versus warp grouping) for an equal-work comparison after discussion.

For Fermi/Kepler and nested profiling, retain historical/capability limits. Modern CDP reference: [NVIDIA](https://docs.nvidia.com/cuda/cuda-programming-guide/04-special-topics/dynamic-parallelism.html).

The table records the book's questions/experiments, not a claim that every historical
variant was reproduced or optimized. The code is the representative implementation
specified above. Any external-hardware or missing-tool work is marked separately.
No source timers or automatic numerical comparisons are introduced. Read printed
outputs and reason about bounds/ownership; completion alone does not prove correctness.

## Build and observation

`make clean build run` and `make ptx` succeeded on the local Orin. Printed output was inspected, not automatically compared. No profiling or timing was run.

## Profiling and next step

You personally capture actual kernels in ncu-ui. The
[matching handout](../ncu-profiling/lesson-32-reduction-and-divergence.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
