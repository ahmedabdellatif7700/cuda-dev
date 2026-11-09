# Lesson 35 — Chapter 3 Review: profiling handout

Chapter 3, section 3.7; printed start 132.
See [lesson notes](../professional-cuda/lesson-35-chapter-3-review.md).

## Core idea

Execution geometry, divergence, independent work, resource limits and synchronization explain performance only when connected to measured evidence.

## What to observe

Kernel(s): InterleavedReduceKernel. Start with launch geometry and
Duration. Then inspect the relevant group: occupancy/registers and eligible warps
for execution/resource questions; source/predication for divergence; actual cache/
DRAM traffic and sectors for global access; bank conflicts/wavefronts for shared
layouts; instructions and error budgets for math; host DAG/timeline for concurrency.
Select only the relevant sections for this lesson rather than gathering everything.

Inputs are 1.0f; reductions print 256. The branch exercise has two numerical paths, so it does not isolate divergence cost from arithmetic effects. Modify only the predicate (lane versus warp grouping) for an equal-work comparison after discussion.

For Fermi/Kepler and nested profiling, retain historical/capability limits. Modern CDP reference: [NVIDIA](https://docs.nvidia.com/cuda/cuda-programming-guide/04-special-topics/dynamic-parallelism.html).

## Comparison discipline

Record input and launch parameters, revision, target/tool versions, reported clocks,
power/thermal context, replay/cache settings, and repeated-capture variation. Compare
identical useful work when optimizing; changing input size is scaling. Do not infer
DRAM bandwidth from a composite memory-throughput percentage, or application latency
from an isolated kernel duration. Theoretical occupancy is capacity, not observed use.

## Pending evidence

Your capture: pending. Interpretation: pending. Next code change: agree from evidence.
Unsupported hardware/compiler/API measurements remain unavailable, not simulated proof.
