# Lesson 59 — Sparse Linear Algebra

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 8; section 8.2.
Printed section start: 332. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Local library call ran; comparative/user profiling pending**.

## Core idea

Sparse formats describe nonzero coordinates and row structure. Generic descriptors preserve dimensions, index base/type and values; pattern-dependent traffic governs SpMV efficiency.

## Current focused code

- `src/sparseproduct.cpp`
- `src/main.cpp`

Kernel(s): Library-managed kernels; no custom kernel PTX.
No custom .cu file is required. make ptx has no application kernel to export; inspect actual library kernels only in your supported ncu-ui capture.
Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 59 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| The CUSPARSE Library (p. 332) | compare sparse operations with a dense/CPU reference using current supported APIs. [B,M] |
| cuSPARSE Data Storage Formats (p. 333) | construct COO/CSR/CSC examples and validate indexing, duplicates, and empty rows. [B,V] |
| Formatting Conversion with cuSPARSE (p. 337) | round-trip supported formats; count conversion time and compare recovered coordinates. [B,T,V] |
| Demonstrating cuSPARSE (p. 338) | run deterministic CSR SpMV using current descriptors and a CPU reference. [B,M] |
| Important Topics in cuSPARSE Development (p. 340) | vary sparsity pattern, index width, workspace, and supported algorithm; separate conversion/setup. [B,M] |
| cuSPARSE Summary (p. 341) | explain when sparse storage pays off and record API differences from the book. [B] |
| Stage 6: Executing (p. 332) | Execute with checked status and completion; identify actual library kernels. [B,T] |
| Stage 7: Retrieving Results from Device Memory (p. 332) | Retrieve output after completion and separate transfer from compute time. [B,H] |
| Stage 8: Converting Back to Native Format (p. 332) | Convert output to the native format and verify semantics and numerical tolerance. [B,V] |
| Stage 9: Releasing CUDA Resources (p. 332) | Release handles/plans/workspaces/buffers using correct lifetime order. [B,V] |
| Stage 10: Continuing with the Application (p. 332) | Validate the full application and report setup, steady-state, and pipeline costs. [B,T,V] |
| Dense (p. 334) | Validate dense leading dimensions and zeros before sparse conversion. [B,V] |
| Coordinate (COO) (p. 334) | Construct row/column/value triples and verify indexing, duplicates, and order. [B,V] |
| Compressed Sparse Row (CSR) (p. 334) | Derive row offsets including empty rows and compare SpMV with the dense reference. [B,V] |
| cuSPARSE Storage Formats Summary (p. 336) | Compare storage bytes and supported format tradeoffs for the same matrix. [B,M] |


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
[matching handout](../ncu-profiling/lesson-59-sparse-linear-algebra.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
