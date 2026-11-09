# 8. CUDA libraries and OpenACC

**Book:** Chapter 8, printed pp. 327–386. Sections/subsections are listed in the
[complete roadmap](cuda-learning-path.md). Replaces review micro-lessons 58–66.

## Core idea

Use supported library/data-layout contracts and compare equal numerical tasks; toolchain support determines whether directives actually offload.

## Remember these concepts

| Concept | What you need to explain |
|---|---|
| Library lifecycle | Separate handle/plan setup, descriptors, workspace, execution, completion and cleanup. |
| cuSPARSE | CSR/COO/dense formats, index bases and pattern-dependent behavior define sparse operations. Generic descriptors replace historical calls where appropriate. |
| cuBLAS | Layout, leading dimensions, transpose flags, scalars and math mode define GEMM; Tensor Core use must be observed, not assumed. |
| cuFFT | Transform shape, strides/batches, plan reuse and normalization determine the task. |
| cuRAND | Seed/subsequence/state/distribution choices govern reproducibility and sampling; printed values are not statistical validation. |
| Comparisons and historical features | MKL/FFTW, drop-in and multi-GPU claims need compatible actual backends and matching setup/precision. |
| OpenACC | Compute/data directives and runtime/interoperability express ownership and work; host fallback does not prove GPU execution. |

## Pattern to recognize

```cpp
// Library sequence:
// create handle/plan -> prepare compatible data -> execute -> wait -> retrieve -> release
```

This is a review pattern, not a complete standalone program. Refer to the focused
source snapshot for declarations, bounds, allocation and completion details.

## One experiment to revisit

Ran a 2-by-2 CSR product (2,3), identity GEMM (1,2,3,4), impulse FFT (ones), and seeded uniform RNG. OpenACC directive source was preserved in its snapshot; GPU offload remains unvalidated.

Start with that example; revisit historical variants only when they answer a
specific question. Your ncu-ui captures and numerical/performance comparisons
remain separate from theory or successful build evidence.

## Review questions

1. Which setup costs should be amortized?
2. What layout mismatch can silently change a BLAS result?
3. How would you prove an OpenACC loop ran on the GPU?

## Code snapshots

| Focused code snapshot | Commit |
|---|---|
| cuda library workflow | `7422d5f` |
| sparse linear algebra | `aa0fa3b` |
| dense linear algebra | `01b743f` |
| fourier transforms | `e8dad0d` |
| random number generation | `5869243` |
| historical cuda library features | `5055d87` |
| fair library comparisons | `9747236` |
| openacc directives and interoperability | `5a7d6ba` |
| chapter 8 review | `9a890d3` |


Find a prior implementation with `git show <commit>:src/main.cpp`, or use a clean
worktree at that commit. Keep only current-lesson code in the main working tree;
we are not rewriting the existing history to renumber it.

## Profiling

Use the [chapter checklist](../ncu-profiling/chapter-08-libraries-and-openacc.md). The
[coverage/open-work record](remaining-chapters-coverage.md) retains detailed
headings and explicit unfinished work. No performance ranking is implied here.
