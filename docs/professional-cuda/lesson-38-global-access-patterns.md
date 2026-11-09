# Lesson 38 — Global Access Patterns

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 4; section 4.3.
Printed section start: 158. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Transactions are formed from participating lane addresses. Contiguous lanes and natural alignment usually use sectors more efficiently; vector width and AoS/SoA layout change instruction/access structure.

## Current focused code

- `src/stridedread.cu`
- `src/stridedread.cpp`
- `src/main.cpp`

Kernel(s): StridedReadKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 38 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Memory Access Patterns (p. 158) | isolate lane stride, base offset, instruction width, and data layout. [M,I] |
| Aligned and Coalesced Access (p. 158) | sweep scalar offsets and strides without invalid vector alignment; predict useful bytes per sector. [M] |
| Global Memory Reads (p. 160) | compare offset and stride read kernels, reuse, cache policies, and read-only paths supported by the compiler. [M,I] |
| Global Memory Writes (p. 169) | compare contiguous, offset, and strided stores with deterministic scatter validation. [M] |
| Array of Structures versus Structure of Arrays (p. 171) | access one field and all fields in AoS/SoA; compare traffic and instruction counts. [M,I] |
| Performance Tuning (p. 176) | sweep read-only annotations, vector widths, and legal cache options one at a time; check SASS and tails. [M,I,O] |
| Cached Loads (p. 161) | Compare supported cache-policy variants on a reusable working set; inspect final instructions. [M,I] |
| Uncached Loads (p. 163) | Test supported bypass policies and explain which cache level is bypassed; avoid assuming no caching anywhere. [M,I] |
| Example of Misaligned Reads (p. 164) | Sweep legal scalar offsets at fixed work and count sectors per useful byte. [M] |
| Read-Only Cache (p. 168) | Compare const/restrict and supported read-only intrinsics; inspect generated read paths. [M,I] |
| Example of Misaligned Writes (p. 170) | Sweep store offsets with aligned allocation and validate all destinations. [M,V] |
| Example: Simple Math with the AoS Data Layout (p. 172) | Compute one field and all fields; measure extra traffic for unused fields. [M,I] |
| Example: Simple Math with the SoA Data Layout (p. 175) | Repeat equal arithmetic with separate field arrays and compare traffic. [M,I] |
| Unrolling Techniques (p. 176) | Compare fixed unroll factors with safe tails and equal useful work. [I,O] |
| Exposing More Parallelism (p. 177) | Increase independent work/grid coverage while tracking eligible warps and live registers. [W,O] |


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
[matching handout](../ncu-profiling/lesson-38-global-access-patterns.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
