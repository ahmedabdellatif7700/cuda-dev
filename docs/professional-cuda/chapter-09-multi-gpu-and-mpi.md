# 9. Multi-GPU ownership and MPI

**Book:** Chapter 9, printed pp. 387–424. Sections/subsections are listed in the
[complete roadmap](cuda-learning-path.md). Replaces review micro-lessons 67–72.

## Core idea

Partitioning, communication permissions, and transport completion are separate contracts; local simulation cannot validate remote hardware.

## Remember these concepts

| Concept | What you need to explain |
|---|---|
| Device ownership | Select a device before allocation/launch and keep per-device buffers/streams/lifetimes explicit. |
| Partitioning | Split useful work with correct offsets/remainders; local subdomains are a control, not multi-GPU scaling evidence. |
| Peers and UVA | Addressability, permission, copy support and remote access cost differ. Query directional peer capability first. |
| Stencil halos | Boundary exchange must complete before dependent cells/steps read it. Interior work may be independent. |
| MPI transport | Host-staged, CUDA-aware and GPUDirect RDMA paths have different support, synchronization, NIC/topology and registration requirements. |
| Scaling and affinity | Rank/CPU/GPU binding, message chunks, strong/weak scaling and actual network topology require measurements on the target system. |

## Pattern to recognize

```cpp
// Local control:
// partition useful outputs -> compute independent interiors -> complete halos -> compute boundaries
```

This is a review pattern, not a complete standalone program. Refer to the focused
source snapshot for declarations, bounds, allocation and completion details.

## One experiment to revisit

One Orin was queried; true P2P/multi-GPU/RDMA was unavailable. Local partitioned scaling and a single wave step ran. MPI demonstrated host-message semantics only; no CUDA-aware/network scaling result is claimed.

Start with that example; revisit historical variants only when they answer a
specific question. Your ncu-ui captures and numerical/performance comparisons
remain separate from theory or successful build evidence.

## Review questions

1. Why does UVA not grant peer permission?
2. Which stencil cells can run before halo arrival?
3. What extra evidence proves RDMA rather than host staging?

## Code snapshots

| Focused code snapshot | Commit |
|---|---|
| moving to multiple gpus | `5dec539` |
| partitioning across devices | `d550b35` |
| peer access and uva | `810f021` |
| wave equation and halo exchange | `6435674` |
| mpi and gpu clusters | `feb3b79` |
| chapter 9 review | `f8f1b2f` |


Find a prior implementation with `git show <commit>:src/main.cpp`, or use a clean
worktree at that commit. Keep only current-lesson code in the main working tree;
we are not rewriting the existing history to renumber it.

## Profiling

Use the [chapter checklist](../ncu-profiling/chapter-09-multi-gpu-and-mpi.md). The
[coverage/open-work record](remaining-chapters-coverage.md) retains detailed
headings and explicit unfinished work. No performance ranking is implied here.
