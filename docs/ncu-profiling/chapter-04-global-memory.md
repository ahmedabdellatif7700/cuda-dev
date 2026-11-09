# 4. Global memory and data layout — profiling checklist

Companion: [chapter guide](../professional-cuda/chapter-04-global-memory.md).
Book Chapter 4, printed pp. 135–202.

## Core idea

Performance depends on lane addresses, reuse, and traffic at each memory level—not merely on allocation or pointer syntax.

## Observe only what answers your question

| Where / evidence | What to record | Interpretation |
|---|---|---|
| Memory Workload Analysis | Sectors/requests and per-level bytes | Locate extra traffic before naming a bottleneck. |
| Source/SASS | Access width and address arithmetic | float4 does not promise fourfold speedup. |
| Duration / working set | Time across fixed work and reuse | Cache state and collection settings matter. |

## A focused review capture

Inspect contiguous copy, strided read, transpose and managed-add snapshots. Change one address/layout variable at a time. Texture/AoS/SoA and allocation-policy sweeps are follow-ups, not fabricated measurements.

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

- What makes adjacent lane accesses coalesced?
- Why does logical bandwidth differ from DRAM traffic?
- What does UVA guarantee—and what does it not?

Pending captures remain pending; do not fill them with predicted numbers.
