# Lesson 27 — Setting Devices at Runtime

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Managing Devices |
| Subsection | Setting Devices at Runtime |
| Printed pages | 64–65 |
| Roadmap ID | 2.4.4 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Concept and code connection

cudaSetDevice selects the current logical device for the host thread. CUDA_VISIBLE_DEVICES can mask/reorder visible devices, so logical index 0 is not a permanent physical identifier. Our helper selects device 0 only when at least one device is visible. The isolated error exercise tries device_count as an invalid ID. Select a device before allocating its buffers; memory ownership remains tied to the allocating context/device.

## Expected observations

Capture target identity and logical selection. No extra GPU kernel is required to demonstrate the selection API.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): None: device selection. See the [handout](../ncu-profiling/lesson-27-setting-devices.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
