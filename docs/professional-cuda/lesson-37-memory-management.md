# Lesson 37 — Memory Management

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 4; section 4.2.
Printed section start: 145. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Allocation choices change mapping, coherency and synchronization costs. UVA identifies address spaces, while managed allocation supplies an ownership/migration policy. Shared DRAM does not eliminate CUDA access rules.

## Current focused code

- `src/managedadd.cu`
- `src/managedadd.cpp`
- `src/main.cpp`

Kernel(s): ManagedAddKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 37 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Memory Management (p. 145) | compare allocation/transfer strategies with identical output and explicit synchronization. [H,T] |
| Memory Allocation and Deallocation (p. 146) | measure allocation separately from steady-state kernels; verify lifetime and zero-size handling. [H,V] |
| Memory Transfer (p. 146) | compare copy size/direction and complete pipeline costs on shared physical DRAM. [H,T] |
| Pinned Memory (p. 148) | compare pageable and pinned host buffers; record CPU caching/coherency effects and bounded allocation size. [H,T] |
| Zero-Copy Memory (p. 150) | test mapped host storage with one-pass and repeated GPU access; verify mapping support and ownership. [H,M] |
| Unified Virtual Addressing (p. 156) | inspect pointer attributes and distinguish shared address interpretation from automatic migration. [H] |
| Unified Memory (p. 157) | compare managed and explicit allocations with legal host/device access phases; query capabilities before prefetch/advice. [H,T] |


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
[matching handout](../ncu-profiling/lesson-37-memory-management.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
