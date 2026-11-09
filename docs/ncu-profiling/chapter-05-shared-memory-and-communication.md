# 5. Shared memory, constants, and shuffles — profiling checklist

Companion: [chapter guide](../professional-cuda/chapter-05-shared-memory-and-communication.md).
Book Chapter 5, printed pp. 203–266.

## Core idea

Use explicit communication only when its reuse or layout benefit compensates for barriers, resources, and extra instructions.

## Observe only what answers your question

| Where / evidence | What to record | Interpretation |
|---|---|---|
| Shared tables | Bank conflicts, requests/wavefronts | Separate conflicts from broadcasts. |
| Occupancy / Warp State | Shared bytes and barrier stalls | Reuse can trade traffic for resources and waiting. |
| Global traffic / Duration | Bytes saved and total time | Do not optimize conflicts independently of runtime. |

## A focused review capture

Review shared exchange, bank-stride, padded transpose, dynamic-shared reduction, constant-coefficient stencil and full-warp shuffle snapshots. The 8-by-8 tile teaches layout, not universal conflict elimination.

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

- When does shared memory actually save traffic?
- How does padding change a bank index?
- Why is a correct shuffle mask part of the algorithm?

Pending captures remain pending; do not fill them with predicted numbers.
