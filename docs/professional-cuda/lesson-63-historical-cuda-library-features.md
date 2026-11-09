# Lesson 63 — Historical CUDA Library Features

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 8; section 8.6.
Printed section start: 358. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Local library call ran; comparative/user profiling pending**.

## Core idea

Drop-in and multi-GPU library features are historical/API-specific capabilities. A local single-GPU call does not validate interception, multi-device distribution or removed interfaces.

## Current focused code

- `src/blasproduct.cpp`
- `src/main.cpp`

Kernel(s): Library-managed kernels; no custom kernel PTX.
No custom .cu file is required. make ptx has no application kernel to export; inspect actual library kernels only in your supported ncu-ui capture.
Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 63 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| CUDA Library Features Introduced in CUDA 6 (p. 358) | identify historical features and current replacements; retain compatibility notes. [B] |
| Drop-In CUDA Libraries (p. 358) | analyze historical interception versus explicit supported library calls; reproduce equivalent math locally if the old facility is absent. [B,X] |
| Multi-GPU Libraries (p. 359) | analyze distribution and communication costs; run single-GPU controls locally and reserve genuine multi-device execution for suitable hardware. [X,B] |


## How to work through it

cuBLAS uses a 2-by-2 column-major matrix and identity product; cuFFT uses an eight-point complex impulse; cuRAND prints eight seeded uniform values; cuSPARSE uses a 2-by-2 CSR diagonal and ones. Only the current lesson code is present. Library kernels are not in application PTX. COO/CSR conversion, quasi-random sampling, full error-domain/statistical tests and backend comparisons are explained as reading/follow-up questions rather than claimed implemented variants. MKL comparison and genuine multi-GPU library measurements need compatible external hardware. OpenACC accelerator execution remains pending the compiler/offload toolchain; directive source is preserved but not silently treated as a GPU result.

The table records the book's questions/experiments, not a claim that every historical
variant was reproduced or optimized. The code is the representative implementation
specified above. Any external-hardware or missing-tool work is marked separately.
No source timers or automatic numerical comparisons are introduced. Read printed
outputs and reason about bounds/ownership; completion alone does not prove correctness.

## Build and observation

`make clean build run` and `make ptx` succeeded for the current application. Library results were printed; no numerical assertions or timings. For OpenACC, only the normal C++ capability message ran.

## Profiling and next step

You personally capture actual kernels in ncu-ui. The
[matching handout](../ncu-profiling/lesson-63-historical-cuda-library-features.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
