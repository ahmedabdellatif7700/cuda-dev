# 3. Execution, occupancy, and reduction

**Book:** Chapter 3, printed pp. 67–133. Sections/subsections are listed in the
[complete roadmap](cuda-learning-path.md). Replaces review micro-lessons 29–35.

## Core idea

Warps and resources determine execution opportunities; synchronization and ownership determine whether a reduction is valid.

## Remember these concepts

| Concept | What you need to explain |
|---|---|
| Architecture generations | Read Fermi/Kepler as historical context. Query Orin rather than borrowing another architecture’s resource table. |
| Warps and branches | Warps contain 32 lanes. Mixed paths may serialize or predicate; inspect actual instructions and useful lane activity. |
| Resources and latency | Registers/shared bytes limit resident work. Eligible warps and dependencies explain issue opportunity; occupancy alone does not. |
| Reduction | Neighbor/interleaved pair patterns combine inputs through dependent steps. Block barriers must be reached by every thread. |
| Unrolling | Loop overhead can fall while code size/register pressure rise. Old volatile warp-synchronous code requires a modern synchronization review. |
| Dynamic parallelism | Children launch from the device. Consume child results only under supported completion/continuation rules; no removed device-side wait recipe. |

## Pattern to recognize

```cpp
for (int stride = 128; stride > 0; stride /= 2) {
    if (lane < stride) values[lane] += values[lane + stride];
    __syncthreads();
}
```

This is a review pattern, not a complete standalone program. Refer to the focused
source snapshot for declarations, bounds, allocation and completion details.

## One experiment to revisit

Compare the neighbor/interleaved block reductions of 256 ones. Use branch patterns and a bounded nested reduction as focused follow-ups; full grid reduction and performance sweeps remain separate extensions.

Start with that example; revisit historical variants only when they answer a
specific question. Your ncu-ui captures and numerical/performance comparisons
remain separate from theory or successful build evidence.

## Review questions

1. What differs between theoretical occupancy and eligible warps?
2. Why is a barrier inside a lane-dependent branch dangerous?
3. What does unrolling cost as well as save?

## Code snapshots

| Focused code snapshot | Commit |
|---|---|
| execution architecture | `44603b2` |
| warp execution and resources | `db0a586` |
| exposing parallelism | `8529a73` |
| reduction and divergence | `aa87fb6` |
| reduction unrolling | `aa24c98` |
| dynamic parallelism | `f7e1af0` |
| chapter 3 review | `bc55848` |


Find a prior implementation with `git show <commit>:src/main.cpp`, or use a clean
worktree at that commit. Keep only current-lesson code in the main working tree;
we are not rewriting the existing history to renumber it.

## Profiling

Use the [chapter checklist](../ncu-profiling/chapter-03-execution-and-reduction.md). The
[coverage/open-work record](remaining-chapters-coverage.md) retains detailed
headings and explicit unfinished work. No performance ranking is implied here.
