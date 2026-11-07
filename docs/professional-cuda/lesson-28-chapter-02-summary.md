# Lesson 28 — Chapter 2 Summary and Exercises

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Summary |
| Subsection | N/A — summary |
| Printed pages | 65 |
| Roadmap ID | 2.5 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Concept and code connection

The chapter covers program structure, memory, thread hierarchy, launches, kernel writing, verification/error distinctions, compilation, timing concepts, matrix mappings and device management. No topic is dropped; timing and automatic numerical checking remain conceptual/adapted under your preferences. Earlier modules and standalone exercises stay preserved. Chapter 3 has not started.

## Expected observations

Your actual profiling and configuration ranking remain pending. Coverage/build completion is not proof of numerical correctness or mastery.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): All current matrix variants. See the [handout](../ncu-profiling/lesson-28-chapter-02-summary.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.

## Exercise record — printed p. 65

| Exercise | Preserved implementation and observation | Still pending |
|---|---|---|
| 1: 1023 vs 1024 threads | `exercises/chapter-02/launch_sizes.cpp`: 2051 elements, both printed first/last `3 3`; both use 3 blocks. 1023 uses 32 warps/block with one inactive lane in its final warp. | Your equal-work duration/resource comparison |
| 2: two elements/thread | `AddVectorPairs` in `vector_add_pairs.cu`, each thread handles two positions separated by blockDim.x, each bounds checked. | Matching performance captures |
| 3: integer matrix addition | `AddMatrixInteger`, separate kernel and host wrapper; current main prints 21 sums of 5. | Best launch configuration requires your sweep/captures |
| 4: 2D-grid/1D-block two elements | `AddMatrixPairs`: row from blockIdx.y; two column positions/thread, with separate bounds checks; printed 10–30. | Best configuration requires your sweep/captures |
| 5: maximum dimensions | `PrintDeviceInfo` reports block axes 1024,1024,64; max threads/block 1024; grid axes 2147483647,65535,65535. | None for the local inventory query |

## Observed build and device context

`make clean build run` and `make ptx` succeeded on 2026-11-07, Release, GNU C++
13.3.0, nvcc 13.2.86, architecture 87. The 7-by-3 float matrix mappings printed
10–30 in the intended order; the integer mapping printed 5s. Visual inspection,
not automatic numerical comparisons. CUDA wrappers remain deliberately simple.

Runtime inventory: one Orin, CC 8.7, 8 SMs, warp 32, global memory 7,912,701,952
bytes, default shared-memory-per-block property 49,152 bytes. Limits are capacities,
not instantaneous free memory or achieved performance. `nvidia-smi -L` identified
Orin; a one-second tegrastats sample reported CPU/RAM/GPU/thermal/power telemetry.
These were separate idle-context samples, not kernel-correlated measurements.

## Coverage and adaptations

All contents entries in Chapter 2 have notes, including parent introductions.
Verification is explained without adding the automatic checker you declined.
CPU/event timing is explained without adding timers. 3D thread linearization is
derived conceptually; the preserved hands-on mappings exercise 1D and 2D. Error
handling is isolated without deliberately triggering an execution memory fault.
Profiling-based configuration rankings remain pending; they are not marked complete.
All earlier kernels stay available; the Chapter 1 direct main is preserved outside
`src/`. No Chapter 3 implementation is started.
