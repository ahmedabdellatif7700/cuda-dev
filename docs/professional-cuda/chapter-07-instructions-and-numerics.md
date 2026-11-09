# 7. Instructions, numerical behavior, and atomics

**Book:** Chapter 7, printed pp. 299–325. Sections/subsections are listed in the
[complete roadmap](cuda-learning-path.md). Replaces review micro-lessons 55–57.

## Core idea

A valid optimization meets numerical and ordering requirements before instruction count or utilization becomes useful evidence.

## Remember these concepts

| Concept | What you need to explain |
|---|---|
| Floating point | Precision, rounding and FMA contraction can change answers. Define a domain and error budget before changing math. |
| Standard vs intrinsic | Standard math, intrinsics and fast-math flags can select different approximations/instructions. |
| Precision throughput | Single/double hardware rates differ; equal algorithms and explicit precision are required for fair comparisons. |
| Atomics | Atomic updates protect a particular operation, not arbitrary surrounding data. Scope/order and floating addition order still matter. |
| Contention | Same-address updates serialize differently from distributed updates; warp/block aggregation trades resources for fewer global atomics. |

## Pattern to recognize

```cpp
atomicAdd(output, input[index]);
// Output must be initialized, and all writers must use the intended protocol.
```

This is a review pattern, not a complete standalone program. Refer to the focused
source snapshot for declarations, bounds, allocation and completion details.

## One experiment to revisit

Compare standard and intrinsic sine snapshots; inspect the initialized atomic sum of 1024 ones. Accuracy-domain, FP64 and contention sweeps remain open until explicitly measured.

Start with that example; revisit historical variants only when they answer a
specific question. Your ncu-ui captures and numerical/performance comparisons
remain separate from theory or successful build evidence.

## Review questions

1. How can FMA improve one answer and change another?
2. Why is a deterministic seed/input insufficient for numerical validation?
3. What reduces global atomic pressure?

## Code snapshots

| Focused code snapshot | Commit |
|---|---|
| cuda instruction primitives | `90cda0b` |
| tuning math and atomics | `5c6bfcf` |
| chapter 7 review | `8014e3f` |


Find a prior implementation with `git show <commit>:src/main.cpp`, or use a clean
worktree at that commit. Keep only current-lesson code in the main working tree;
we are not rewriting the existing history to renumber it.

## Profiling

Use the [chapter checklist](../ncu-profiling/chapter-07-instructions-and-numerics.md). The
[coverage/open-work record](remaining-chapters-coverage.md) retains detailed
headings and explicit unfinished work. No performance ranking is implied here.
