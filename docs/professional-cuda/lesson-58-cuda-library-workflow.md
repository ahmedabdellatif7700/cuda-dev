# Lesson 58 — CUDA Library Workflow

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 8; section 8.1.
Printed section start: 328. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Local library call ran; comparative/user profiling pending**.

## Core idea

A library operation has a handle/plan, data layout, workspace, execution and lifetime contract. Setup and steady execution answer different performance questions.

## Current focused code

- `src/blasproduct.cpp`
- `src/main.cpp`

Kernel(s): Library-managed kernels; no custom kernel PTX.
No custom .cu file is required. make ptx has no application kernel to export; inspect actual library kernels only in your supported ncu-ui capture.
Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 58 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Introducing the CUDA Libraries (p. 328) | identify installed library versions and workloads before writing wrappers. [B] |
| Supported Domains for CUDA Libraries (p. 329) | map sparse/dense algebra, FFT, and RNG to representative tasks and data access. [B] |
| A Common Library Workflow (p. 330) | separate handle/plan setup, workspace, execution, synchronization, and cleanup. [B,V] |
| Stage 1: Creating a Library Handle (p. 331) | Create/reuse a checked handle and distinguish setup lifetime from execution. [B,T] |
| Stage 2: Allocating Device Memory (p. 331) | Allocate bounded buffers with checked ownership and cleanup. [B,V] |
| Stage 3: Converting Inputs to a Library-Supported Format (p. 331) | Validate shape, indexing, and conversion against a native-format reference. [B,V] |
| Stage 4: Populating Device Memory with Inputs (p. 331) | Copy deterministic input and record ownership/completion boundaries. [B,H] |
| Stage 5: Configuring the Library (p. 331) | Configure descriptors, algorithm, workspace, precision, and stream explicitly. [B,V] |


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
[matching handout](../ncu-profiling/lesson-58-cuda-library-workflow.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
