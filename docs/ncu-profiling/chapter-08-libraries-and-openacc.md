# 8. CUDA libraries and OpenACC — profiling checklist

Companion: [chapter guide](../professional-cuda/chapter-08-libraries-and-openacc.md).
Book Chapter 8, printed pp. 327–386.

## Core idea

Use supported library/data-layout contracts and compare equal numerical tasks; toolchain support determines whether directives actually offload.

## Observe only what answers your question

| Where / evidence | What to record | Interpretation |
|---|---|---|
| Actual library kernels | Launches, Duration and resource/traffic evidence | No application PTX exposes a closed library implementation. |
| Matched operation | Shapes, layout, precision and algorithm | Avoid comparing different mathematical tasks. |
| Setup/pipeline context | Plan/workspace and transfer costs | Tiny calls can be setup dominated. |

## A focused review capture

Ran a 2-by-2 CSR product (2,3), identity GEMM (1,2,3,4), impulse FFT (ones), and seeded uniform RNG. OpenACC directive source was preserved in its snapshot; GPU offload remains unvalidated.

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

- Which setup costs should be amortized?
- What layout mismatch can silently change a BLAS result?
- How would you prove an OpenACC loop ran on the GPU?

Pending captures remain pending; do not fill them with predicted numbers.
