# Lesson 34 — Dynamic Parallelism

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 3; section 3.6.
Printed section start: 122. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

GPU threads can launch children. Child output is consumed only by the host after nested completion; a parent must not read an unfinished child result or call the removed device-side synchronization pattern.

## Current focused code

- `src/nestedreduce.cu`
- `src/nestedreduce.cpp`
- `src/main.cpp`
- `src/child_sum.cu`

Kernel(s): NestedReduceKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 34 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Dynamic Parallelism (p. 122) | compare device-launched work with host launches; check installed runtime and profiler support first. [X,T] |
| Nested Execution (p. 123) | draw parent/child ordering and visibility; use current CDP semantics and a continuation instead of old device synchronization. [X,V] |
| Nested Hello World on the GPU (p. 124) | bound recursion and launches; validate parent/child records rather than printf order. [X,L] |
| Nested Reduction (p. 128) | compare a modern supported child/continuation reduction with host multistage reduction; avoid parent reads of unfinished child output. [X,T] |


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
[matching handout](../ncu-profiling/lesson-34-dynamic-parallelism.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
