# Lesson 42 — Introducing Shared Memory

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 5; section 5.1.
Printed section start: 204. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Shared memory is per-block on-chip storage with explicit cooperation and barriers. It saves global traffic only when there is useful reuse or communication.

## Current focused code

- `src/sharedexchange.cu`
- `src/sharedexchange.cpp`
- `src/main.cpp`

Kernel(s): SharedExchangeKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 42 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Introducing CUDA Shared Memory (p. 204) | establish shared-memory scope, lifetime, and tradeoffs with L1 capacity and occupancy. [S,O] |
| Shared Memory (p. 204) | compare cooperative reuse with repeated global reads; count traffic saved versus barrier cost. [S,M,W] |
| Shared Memory Allocation (p. 206) | compare static and dynamic allocations at equal size; validate per-block independence and limits. [S,O] |
| Shared Memory Banks and Access Mode (p. 206) | sweep bank strides, broadcasts, and data widths; explain historical modes versus current hardware. [S] |
| Configuring the Amount of Shared Memory (p. 212) | query supported carveout/opt-in limits and compare legal settings; treat preferences as hints. [S,O] |
| Synchronization (p. 214) | produce/consume shared tiles with convergent block barriers; verify with racecheck and synccheck. [V,W] |
| Memory Banks (p. 206) | Derive bank indices for each lane and compare unit-stride versus bank-stride access. [S] |
| Bank Conflict (p. 207) | Compare distinct addresses in one bank with a same-address broadcast. [S] |
| Access Mode (p. 208) | Compare supported data widths and explain historical 4/8-byte bank modes without requiring a removed setting. [S,I] |
| Memory Padding (p. 211) | Add one element to the row stride and measure conflict changes. [S] |
| Access Mode Configuration (p. 212) | Query/support-check historical configuration behavior; compare only legal current settings. [S,H] |
| Weakly-Ordered Memory Model (p. 214) | Draw producer/consumer ordering and validate a correctly synchronized exchange. [V] |
| Explicit Barrier (p. 214) | Use a convergent block barrier and run synccheck on a separate bounded misuse example. [V,W] |
| Memory Fence (p. 215) | Distinguish ordering from rendezvous; validate a publication protocol with proper atomics/synchronization. [V,I] |


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
[matching handout](../ncu-profiling/lesson-42-introducing-shared-memory.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
