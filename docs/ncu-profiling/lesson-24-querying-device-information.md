# Lesson 24 — Using the Runtime API to Query GPU Information: observation handout

Chapter 2 → Managing Devices → Using the Runtime API to Query GPU Information, printed pp. 60–62; roadmap 2.4.1.
See [lesson notes](../professional-cuda/lesson-24-querying-device-information.md).

## Core idea

Query actual device properties to derive legal configurations instead of importing another GPU’s limits.

**Code or evidence:** [device_info.cpp](../../src/device_info.cpp). The observed Orin allows 1024 total threads/block. Per-axis maxima do not mean that multiplying all maximum dimensions forms a legal block.

**Original lesson commit:** `83eba28`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Monitor and interpret

Kernel(s): **None: runtime property query**.

Use reported hardware limits to derive legal launches. Compare capture launch attributes to runtime properties; do not copy a Tesla table.

For actual kernels: begin with Launch Statistics (grid/block dimensions), Duration,
and relevant Source/SASS or generated PTX. Inspect Occupancy and Memory Workload
Analysis only when they answer a concrete question. Record revision, input shape,
block size, tool/collection settings, clocks, and variation. Keep numerical correctness,
compiled PTX, and measured behavior as distinct forms of evidence.

## Change candidates

For matrix kernels, vary one launch dimension/shape at equal output count after
deriving the new indexing and bounds. For host API topics, inspect returned values
or messages rather than optimizing a nonexistent kernel. No code change or tool
suggestion is automatically a speedup; keep the baseline and ask what measurement
would distinguish competing explanations.

## Observation record

- Expected geometry or host API outcome: derive before capturing.
- Actual capture or command output: pending user discussion unless recorded in summary.
- Predicted versus observed behavior: pending.
- Proposed next change and acceptance criterion: pending.

You perform ncu-ui captures. No automatic profiling is run, and no kernel Duration
is presented as the whole pipeline cost.
