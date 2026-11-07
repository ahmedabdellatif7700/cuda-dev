# Lesson 1 — Nsight Compute profiling handout

Book: *Professional CUDA C Programming* (2014), Chapter 1 — Heterogeneous Parallel Computing with CUDA → Parallel Computing → Sequential and Parallel Programming (printed p. 3).

Companion to [lesson 1](../professional-cuda/lesson-01-sequential-and-parallel-programming.md). Kernel: `VectorAddScalar`.

## Core idea

Independent outputs can run concurrently; dependent operations must respect their order.

**Code or evidence:** [vector_add.cu](../../src/vector_add.cu). Output 37 depends on A[37] and B[37], not output 36. Each thread can therefore own one addition.

**Original lesson commit:** `089a885`. This note explains that lesson;
the current main may have advanced to a later experiment.

## 1. Start with a question

For this lesson: **how does the amount of independent work change GPU usage?**
First compare existing input sizes with the block size fixed at 256. This requires
no source changes. Keep optimizations as proposals until we review the evidence
and you approve the next change.

## 2. Identify the exact launch

In the Summary tab, select `VectorAddScalar`; double-click the result to inspect
its Details. Record the input size, grid, and block dimensions before interpreting
percentages. In the current application, the kernel launches in this order:

| Nonempty launch order | Input elements | Blocks at 256 threads/block | Useful threads in final block |
|---|---:|---:|---:|
| 1 | 1 | 1 | 1 |
| 2 | 16 | 1 | 16 |
| 3 | 31 | 1 | 31 |
| 4 | 33 | 1 | 33 |
| 5 | 257 | 2 | 1 |
| 6 | 1,024 | 4 | 256 |
| 7 | 65,536 | 256 | 256 |
| 8 | 4,194,307 | 16,385 | 3 |

Zero input does not launch. These are application launch positions, not guaranteed
Nsight result IDs: filters can omit launches and result numbering can differ.
A one-block grid alone cannot distinguish the first four inputs. Check captured
arguments if available, or correlate the complete launch sequence. If that remains
ambiguous, a proposed follow-up is to run just one existing input size from
`main.cpp`; do not assume which input produced the screenshots.

## 3. Read these panels in order

| Where in ncu-ui | What to record | How to reason about this kernel |
|---|---|---|
| Summary / header | Kernel, Duration, SM Frequency, grid/block dimensions | Establish which workload and operating conditions you are comparing. Duration is kernel time, not complete program time. |
| Details → Launch Statistics | Grid Size, Block Size, Threads, Waves per SM | Ask whether there are enough independent blocks to feed the device. A 256-thread block contains 8 warps. |
| Details → Occupancy | Theoretical versus achieved occupancy; registers/thread; limiting resources | Separate resource capacity from the work actually supplied. Do not change registers merely because achieved occupancy is low. |
| Details → GPU Speed Of Light Throughput | Compute, Memory, L1/TEX, L2 throughput | Use as an initial direction for investigation. A tiny launch can have low percentages because too little work was supplied. |
| Details → Memory Workload Analysis, when collected | Actual bytes, sectors/requests, cache behavior at each level | Investigate memory only after identifying the workload. Adjacent scalar threads already access adjacent floats. |
| Source → SASS | Bounds check/exit, address calculation, loads, addition, store | Relate instructions to the kernel. Static disassembly is not evidence that every instruction executed for every thread. |
| Details → Scheduler/Warp State, if needed later | Eligible warps, issue activity, dependency/barrier stalls | Investigate persistent issues on substantial workloads; tiny launches are poor foundations for detailed tuning. |

