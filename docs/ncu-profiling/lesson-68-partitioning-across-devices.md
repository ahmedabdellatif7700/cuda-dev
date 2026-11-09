# Lesson 68 — Partitioning Across Devices: profiling handout

Chapter 9, section 9.2; printed start 393.
See [lesson notes](../professional-cuda/lesson-68-partitioning-across-devices.md).

## Core idea

Divide useful work and retain exact ownership/offsets before adding hardware communication. Local partition correctness is a control, not proof of multi-GPU scaling.

## What to observe

Kernel(s): PartitionedScaleKernel. Start with launch geometry and
Duration. Then inspect the relevant group: occupancy/registers and eligible warps
for execution/resource questions; source/predication for divergence; actual cache/
DRAM traffic and sectors for global access; bank conflicts/wavefronts for shared
layouts; instructions and error budgets for math; host DAG/timeline for concurrency.
Select only the relevant sections for this lesson rather than gathering everything.

Real multi-GPU, P2P copy/dereference, multi-GPU stencil, inter-node affinity/scaling, CUDA-aware transport and GPUDirect RDMA measurements are pending external hardware. A local subdomain exercise cannot substitute for them. The wave implementation is one 8-by-8 step with previous=current and fixed-zero output boundary, not a distributed time-integration benchmark. MPI uses host integers only; no device pointer is passed without verifying CUDA-aware support. No ranks are sent to external hosts.

## Comparison discipline

Record input and launch parameters, revision, target/tool versions, reported clocks,
power/thermal context, replay/cache settings, and repeated-capture variation. Compare
identical useful work when optimizing; changing input size is scaling. Do not infer
DRAM bandwidth from a composite memory-throughput percentage, or application latency
from an isolated kernel duration. Theoretical occupancy is capacity, not observed use.

## Pending evidence

Your capture: pending. Interpretation: pending. Next code change: agree from evidence.
Unsupported hardware/compiler/API measurements remain unavailable, not simulated proof.
