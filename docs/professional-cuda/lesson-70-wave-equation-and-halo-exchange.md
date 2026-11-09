# Lesson 70 — Wave Equation and Halo Exchange

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 9; section 9.4.
Printed section start: 400. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Local control/capability evidence; genuine multi-GPU/cluster execution unavailable**.

## Core idea

A stencil needs neighboring subdomain data. Correct time-step buffers, boundaries and halo completion precede communication overlap or multi-device speedup.

## Current focused code

- `src/wavestep.cu`
- `src/wavestep.cpp`
- `src/main.cpp`

Kernel(s): WaveStepKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 70 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Finite Difference on Multi-GPU (p. 400) | build a deterministic local 2D wave-equation solver with explicit halo ownership. [X,M,V] |
| Stencil Calculation for 2D Wave Equation (p. 400) | validate time-stepping, boundary conditions, and CPU/GPU numerical tolerance. [M,V] |
| Typical Patterns for Multi-GPU Programs (p. 401) | model decomposition, halo exchange, synchronization, and gather with local subdomains. [X,H] |
| 2D Stencil Computation with Multiple GPUs (p. 403) | compare partitioned local subdomains with the monolithic stencil; label this a decomposition test only. [X,M,V] |
| Overlapping Computation and Communication (p. 405) | split interior/boundary work and event dependencies; multi-device overlap requires external hardware. [X,H] |
| Compiling and Executing (p. 406) | retain make clean build run and compare partitioned correctness; defer real topology/scaling results. [X,V] |


## How to work through it

Real multi-GPU, P2P copy/dereference, multi-GPU stencil, inter-node affinity/scaling, CUDA-aware transport and GPUDirect RDMA measurements are pending external hardware. A local subdomain exercise cannot substitute for them. The wave implementation is one 8-by-8 step with previous=current and fixed-zero output boundary, not a distributed time-integration benchmark. MPI uses host integers only; no device pointer is passed without verifying CUDA-aware support. No ranks are sent to external hosts.

The table records the book's questions/experiments, not a claim that every historical
variant was reproduced or optimized. The code is the representative implementation
specified above. Any external-hardware or missing-tool work is marked separately.
No source timers or automatic numerical comparisons are introduced. Read printed
outputs and reason about bounds/ownership; completion alone does not prove correctness.

## Build and observation

`make clean build run` and `make ptx` succeeded locally. Capability messages explicitly identify unavailable execution. No performance/timing/profiler claims.

## Profiling and next step

You personally capture actual kernels in ncu-ui. The
[matching handout](../ncu-profiling/lesson-70-wave-equation-and-halo-exchange.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
