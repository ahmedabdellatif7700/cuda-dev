# Lesson 39 — Bandwidth and Matrix Transpose

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 4; section 4.4.
Printed section start: 179. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

A transpose changes layout; coalescing one side can make the other side strided. Logical effective bandwidth is not measured DRAM traffic or a cache hit rate.

## Current focused code

- `src/transposematrix.cu`
- `src/transposematrix.cpp`
- `src/main.cpp`

Kernel(s): TransposeMatrixKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 39 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| What Bandwidth Can a Kernel Achieve? (p. 179) | define logical traffic separately from measured cache/DRAM bytes; compare copy and transpose. [M,T] |
| Memory Bandwidth (p. 179) | sweep size beyond cache and compute logical GB/s from events; correlate with per-level profiler traffic. [M,T] |
| Matrix Transpose Problem (p. 180) | implement copy, naive read/write-coalesced transpose, diagonal mapping, and unrolled variants; test non-square edges. [M,L] |
| Setting An Upper and Lower Performance Bound for Transpose Kernels (p. 181) | Use contiguous copy and a deliberately strided control as empirical comparison bounds, not universal guarantees. [M,T] |
| Naive Transpose: Reading Rows versus Reading Columns (p. 185) | Swap which side is coalesced; validate rectangular transpose and sector counts. [M,V] |
| Unrolling Transpose: Reading Rows versus Reading Columns (p. 187) | Repeat both mappings with equal unroll factors and tail coverage. [M,I] |
| Diagonal Transpose: Reading Rows versus Reading Columns (p. 189) | Remap block order, validate coverage, and test whether historical partition effects appear on Orin. [M,L] |
| Expose More Parallelism with Thin Blocks (p. 193) | Sweep thin block shapes at equal work; compare memory efficiency and grid waves. [L,M,O] |


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
[matching handout](../ncu-profiling/lesson-39-bandwidth-and-matrix-transpose.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
