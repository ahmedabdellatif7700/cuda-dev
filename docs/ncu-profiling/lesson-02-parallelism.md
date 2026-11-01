# Lesson 2 — Parallelism: Nsight Compute handout

Book: *Professional CUDA C Programming* (2014), Chapter 1 → Parallel Computing →
Parallelism (printed pp. 4–5). Roadmap ID: 1.1.2.
See [lesson 2](../professional-cuda/lesson-02-parallelism.md) for theory and code.

## Question and baseline

Does reusing threads through cyclic ownership change execution cost for the same
vector addition? Keep `VectorAddScalar` as the baseline. Compare with
`VectorAddCyclic` at the same n and 256 threads/block. The new variant caps the
grid at 64 blocks. It changes both grid size and per-thread iteration count;
timing differences alone cannot isolate which effect caused a change.

## Select matched launches

The application runs scalar then cyclic for one selected input size, currently
65,536. This produces two kernel launches: scalar with 256 blocks and cyclic
with 64 blocks. Change `element_count` in `main.cpp` to explore another size.
Zero launches neither kernel. Profiler result IDs are not input-size labels.

The following table predicts launch geometry for possible input settings; it is
not an automatic sweep:

| n | Scalar blocks | Cyclic blocks | Cyclic grid stride | Cyclic outputs per launched thread |
|---|---:|---:|---:|---|
| 1 / 16 / 31 / 33 | 1 | 1 | 256 | 0 or 1 |
| 257 | 2 | 2 | 512 | 0 or 1 |
| 1,024 | 4 | 4 | 1,024 | 1 |
| 65,536 | 256 | 64 | 16,384 | 4 |
| 4,194,307 | 16,385 | 64 | 16,384 | 256; first three threads do 257 |

Start with the two largest sizes. They expose the difference in work ownership.
Small sizes help explain loop setup and partial participation, but may be noisy.

## Monitor and interpret

| ncu-ui panel | Observe | Prediction / interpretation |
|---|---|---|
| Summary / header | Kernel name, duration, grid, block, SM frequency | Compare equal n and comparable target conditions; no speedup is assumed. |
| Launch Statistics | Grid size, waves/SM, registers/thread | Cyclic uses fewer blocks for large n; compute and memory work remain logically equal. |
| Occupancy | Theoretical limiting resources and achieved occupancy | Added loop state may change registers; fewer blocks may change residency/tail behavior. Neither direction alone proves a speedup. |
| Source / SASS and Instruction Statistics | Loop condition, index increment, loads, addition, store; executed instructions if available | Cyclic adds looping but amortizes thread setup over several elements. Static instruction count alone is insufficient. |
| Memory Workload Analysis | Actual bytes/sectors and cache behavior | Both kernels use adjacent-lane accesses. Cyclic ownership is not a strided-lane access pattern. Both logically transfer 12 bytes/output. |
| Scheduler/Warp State, if needed | Eligible warps and dependency stalls | Enough resident independent work can hide latency; a smaller grid is not automatically better. |

For the reported eight-SM target, 64 blocks supply multiple blocks per SM in
aggregate, but neither balanced placement nor full residency is guaranteed. If
resource limits still allow six blocks/SM, 64 blocks represent about 64/48 = 1.33
waves. Recheck actual limits for the cyclic kernel before using that estimate.

## What code changes might the evidence justify?

No further changes are included in this experiment. Propose and approve one at a time:

- Change only `max_blocks` in `main.cpp`, for example 32/64/128, keeping n and
  threads fixed. Compare duration, waves, and achieved occupancy.
- Later compare 128/256 threads/block with the grid cap fixed. This changes the
  stride and work/thread as well as residency; explain both effects.
- If exact launch identification is difficult, temporarily run a single existing
  n from `main.cpp` and capture both kernels.
- If cyclic is slower, investigate loop instructions, register use, and available
  parallelism before attempting unrolling or vectorization. Those are later topics.

## Comparison discipline

Use the same build, input, collected sections, replay/cache configuration, and
comparable clocks/temperature. The application has no warmup or internal timers.
Separate calls use separate allocations, and fixed launch order can affect state;
repeat captures before interpreting a small difference. Duration refers to kernels,
not allocation/copies or the whole application. Profiling does not validate output.
For metric definitions and replay considerations, see NVIDIA's
[Profiling Guide](https://docs.nvidia.com/nsight-compute/ProfilingGuide/).

## Observation record

| Field | Scalar | Cyclic |
|---|---|---|
| Revision / n / threads / blocks | Pending | Pending |
| Duration and repeated-capture variation | Pending | Pending |
| SM frequency / target conditions | Pending | Pending |
| Registers/thread | Pending | Pending |
| Theoretical / achieved occupancy | Pending | Pending |
| Waves/SM | Pending | Pending |
| Executed instruction evidence | Pending | Pending |
| Memory traffic and cache evidence | Pending | Pending |

Explain which observations follow from ownership and which remain hypotheses.
User profiling and discussion are pending.
