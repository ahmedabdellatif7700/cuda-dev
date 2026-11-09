# Lesson 31 — Exposing Parallelism

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 3; section 3.3.
Printed section start: 98. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Independent work and adequate grids help cover latency, but larger occupancy alone is not a performance objective. Compare useful work, traffic and issue opportunity together.

## Current focused code

- `src/scalevalues.cu`
- `src/scalevalues.cpp`
- `src/main.cpp`

Kernel(s): ScaleValuesKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 31 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Exposing Parallelism (p. 98) | vary independent work and grid size while holding total output constant. [L,W] |
| Checking Active Warps with nvprof (p. 100) | translate active-warps evidence to achieved occupancy and scheduler views in ncu-ui. [O,W] |
| Checking Memory Operations with nvprof (p. 100) | translate historical memory metrics to L1/L2 sectors, bytes, and request behavior. [M] |
| Exposing More Parallelism (p. 101) | compare one-output/thread with multiple independent outputs/thread; watch registers and eligible warps. [O,W,I] |


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
[matching handout](../ncu-profiling/lesson-31-exposing-parallelism.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
