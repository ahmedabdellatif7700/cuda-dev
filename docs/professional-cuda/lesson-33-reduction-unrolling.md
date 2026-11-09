# Lesson 33 — Reduction Unrolling

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 3; section 3.5.
Printed section start: 114. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Unrolling trades loop control for code size and live state. Safe block synchronization is retained; old volatile warp-synchronous code is not a modern correctness recipe.

## Current focused code

- `src/unrolledreduce.cu`
- `src/unrolledreduce.cpp`
- `src/main.cpp`

Kernel(s): UnrolledReduceKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 33 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Unrolling Loops (p. 114) | separate reduced loop overhead from added work/thread and register pressure. [I,O] |
| Reducing with Unrolling (p. 115) | aggregate 2/4/8 inputs per thread with tail checks; compare bandwidth and instructions. [M,I] |
| Reducing with Unrolled Warps (p. 117) | translate historical volatile warp-synchronous code into explicit safe synchronization; test partial participating warps. [V,I] |
| Reducing with Complete Unrolling (p. 119) | specialize legal block sizes and compare generated instructions against looped reduction. [I,O] |
| Reducing with Template Functions (p. 120) | instantiate block-size templates and verify launch/compile-time contracts. [I,L] |


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
[matching handout](../ncu-profiling/lesson-33-reduction-unrolling.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
