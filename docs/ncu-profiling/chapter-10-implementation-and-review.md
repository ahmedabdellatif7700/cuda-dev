# 10. Implementation workflow and final review — profiling checklist

Companion: [chapter guide](../professional-cuda/chapter-10-implementation-and-review.md).
Book Chapter 10, printed pp. 425–476.

## Core idea

Use assessment, correctness, measured hypotheses, and reproducible deployment to turn a kernel into a defensible implementation.

## Observe only what answers your question

| Where / evidence | What to record | Interpretation |
|---|---|---|
| Bottleneck evidence | Relevant traffic, issue and instructions | Choose one discriminating experiment. |
| Correctness/diagnostics | Reference requirements and supported diagnostic output | Execution success does not establish correctness. |
| End-to-end context | Setup, transfers, concurrency, deployment | Kernel-only wins need not improve the application. |

## A focused review capture

Current focused code encrypts one IDEA block and prints 11fb ed2b 0198 6de5. Builds/PTX generation succeeded. Memcheck could not validate it because GPU debugging features are disabled. Full case-study and numerical suites remain open.

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

- Which hotspot can actually be parallelized?
- What distinguishes an optimization hypothesis from a measured result?
- What evidence is still missing before calling the implementation validated?

Pending captures remain pending; do not fill them with predicted numbers.
