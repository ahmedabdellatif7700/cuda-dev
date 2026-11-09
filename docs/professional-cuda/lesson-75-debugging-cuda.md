# Lesson 75 — Debugging CUDA

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 10; section 10.3.
Printed section start: 448. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Representative local code ran; full case-study and diagnostic/performance comparisons remain open**.

## Core idea

Breakpoints, prints/asserts and memory/race/synchronization diagnostics expose different failures. Keep faulty demonstrations isolated and restore a passing default snapshot.

## Current focused code

- `src/synchronizedexchange.cu`
- `src/synchronizedexchange.cpp`
- `src/main.cpp`

Kernel(s): SynchronizedExchangeKernel.

Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 75 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| CUDA Debugging (p. 448) | isolate faults in dedicated diagnostic exercises and restore a passing default runner. [V] |
| Kernel Debugging (p. 448) | use existing cuda-debug target for breakpoints, indices, variables, and race/ordering reasoning on small inputs. [V] |
| Memory Debugging (p. 456) | translate cuda-memcheck work to Compute Sanitizer memcheck/racecheck/initcheck/synccheck; introduce and fix bounded faults. [V] |
| Debugging Summary (p. 462) | distinguish illegal access, uninitialized memory, shared races, bad barriers, and ordinary numeric mismatches. [V] |
| Using cuda-gdb (p. 448) | Use make cuda-debug on a tiny deterministic kernel and inspect indices and device variables. [V] |
| CUDA printf (p. 454) | Bound diagnostic output and show why order and instrumented timings are not reliable scheduling evidence. [V] |
| CUDA assert (p. 455) | Trigger a bounded failed invariant in a separate process; rebuild/restore the passing exercise. [V] |
| Kernel Debugging Summary (p. 456) | Classify logic, launch, execution, and synchronization faults with a minimal reproducer. [V] |
| Compiling for cuda-memcheck (p. 456) | Translate debug/symbol requirements to installed Compute Sanitizer; separate debug and performance builds. [V] |
| memcheck (p. 457) | Detect and repair an isolated out-of-bounds/misaligned access; review leaks/API error reporting. [V] |
| racecheck (p. 458) | Detect and repair a shared-memory producer/consumer hazard; use synccheck/initcheck for their distinct questions. [V] |


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
[matching handout](../ncu-profiling/lesson-75-debugging-cuda.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.
