# 6. Streams, events, and pipelines — profiling checklist

Companion: [chapter guide](../professional-cuda/chapter-06-streams-and-concurrency.md).
Book Chapter 6, printed pp. 267–298.

## Core idea

Dependencies define correctness; streams permit overlap, but only a timeline and whole-pipeline evidence can establish it.

## Observe only what answers your question

| Where / evidence | What to record | Interpretation |
|---|---|---|
| Launch/resource metrics | Per-kernel resource pressure | Explains possible co-residency, not proof of overlap. |
| Timeline, if collected by you | CPU/API/copy/kernel dependencies | Use a suitable timeline tool; isolated kernel replay can distort concurrency. |
| Completed pipeline evidence | Equal-work completion latency | A kernel duration excludes orchestration and transfers. |

## A focused review capture

Use four pinned-buffer chunks with explicit event completion. Compare issue order and inspect host callbacks. OpenMP/environment-variable variants and historical queue behavior remain reading extensions.

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

- What orders operations within and across streams?
- Why can two independent kernels still fail to overlap?
- When can the CPU safely reuse a chunk buffer?

Pending captures remain pending; do not fill them with predicted numbers.
