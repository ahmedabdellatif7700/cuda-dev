# Lesson 5 — Paradigm of Heterogeneous Computing

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 1 — Heterogeneous Parallel Computing with CUDA |
| Section | Heterogeneous Computing |
| Subsection | Paradigm of Heterogeneous Computing |
| Printed pages | 12–13 |
| Roadmap ID | 1.2.2 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run completed; user profiling/discussion pending where applicable |

## Concept

CPU and GPU complement each other. Choose placement using useful parallelism,
data size, control flow, and data-movement costs—not simply “GPU is faster.”
Small/irregular control work often suits the CPU; abundant independent arithmetic
can suit the GPU. The book's thread-count examples are historical, not Orin limits.
CPU operating-system threads and GPU threads/warps have different scheduling models.

## Simple code connection

The existing GPU kernel adds A and B. After its blocking result copy returns,
`main.cpp` performs a plain CPU loop:

```cpp
float total = 0.0f;
for (int index = 0; index < element_count; ++index)
    total += output[index];
```

The displayed total is **2656** for sums 10 through 73. This is useful CPU follow-up
work, not an automated correctness check. A 64-element CPU sum keeps this exercise
simple; it does not prove CPU reduction is always better. GPU reductions come later.
The CPU sum has no kernel PTX. The existing `ld.global.f32`, `add.f32`, and
`st.global.f32` annotations describe the GPU addition only.

## Takeaway

Trace CPU preparation → GPU addition → CPU consumption. Do not infer pipeline
speedup from one kernel duration. No new kernel is needed for this concept.

## Build and observation

`make clean build run` and `make ptx` succeeded on 2026-11-06 using nvcc 13.2.86,
GNU C++ 13.3.0, Release, architecture 87. This shell needed
`export PATH="/usr/local/cuda-13.2/bin:$PATH"` to discover the installed compiler.
No persistent environment or Makefile change was made. Observed CPU total: 2656;
GPU greeting from thread 5; existing block rows retained. This was visual
inspection, not numerical assertions or timing.

See the [profiling handout](../ncu-profiling/lesson-05-paradigm-of-heterogeneous-computing.md).
