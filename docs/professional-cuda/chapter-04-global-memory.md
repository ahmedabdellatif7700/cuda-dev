# 4. Global memory and data layout

**Book:** Chapter 4, printed pp. 135–202. Sections/subsections are listed in the
[complete roadmap](cuda-learning-path.md). Replaces review micro-lessons 36–41.

## Core idea

Performance depends on lane addresses, reuse, and traffic at each memory level—not merely on allocation or pointer syntax.

## Remember these concepts

| Concept | What you need to explain |
|---|---|
| Memory spaces | Registers/local/shared/constant/texture/global describe different scopes and access paths. Local memory is not automatically on-chip. |
| Allocation choices | Pageable, pinned, mapped, explicit device, UVA and managed policies differ in mapping/coherency/ownership. UVA is not automatic migration. |
| Coalescing | Contiguous aligned lane addresses often use sectors efficiently. Stride, offset, AoS/SoA and vector width change access/instruction structure. |
| Caches and bandwidth | Logical bytes differ from L1/L2/DRAM traffic. A composite memory throughput percentage is neither a cache hit rate nor DRAM saturation. |
| Transpose | A layout change may coalesce reads while striding writes. Use a copy control and explicit row/column addressing. |
| Orin managed memory | Shared physical DRAM still requires legal CPU/GPU completion and supported memory policies; do not assume prefetch support. |

## Pattern to recognize

```cpp
logical_bytes = output_count * (2 * sizeof(float) + sizeof(float));
// For float vector addition: 12 logical bytes per output.
```

This is a review pattern, not a complete standalone program. Refer to the focused
source snapshot for declarations, bounds, allocation and completion details.

## One experiment to revisit

Inspect contiguous copy, strided read, transpose and managed-add snapshots. Change one address/layout variable at a time. Texture/AoS/SoA and allocation-policy sweeps are follow-ups, not fabricated measurements.

Start with that example; revisit historical variants only when they answer a
specific question. Your ncu-ui captures and numerical/performance comparisons
remain separate from theory or successful build evidence.

## Review questions

1. What makes adjacent lane accesses coalesced?
2. Why does logical bandwidth differ from DRAM traffic?
3. What does UVA guarantee—and what does it not?

## Code snapshots

| Focused code snapshot | Commit |
|---|---|
| cuda memory spaces | `2cc3a1a` |
| memory management | `0e76e31` |
| global access patterns | `edb5fdd` |
| bandwidth and matrix transpose | `333c835` |
| matrix addition with unified memory | `c0b2474` |
| chapter 4 review | `de11959` |


Find a prior implementation with `git show <commit>:src/main.cpp`, or use a clean
worktree at that commit. Keep only current-lesson code in the main working tree;
we are not rewriting the existing history to renumber it.

## Profiling

Use the [chapter checklist](../ncu-profiling/chapter-04-global-memory.md). The
[coverage/open-work record](remaining-chapters-coverage.md) retains detailed
headings and explicit unfinished work. No performance ranking is implied here.
