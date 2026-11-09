# 5. Shared memory, constants, and shuffles

**Book:** Chapter 5, printed pp. 203–266. Sections/subsections are listed in the
[complete roadmap](cuda-learning-path.md). Replaces review micro-lessons 42–48.

## Core idea

Use explicit communication only when its reuse or layout benefit compensates for barriers, resources, and extra instructions.

## Remember these concepts

| Concept | What you need to explain |
|---|---|
| Shared allocation | Per-block shared storage may be static or dynamic; carveout/opt-in limits and occupancy are device-specific. |
| Banks and layouts | Different addresses in one bank can conflict. Same-address broadcast is different. Square/rectangular strides and padding change bank mapping. |
| Ordering | A barrier coordinates participating threads; a memory fence orders accesses. Volatile alone supplies neither safe rendezvous nor complete synchronization. |
| Reduction and transpose | Stage intermediates or tiles to reduce global traffic/reconcile access orientations. Bounds and complete stage ordering remain essential. |
| Constant memory | Uniform coefficient addresses suit broadcast; per-lane addresses can change behavior. Read-only paths are not interchangeable promises. |
| Shuffle | Register exchange needs valid source lanes, subgroup widths and participation masks. Full-warp examples do not automatically handle partial warps. |

## Pattern to recognize

```cpp
__shared__ float tile[8][9];
tile[row][column] = input[row * 8 + column];
__syncthreads();
output[row * 8 + column] = tile[column][row];
```

This is a review pattern, not a complete standalone program. Refer to the focused
source snapshot for declarations, bounds, allocation and completion details.

## One experiment to revisit

Review shared exchange, bank-stride, padded transpose, dynamic-shared reduction, constant-coefficient stencil and full-warp shuffle snapshots. The 8-by-8 tile teaches layout, not universal conflict elimination.

Start with that example; revisit historical variants only when they answer a
specific question. Your ncu-ui captures and numerical/performance comparisons
remain separate from theory or successful build evidence.

## Review questions

1. When does shared memory actually save traffic?
2. How does padding change a bank index?
3. Why is a correct shuffle mask part of the algorithm?

## Code snapshots

| Focused code snapshot | Commit |
|---|---|
| introducing shared memory | `7242677` |
| shared memory layout | `cd11149` |
| reducing global access | `f36a737` |
| coalesced shared transpose | `df09b3a` |
| constant memory stencil | `25d368d` |
| warp shuffle communication | `4463541` |
| chapter 5 review | `3f9a4ff` |


Find a prior implementation with `git show <commit>:src/main.cpp`, or use a clean
worktree at that commit. Keep only current-lesson code in the main working tree;
we are not rewriting the existing history to renumber it.

## Profiling

Use the [chapter checklist](../ncu-profiling/chapter-05-shared-memory-and-communication.md). The
[coverage/open-work record](remaining-chapters-coverage.md) retains detailed
headings and explicit unfinished work. No performance ranking is implied here.
