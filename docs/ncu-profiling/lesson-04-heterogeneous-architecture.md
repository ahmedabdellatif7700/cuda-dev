# Lesson 4 — Heterogeneous Architecture: Nsight Compute handout

Book: *Professional CUDA C Programming* (2014), Chapter 1 → Heterogeneous Computing
→ Heterogeneous Architecture (pp. 9–11), with the parent introduction on pp. 8–9.
Roadmap ID: 1.2.1. See [lesson 4](../professional-cuda/lesson-04-heterogeneous-architecture.md).

## What question are we answering?

Which parts of the program run on the CPU, which run on the GPU, and which facts
can a kernel capture establish? The kernel computations and launch geometry are
unchanged from lesson three. The new console labels explain host orchestration.

## Follow the program before opening a report

| Stage | Source location | Evidence |
|---|---|---|
| Prepare A/B | `main.cpp` | Host initialization loop; A[i] = i, B[i] = 10 |
| Produce index labels | Mapping wrapper/kernel | Separate kernel and returned indices |
| Allocate device buffers | `vector_add.cpp`, `DeviceBuffer` | Host calls CUDA allocation APIs |
| Copy A/B | `vector_add.cpp` | Two host-to-device copy calls |
| Submit addition | Host launch wrapper in `vector_add.cu` | `<<<block_count, threads_per_block>>>` |
| Add | `VectorAddScalar` | GPU instructions in the selected kernel report |
| Retrieve output | `vector_add.cpp` | Blocking device-to-host copy before return |
| Print horizontal rows | `main.cpp` | CPU reads returned output values |

These messages are not GPU timestamps. No source timer or device printf is added.

## What to inspect in ncu-ui

| Panel | Observe | Interpretation |
|---|---|---|
| Summary / kernel selection | `WriteThreadIndices`, then `VectorAddScalar` if both are collected | Separate computations, not one fused kernel |
| Launch Statistics | Each grid 2, block 32, total threads 64 | Same logical layout; no proof of identical physical SM placement |
| Source / SASS | Index/address calculation and output store versus two loads, addition, store | Connect mapping to actual arithmetic and data access |
| Occupancy / Speed of Light | Small-grid behavior, resource limits, frequency, duration | Two blocks cannot fill an eight-SM target; no improvement is expected from CPU logging |
| Memory Workload Analysis, optional | Device kernel traffic at each hierarchy level | These are kernel memory accesses, not a measurement of the two API input copies and result copy |

For addition, logical input/output traffic is `64 * 12 = 768` bytes: two float
reads and one float store per result. Mapping logically writes `64 * 4 = 256`
bytes. Actual measured hierarchy traffic can differ. Neither calculation measures
PCIe bandwidth, and our integrated Orin does not use the book's discrete-GPU
physical arrangement for these buffers.

## What a kernel report does not establish

An individual kernel duration does not include the complete allocation, input-copy,
output-copy, and CPU-printing pipeline. It does not prove CPU/GPU overlap, quantify
CPU preparation, or show that GPU offload improved application runtime. Replay and
collection can alter execution conditions; see NVIDIA's
[Profiling Guide](https://docs.nvidia.com/nsight-compute/ProfilingGuide/).

If you later want a CPU/API/copy/kernel timeline, a timeline tool such as Nsight
Systems is appropriate. It is not necessary to complete this source-level ownership
exercise, and no capture is performed for you. CPU logging adds host overhead;
do not interpret that overhead as a kernel optimization or regression.

## Code changes to consider only after discussion

- None are needed to establish the host/device roles in this lesson.
- Later repeated-work experiments could reuse device allocations across calls.
- Later memory lessons can compare explicit copies with supported mapped/managed
  allocations; do not remove copies just because physical DRAM is shared.
- Larger useful work can make performance comparisons more meaningful. Changing
  input size changes the problem, not the speed of this original 64-element task.

These are future hypotheses, not changes included or approved by this handout.

## Observation record

| Field | Observation |
|---|---|
| Revision, tool version, target conditions | Pending |
| Captured kernel names / launch geometry | Pending |
| Actual addition load/add/store instructions | Pending |
| Duration and frequency | Pending |
| Kernel traffic, if collected | Pending |
| CPU functions and completion boundary explained | Pending discussion |
| What cannot be concluded from this capture? | Pending discussion |

Retain native reports and capture settings. Output display is a teaching aid, not
an automated correctness test. User profiling and discussion remain pending.
