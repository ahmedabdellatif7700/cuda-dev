# Lesson 69 — Peer Access and UVA

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 9; section 9.3.
Printed section start: 396. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Local control/capability evidence; genuine multi-GPU/cluster execution unavailable**.

## Core idea

Addressability, access permission, transfer capability and remote-memory cost are distinct. Query directional peer support before enabling or dereferencing peers.

## Current focused code

- `src/main.cpp`

Kernel(s): No custom kernel; real device capability query.
The single-Orin capability result is printed. No peer bandwidth or RDMA execution is simulated.
Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 69 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Peer-to-Peer Communication on Multiple GPUs (p. 396) | plan staged-copy and peer baselines with identical payload sizes. [X,H] |
| Enabling Peer-to-Peer Access (p. 396) | query directional peer support before enabling; exercise unsupported/single-device handling. [X,V] |
| Peer-to-Peer Memory Copy (p. 396) | compare explicit peer copy with host staging on a suitable system; locally validate payload and reference logic. [X,H] |
| Peer-to-Peer Memory Access with Unified Virtual Addressing (p. 398) | separate addressability from permission and locality; reserve remote-pointer throughput for real peer hardware. [X,M] |


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
[matching handout](../ncu-profiling/lesson-69-peer-access-and-uva.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
