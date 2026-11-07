# Lesson 14 — Writing Your Kernel: observation handout

Chapter 2 → Introducing the CUDA Programming Model → Writing Your Kernel, printed pp. 37–38; roadmap 2.1.5.
See [lesson notes](../professional-cuda/lesson-14-writing-your-kernel.md).

## Core idea

A kernel describes one thread’s independent operation and must assign every valid output to an appropriate owner.

**Code or evidence:** [vector_add.cu](../../src/vector_add.cu). The source addition becomes two PTX global loads, a float addition, and a store. The index and bounds check decide which element that operation owns.

**Original lesson commit:** `960e567`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Monitor and interpret

Kernel(s): **VectorAddScalar / VectorAddCyclic**.

Read relevant PTX loads, add, store beside the statement. PTX virtual-register counts are not physical resource use.

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
