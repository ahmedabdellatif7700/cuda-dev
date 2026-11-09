# Lesson 62 — Random Number Generation

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 8; section 8.5.
Printed section start: 349. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Local library call ran; comparative/user profiling pending**.

## Core idea

Seeds, subsequences, distribution choice and state ownership define reproducible sampling. A deterministic seed is not proof of distribution quality or independent streams.

## Current focused code

- `src/randomuniform.cpp`
- `src/main.cpp`

Kernel(s): Library-managed kernels; no custom kernel PTX.
No custom .cu file is required. make ptx has no application kernel to export; inspect actual library kernels only in your supported ncu-ui capture.
Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 62 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| The cuRAND Library (p. 349) | compare host and device generation with reproducible seeds and stream ordering. [B] |
| Choosing Pseudo- or Quasi- Random Numbers (p. 349) | compare pseudo sequences and Sobol sampling on integration error versus sample count. [B,V] |
| Overview of the cuRAND Library (p. 350) | define generator/state/seed/subsequence ownership and verify deterministic replay. [B,V] |
| Demonstrating cuRAND (p. 354) | generate uniform/normal samples and estimate pi or an integral with confidence bounds. [B,C] |
| Important Topics in cuRAND Development (p. 357) | compare state initialization cost, state reuse, independent subsequences, and distribution statistics. [B,O,V] |
| Covering the Concepts (p. 351) | Explain RNG seed, sequence, offset, distributions, and state ownership with reproducibility checks. [B,V] |
| Comparing the Host and Device APIs (p. 353) | Compare equal distributions and include state setup/generation costs separately. [B,T] |
| Replacing rand() (p. 354) | Replace a CPU sampling loop with a seeded generator; validate statistics rather than identical CPU sequences. [B,V] |
| Generating Randomness for CUDA Kernels (p. 357) | Generate within a Monte Carlo kernel using disjoint state/subsequences and reusable state. [B,O,V] |


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
[matching handout](../ncu-profiling/lesson-62-random-number-generation.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
