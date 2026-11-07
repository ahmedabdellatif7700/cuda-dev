# Lesson 8 — Is CUDA C Programming Difficult?

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 1 — Heterogeneous Parallel Computing with CUDA |
| Section | Is CUDA C Programming Difficult? |
| Subsection | N/A — section-level lesson |
| Printed pages | 20–21 |
| Roadmap ID | 1.4 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run completed; user profiling/discussion pending where applicable |

## Important ideas

CUDA makes work distribution and memory placement visible. The essentials are
thread groups, memory spaces, and synchronization. Learn these deliberately rather
than adding optimizations simply because a tool displays low utilization.

- **Spatial locality:** nearby array elements occupy nearby addresses. Adjacent
  vector-add threads access adjacent floats.
- **Temporal locality:** reuse a value soon after using it. Our single-pass addition
  has little explicit reuse, so shared staging has no obvious benefit yet.
- **Memory hierarchy:** registers, caches, global storage, and programmer-managed
  shared storage have different roles. Shared physical DRAM on Orin is not CUDA
  per-block `__shared__` memory.
- **Thread hierarchy:** choose logical block/grid dimensions; the scheduler still
  determines physical placement/order.
- **Synchronization:** establish when produced data can safely be consumed. Our
  result copy completes before the CPU reads the output.

## Short code review

Read the bounds check and single addition in `VectorAddScalar`. Explain why the
check protects partial blocks, why each thread owns one output, and why the host
can print after copying back. Keep the inline PTX loads/add/store as the bridge
from the statement to intermediate operations. No new kernel is warranted.

## Tools to recognize

Use the existing build, `make ptx`, cuda-gdb when debugging, and your ncu-ui
captures when discussing kernel behavior. The book's older memory-checker name
maps to modern Compute Sanitizer. Tool availability and detailed debugging are
checked when needed; no new tool installation is part of this lesson.

## Build and observation

`make clean build run` and `make ptx` succeeded on 2026-11-06 using nvcc 13.2.86,
GNU C++ 13.3.0, Release, architecture 87. This shell needed
`export PATH="/usr/local/cuda-13.2/bin:$PATH"` to discover the installed compiler.
No persistent environment or Makefile change was made. Observed CPU total: 2656;
GPU greeting from thread 5; existing block rows retained. This was visual
inspection, not numerical assertions or timing.

See the [profiling handout](../ncu-profiling/lesson-08-is-cuda-c-programming-difficult.md).
