# Lesson 7 — Hello World from GPU

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 1 — Heterogeneous Parallel Computing with CUDA |
| Section | Hello World from GPU |
| Subsection | N/A — section-level lesson |
| Printed pages | 17–19 |
| Roadmap ID | 1.3 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run completed; user profiling/discussion pending where applicable |

## Concept and code

`__global__` marks a kernel. The host launches it with `<<<blocks, threads>>>`.
`GpuGreeting()` launches **one block of ten threads**, and the kernel lets only
local thread 5 print. This also covers Chapter 1 exercise 6.

- `src/gpu_greeting.cu`: `PrintGpuGreeting` plus its small host launch wrapper.
- `include/GpuGreeting.h`: declares the host call.
- `main.cpp`: CPU greeting, GPU greeting, then the existing mapping/addition work.

`cudaDeviceSynchronize()` waits before the wrapper returns. Device printf is
buffered; it is a teaching/debugging mechanism, not a timing or scheduling probe.
We do not reset the device between lessons or invalidate live allocations.

## Relevant PTX

The exact generated thread-index read and branch appear beside the corresponding
kernel condition. `printf` generates a `vprintf` call with argument setup; do not
study that entire sequence yet. Ten threads launch even though only one prints.
Other threads skip the printing path. Block/thread IDs do not reveal SM placement.

## Typical CUDA program structure

Allocate GPU storage → copy inputs → launch → copy output → release storage.
The greeting needs no array allocation; our vector-add wrapper shows all five
steps, with allocation ownership releasing storage when the function returns.
The book's standalone `sm_20` command is historical; this repository targets 87.

## Build and observation

`make clean build run` and `make ptx` succeeded on 2026-11-06 using nvcc 13.2.86,
GNU C++ 13.3.0, Release, architecture 87. This shell needed
`export PATH="/usr/local/cuda-13.2/bin:$PATH"` to discover the installed compiler.
No persistent environment or Makefile change was made. Observed CPU total: 2656;
GPU greeting from thread 5; existing block rows retained. This was visual
inspection, not numerical assertions or timing.

See the [profiling handout](../ncu-profiling/lesson-07-hello-world-from-gpu.md).
