# 3. Execution, occupancy, and reduction — profiling checklist

Companion: [chapter guide](../professional-cuda/chapter-03-execution-and-reduction.md).
Book Chapter 3, printed pp. 67–133.

## Core idea

Warps and resources determine execution opportunities; synchronization and ownership determine whether a reduction is valid.

## Observe only what answers your question

| Where / evidence | What to record | Interpretation |
|---|---|---|
| Occupancy / Scheduler | Registers, active/eligible warps, issue | Connect resource pressure to time, not to a utilization score. |
| Source Counters | Active/predicated lanes and branches | Equal-work comparisons are needed. |
| Instructions / Duration | Loop/control mix and runtime | A compiler suggestion is not a measured speedup. |

## A focused review capture

Compare the neighbor/interleaved block reductions of 256 ones. Use branch patterns and a bounded nested reduction as focused follow-ups; full grid reduction and performance sweeps remain separate extensions.

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

- What differs between theoretical occupancy and eligible warps?
- Why is a barrier inside a lane-dependent branch dangerous?
- What does unrolling cost as well as save?

Pending captures remain pending; do not fill them with predicted numbers.
