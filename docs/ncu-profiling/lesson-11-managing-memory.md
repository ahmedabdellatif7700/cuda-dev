# Lesson 11 — Managing Memory: observation handout

Chapter 2 → Introducing the CUDA Programming Model → Managing Memory, printed pp. 26–29; roadmap 2.1.2.
See [lesson notes](../professional-cuda/lesson-11-managing-memory.md).

## Core idea

Memory APIs operate on byte ranges whose ownership and lifetime must cover every GPU access.

**Code or evidence:** [memory_roundtrip.cpp](../../exercises/chapter-02/memory_roundtrip.cpp). Four floats require 4 * sizeof(float) bytes. The round trip prints the copied data before cudaFree releases the allocation.

**Original lesson commit:** `84e0596`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Monitor and interpret

Kernel(s): **None: host-only round trip**.

A kernel report cannot time a host allocation or attribute pipeline copy costs. No GPU kernel is needed for a memory-copy API exercise.

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
