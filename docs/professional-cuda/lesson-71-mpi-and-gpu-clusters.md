# Lesson 71 — MPI and GPU Clusters

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 9; section 9.5.
Printed section start: 409. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Local control/capability evidence; genuine multi-GPU/cluster execution unavailable**.

## Core idea

MPI ranks exchange messages; host staging, CUDA-aware device pointers, and GPUDirect RDMA require different transport capabilities and completion contracts.

## Current focused code

- `src/main.cpp`

Kernel(s): No GPU kernel; host MPI message semantics only.
A normal make run starts one rank and reports the limitation. A two-rank local payload check is not network, CUDA-aware MPI, GPU-direct, or cluster scaling evidence.
Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 71 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Scaling Applications across GPU Clusters (p. 409) | study ranks, transport, latency/bandwidth, and strong/weak scaling. [X,H] |
| CPU-to-CPU Data Transfer (p. 410) | plan MPI ping-pong and validate message payloads; local ranks teach semantics but do not measure network performance. [X,H,V] |
| GPU-to-GPU Data Transfer Using Traditional MPI (p. 413) | design device→host→MPI→host→device staging and synchronized ownership. [X,H] |
| GPU-to-GPU Data Transfer with CUDA-aware MPI (p. 416) | verify MPI GPU-buffer support before passing device pointers; compare with staged exchange on a cluster. [X,H,V] |
| Intra-Node GPU-to-GPU Data Transfer with CUDA-Aware MPI (p. 417) | relate rank/device binding to peer topology; preserve a genuine multi-GPU experiment as pending. [X,H] |
| Adjusting Message Chunk Size (p. 418) | sweep payload/chunk sizes in local controls and later network runs; distinguish latency amortization from bandwidth. [X,H,T] |
| GPU to GPU Data Transfer with GPUDirect RDMA (p. 419) | identify supported NIC, driver, topology, MPI, and registration requirements; no RDMA claim from local simulation. [X,H] |
| Implementing Inter-Node MPI Communication (p. 411) | Plan a checked ping-pong; local ranks validate semantics while inter-node timing remains pending. [X,H,V] |
| CPU Affinity (p. 412) | Inspect CPU binding and compare dispatch/communication timing under explicit supported binding. [X,H] |
| Affinity in MPI-CUDA Programs (p. 413) | Define rank↔CPU↔GPU binding; inspect topology on the eventual multi-device system. [X,H] |
| Performing GPU-to-GPU Communication With MPI (p. 415) | Verify staged buffer completion and payload integrity before comparing GPU-aware transport. [X,H,V] |


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
[matching handout](../ncu-profiling/lesson-71-mpi-and-gpu-clusters.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
