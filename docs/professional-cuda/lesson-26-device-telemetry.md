# Lesson 26 — Using nvidia-smi to Query GPU Information

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Managing Devices |
| Subsection | Using nvidia-smi to Query GPU Information |
| Printed pages | 63–64 |
| Roadmap ID | 2.4.3 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Concept and code connection

The book uses nvidia-smi for inventory/utilization. Tool availability differs on Jetson. Record what nvidia-smi actually reports; use available tegrastats for system CPU/GPU/memory/thermal context. Do not assume support merely because a binary is on PATH. A sampled utilization percentage is not the same as per-kernel occupancy or throughput. Runtime properties remain the reliable source for launch limits.

## Expected observations

Record observed clocks/power/thermal context with captures. Do not automatically change clocks or power modes. Missing telemetry is a recorded limitation, not a reason to invent values.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): None: host telemetry. See the [handout](../ncu-profiling/lesson-26-device-telemetry.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
