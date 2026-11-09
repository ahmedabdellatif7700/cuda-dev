# 10. Implementation workflow and final review

**Book:** Chapter 10, printed pp. 425–476. Sections/subsections are listed in the
[complete roadmap](cuda-learning-path.md). Replaces review micro-lessons 73–77.

## Core idea

Use assessment, correctness, measured hypotheses, and reproducible deployment to turn a kernel into a defensible implementation.

## Remember these concepts

| Concept | What you need to explain |
|---|---|
| APOD | Assess hotspots/dependencies, parallelize suitable work, optimize measured limits, deploy under an explicit workload contract. |
| Compilation and errors | Separate host/device compilation and linking; classify launch, execution, memory, synchronization and numerical failures. |
| Profile-driven changes | Define one variable, baseline, prediction and acceptance criterion. A tool estimate is not an achieved improvement. |
| Debugging | cuda-gdb, bounded printf/asserts and sanitizer modes answer different questions. Unsupported diagnostics are not a pass. |
| Porting crypt | Flatten linked-list dependencies into independent blocks; key setup, transfers, arithmetic and file pipeline are separate concerns. |
| Deployment | Preserve revision/toolchain/target/settings and pending evidence. Full crypt decryption/hybrid/multi-GPU deployment is not implemented by an encryption example. |

## Pattern to recognize

```cpp
// assess -> simplest correct parallel mapping -> measured single change -> reproduce and deploy
```

This is a review pattern, not a complete standalone program. Refer to the focused
source snapshot for declarations, bounds, allocation and completion details.

## One experiment to revisit

Current focused code encrypts one IDEA block and prints 11fb ed2b 0198 6de5. Builds/PTX generation succeeded. Memcheck could not validate it because GPU debugging features are disabled. Full case-study and numerical suites remain open.

Start with that example; revisit historical variants only when they answer a
specific question. Your ncu-ui captures and numerical/performance comparisons
remain separate from theory or successful build evidence.

## Review questions

1. Which hotspot can actually be parallelized?
2. What distinguishes an optimization hypothesis from a measured result?
3. What evidence is still missing before calling the implementation validated?

## Code snapshots

| Focused code snapshot | Commit |
|---|---|
| cuda development process | `3c4a357` |
| profile driven optimization | `a048914` |
| debugging cuda | `74843a3` |
| porting the idea crypt case study | `d85f25d` |
| chapter 10 and book review | `84aba61` |


Find a prior implementation with `git show <commit>:src/main.cpp`, or use a clean
worktree at that commit. Keep only current-lesson code in the main working tree;
we are not rewriting the existing history to renumber it.

## Profiling

Use the [chapter checklist](../ncu-profiling/chapter-10-implementation-and-review.md). The
[coverage/open-work record](remaining-chapters-coverage.md) retains detailed
headings and explicit unfinished work. No performance ranking is implied here.
