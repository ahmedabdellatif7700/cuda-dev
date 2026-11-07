# Lesson 25 — Determining the Best GPU

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Managing Devices |
| Subsection | Determining the Best GPU |
| Printed pages | 63 |
| Roadmap ID | 2.4.2 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Core idea

The best device depends on workload requirements and measured behavior, not one advertised hardware number.

**Code or evidence:** [device_info.cpp](../../src/device_info.cpp). Only one GPU is visible here. Selecting logical device 0 is a local policy; a genuine multi-device ranking remains unmeasured.

**Original lesson commit:** `df2b629`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Concept and code connection

A heuristic may rank devices by SMs, clocks, capacity or capability, but best depends on workload and required features. This system exposes one Orin, so choose logical device 0 rather than inventing a multi-GPU comparison. PrintDeviceInfo lists all visible devices before selection. Genuine selection/scaling benchmarks require additional devices and are pending hardware. No GPU purchases or remote execution are needed for this topic.

## Expected observations

An isolated kernel can help rank a workload on actual candidate hardware; device count or advertised peak alone cannot establish the best device.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): None: selection policy. See the [handout](../ncu-profiling/lesson-25-determining-the-best-gpu.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
