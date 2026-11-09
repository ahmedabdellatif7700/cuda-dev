# Lesson 65 — OpenACC Directives and Interoperability

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 8; section 8.8.
Printed section start: 365. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Theory and preserved directive source; OpenACC GPU execution pending**.

## Core idea

Compiler directives express parallelism and data lifetimes; actual GPU offload requires a compatible enabled toolchain. Host fallback is not evidence of accelerator execution.

## Current focused code

- `src/main.cpp`

Kernel(s): No GPU execution claimed for unavailable OpenACC offload compiler.
reference/openacc_vector.cpp preserves a simple directive experiment outside the application source glob. Compile with a compatible GPU-offload compiler; the normal main reports availability only.
Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 65 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Using OpenACC (p. 365) | study compiler-directed parallelism; build a capability-gated directive version beside an equivalent CUDA control. [X,B] |
| Using OpenACC Compute Directives (p. 367) | cover parallel/kernels/loop, gang/worker/vector, private/reduction, and dependency correctness; compare generated work to explicit CUDA. [X,L,V] |
| Using OpenACC Data Directives (p. 375) | cover data regions, copy/copyin/copyout/create/present and update/lifetime; compare transfer counts and residency. [X,H] |
| The OpenACC Runtime API (p. 380) | inspect devices, initialization, async/wait, and supported data-management calls; verify equal output. [X,H,V] |
| Combining OpenACC and the CUDA Libraries (p. 382) | pass device pointers with supported interoperability and align stream ownership; compare explicit CUDA/library control. [X,B,V] |
| Summary of OpenACC (p. 384) | explain control/productivity tradeoffs and record compiler/platform prerequisites. [X,B] |
| Using the kernels Directive (p. 367) | Study compiler-discovered parallelism and validate a tool-gated kernels region against CUDA. [X,L,V] |
| Using the parallel Directive (p. 370) | Express known independence explicitly and compare the tool-gated result with the reference. [X,L,V] |
| Using the loop Directive (p. 372) | Test gang/worker/vector mapping, private data, and reduction semantics with a compatible compiler. [X,L,V] |
| OpenACC Compute Directives Summary (p. 375) | Explain each compute directive’s responsibility and verify the same numerical task. [X,V] |
| Using the data Directive (p. 375) | Keep arrays resident across multiple regions and compare setup/transfer counts. [X,H] |
| Adding Data Clauses to kernels and parallel Directives (p. 379) | Compare scoped clauses with persistent data regions and validate updates/lifetimes. [X,H,V] |


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
[matching handout](../ncu-profiling/lesson-65-openacc-directives-and-interoperability.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
