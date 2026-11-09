# 6. Streams, events, and pipelines

**Book:** Chapter 6, printed pp. 267–298. Sections/subsections are listed in the
[complete roadmap](cuda-learning-path.md). Replaces review micro-lessons 49–54.

## Core idea

Dependencies define correctness; streams permit overlap, but only a timeline and whole-pipeline evidence can establish it.

## Remember these concepts

| Concept | What you need to explain |
|---|---|
| Streams and priorities | Each stream orders its operations. Independent/nonblocking streams remove some dependencies; priorities are hints. |
| Events | Dependency-only events establish completion and cross-stream ordering without adding source timers. |
| Default and implicit waits | Legacy/per-thread default semantics and implicit synchronization affect the DAG. Fermi/Hyper-Q queue behavior is historical context. |
| Scheduling | Depth-first vs breadth-first changes issue order. Pinning buffers enables async APIs but does not guarantee transfer/kernel overlap. |
| CPU work | Independent host work can run while device work is queued; output ownership changes only after completion. |
| Host callbacks | Stream-ordered host functions must not call CUDA APIs and must not outlive referenced data. |

## Pattern to recognize

```cpp
cudaMemcpyAsync(device, host, bytes, cudaMemcpyHostToDevice, stream);
// Launch the kernel into the same stream.
cudaEventRecord(done, stream);
cudaEventSynchronize(done);
```

This is a review pattern, not a complete standalone program. Refer to the focused
source snapshot for declarations, bounds, allocation and completion details.

## One experiment to revisit

Use four pinned-buffer chunks with explicit event completion. Compare issue order and inspect host callbacks. OpenMP/environment-variable variants and historical queue behavior remain reading extensions.

Start with that example; revisit historical variants only when they answer a
specific question. Your ncu-ui captures and numerical/performance comparisons
remain separate from theory or successful build evidence.

## Review questions

1. What orders operations within and across streams?
2. Why can two independent kernels still fail to overlap?
3. When can the CPU safely reuse a chunk buffer?

## Code snapshots

| Focused code snapshot | Commit |
|---|---|
| streams events and dependencies | `241fceb` |
| concurrent kernel execution | `4ba6307` |
| transfer and kernel pipelines | `08ce89f` |
| cpu gpu cooperation | `6a3fdaa` |
| stream host functions | `fbaf6be` |
| chapter 6 review | `3c226d5` |


Find a prior implementation with `git show <commit>:src/main.cpp`, or use a clean
worktree at that commit. Keep only current-lesson code in the main working tree;
we are not rewriting the existing history to renumber it.

## Profiling

Use the [chapter checklist](../ncu-profiling/chapter-06-streams-and-concurrency.md). The
[coverage/open-work record](remaining-chapters-coverage.md) retains detailed
headings and explicit unfinished work. No performance ranking is implied here.
