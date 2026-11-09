# 1. CPU/GPU foundations — profiling checklist

Companion: [chapter guide](../professional-cuda/chapter-01-foundations.md).
Book Chapter 1, printed pp. 1–22.

## Core idea

Independent data work can run in parallel; CPU and GPU cooperate through an explicit data and completion contract.

## Observe only what answers your question

| Where / evidence | What to record | Interpretation |
|---|---|---|
| Launch Statistics | Grid/block dimensions and total threads | One block cannot distribute work across eight SMs. |
| Duration and frequency | Kernel duration and reported clock | Do not infer full application speedup. |
| Source/PTX | Loads → addition → store | Host preparation/copy/print calls are outside kernel PTX. |

## A focused review capture

Use vector addition plus thread mapping; optionally the ten-thread greeting that prints only thread 5. Trace A[37]=37, B[37]=10, output[37]=47. A separate CPU sum consumes returned data.

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

- Why can additions run independently?
- Why does printed index order not reveal GPU scheduling?
- What must complete before the CPU reads output?

Pending captures remain pending; do not fill them with predicted numbers.
