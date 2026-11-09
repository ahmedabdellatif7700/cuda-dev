# Lesson 36 — CUDA Memory Spaces

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 4; section 4.1.
Printed section start: 136. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Address spaces describe visibility, lifetime and access rules; physical backing and caching are separate questions. Registers/local/shared/constant/texture/global storage cannot be inferred from a variable name.

## Current focused code

- `src/copyglobal.cu`
- `src/copyglobal.cpp`
- `src/main.cpp`

Kernel(s): CopyGlobalKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 36 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Introducing the CUDA Memory Model (p. 136) | map every memory space to scope, lifetime, and hardware; compare streaming and reuse kernels. [M] |
| Benefits of a Memory Hierarchy (p. 136) | sweep working set and reuse count; predict transitions in cache hit behavior. [M] |
| CUDA Memory Model (p. 137) | run the detailed memory-space sublessons listed below, including register, local, texture, and global storage. [M,O] |
| Registers (p. 138) | Vary live accumulator count; compare register allocation, occupancy, and SASS. [O,I] |
| Local Memory (p. 139) | Use runtime-indexed per-thread arrays; inspect local loads/stores and possible spilling without assuming all local storage is a spill. [M,I,O] |
| Shared Memory (p. 139) | Exchange deterministic values within a block and validate scope/lifetime and a convergent barrier. [S,V] |
| Constant Memory (p. 140) | Compare a uniform coefficient address with per-lane coefficient addresses. [I,M] |
| Texture Memory (p. 141) | Use a supported texture object for 2D reads, addressing, and filtering; compare an ordinary global-read control. [M,I,V] |
| Global Memory (p. 141) | Compare allocated buffers and global symbols; explain lifetime, visibility, and race-free writes. [M,V] |
| GPU Caches (p. 142) | Sweep working set/reuse to distinguish L1, L2, and DRAM evidence. [M] |
| CUDA Variable Declaration Summary (p. 142) | Build a scope/lifetime/storage table and validate one representative access per declaration. [V,I] |
| Static Global Memory (p. 143) | Upload/read back a device symbol and compare with explicit allocation. [H,V] |


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
[matching handout](../ncu-profiling/lesson-36-cuda-memory-spaces.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
