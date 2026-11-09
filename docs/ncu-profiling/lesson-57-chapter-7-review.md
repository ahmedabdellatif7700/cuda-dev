# Lesson 57 — Chapter 7 Review: profiling handout

Chapter 7, section 7.3; printed start 324.
See [lesson notes](../professional-cuda/lesson-57-chapter-7-review.md).

## Core idea

Useful work, numerical requirements and ordering define a valid optimization; lower instruction count or higher utilization alone is insufficient.

## What to observe

Kernel(s): AtomicSumKernel. Start with launch geometry and
Duration. Then inspect the relevant group: occupancy/registers and eligible warps
for execution/resource questions; source/predication for divergence; actual cache/
DRAM traffic and sectors for global access; bank conflicts/wavefronts for shared
layouts; instructions and error budgets for math; host DAG/timeline for concurrency.
Select only the relevant sections for this lesson rather than gathering everything.

For streams, the printed independent CPU sum is 4950 and chunk output is 2. No overlap claim is made without your timeline evidence. Default-stream, Fermi false-dependency, OpenMP dispatch and environment-variable topics are explicitly reading questions in the table; the current representative code uses four nonblocking streams and dependency-only events. For math, printed sine values cover input 1 only; error-domain/FP64 and fast-math sweeps remain numerical discussion exercises, not measured accuracy claims. Atomic input 1024 ones prints 1024. Record missing comparisons as pending.

## Comparison discipline

Record input and launch parameters, revision, target/tool versions, reported clocks,
power/thermal context, replay/cache settings, and repeated-capture variation. Compare
identical useful work when optimizing; changing input size is scaling. Do not infer
DRAM bandwidth from a composite memory-throughput percentage, or application latency
from an isolated kernel duration. Theoretical occupancy is capacity, not observed use.

## Pending evidence

Your capture: pending. Interpretation: pending. Next code change: agree from evidence.
Unsupported hardware/compiler/API measurements remain unavailable, not simulated proof.
