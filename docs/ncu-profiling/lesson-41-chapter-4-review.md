# Lesson 41 — Chapter 4 Review: profiling handout

Chapter 4, section 4.6; printed start 199.
See [lesson notes](../professional-cuda/lesson-41-chapter-4-review.md).

## Core idea

Explain traffic at the correct hierarchy level before selecting an allocation policy, layout or access optimization.

## What to observe

Kernel(s): CopyGlobalKernel. Start with launch geometry and
Duration. Then inspect the relevant group: occupancy/registers and eligible warps
for execution/resource questions; source/predication for divergence; actual cache/
DRAM traffic and sectors for global access; bank conflicts/wavefronts for shared
layouts; instructions and error budgets for math; host DAG/timeline for concurrency.
Select only the relevant sections for this lesson rather than gathering everything.

Representative inputs and geometry are intentionally small and explicit. The memory-space survey includes historical configurations and unsupported cache/bank modes as theory, not reproduced hardware. AoS/SoA, texture filtering and every old tuning variant are reading/experiment questions in the table; no measurement is fabricated. Managed prefetch is not called without capability checks. The transpose uses one 8-by-8 matrix; larger rectangular/tail versions are follow-up exercises, not claimed tested cases. Reduction/shuffle examples use full fixed-size participation. Read the current code contracts before changing dimensions.

## Comparison discipline

Record input and launch parameters, revision, target/tool versions, reported clocks,
power/thermal context, replay/cache settings, and repeated-capture variation. Compare
identical useful work when optimizing; changing input size is scaling. Do not infer
DRAM bandwidth from a composite memory-throughput percentage, or application latency
from an isolated kernel duration. Theoretical occupancy is capacity, not observed use.

## Pending evidence

Your capture: pending. Interpretation: pending. Next code change: agree from evidence.
Unsupported hardware/compiler/API measurements remain unavailable, not simulated proof.
