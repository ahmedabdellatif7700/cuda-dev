# Lesson 48 — Chapter 5 Review

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 5; section 5.7.
Printed section start: 264. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Choose shared memory, constant broadcast or shuffle communication according to actual reuse, scope and synchronization requirements.

## Current focused code

- `src/shufflereduce.cu`
- `src/shufflereduce.cpp`
- `src/main.cpp`

Kernel(s): ShuffleReduceKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 48 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Summary (p. 264) | justify shared/constant/shuffle choices from evidence and finish all chapter exercises. [S,M,V] |


## How to work through it

Representative inputs and geometry are intentionally small and explicit. The memory-space survey includes historical configurations and unsupported cache/bank modes as theory, not reproduced hardware. AoS/SoA, texture filtering and every old tuning variant are reading/experiment questions in the table; no measurement is fabricated. Managed prefetch is not called without capability checks. The transpose uses one 8-by-8 matrix; larger rectangular/tail versions are follow-up exercises, not claimed tested cases. Reduction/shuffle examples use full fixed-size participation. Read the current code contracts before changing dimensions.

The table records the book's questions/experiments, not a claim that every historical
variant was reproduced or optimized. The code is the representative implementation
specified above. Any external-hardware or missing-tool work is marked separately.
No source timers or automatic numerical comparisons are introduced. Read printed
outputs and reason about bounds/ownership; completion alone does not prove correctness.

## Build and observation

`make clean build run` and `make ptx` succeeded. Outputs were printed for visual inspection; no numerical assertion or timing was performed.

## Profiling and next step

You personally capture actual kernels in ncu-ui. The
[matching handout](../ncu-profiling/lesson-48-chapter-5-review.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
