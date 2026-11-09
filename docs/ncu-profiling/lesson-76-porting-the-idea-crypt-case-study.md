# Lesson 76 — Porting the IDEA Crypt Case Study: profiling handout

Chapter 10, section 10.4; printed start 462.
See [lesson notes](../professional-cuda/lesson-76-porting-the-idea-crypt-case-study.md).

## Core idea

Remove linked-list traversal dependencies by flattening independent blocks, then port the block transform. Avoid unnecessary output uploads and separate key setup, transfer, computation and deployment questions.

## What to observe

Kernel(s): EncryptIdeaBlocks. Start with launch geometry and
Duration. Then inspect the relevant group: occupancy/registers and eligible warps
for execution/resource questions; source/predication for divergence; actual cache/
DRAM traffic and sectors for global access; bank conflicts/wavefronts for shared
layouts; instructions and error budgets for math; host DAG/timeline for concurrency.
Select only the relevant sections for this lesson rather than gathering everything.

The crypt example is an original concise IDEA encryption adaptation using 64-bit blocks and a 128-bit key expanded into 52 words. It is not the full downloaded legacy application: decryption-key generation, file I/O, overlapping/multi-GPU/OpenMP deployment and full test-vector/error-domain validation are reading/follow-up work, not claimed complete. Do not substitute an XOR toy and call it the book algorithm. The debugger lesson runs safe synchronized code; intentional invalid accesses/races are not injected into the default. Detailed NVTX/timeline and interactive cuda-gdb sessions remain user/tool follow-ups. Retain every original body topic in the table.

## Comparison discipline

Record input and launch parameters, revision, target/tool versions, reported clocks,
power/thermal context, replay/cache settings, and repeated-capture variation. Compare
identical useful work when optimizing; changing input size is scaling. Do not infer
DRAM bandwidth from a composite memory-throughput percentage, or application latency
from an isolated kernel duration. Theoretical occupancy is capacity, not observed use.

## Pending evidence

Your capture: pending. Interpretation: pending. Next code change: agree from evidence.
Unsupported hardware/compiler/API measurements remain unavailable, not simulated proof.
