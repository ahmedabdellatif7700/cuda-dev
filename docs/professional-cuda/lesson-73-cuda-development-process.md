# Lesson 73 — CUDA Development Process

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 10; section 10.1.
Printed section start: 426. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Representative local code ran; full case-study and diagnostic/performance comparisons remain open**.

## Core idea

Assess, parallelize, optimize and deploy using explicit workload and correctness contracts. Compilation, separate linking and error boundaries are part of the implementation, not measured speedups.

## Current focused code

- `src/transformvalues.cu`
- `src/transformvalues.cpp`
- `src/main.cpp`

Kernel(s): TransformValuesKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 73 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| The CUDA C Development Process (p. 426) | connect each development stage to evidence and a measurable acceptance criterion. [V,T] |
| APOD Development Cycle (p. 426) | assess, parallelize, optimize, deploy a bounded workload with one saved baseline per stage. [V,T] |
| Optimization Opportunities (p. 429) | apply Amdahl’s law, arithmetic intensity, data residency, and launch overhead to select the next change. [C,M,T] |
| CUDA Code Compilation (p. 432) | trace preprocessing, PTX/SASS, fatbinary, separate compilation, device linking, and architecture selection using make asm. [I,L] |
| CUDA Error Handling (p. 437) | use checked runtime/library calls, launch checks, completion checks, and RAII; test diagnostic paths. [V] |
| Assessment (p. 427) | Identify the CPU hotspot and maximum possible application speedup before writing a kernel. [T] |
| Parallelization (p. 427) | Implement the simplest correct independent work mapping and validate it. [L,V] |
| Optimization (p. 428) | Change one measured limiting factor and retain the baseline. [T,M,I] |
| Deployment (p. 429) | Record reproducible build/run settings and check complete application behavior. [T,V] |
| Exposing Sufficient Parallelism (p. 430) | Sweep independent work and grid size with fixed algorithmic output. [L,W] |
| Optimizing Memory Access (p. 430) | Apply traffic accounting, coalescing, reuse, and data residency to a measured hotspot. [M] |
| Optimizing Instruction Execution (p. 432) | Compare final instruction mix and dependencies after one safe transformation. [I,W] |
| Separate Compilation (p. 434) | Trace existing relocatable device compilation and device link with a cross-file device function exercise. [I,V] |
| Sample Makefile (p. 434) | Map historical nvcc flags to the existing CMake-generated build; retain the repository Makefile. [H] |
| Integrating CUDA Files into a C Project (p. 436) | Explain C/C++ linkage boundaries and use a narrow host wrapper; keep main.cpp and dedicated .cu files. [V] |


## How to work through it

The crypt example is an original concise IDEA encryption adaptation using 64-bit blocks and a 128-bit key expanded into 52 words. It is not the full downloaded legacy application: decryption-key generation, file I/O, overlapping/multi-GPU/OpenMP deployment and full test-vector/error-domain validation are reading/follow-up work, not claimed complete. Do not substitute an XOR toy and call it the book algorithm. The debugger lesson runs safe synchronized code; intentional invalid accesses/races are not injected into the default. Detailed NVTX/timeline and interactive cuda-gdb sessions remain user/tool follow-ups. Retain every original body topic in the table.

The table records the book's questions/experiments, not a claim that every historical
variant was reproduced or optimized. The code is the representative implementation
specified above. Any external-hardware or missing-tool work is marked separately.
No source timers or automatic numerical comparisons are introduced. Read printed
outputs and reason about bounds/ownership; completion alone does not prove correctness.

## Build and observation

`make clean build run` and `make ptx` succeeded. Printed outputs were inspected without automatic numerical comparisons or source timers. No profiler capture or deployment to external systems was performed.

## Profiling and next step

You personally capture actual kernels in ncu-ui. The
[matching handout](../ncu-profiling/lesson-73-cuda-development-process.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
