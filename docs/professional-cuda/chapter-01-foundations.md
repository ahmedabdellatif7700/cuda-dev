# 1. CPU/GPU foundations

**Book:** Chapter 1, printed pp. 1–22. Sections/subsections are listed in the
[complete roadmap](cuda-learning-path.md). Replaces review micro-lessons 1–9.

## Core idea

Independent data work can run in parallel; CPU and GPU cooperate through an explicit data and completion contract.

## Remember these concepts

| Concept | What you need to explain |
|---|---|
| Sequential vs parallel | Dependencies determine which operations may overlap. More threads do not remove a dependency. |
| Task vs data parallelism | Different functions can be independent tasks; vector addition applies one function to many independent elements. |
| Thread ownership | global = blockIdx.x * blockDim.x + threadIdx.x. Blocks/threads are logical IDs, not physical core or SM IDs. |
| Architecture vocabulary | SISD/SIMD/MISD/MIMD classify instruction/data streams. CUDA uses SIMT warps; multicore CPUs may also use SIMD. |
| Heterogeneous execution | CPU prepares/submits/consumes; GPU performs device computation. Orin shares physical DRAM, but our allocations remain distinct. |
| CUDA platform and first kernel | Runtime, driver, compiler and libraries serve different roles. Kernel launch is not completion; buffered device printf needs an appropriate wait. |
| Locality and tools | Adjacent accesses give spatial locality; repeated use gives temporal locality. Read relevant PTX beside source before discussing final SASS. |

## Pattern to recognize

```cpp
global_index = block_index * threads_per_block + thread_index;
output[global_index] = a[global_index] + b[global_index];
```

This is a review pattern, not a complete standalone program. Refer to the focused
source snapshot for declarations, bounds, allocation and completion details.

## One experiment to revisit

Use vector addition plus thread mapping; optionally the ten-thread greeting that prints only thread 5. Trace A[37]=37, B[37]=10, output[37]=47. A separate CPU sum consumes returned data.

Start with that example; revisit historical variants only when they answer a
specific question. Your ncu-ui captures and numerical/performance comparisons
remain separate from theory or successful build evidence.

## Review questions

1. Why can additions run independently?
2. Why does printed index order not reveal GPU scheduling?
3. What must complete before the CPU reads output?

## Code snapshots

| Focused code snapshot | Commit |
|---|---|
| scalar vector addition | `089a885` |
| cyclic vector addition | `ce01ba4` |
| thread mapping | `a2d5aa2` |
| heterogeneous architecture | `870a331` |
| paradigm of heterogeneous computing | `b0df87b` |
| CUDA platform and compilation model | `1e8f7c0` |
| GPU greeting and explicit completion | `3ded1e6` |
| locality, hierarchies, and development tools | `3b2a2e0` |
| preserve exercises and chapter completion record | `72f503e` |


Find a prior implementation with `git show <commit>:src/main.cpp`, or use a clean
worktree at that commit. Keep only current-lesson code in the main working tree;
we are not rewriting the existing history to renumber it.

## Profiling

Use the [chapter checklist](../ncu-profiling/chapter-01-foundations.md). The
[coverage/open-work record](remaining-chapters-coverage.md) retains detailed
headings and explicit unfinished work. No performance ranking is implied here.
