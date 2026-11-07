# Lesson 9 — Chapter 1 Summary and Exercises

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 1 — Heterogeneous Parallel Computing with CUDA |
| Section | Summary |
| Subsection | N/A — section-level lesson |
| Printed pages | 21–22 |
| Roadmap ID | 1.5 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run completed; user profiling/discussion pending where applicable |

## Core idea

Chapter 1 connects parallel work, architecture, host/device roles, and the first reproducible CUDA program.

**Code or evidence:** [README.md](../../exercises/chapter-01/README.md). Preserved greeting variants separate launch, completion, and teardown. Notes supply architecture/partition reasoning that does not require an invented kernel.

**Original lesson commit:** `72f503e`. This note explains that lesson;
the current main may have advanced to a later experiment.

## Chapter recap

We covered sequential/dependent work, data/task parallelism, contiguous/cyclic
partitioning, architecture classes, threads/warps/blocks, host/device cooperation,
the CUDA platform, a first kernel, locality, and development tools. Existing notes
for lessons 1–4 retain their detailed discussions. Lessons 5–8 are intentionally brief.

The current program ties these together: CPU greeting → GPU greeting → prepare
inputs → mapping and addition kernels → copy back → CPU sum → horizontal block
rows. Its launch sizes are teaching examples, not optimized production settings.
No timers or numerical result checks were introduced.

## Chapter exercises (printed p. 22)

### 1 — Partitioning sketches

Let x vary across columns, y across rows, and z across depth slices. “Block” below
means a data chunk, not necessarily a CUDA thread block.

| Requested pattern | Small explicit example |
|---|---|
| Block along x for 2D data | For width 6 and workers 0/1/2, each row has owners `0 0 1 1 2 2`; workers own two-column strips |
| Cyclic along y for 2D data | For 6 rows and 3 workers, row owners are `0 1 2 0 1 2`; worker 0 visits rows 0 and 3, across all columns |
| Cyclic along z for 3D data | For 6 slices and 3 workers, slice owners are `0 1 2 0 1 2`; worker 0 visits z = 0 and 3, across each slice |

For a row-major 3D array, flatten with `index = (z * height + y) * width + x`.
Work ownership is separate from physical layout; cyclic y/z ownership does not
require cyclic storage. These are paper exercises, not additional kernels.

### 2–4 — Completion and compiler architecture experiments

Standalone ten-thread greeting variants were compiled/run under `/tmp` on
2026-11-06 with nvcc 13.2.86. Repository Make/CMake targets remain unchanged.

| Variant | Actual observation in this run |
|---|---|
| No reset and no explicit wait | Exit 0, no greeting lines observed |
| Replace reset with `cudaDeviceSynchronize()` | Exit 0, ten greeting lines observed |
| Original reset-style completion | Exit 0, ten greeting lines observed |
| Omit compiler architecture flag, retain synchronize | Compiled and ran, ten greeting lines observed |

Without a wait, buffered output/completion is not assured; do not treat this one
run's absence as a universal result. Synchronization waits; reset also destroys
device context resources, so it is not a replacement for routine synchronization
in a reusable application. The successful default-architecture build establishes
only behavior of this installed toolchain; keep explicit architecture 87 in this
repository. Do not infer its default target from success alone.

### 5 — nvcc suffixes

CUDA source: `.cu`; C: `.c`; C++: `.cc`, `.cxx`, `.cpp`; PTX: `.ptx`; device images:
`.cubin`, `.fatbin`; link inputs: `.o`, `.obj`, `.a`, `.lib`, `.res`, `.so`.
Some are forwarded to the linker rather than compiled as source. See
[NVIDIA's supported-input table](https://docs.nvidia.com/cuda/cuda-compiler-driver-nvcc/#supported-input-file-suffixes).

### 6 — Only GPU thread 5 prints

The repository's `PrintGpuGreeting` uses `if (threadIdx.x == 5)` inside a ten-thread
launch. Output observed: `Hello World from GPU thread 5!` after the CPU greeting.
This is conditional participation, not a launch containing only thread 5.

## Suggested readings and chapter status

Review the Appendix's Chapter 1 reading group (p. 477) as background on massively
parallel computing and why GPU computing is useful. Its historical slides are
supplementary; use current documentation for API behavior. No downloads are needed.

Chapter 1 topic coverage, concise exercises, implementation, and build/run work
are complete. **User profiling/discussion remains pending where not supplied**;
completion here does not certify understanding or close those observations.
Next: Chapter 2 — CUDA Programming Model (p. 23). Stop here before starting it.

## Build and observation

`make clean build run` and `make ptx` succeeded on 2026-11-06 using nvcc 13.2.86,
GNU C++ 13.3.0, Release, architecture 87. This shell needed
`export PATH="/usr/local/cuda-13.2/bin:$PATH"` to discover the installed compiler.
No persistent environment or Makefile change was made. Observed CPU total: 2656;
GPU greeting from thread 5; existing block rows retained. This was visual
inspection, not numerical assertions or timing.

See the [profiling handout](../ncu-profiling/lesson-09-chapter-01-summary.md).

## Preserved experiment sources

All current Chapter 1 modules remain under `src/`, including the restored
`vector_add_cyclic.cu` and `VectorAddCyclic` host entry point. The simple main
runs the current combined exercise; earlier variants can be called directly.
Standalone completion/default-architecture experiments and their captured output
are preserved under [exercises/chapter-01](../../exercises/chapter-01/README.md).
They have independent entry points and stay outside the application's source glob.
Conceptual architecture classes and partition sketches remain in the lesson notes;
there is no invented GPU kernel for a concept that does not need one.
