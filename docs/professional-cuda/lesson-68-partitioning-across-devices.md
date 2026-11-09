# Lesson 68 — Partitioning Across Devices

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 9; section 9.2.
Printed section start: 393. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Local control/capability evidence; genuine multi-GPU/cluster execution unavailable**.

## Core idea

Divide useful work and retain exact ownership/offsets before adding hardware communication. Local partition correctness is a control, not proof of multi-GPU scaling.

## Current focused code

- `src/partitionedscale.cu`
- `src/partitionedscale.cpp`
- `src/main.cpp`

Kernel(s): PartitionedScaleKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 68 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Subdividing Computation across Multiple GPUs (p. 393) | partition vector work with an uneven remainder and compare to a whole-array reference. [X,V] |
| Allocating Memory on Multiple Devices (p. 393) | plan allocation ownership and cleanup per device; validate local ownership tracking. [X,V] |
| Distributing Work from a Single Host Thread (p. 394) | describe device-switch dispatch order and exercise the one-device path. [X,H] |
| Compiling and Executing (p. 395) | keep the Make entry point and validate device count before multi-GPU launch; genuine scaling remains pending. [X,V] |


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
[matching handout](../ncu-profiling/lesson-68-partitioning-across-devices.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
