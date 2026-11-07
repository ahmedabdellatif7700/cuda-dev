# Lesson 3 — Computer Architecture: Nsight Compute handout

Book: *Professional CUDA C Programming* (2014), Chapter 1 → Parallel Computing →
Computer Architecture (printed pp. 6–8). Roadmap ID: 1.1.3.
See [lesson 3](../professional-cuda/lesson-03-computer-architecture.md).

## Core idea

Logical CUDA threads, warps, blocks, and grids map onto physical execution resources; they are not physical core identifiers.

**Code or evidence:** [thread_mapping.cu](../../src/thread_mapping.cu). Two blocks of 32 threads contain two warps and 64 logical threads. The returned indices identify output ownership, not SM placement.

**Original lesson commit:** `a2d5aa2`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Question and capture

How does the logical launch relate to the hardware's execution capacity?
Capture `WriteThreadIndices`. The current main launches it once, then launches `VectorAddScalar`: two blocks,
32 threads/block, 64 threads total. Each block contains one warp: two warps total.
The scalar vector-add module is restored to show the same indexing applied to
input arrays. The cyclic variant remains removed.

## What to inspect

| ncu-ui view | Expected observation | Interpretation |
|---|---|---|
| Launch Statistics | Grid 2; block 32; 64 threads | Verify that the captured launch matches the source. |
| Launch Statistics / Occupancy | Registers/thread, resource limits, theoretical occupancy | A one-warp block can reach the resident-block limit before filling available warp slots. Do not assume theoretical occupancy is 100%. |
| Occupancy / Speed of Light | Small-grid warning, limited achieved utilization | Two blocks cannot supply work to all eight SMs. This is expected, not evidence of incorrect indexing. |
| Source → SASS | Block/thread index reads, index/address calculation, conversion and output store | Relate the actual instructions to `global_index`. Compiler-generated details can differ from source expressions. |
| Header / Summary | Duration and SM frequency | Record conditions; tiny-run duration is not evidence of peak throughput. |
| Memory Workload Analysis, optional | Small store traffic | 64 float outputs mean 256 logical output bytes. Actual traffic can differ; this is not a bandwidth benchmark. |

The output has no SM identifier, and the shown grid is logical. Neither output
values nor aggregate occupancy establish the exact SM assignment or execution
order of the two blocks. GPU execution of warps does not mean all 64 threads finish
at the same instant. The host prints in index order after copying the array back.

## Candidate follow-up, after review

Compare 2 blocks × 32 threads with 1 block × 64 threads. Keep 64 output elements.
Both launches contain two warps; the second keeps them in the same block. Inspect
theoretical block/warp limits, but do not treat the occupancy calculator's predictions
as measured speedups. No timing improvement is expected or required for this lesson.

Do not add shared memory, vectorization, or arithmetic merely to increase a
utilization percentage. The experiment is intentionally small and demonstrates
thread organization, not an optimized production workload.

## Record and discuss

| Field | Observation |
|---|---|
| Revision, target and tool version | Pending |
| Grid / block / total threads | Expected: 2 / 32 / 64 |
| Warps/block and total warps | Expected: 1 and 2 |
| Duration and SM frequency | Pending |
| Registers and theoretical limiting resource | Pending |
| Theoretical / achieved occupancy | Pending |
| Indexing and store instructions | Pending |
| Which facts are logical versus physical? | Pending discussion |

Keep native reports and collection settings. Repeat captures before interpreting
small timing differences. No timers, automated numerical result checks, or profiler
captures are added to the program. Definitions and collection caveats are described
in NVIDIA's [Profiling Guide](https://docs.nvidia.com/nsight-compute/ProfilingGuide/).

## Companion vector-add capture

Capture `VectorAddScalar` as well: grid 2, block 32, 64 output sums. Compare the
mapping kernel's index store with addition's two input loads, addition, and output
store. Both calculate global indices independently. The host's horizontal display
connects the same logical indices across launches; it does not track physical
threads or assert that both kernels use identical SM placement. Duration comparisons
on these tiny kernels do not establish general performance rankings.
