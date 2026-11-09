# Lesson 47 — Warp Shuffle Communication

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 5; section 5.6.
Printed section start: 255. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

A shuffle moves register values between participating lanes. Correct source lanes, masks and convergence are part of the algorithm, especially for partial warps.

## Current focused code

- `src/shufflereduce.cu`
- `src/shufflereduce.cpp`
- `src/main.cpp`

Kernel(s): ShuffleReduceKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 47 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| The Warp Shuffle Instruction (p. 255) | move values through registers without shared staging, with explicit participation masks. [I,V] |
| Variants of the Warp Shuffle Instruction (p. 256) | test sync, up, down, xor, width, and source-lane semantics with known lane patterns. [I,V] |
| Sharing Data within a Warp (p. 258) | compare safe shuffle and shared-memory exchange for full and partial warps. [S,I,V] |
| Parallel Reduction Using the Warp Shuffle Instruction (p. 262) | build warp then block then grid reduction; validate masks and non-power-of-two input. [I,S,O] |
| Broadcast of a Value across a Warp (p. 258) | Broadcast a known source lane with a correct participation mask. [I,V] |
| Shift Up within a Warp (p. 258) | Validate lane-wise up-shift and unchanged boundary-lane semantics. [I,V] |
| Shift Down within a Warp (p. 259) | Validate down-shift and source-lane validity, including partial warps. [I,V] |
| Shift within a warp with Wrap Around (p. 259) | Implement the stated wrap indexing explicitly and verify every lane. [I,V] |
| Butterfly Exchange across the Warp (p. 260) | Test XOR masks and subgroup widths against CPU lane permutations. [I,V] |
| Exchange Values of an Array across a Warp (p. 260) | Exchange per-lane array values via safe shuffles; compare shared staging. [I,S,V] |
| Exchange Values Using Array Indices Across a Warp (p. 261) | Derive source lane/component from an array index and validate partial participation. [I,V] |


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
[matching handout](../ncu-profiling/lesson-47-warp-shuffle-communication.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
