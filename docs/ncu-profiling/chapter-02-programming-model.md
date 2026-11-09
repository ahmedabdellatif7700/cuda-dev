# 2. Programming model and indexing — profiling checklist

Companion: [chapter guide](../professional-cuda/chapter-02-programming-model.md).
Book Chapter 2, printed pp. 23–65.

## Core idea

Derive data ownership, legal launch geometry, bounds, memory lifetimes, and completion before tuning anything.

## Observe only what answers your question

| Where / evidence | What to record | Interpretation |
|---|---|---|
| Launch Statistics | Actual shape vs derived grid | Same outputs can have different inactive-thread patterns. |
| Occupancy | Resource limits, registers and achieved residency | Capacity is not a performance ranking. |
| Memory Workload Analysis | Sectors and bytes at matching n | Compare equal useful work and datatype. |

## A focused review capture

Use a 7-by-3 matrix to expose non-square edges. Compare flat 1D, 2D-block, and row-wise mappings; pair-per-thread and integer variants are optional extensions. Device queries give actual Orin limits.

Before collecting, state one prediction. For an optimization, keep useful work,
datatype and correctness requirements fixed; input-size changes are scaling.
Only change one relevant variable after the baseline is understood.

## Record once per comparison

- Source commit, kernel/API, input dimensions and block/grid configuration.
- Target/tool versions, reported clocks, power/thermal context and background load.
- Collection/replay/cache settings and duration variation across captures.
- Observation, interpretation, one proposed change, and its acceptance criterion.

You perform ncu-ui captures. Use a timeline for host/copy/concurrency questions.
PTX helps explain source operations; SASS resolves final instruction selection.
A profiler counter does not prove numerical correctness or external-hardware support.

## Review questions

- Why do a 2D grid and a flat grid need different bounds?
- What does a successful launch fail to establish?
- Which timing scope would include copies?

Pending captures remain pending; do not fill them with predicted numbers.
