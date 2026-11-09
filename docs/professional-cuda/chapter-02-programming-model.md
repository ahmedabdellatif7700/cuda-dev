# 2. Programming model and indexing

**Book:** Chapter 2, printed pp. 23–65. Sections/subsections are listed in the
[complete roadmap](cuda-learning-path.md). Replaces review micro-lessons 10–28.

## Core idea

Derive data ownership, legal launch geometry, bounds, memory lifetimes, and completion before tuning anything.

## Remember these concepts

| Concept | What you need to explain |
|---|---|
| Program structure | Allocate → input copies → launch → output copy → release. Sizes passed to memory APIs are bytes. |
| Thread hierarchy | Local coordinates become global coordinates through block offsets. Unused dim3 dimensions default to one. |
| Bounds and geometry | ceil(n/threads) supplies enough threads; guards protect extra threads. Per-axis limits and total threads/block are separate constraints. |
| Matrix layouts | Row-major index = row*width+column. Flat 1D, 2D tiles, and one-grid-row-per-matrix-row can compute the same output. |
| Errors vs correctness | Launch/API/completion status differs from a numerical reference comparison. Printed plausible values do not prove correctness. |
| Timing scopes | Enqueue time, completed kernel time and whole-pipeline time answer different questions. No source timers are required for this course. |
| Device management | Query actual properties, select logical devices before allocation, and record telemetry separately from kernel metrics. |

## Pattern to recognize

```cpp
column = blockIdx.x * blockDim.x + threadIdx.x;
row = blockIdx.y * blockDim.y + threadIdx.y;
index = row * width + column;
```

This is a review pattern, not a complete standalone program. Refer to the focused
source snapshot for declarations, bounds, allocation and completion details.

## One experiment to revisit

Use a 7-by-3 matrix to expose non-square edges. Compare flat 1D, 2D-block, and row-wise mappings; pair-per-thread and integer variants are optional extensions. Device queries give actual Orin limits.

Start with that example; revisit historical variants only when they answer a
specific question. Your ncu-ui captures and numerical/performance comparisons
remain separate from theory or successful build evidence.

## Review questions

1. Why do a 2D grid and a flat grid need different bounds?
2. What does a successful launch fail to establish?
3. Which timing scope would include copies?

## Code snapshots

| Focused code snapshot | Commit |
|---|---|
| cuda programming structure | `1779c4c` |
| managing memory | `84e0596` |
| organizing threads | `0d60fee` |
| launching a cuda kernel | `de13c9e` |
| writing your kernel | `960e567` |
| verifying your kernel | `f9cb9c8` |
| handling errors | `5fbcb3f` |
| compiling and executing | `ce6d1e1` |
| timing with cpu timer | `ab4621b` |
| timing with nvprof | `e5bd970` |
| indexing matrices | `f96534d` |
| matrix add 2d | `62932e7` |
| matrix add 1d | `88ef1a3` |
| matrix add rows | `d9c9df1` |
| querying device information | `83eba28` |
| determining the best gpu | `df2b629` |
| device telemetry | `9cd43f4` |
| setting devices | `af56de1` |
| chapter 02 summary | `cff1695` |


Find a prior implementation with `git show <commit>:src/main.cpp`, or use a clean
worktree at that commit. Keep only current-lesson code in the main working tree;
we are not rewriting the existing history to renumber it.

## Profiling

Use the [chapter checklist](../ncu-profiling/chapter-02-programming-model.md). The
[coverage/open-work record](remaining-chapters-coverage.md) retains detailed
headings and explicit unfinished work. No performance ranking is implied here.
