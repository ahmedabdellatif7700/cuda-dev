# Lesson 29 — Execution Architecture

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 3; section 3.1.
Printed section start: 67. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

A launch describes logical work; SMs schedule blocks subject to register, shared-memory, thread and block limits. Fermi and Kepler are historical comparisons, not Orin resource specifications.

## Current focused code

- `src/scalevalues.cu`
- `src/scalevalues.cpp`
- `src/main.cpp`

Kernel(s): ScaleValuesKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 29 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Introducing the CUDA Execution Model (p. 67) | separate logical launch geometry from physical residency with a block-count sweep. [L,O] |
| GPU Architecture Overview (p. 68) | draw Orin SM, schedulers, registers, shared/L1, L2, and DRAM; map a simple kernel to each. [C,M] |
| The Fermi Architecture (p. 71) | study historical SM organization and scheduling; contrast the diagram with queried Orin limits, without claiming Fermi measurements. [H,O] |
| The Kepler Architecture (p. 73) | explain historical architectural changes and Hyper-Q; compare the model with present launch/resource observations. [H,O] |
| Profile-Driven Optimization (p. 78) | predict one bottleneck, capture a baseline, change one variable, and retain or reject it from evidence. [T,C,M] |


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
[matching handout](../ncu-profiling/lesson-29-execution-architecture.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
