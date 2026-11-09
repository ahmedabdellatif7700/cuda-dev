# 9. Multi-GPU ownership and MPI — profiling checklist

Companion: [chapter guide](../professional-cuda/chapter-09-multi-gpu-and-mpi.md).
Book Chapter 9, printed pp. 387–424.

## Core idea

Partitioning, communication permissions, and transport completion are separate contracts; local simulation cannot validate remote hardware.

## Observe only what answers your question

| Where / evidence | What to record | Interpretation |
|---|---|---|
| Capability/topology | Actual device count and directional support | Unavailable hardware stays pending. |
| Per-device kernels plus timeline | Binding, dependencies and exchange | A single kernel cannot explain cluster throughput. |
| Scaling protocol | Fixed/weak work and message size | Local ranks do not measure network performance. |

## A focused review capture

One Orin was queried; true P2P/multi-GPU/RDMA was unavailable. Local partitioned scaling and a single wave step ran. MPI demonstrated host-message semantics only; no CUDA-aware/network scaling result is claimed.

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

- Why does UVA not grant peer permission?
- Which stencil cells can run before halo arrival?
- What extra evidence proves RDMA rather than host staging?

Pending captures remain pending; do not fill them with predicted numbers.
