# Lesson 77 — Chapter 10 and Book Review

## Book location

Book: *Professional CUDA C Programming* (2014). Chapter 10; section 10.5.
Printed section start: 476. This compact lesson groups the subsections listed below;
their names/pages remain explicit rather than silently skipping them.
Status: **Representative local code ran; full case-study and diagnostic/performance comparisons remain open**.

## Core idea

A reproducible implementation connects semantics, architecture, source/PTX, build evidence and actual profiling. Topic coverage is separate from optimized, numerically verified, or hardware-validated execution.

## Current focused code

- `src/idea_blocks.cu`
- `src/idea_blocks.cpp`
- `src/main.cpp`

Kernel(s): EncryptIdeaBlocks.
Independent 64-bit IDEA encryption blocks with a host-expanded 128-bit key; a focused adaptation of the porting case, not the full historical file/decryption application.
Only this lesson's source files belong in this commit. Previous source is in Git history:
find the lesson with `git log --all --oneline --grep="lesson 77 "`, then check
out that commit in a separate worktree if needed. Retained Markdown is reference history;
its source links may refer to an earlier snapshot rather than today's working tree.

## All enclosed topics

| Book topic / printed page | Reading question or experiment to understand |
|---|---|
| Summary (p. 476) | finish every chapter exercise and deliver a reproducible report linking theory, implementation, and user-supplied profiles. [V,T] |


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
[matching handout](../ncu-profiling/lesson-77-chapter-10-and-book-review.md) states the evidence to inspect.
No speedup or bottleneck is asserted without your captures. PTX is intermediate code;
SASS is used only when final instruction selection matters. No next chapter is
implicitly completed by this note.

## Final local diagnostic attempt — 2026-11-09

The final IDEA snapshot printed `11fb ed2b 0198 6de5` for the documented input/key.
This is an observed output, not a full encryption/decryption validation suite.
`compute-sanitizer --tool memcheck ./bin/main` reported that GPU debugging features
are disabled and emitted an error summary. The program still printed its result,
but **memcheck validation is unavailable**, not passed. No profiler was run.
