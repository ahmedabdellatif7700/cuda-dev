# Lesson 1: scalar and vectorized vector addition

## Capture context

These observations come from the Nsight Compute screenshots supplied during the learning session on 2026-11-01. The kernels ran on an NVIDIA Orin; the UI was used on the host. The reports show 8 SMs and approximately 306 MHz SM frequency for both captures. These are measurements at the reported conditions, not the GPU's maximum performance.

The scalar and vectorized results came from separate processes. Raw reports, exact capture settings, and repeated measurements are not stored here. Conclusions about small differences are provisional.

## Observed results

| Metric | VectorAddScalar | VectorAddFloat4 |
|---|---:|---:|
| Duration | 1.60 ms | 1.55 ms |
| Elapsed cycles | 491,024 | 474,197 |
| Blocks | 16,385 | 4,096 |
| Threads per block | 256 | 256 |
| Launched threads | 4,194,560 | 1,048,576 |
| Registers per thread | 16 | 22 |
| Compute throughput | 21.13% | 7.76% |
| Memory throughput | 91.17% | 90.25% |
| L1/TEX throughput | 19.05% | 18.23% |
| L2 throughput | 91.17% | 90.25% |
| Theoretical occupancy | 100% | 100% |
| Achieved occupancy | 83.34% | 91.59% |
| Theoretical active warps per SM | 48 | 48 |
| Achieved active warps per SM | 40.00 | 43.96 |
| Waves per SM | 341.35 | 85.33 |
| Static/dynamic shared memory requested per block | 0 / 0 bytes | 0 / 0 bytes |

Using the rounded durations, vectorization reduced time by about 3.1%, or a 1.03x speedup. Repeat captures before treating this small difference as reliable.

The vectorized grid in the screenshot has 4,096 blocks. The current code uses 4,194,307 elements and launches enough threads for both full float4 groups and the three tail elements; that also gives 4,096 blocks. An earlier ceil(count / 4) launch calculation would give 4,097 blocks for this input. Grid dimensions alone do not establish the capture's exact input size or source revision.

## What each GPU thread does

The scalar kernel assigns one float addition to each thread. Adjacent threads access adjacent floats, so accesses within a warp are already coalesced.

The vectorized kernel assigns four adjacent floats to each thread. It needs about one quarter as many threads for the same input. Its pointers must be aligned for float4 (16 bytes); cudaMalloc provides sufficient alignment for the allocation base. Arbitrary pointer offsets may break that alignment.

Vectorization changes the instruction width and work per thread. It does not reduce the required input or output data: each result still requires two float reads, one addition, and one float write. That is 12 logical bytes per output and about 1/12 floating-point operation per byte. Actual traffic at each cache or memory level depends on caching and transaction behavior.

## What the generated instructions show

The vectorized Source/SASS screenshot contains:

```text
LDG.E.128   # Read four floats from A into registers
LDG.E.128   # Read four floats from B into registers
FADD        # Add one component
FADD
FADD
FADD
STG.E.128   # Write four output floats
```

The .128 suffix means a 128-bit memory instruction per participating thread, equivalent to four 32-bit floats. The compiler generated wide loads and stores, followed by four separate additions. float4 is not a single instruction that adds all four components.

The scalar SASS was not supplied, so its instruction sequence remains to be checked directly. Wider per-thread instructions also do not imply four times fewer physical memory transactions: scalar warp accesses can already be combined by the memory system.

## Interpreting the bottleneck

Both captures have high L2 throughput and much lower compute throughput. This supports the hypothesis that memory-system throughput, particularly L2, limits these executions. Wider instructions give little runtime benefit when data movement is already the main constraint.

The Memory Throughput summary is a composite throughput indicator; it is not a cache hit rate or a direct statement of DRAM bandwidth use. Here it matches L2 throughput. Inspect Memory Workload Analysis, including DRAM traffic, cache hit rates, and request/sector counts, before claiming DRAM saturation or identifying the precise limiting path.

Compute throughput is a hardware utilization metric, not a score to maximize independently of runtime. The lower value for float4 does not mean fewer output additions were computed. The screenshots alone do not establish which instruction changes caused that reduction.

## Warps, registers, and occupancy

A block of 256 threads contains 8 warps of 32 threads. The reported theoretical limit is 48 resident warps per SM, equivalent to 6 such blocks. These are resident blocks; the thousands of blocks in the grid are scheduled over time, not all at once.

Each vectorized thread holds more values, consistent with the increase from 16 to 22 registers per thread. This increase did not reduce theoretical occupancy in these captures: both remain at 100%.

Achieved occupancy measures average resident warps relative to the supported maximum. It is not the fraction of threads actively executing arithmetic on every cycle. The vectorized result has higher achieved occupancy, but these measurements do not prove that this caused its small speedup. Occupancy alone does not determine performance.

The scalar report's estimated local speedup of 16.66% for occupancy is an analysis estimate, not a promised improvement. Likewise, the absence of a quantified optimization suggestion for float4 does not prove that the kernel is optimal.

## Next measurements

1. Repeat both captures with the same build, input size, collection settings, and comparable clock/power conditions. Record several durations and their variation.
2. Inspect scalar SASS beside float4 SASS. Compare load/store widths and executed instruction counts.
3. Inspect Memory Workload Analysis to distinguish L2 pressure from DRAM limits.
4. Try 128, 256, and 512 threads per block, changing only block size. Compare duration, occupancy, and registers.
5. Keep correctness checks for tiny inputs and tails, especially with very small blocks. A launch-size bug discovered during testing left float4 tail elements unwritten with one-thread blocks; the current launch covers both vector groups and tail work.

The current main calls the scalar example and then the vectorized example, with one launch each and no warmup loop. Plain `make run` validates both. For profiler captures, use the kernel duration reported by Nsight Compute; application CUDA-event timings collected under profiling can include tool overhead.

## Metric reference

See NVIDIA's [Nsight Compute Profiling Guide](https://docs.nvidia.com/nsight-compute/ProfilingGuide/) for throughput aggregation, occupancy definitions, and profiling effects. Screenshot values above are our observations; bottleneck explanations are interpretations to test with further measurements.
