# Lesson 46 — Constant Memory Stencil

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 5; section 5.5.
Printed section start: 250. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Constant-cache broadcast suits coefficients accessed uniformly across a warp. Boundary rules and reuse of neighboring input values are separate design choices.

## Current focused code

- `src/constantstencil.cu`
- `src/constantstencil.cpp`
- `src/main.cpp`

Kernel(s): ConstantStencilKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 46 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Constant Memory (p. 250) | contrast uniform broadcast with per-lane addresses; validate uploaded coefficients. [I,M] |
| Implementing a 1D Stencil with Constant Memory (p. 250) | define halo rules, upload coefficients, and compare global versus constant coefficients. [M,I,V] |
| Comparing with the Read-Only Cache (p. 253) | compare constant, ordinary const/restrict, and supported read-only loads; vary coefficient uniformity. [M,I] |


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
[matching handout](../ncu-profiling/lesson-46-constant-memory-stencil.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
