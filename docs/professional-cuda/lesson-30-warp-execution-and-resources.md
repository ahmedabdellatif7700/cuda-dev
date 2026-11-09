# Lesson 30 — Warp Execution and Resources

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 3; section 3.2.
Printed section start: 80. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Runnable representative experiment; user profiling pending**.

## Core idea

Warps contain 32 lanes. Mixed control paths can serialize or predicate; residency and eligible warps are different from useful issue throughput. Synchronization establishes correctness, while occupancy only describes capacity/residency.

## Current focused code

- `src/branchpaths.cu`
- `src/branchpaths.cpp`
- `src/main.cpp`

Kernel(s): BranchPathsKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 30 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Understanding the Nature of Warp Execution (p. 80) | map linearized block threads into 32-lane warps; predict partial-warp behavior. [L,D] |
| Warps and Thread Blocks (p. 80) | compare 31/32/33-thread blocks and multidimensional blocks; verify linear lane mapping. [L,O] |
| Warp Divergence (p. 82) | compare uniform, alternating-lane, and warp-aligned branches with equal useful work; inspect predication/SASS. [D,I] |
| Resource Partitioning (p. 87) | independently vary register live ranges and dynamic shared bytes; observe occupancy limit transitions. [O] |
| Latency Hiding (p. 90) | compare dependent instruction chains with independent accumulators and more resident warps. [W,I] |
| Occupancy (p. 93) | compare runtime occupancy predictions and achieved occupancy across legal block sizes; test whether time improves. [O,T] |
| Synchronization (p. 97) | compare correct block barriers and stream completion; use sanitizer on isolated invalid-barrier demonstrations rather than risking a hang. [V,W] |
| Scalability (p. 98) | sweep grid size from underfilled to many waves; identify fixed-work saturation. [L,T] |


## How to work through it

Inputs are 1.0f; reductions print 256. The branch exercise has two numerical paths, so it does not isolate divergence cost from arithmetic effects. Modify only the predicate (lane versus warp grouping) for an equal-work comparison after discussion.

For Fermi/Kepler and nested profiling, retain historical/capability limits. Modern CDP reference: [NVIDIA](https://docs.nvidia.com/cuda/cuda-programming-guide/04-special-topics/dynamic-parallelism.html).

The table records the book's questions/experiments, not a claim that every historical
variant was reproduced or optimized. The code is the representative implementation
specified above. Any external-hardware or missing-tool work is marked separately.
No source timers or automatic numerical comparisons are introduced. Read printed
outputs and reason about bounds/ownership; completion alone does not prove correctness.

## Build and observation

`make clean build run` and `make ptx` succeeded on the local Orin. Printed output was inspected, not automatically compared. No profiling or timing was run.

## Profiling and next step

You personally capture actual kernels in ncu-ui. The
[matching handout](../ncu-profiling/lesson-30-warp-execution-and-resources.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
