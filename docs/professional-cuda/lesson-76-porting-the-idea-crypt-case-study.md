# Lesson 76 — Porting the IDEA Crypt Case Study

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 10; section 10.4.
Printed section start: 462. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Representative local code ran; full case-study and diagnostic/performance comparisons remain open**.

## Core idea

Remove linked-list traversal dependencies by flattening independent blocks, then port the block transform. Avoid unnecessary output uploads and separate key setup, transfer, computation and deployment questions.

## Current focused code

- `src/idea_blocks.cu`
- `src/idea_blocks.cpp`
- `src/main.cpp`

Kernel(s): EncryptIdeaBlocks.
Independent 64-bit IDEA encryption blocks with a host-expanded 128-bit key; a focused adaptation of the porting case, not the full historical file/decryption application.
Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 76 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| A Case Study in Porting C Programs to CUDA C (p. 462) | reproduce the book’s crypt case study with deterministic test vectors and a documented modern implementation. [I,V,T] |
| Assessing crypt (p. 463) | inspect the algorithm, CPU hotspots, independence, data structures, and reference outputs before porting. [T,V] |
| Parallelizing crypt (p. 464) | map independent items to GPU threads; preserve the algorithm and validate all known test vectors. [L,V] |
| Optimizing crypt (p. 465) | test memory layout, constants, instruction choices, and launch geometry individually; require unchanged results. [I,M,O] |
| Deploying Crypt (p. 472) | record target/toolchain/configuration, resource use, correctness, and kernel/end-to-end timings. [T,V] |
| Summary of Porting crypt (p. 475) | compare CPU, initial CUDA, and final CUDA versions; explain each measured change. [T,V] |
| Multi-GPU Crypt (p. 473) | Partition independent crypt items, validate a local decomposition control, and defer real multi-GPU scaling. [X,V,T] |
| Hybrid OpenMP-CUDA Crypt (p. 473) | Study data/task-parallel host/GPU splits; retain an OpenMP-gated implementation plus a local C++-thread control if needed. [X,H,V] |


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
[matching handout](../ncu-profiling/lesson-76-porting-the-idea-crypt-case-study.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
