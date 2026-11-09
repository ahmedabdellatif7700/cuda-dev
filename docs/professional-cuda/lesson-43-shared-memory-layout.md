# Lesson 43 — Shared Memory Layout

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 5; section 5.2.
Printed section start: 216. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Different addresses mapping to the same bank can serialize. Broadcast to one address is a different case; padding changes bank mapping at a storage/occupancy cost.

## Current focused code

- `src/bankstride.cu`
- `src/bankstride.cpp`
- `src/main.cpp`

Kernel(s): BankStrideKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 43 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Checking the Data Layout of Shared Memory (p. 216) | predict bank indices before comparing layouts. [S] |
| Square Shared Memory (p. 217) | compare row, column, broadcast, padded, and dynamic square layouts; validate permutation output. [S] |
| Rectangular Shared Memory (p. 225) | repeat bank analysis for rectangular tiles and changed block geometry. [S,L] |
| Volatile Qualifier (p. 216) | Inspect access generation while demonstrating why volatile alone cannot replace synchronization. [I,V] |
| Accessing Row-Major versus Column-Major (p. 218) | Predict bank mapping and compare row/column reads with identical deterministic outputs. [S] |
| Writing Row-Major and Reading Column-Major (p. 220) | Separate producer and consumer with a barrier; measure transpose-like bank conflicts. [S,V] |
| Dynamic Shared Memory (p. 221) | Repeat the layout experiment with launch-sized storage and verified byte counts. [S,O] |
| Padding Statically Declared Shared Memory (p. 223) | Pad compile-time shared row pitch and compare conflicts and resource use. [S,O] |
| Padding Dynamically Declared Shared Memory (p. 223) | Compute padded pitch/bytes at runtime and verify all indices and conflicts. [S,V] |
| Comparing the Performance of the Square Shared Memory Kernels (p. 225) | Compare all square variants at equal work with conflict counts and repeated timings. [S,T] |
| Accessing Row-Major versus Accessing Column-Major (p. 226) | Repeat row/column bank mapping for rectangular geometry. [S,L] |
| Writing Row-Major and Reading Column-Major (p. 227) | Separate producer and consumer with a barrier; measure transpose-like bank conflicts. [S,V] |
| Dynamically Declared Shared Memory (p. 228) | Use runtime-sized rectangular shared storage with explicit strides and validated bounds. [S,V] |
| Padding Statically Declared Shared Memory (p. 229) | Pad compile-time shared row pitch and compare conflicts and resource use. [S,O] |
| Padding Dynamically Declared Shared Memory (p. 230) | Compute padded pitch/bytes at runtime and verify all indices and conflicts. [S,V] |
| Comparing the Performance of the Rectangular Shared Memory Kernels (p. 231) | Compare all rectangular variants at equal work and launch resources. [S,L,T] |


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
[matching handout](../ncu-profiling/lesson-43-shared-memory-layout.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
