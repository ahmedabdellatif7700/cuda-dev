# Lesson 45 — Coalesced Shared Transpose

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 5; section 5.4.
Printed section start: 239. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

A shared tile separates global read and write orientations. Padding can reduce bank conflicts but is useful only when supported by actual access geometry.

## Current focused code

- `src/paddedtranspose.cu`
- `src/paddedtranspose.cpp`
- `src/main.cpp`

Kernel(s): PaddedTransposeKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 45 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Coalescing Global Memory Accesses (p. 239) | use shared tiles to reconcile coalesced reads with coalesced writes. [M,S] |
| Baseline Transpose Kernel (p. 240) | reproduce naive transpose with a CPU reference and a copy-bandwidth control. [M,T] |
| Matrix Transpose with Shared Memory (p. 241) | transpose through a synchronized tile; predict improved global transactions and possible bank conflicts. [M,S] |
| Matrix Transpose with Padded Shared Memory (p. 245) | add one column of padding; predict fewer conflicts, with slightly larger resource usage. [S,O] |
| Matrix Transpose with Unrolling (p. 246) | process multiple tile elements per thread and check register/resource tradeoffs. [I,O,M] |
| Exposing More Parallelism (p. 249) | sweep tile/block geometry and grid coverage for fixed matrix dimensions. [L,O,T] |


## How to work through it

Representative inputs and geometry are intentionally small and explicit. The memory-space survey includes historical configurations and unsupported cache/bank modes as theory, not reproduced hardware. AoS/SoA, texture filtering and every old tuning variant are reading/experiment questions in the table; no measurement is fabricated. Managed prefetch is not called without capability checks. The transpose uses one 8-by-8 matrix; larger rectangular/tail versions are follow-up exercises, not claimed tested cases. Reduction/shuffle examples use full fixed-size participation. Read the current code contracts before changing dimensions.

The table records the book's questions/experiments, not a claim that every historical
variant was reproduced or optimized. The code is the representative implementation
specified above. Any external-hardware or missing-tool work is marked separately.
No source timers or automatic numerical comparisons are introduced. Read printed
outputs and reason about bounds/ownership; completion alone does not prove correctness.

## Build and observation

`make clean build run` and `make ptx` succeeded. Outputs were printed for visual inspection; no numerical assertion or timing was performed.

## Profiling and next step

You personally capture actual kernels in ncu-ui. The
[matching handout](../ncu-profiling/lesson-45-coalesced-shared-transpose.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
