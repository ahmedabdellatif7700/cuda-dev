# Lesson 74 — Profile Driven Optimization

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 10; section 10.2.
Printed section start: 438. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Representative local code ran; full case-study and diagnostic/performance comparisons remain open**.

## Core idea

A hypothesis must identify the measured limiting path and a controlled change. Kernel counters and pipeline traces answer different questions; suggestions are estimates, not guarantees.

## Current focused code

- `src/transformvalues.cu`
- `src/transformvalues.cpp`
- `src/main.cpp`

Kernel(s): TransformValuesKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 74 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Profile-Driven Optimization (p. 438) | establish a hypothesis→measurement→change→validation ledger. [T,C,M] |
| Finding Optimization Opportunities Using nvprof (p. 439) | translate summary/trace/metric tasks into appropriate current tools; select kernel versus pipeline questions. [T,H] |
| Guiding Optimization Using nvvp (p. 443) | interpret current ncu-ui sections and optional timeline evidence rather than reproduce the obsolete UI. [T,M,W] |
| NVIDIA Tools Extension (p. 446) | annotate host stages with supported NVTX ranges and relate them to kernel naming and user captures. [H] |
| Profiling Modes (p. 439) | Map historical summary, trace, and metric modes to timing, timeline, and kernel-counter evidence. [T,H,M] |
| Profiling Scope (p. 440) | Select kernels/ranges and exclude setup where appropriate; keep a separate whole-pipeline measurement. [T,H] |
| Memory Bandwidth (p. 440) | Compare logical bandwidth with actual hierarchy traffic on the chosen hotspot. [M,T] |
| Instruction Throughput (p. 443) | Inspect active pipelines and dependencies rather than treating utilization as a score. [C,I,W] |
| Guided Analysis (p. 444) | Test a tool suggestion with a controlled variant and verify both correctness and time. [V,T] |
| Unguided Analysis (p. 444) | Form an independent hypothesis from traffic/instructions and collect discriminating evidence. [M,I,T] |


## How to work through it

The crypt example is an original concise IDEA encryption adaptation using 64-bit blocks and a 128-bit key expanded into 52 words. It is not the full downloaded legacy application: decryption-key generation, file I/O, overlapping/multi-GPU/OpenMP deployment and full test-vector/error-domain validation are reading/follow-up work, not claimed complete. Do not substitute an XOR toy and call it the book algorithm. The debugger lesson runs safe synchronized code; intentional invalid accesses/races are not injected into the default. Detailed NVTX/timeline and interactive cuda-gdb sessions remain user/tool follow-ups. Retain every original body topic in the table.

The table records the book's questions/experiments, not a claim that every historical
variant was reproduced or optimized. The code is the representative implementation
specified above. Any external-hardware or missing-tool work is marked separately.
No source timers or automatic numerical comparisons are introduced. Read printed
outputs and reason about bounds/ownership; completion alone does not prove correctness.

## Build and observation

`make clean build run` and `make ptx` succeeded. Printed outputs were inspected without automatic numerical comparisons or source timers. No profiler capture or deployment to external systems was performed.

## Profiling and next step

You personally capture actual kernels in ncu-ui. The
[matching handout](../ncu-profiling/lesson-74-profile-driven-optimization.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
