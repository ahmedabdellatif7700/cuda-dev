# 7. Instructions, numerical behavior, and atomics — profiling checklist

Companion: [chapter guide](../professional-cuda/chapter-07-instructions-and-numerics.md).
Book Chapter 7, printed pp. 299–325.

## Core idea

A valid optimization meets numerical and ordering requirements before instruction count or utilization becomes useful evidence.

## Observe only what answers your question

| Where / evidence | What to record | Interpretation |
|---|---|---|
| Instructions / pipelines | Actual math/atomic operations | PTX and SASS can differ after lowering. |
| Atomic traffic / Duration | Address concentration and request count | Use a controlled contention sweep. |
| Numerical evidence | Domain, tolerance and special values | Counters cannot establish accuracy. |

## A focused review capture

Compare standard and intrinsic sine snapshots; inspect the initialized atomic sum of 1024 ones. Accuracy-domain, FP64 and contention sweeps remain open until explicitly measured.

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

- How can FMA improve one answer and change another?
- Why is a deterministic seed/input insufficient for numerical validation?
- What reduces global atomic pressure?

Pending captures remain pending; do not fill them with predicted numbers.
