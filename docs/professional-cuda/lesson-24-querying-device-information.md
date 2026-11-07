# Lesson 24 — Using the Runtime API to Query GPU Information

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Managing Devices |
| Subsection | Using the Runtime API to Query GPU Information |
| Printed pages | 60–62 |
| Roadmap ID | 2.4.1 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Core idea

Query actual device properties to derive legal configurations instead of importing another GPU’s limits.

**Code or evidence:** [device_info.cpp](../../src/device_info.cpp). The observed Orin allows 1024 total threads/block. Per-axis maxima do not mean that multiplying all maximum dimensions forms a legal block.

**Original lesson commit:** `83eba28`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Concept and code connection

Read Managing Devices on p. 60 first. PrintDeviceInfo enumerates visible devices and reports properties: compute capability, SMs, warp size, memory, block/grid limits. Read each dimension and total threads/block independently: maximum x,y,z cannot all be multiplied into a legal block. Querying capacity is not measuring utilization. The observed Orin reports 8 SMs, CC 8.7, warp 32 and 1024 threads/block; see the summary for per-axis limits.

## Expected observations

Use reported hardware limits to derive legal launches. Compare capture launch attributes to runtime properties; do not copy a Tesla table.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): None: runtime property query. See the [handout](../ncu-profiling/lesson-24-querying-device-information.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