Section labels and available metrics depend on the installed tool/device. Start
with Launch Statistics, Occupancy, and Speed of Light rather than collecting every
possible metric. The [NVIDIA profiling guide](https://docs.nvidia.com/nsight-compute/ProfilingGuide/)
explains metric definitions, resource residency, and replay behavior; the
[NVIDIA Compute Triage guide](https://docs.nvidia.com/nsight-compute/ComputeTriage/)
provides the small-workload checks used here.

## 4. Interpret your first capture

These are observations from your screenshots, not a saved raw report. All five
screenshots show the same selected result, so they represent one captured launch,
not five independent timing samples.

| Observed value | Interpretation for this capture |
|---|---|
| Grid 1; block 256 | One block can execute on only one of the 8 reported SMs. Other SMs cannot receive additional blocks from this launch. |
| Duration 15.55 µs; frequency 302.34 MHz | A measurement at these reported conditions. It does not establish peak performance or prove why this duration occurred. |
| 16 registers/thread; 0 static/dynamic shared bytes | No evidence here that register pressure or explicit shared allocation needs optimization. Driver-reserved shared storage is separate from kernel-requested storage. |
| Theoretical occupancy 100%; theoretical active warps/SM 48 | The configuration could fit 6 blocks of 8 warps on an SM if enough blocks were available. The grid supplies only one block for the whole GPU. |
| Waves per SM about 0.02 | Consistent with roughly 1 / (8 SMs × 6 resident blocks/SM) = 0.0208 waves for this configuration. |
| Achieved occupancy 11.16%; active warps/SM 5.36 | Numerically consistent with 5.36 / 48. This active-cycle occupancy metric does not mean 11.16% of total GPU compute capacity was used or that all SMs had that many warps. |
| Compute throughput 0.56%; memory throughput 0.90% | Consistent with an underfilled workload; insufficient to diagnose a compute or DRAM bandwidth bottleneck. |
| Small Grid estimated speedup 87.5% | Tool guidance, not a measured or guaranteed speedup. More blocks can distribute work; inventing unnecessary work is not an optimization. |

The occupancy plots for changed block size/register/shared usage are **calculated
capacity scenarios**. They are not benchmark results. The graph cannot tell you
which configuration will run fastest without an actual comparison.

The visible SASS includes the bounds check/exit and two global loads. Scroll to
locate the floating-point addition and output store as well. Do not infer Tensor
Core acceleration merely from a pipeline label or an unfamiliar mnemonic in the
instruction view; examine the actual operation and executed instruction evidence.

## 5. Make the next observation before changing code

Capture the 65,536-element and 4,194,307-element launches using the same build and
collection settings. Their grids are 256 and 16,385 blocks. Compare each with the
small-grid result and repeat selected captures to assess timing variation.

Predict before capturing:

- More blocks allow more SMs to participate and provide multiple scheduling waves.
- Utilization may rise; it is not guaranteed to rise monotonically.
- Total duration may increase because more outputs are computed. Compare
  `elements / duration` as well as duration when workload size changes.
- Memory traffic becomes a more useful question once enough work is available.

A larger problem is a scaling experiment, not a speedup of the original small
problem. For an optimization comparison, keep the number of outputs fixed.

## 6. Let observations determine proposed code changes

These are candidates for discussion, not changes already approved or implemented.

| Observation | Change to consider | What to compare afterward |
|---|---|---|
| Cannot identify the captured input | In `main.cpp`, temporarily run one input size | Unambiguous input-to-report mapping; unchanged kernel |
| A meaningful workload has too few blocks | In `main.cpp`, compare 128 versus 256 threads at the same input size | Grid size, duration, throughput, and achieved occupancy; smaller blocks are not guaranteed to help |
| Real application has many tiny independent jobs | Later, consider batching useful independent jobs | Completion latency and work throughput for the same real jobs; requires a separate design |
| Partial final block | Keep `if (i < n)` in `vector_add.cu` | Edge threads exit safely; the three useful outputs in the large input’s final block remain covered |
| Larger kernel has high memory-system activity | Inspect traffic first; preserve contiguous accesses | Which level is busy, actual bytes, sectors, and time; do not immediately add shared memory |
| Instruction cost matters after memory analysis | Later, compare vectorized loads or more work/thread in a separate kernel file | Equal output count, alignment/tails, instruction mix, registers, traffic, duration |
| Higher register use actually limits residency | Later, reduce unnecessary live state or try another block size | Residency and spills as well as runtime; arbitrary register caps can hurt |
| Measured run differs in frequency/temperature | Repeat under comparable recorded conditions before attributing changes to code | Repeatability; no power or clock changes are made automatically |

For the current scalar addition, each output logically reads two floats and writes
one: **12 bytes/output and one addition**. Compute logical effective bandwidth as
`12 × n / kernel_seconds`, expressed in GB/s by dividing by 10^9. This is useful
algorithmic accounting, not a direct DRAM bandwidth measurement: caches, replay,
and transaction behavior affect traffic at each level. The memory summary
percentage is neither a cache hit rate nor proof of DRAM saturation.

Shared memory has no obvious reuse to exploit here: staging each value once may
add instructions and synchronization without reducing required input/output data.
Likewise, replacing already coalesced scalar accesses with float4 does not promise
fourfold speedup. Those are later hypotheses to test, not first responses to a
Small Grid message.

## 7. Keep comparisons reproducible

For each report, record revision, input, block size, launch selection, tool version,
selected sections, replay/cache settings, reported clocks, power mode, temperature,
and competing workload. Save the native report using the UI so it can be reopened;
screenshots alone hide metric definitions and collection context. Profiling may
replay work and affect cache state; do not equate collection wall time with kernel
duration or compare unlike collection settings as if they were identical runs.

Use the UI comparison facility to compare matched captures. Separate two questions:
**scaling** compares different input sizes; **optimization** compares the same work
before and after one code change. No timer or numerical comparison is added to the
program by this handout. Successful execution still does not establish numerical
correctness.

## 8. Fill in a short observation record

| Field | Small launch | Larger launch / proposed variant |
|---|---|---|
| Input elements and source revision | Unknown in supplied screenshots | Pending |
| Block size / grid size | 256 / 1 | Pending |
| Duration and variation across captures | 15.55 µs; variation unknown | Pending |
| SM frequency | 302.34 MHz | Pending |
| Registers/thread | 16 | Pending |
| Theoretical / achieved occupancy | 100% / 11.16% | Pending |
| Waves per SM | 0.02 | Pending |
| Compute / memory throughput | 0.56% / 0.90% | Pending |
| Actual L1/L2/DRAM traffic, if collected | Not supplied | Pending |
| Prediction and observed explanation | Too few blocks to fill the GPU | Pending |
| One proposed change and its acceptance criterion | First obtain larger-grid comparison | Pending |

The immediate goal is to explain why the one-block launch underuses the device
and how the existing larger launches change that behavior. We will choose any
code modification together after examining that comparison.
