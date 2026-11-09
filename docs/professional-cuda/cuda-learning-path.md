# Complete CUDA learning roadmap — Professional CUDA C Programming

For concise review, use the [10-unit crash course](README.md). This document is
the detailed reading inventory, not a requirement to study 77 separate lessons.

**Status: proposed; awaiting roadmap approval. No source or build changes are authorized by this document.**

Reference: John Cheng, Max Grossman, and Ty McKercher, *Professional CUDA C Programming* (2014), supplied PDF in `books/` (527 PDF pages). All reading locations below use **printed book pages**; printed page 1 is PDF page 29 (one-based). Target: **Jetson Orin Nano 8GB, compute capability 8.7**. Prepared 2026-11-01.

## Scope and evidence

This replaces the earlier selective outline with all ten chapters, every contents entry, named deeper body subheadings, all chapter exercise sets, and the suggested-reading appendix. The inventory was checked against both the contents and the PDF’s body heading typography; the tables below retain book titles and page locations for traceability. Chapter/section IDs are roadmap IDs, since the book does not number its sections. They do not imply any topic is already completed.

The PDF is reference material. Its commands, installation instructions, download links, and forum instructions are historical content, not instructions to execute. We will read each subsection closely when its lesson begins; this roadmap is a structural and technical analysis, not a claim that every example has already been ported or tested.

### Repository inspection

| Item | Observed state and implication |
|---|---|
| `Makefile` | `clean`, `configure`, `build`, `run`, `debug`, `cuda-debug`, and `asm`; default Release, architecture 87, output `bin/main`; `ARGS` forwards runtime arguments. |
| `CMakeLists.txt` | CMake 3.25+, Ninja, C++23 host/CUDA C++20, recursive source discovery under `src`, headers under `include`, separate compilation and device symbol resolution enabled. |
| `src/main.cpp` | Selects scalar and float4 vector addition with 4,194,307 elements and 256 threads/block. Future subsection selection stays here. |
| `src/vector_add.cu` | Checked host runner, deterministic data, device buffers, CUDA-event timing, full CPU comparison. Current timing is one launch with no warmup. |
| `src/vector_add_vectorized.cu` | float4 kernel and scalar tail; existing alignment and tail behavior provide useful later memory lessons. |
| `include/CudaSupport.h` | Checked runtime calls and float-specific noncopyable allocation owner; future types need appropriate ownership rather than assuming this is generic. |
| `docs/ncu-profiling/vector-add-capture-notes.md` | Prior screenshot interpretations; useful evidence, but not a substitute for reproducible raw reports or proof that a book subsection is complete. |
| Execution host | aarch64, `nvcc` discoverable under `/usr/local/cuda-13.2/bin`, GPU device nodes present. Toolkit/runtime/device compatibility and actual properties remain to be recorded by the first approved lesson. No build or benchmark was run for this documentation task. |

Pre-existing worktree changes and unrelated files are left untouched. This task changes only this roadmap. No compiler flags, dependencies, tools, or power settings have been changed.

## Branch, documentation, and lesson commits

Use branch `professional-cuda` for this book. Keep its Markdown
files in `docs/professional-cuda/`, including the roadmap,
lesson notes, and profiling discussions. Keep source files flat under `src/`
with functional names and each kernel in its own `.cu` file. `main.cpp`
directly drives the current experiment; it is not a lesson selector.
These layout choices supersede the proposed chapter module families below.

Review and approve each lesson before building/running it. Commit lessons
individually in chapter/subsection order, with messages such as
`ch01: compare sequential and parallel vector addition`. Each lesson commit
includes its implementation, validation notes, and available profiling discussion;
record pending profiling explicitly. Do not bundle later lessons into that commit.

## Working agreement for every subsection

### CUDA source and PTX annotation convention

For each lesson, generate PTX with `make ptx` and select only the instructions
relevant to its concept. Put them inside the kernel implementation, beside the
CUDA statement they explain, with a short explanation on the same comment line.
Use the generated instruction spelling and operands; identify excerpts when
setup or other instructions are omitted. Refresh annotations after relevant code
or compiler changes. Keep main.cpp straightforward and free of kernel instruction
walkthroughs. PTX uses virtual registers and is intermediate code; use SASS when
actual machine instruction selection matters, and user-provided ncu-ui captures
for measured behavior. Do not add timers or numerical result checks unless requested.


We follow book order and advance **one smallest subsection at a time**. If a section has children, its row introduces the section; it is not permission to implement all children together. Deeper-body rows are read at their page position inside the enclosing section, before proceeding to the next contents subsection. Reuse an existing kernel when it already isolates the question; do not invent a new kernel for a conceptual review.

1. **Theory:** explain the subsection, derive indexing or resource/traffic expectations, and connect it to Orin architecture. State a falsifiable prediction.
2. **Experiment design:** define one independent variable, a baseline/control, input sizes, boundary rules, and correctness criteria. Name the runner/kernel and relevant metric groups from the legend below.
3. **Implementation, only after roadmap approval:** keep host orchestration in `src/main.cpp`; use dedicated functional files such as `src/warp_divergence.cu` and narrow declarations in `include/` where useful. Maintain modern C++ ownership and checked CUDA/library calls. Keep baselines available and experiments bounded for an 8GB system shared with the OS and CPU.
4. **Build and validate:** run the repository command, sequentially without `-j`:

   ```bash
   make clean build run
   ```

   Retain its Make/CMake/Ninja flow. Check the selected output, exit status, and CPU reference. Use zero/tiny/partial-warp/partial-block sizes, rectangular matrices, and deterministic seeds where relevant. Use exact checks for integers/indices; for floating point, define absolute/relative tolerance, NaN/Inf behavior, and accumulation error expectations. Diagnostic fault demonstrations run separately and never become the passing default exercise.
5. **Measure:** use warmup and repeated unprofiled timings, report median and variation, and separate setup, transfers, kernel, and complete pipeline time. Capture source revision, input, dimensions, launch, bytes, compiler/toolkit/JetPack/L4T versions, device properties, power mode, clocks, temperature, and active CPU load. Do not infer peak performance from a throttled or uncontrolled run.
6. **User profiling:** **you personally capture kernels in `ncu-ui`** and share reports/screenshots. I specify kernel names, relevant sections, metrics, and predicted trends, then interpret your results. I do not run profiler captures on your behalf. Keep the exact collection configuration and replay/cache settings with each report.
7. **Discussion and gate:** compare prediction, validation, unprofiled timing, and your profiling evidence. Record surprises and the next discriminating experiment. Advance only after you can explain correctness and the relevant GPU behavior. Pending profiling stays pending.

Some headings concern host APIs, architecture history, debugging, or external hardware. Their appropriate evidence is a diagram, runtime query, debugger/sanitizer output, or pipeline timing; a hardware counter cannot prove those concepts. They still receive a focused exercise and are not skipped.

Optional later library/OpenACC/MPI/NVTX dependencies may require narrowly scoped CMake target linkage or compiler integration. Keep the existing targets and entry command; discuss the concrete integration when that subsection arrives. Do not replace the build system or install dependencies in advance. CMake already discovers new `.cu` files. Debug builds use `-G`; measure performance with Release. Source-line profiling may later benefit from `-lineinfo`, which is a future build adjustment, not a change made here.

## Orin and modern CUDA adaptations

- Treat Fermi/Kepler diagrams, cache partitions, bank-width modes, historical profiler outputs, and performance tables as historical comparisons. Query Orin’s actual limits; do not import A100 or old Tesla resource limits into CC 8.7 calculations. The [NVIDIA Ampere tuning guide](https://docs.nvidia.com/cuda/ampere-tuning-guide/) supplies current architectural context.
- CPU and GPU share physical DRAM on Tegra, while allocation types still differ in mapping, caching, coherency, synchronization, and API behavior. Query mapped-memory and managed-memory capabilities; gate prefetch and concurrent host/device access on support. Use the [CUDA for Tegra application note](https://docs.nvidia.com/cuda/cuda-for-tegra-appnote/) for this distinction.
- Use explicit block/warp synchronization and correct `_sync` shuffle participation masks. Historical `volatile` warp reductions are not sufficient synchronization recipes. A memory fence orders memory; it does not make other threads rendezvous.
- Translate `nvprof`/Visual Profiler/nvvp to current kernel questions in Nsight Compute, and `cuda-memcheck` to Compute Sanitizer. For stream overlap, host dispatch, transfer scheduling, and MPI, use wall time/events and, if you choose, a timeline tool such as Nsight Systems. Kernel replay can perturb concurrency and caches; isolated kernel metrics do not prove overlap. See the [Nsight Compute profiling guide](https://docs.nvidia.com/nsight-compute/ProfilingGuide/).
- Dynamic parallelism is retained in full. Port to the installed toolkit’s supported CDP semantics rather than copying device-side `cudaDeviceSynchronize`; modern CDP uses different continuation/ordering rules. Verify profiling support separately; no child-kernel capture is promised. See [NVIDIA’s dynamic parallelism documentation](https://docs.nvidia.com/cuda/cuda-programming-guide/04-special-topics/dynamic-parallelism.html).
- Libraries use currently supported APIs, including generic sparse descriptors where appropriate. Match precision, layouts, setup costs, and math mode. Historical APIs and speedup tables remain discussion topics, not expected results.
- A single Orin cannot supply genuine multi-GPU, cluster, P2P, or GPUDirect RDMA measurements. Every such subsection includes theory, a local decomposition/control exercise where meaningful, and an explicitly pending external-hardware experiment. Likewise, literal MKL and OpenACC experiments require a compatible platform/compiler. A local fallback teaches part of the topic; it never counts as validation of unavailable hardware behavior.

## Nsight Compute metric and evidence legend

The bracketed codes in each roadmap row select the initial evidence. Each lesson narrows the collection to its hypothesis. Metric names below are examples to confirm in the installed tool’s available metrics/sections, not a guarantee that every metric exists on Orin. Consult the [Nsight Compute CLI documentation](https://docs.nvidia.com/nsight-compute/NsightComputeCli/) for discovery and naming; this does not transfer profiling responsibility away from you.

| Code | Relevant sections / example metrics | Expected behavior and interpretation |
|---|---|---|
| T | Duration (`gpu__time_duration.sum`), CUDA events, synchronized host wall time | Tiny work is often launch dominated; kernel speedup need not improve the entire pipeline. Profiler collection overhead is not application performance. |
| L | Launch Statistics: grid/block size, threads, waves/SM | Underfilled grids and partial warps can leave capacity unused; more blocks eventually stop improving throughput. |
| O | Occupancy and Launch Statistics: `launch__registers_per_thread`, `sm__warps_active.avg.pct_of_peak_sustained_active`, shared bytes/block, theoretical limiting resources | More registers/shared storage can reduce residency. Achieved occupancy differs from theoretical occupancy; higher occupancy does not guarantee lower time. |
| W | Scheduler Statistics and Warp State Statistics: eligible/issued warps, supported `smsp__warp_issue_stalled_*` metrics | More independent work can hide latency; barriers, dependencies, and resource limits can reduce issue opportunity. Stalls require context, not isolated rankings. |
| D | Source Counters: branch uniformity, active/predicated threads per executed instruction; supported branch metrics, SASS | Mixed lane paths may serialize or predicate work; uniform branches and contiguous active lanes can improve useful execution. Verify compiler transformation. |
| M | Memory Workload Analysis: `dram__bytes_read.sum`, `dram__bytes_write.sum`, `dram__throughput.avg.pct_of_peak_sustained_elapsed`, `lts__t_sectors_op_read.sum`, L1/L2 sectors/requests/hit rates | Strides/misalignment often increase sectors for equal useful bytes. Reuse may reduce downstream traffic. Summary memory throughput is not DRAM utilization or a hit rate. |
| S | Shared-memory tables: bank conflicts, shared requests/wavefronts; e.g. `l1tex__data_bank_conflicts_pipe_lsu_mem_shared_op_ld.sum` and store counterpart | Padding may reduce conflicts; broadcasts differ from conflicts. Shared reuse can save global traffic while adding barriers/resources. |
| I | Instruction Statistics, Source/SASS, `smsp__inst_executed.sum`, supported instruction-pipeline metrics; `make asm` | Vector loads/unrolling/shuffles change instruction mix, not automatically useful bytes or total speed. Confirm final SASS as well as PTX. |
| C | Speed of Light / compute pipelines, e.g. `sm__throughput.avg.pct_of_peak_sustained_elapsed`, supported FP32/FP64/SFU/Tensor metrics | Arithmetic intensity and dependency structure shape compute utilization. Check actual instructions before attributing gains to a specialized pipeline. |
| A | Atomic/reduction request or instruction counts, L1/L2 atomic traffic where available, duration under address-contention sweeps | Concentrated updates often serialize; local aggregation can reduce global atomic pressure at a resource cost. Floating-point order may change results. |
| H | Runtime/device queries, ownership DAGs, event completion, pipeline wall time, optional timeline evidence; kernel T/O/M as controls | Host scheduling, allocation, transfer, and communication questions need evidence outside an isolated kernel report. No kernel metric proves stream overlap. |
| B | Library version, API status, setup/workspace costs, matched CPU reference; T/M/C/I on actual library kernels when supported | Library speed depends on shape/layout/algorithm/precision and setup amortization. Compare equivalent numerical tasks. |
| V | CPU/reference comparisons, tolerances/invariants, error checks, cuda-gdb and appropriate Compute Sanitizer checks | Performance counters do not establish correctness; all optimized variants must pass the same criteria. |
| X | Capability/toolchain/topology preflight and explicit pending-execution record; applicable kernel codes for available controls | Unsupported execution stays pending. Local simulation cannot establish P2P bandwidth, network scaling, or missing-tool behavior. |

## Front matter and orientation

Read the Foreword (xvii–xviii), Preface (xix), and Introduction (xxi–xxvi) before Chapter 1. Cover **Who This Book Is For**, **What This Book Covers**, **How This Book Is Structured**, **What You Need to Use This Book**, **CUDA Toolkit Download**, **Conventions**, **Source Code**, **Errata**, **P2P.WROX.COM**, and **Useful Links**. Exercise: create a tool/version and learning-objectives checklist; distinguish historical environment requirements and external resources from the existing repository workflow. No download or registration is required. [H,V]

## Complete chapter sequence

Each main table includes every contents entry. The chapter overview supplies the proposed `.cu` module family; each named experiment is a separate runner/variant selected by `main.cpp`. IDs with `.b` identify deeper body headings absent from the contents. Read those inside their enclosing topic at the stated page, not after completing the chapter. Tables are planning checklists, not implementation batches.

### Chapter 1: Heterogeneous Parallel Computing With Cuda — p. 1

Proposed module family: `src/ch01/` with `foundations.cu`.

| ID | Book topic (printed page) | Theory, experiment, and evidence |
|---|---|---|
| 1.0 | HETEROGENEOUS PARALLEL COMPUTING WITH CUDA (p. 1) | connect CPU orchestration to GPU throughput; map the existing vector-add pipeline. [T] |
| 1.1 | **Parallel Computing** (p. 2) | classify work, dependencies, and costs before running a CPU/GPU size sweep. [T] |
| 1.1.1 | Sequential and Parallel Programming (p. 3) | implement equal-work CPU and GPU sums; validate equality and identify launch-cost crossover. [T] |
| 1.1.2 | Parallelism (p. 4) | distinguish task/data parallelism; compare independent vector chunks with dependent stages. [T] |
| 1.1.3 | Computer Architecture (p. 6) | relate SIMD/SIMT, cores, caches, and bandwidth to a compute-heavy versus streaming kernel. [C,M] |
| 1.2 | **Heterogeneous Computing** (p. 8) | sketch ownership and synchronization of each pipeline stage; time the complete pipeline. [T] |
| 1.2.1 | Heterogeneous Architecture (p. 9) | inspect Orin CPU/GPU shared physical DRAM; compare allocation types without assuming discrete PCIe transfers. [M,H] |
| 1.2.2 | Paradigm of Heterogeneous Computing (p. 12) | vary GPU work per host dispatch; predict amortization of orchestration cost. [T] |
| 1.2.3 | CUDA: A Platform for Heterogeneous Computing (p. 14) | A Platform for Heterogeneous Computing: locate runtime, compiler, libraries, and tools; trace source to executable and kernel. [L] |
| 1.3 | **Hello World from GPU** (p. 17) | bounded device printf plus an output buffer; verify thread IDs as a set, without assuming print order. [L] |
| 1.4 | **Is CUDA C Programming Difficult?** (p. 20) | annotate the existing scalar runner by allocation, copy, launch, completion, and validation; explain each responsibility. [T] |
| 1.5 | **Summary** (p. 21) | explain CPU/GPU roles and revisit every chapter exercise; demonstrate the smallest correct GPU program. [T] |

### Chapter 2: Cuda Programming Model — p. 23

Proposed module family: `src/ch02/` with `programming_model.cu / matrix_add.cu`.

| ID | Book topic (printed page) | Theory, experiment, and evidence |
|---|---|---|
| 2.0 | CUDA PROGRAMMING MODEL (p. 23) | derive logical indexing independently of physical scheduling; walk the scalar baseline. [L] |
| 2.1 | **Introducing the CUDA Programming Model** (p. 23) | draw host/device control flow and thread hierarchy; inspect a minimal launch. [L] |
| 2.1.1 | CUDA Programming Structure (p. 25) | label initialization, transfers, kernel, copy-back, and cleanup in one runner. [T] |
| 2.1.2 | Managing Memory (p. 26) | round-trip deterministic arrays using checked allocations/copies and RAII; check zero size and allocation failure handling. [H] |
| 2.1.3 | Organizing Threads (p. 30) | write thread/block/global IDs to an array for 1D, 2D, and 3D launches; check uniqueness and coverage. [L] |
| 2.1.4 | Launching a CUDA Kernel (p. 36) | sweep legal block sizes and ceil-divided grids; check tiny and partial blocks. [L] |
| 2.1.5 | Writing Your Kernel (p. 37) | implement bounded vector addition and a grid-stride variant; compare exact output coverage. [L,M] |
| 2.1.6 | Verifying Your Kernel (p. 39) | introduce a controlled wrong-index variant, detect it with CPU comparison, then restore correctness. [V] |
| 2.1.7 | Handling Errors (p. 40) | distinguish invalid launch configuration from asynchronous execution faults in isolated diagnostic runs. [V] |
| 2.1.8 | Compiling and Executing (p. 40) | follow Make→CMake→Ninja→nvcc and device link; run the approved subsection with the unchanged workflow. [L,V] |
| 2.2 | **Timing Your Kernel** (p. 43) | separate host wall time, CUDA events, and profiler kernel duration; repeat a size sweep. [T] |
| 2.2.1 | Timing with CPU Timer (p. 44) | synchronize the measured completion boundary; compare enqueue time with completed wall time. [T] |
| 2.2.2 | Timing with nvprof (p. 47) | translate the historical profiler exercise to user-collected ncu-ui Duration; compare with unprofiled events. [T] |
| 2.3 | **Organizing Parallel Threads** (p. 49) | use one rectangular matrix reference for all thread mappings. [L,M] |
| 2.3.1 | Indexing Matrices with Blocks and Threads (p. 49) | derive row-major addressing; write and validate coordinates for a non-square matrix. [L] |
| 2.3.2 | Summing Matrices with a 2D Grid and 2D Blocks (p. 53) | sweep block aspect ratio at fixed thread count; predict contiguous-lane access. [M,L] |
| 2.3.3 | Summing Matrices with a 1D Grid and 1D Blocks (p. 57) | flatten rectangular matrices; compare division/indexing instructions and memory behavior. [I,M] |
| 2.3.4 | Summing Matrices with a 2D Grid and 1D Blocks (p. 58) | map each block row explicitly; validate edge rows and compare utilization. [L,M] |
| 2.4 | **Managing Devices** (p. 60) | query runtime capabilities before choosing legal experiments. [H] |
| 2.4.1 | Using the Runtime API to Query GPU Information (p. 61) | record SM count, warp size, memory, launch limits, shared memory, and concurrency attributes. [H,L] |
| 2.4.2 | Determining the Best GPU (p. 63) | explain capability versus workload performance; implement selection with a deterministic single-device fallback. [H] |
| 2.4.3 | Using nvidia-smi to Query GPU Information (p. 63) | compare book telemetry with available Jetson tools such as tegrastats; record tool availability rather than require nvidia-smi. [H] |
| 2.4.4 | Setting Devices at Runtime (p. 64) | enumerate devices, select device 0, and test invalid-index error handling without allocating on a nonexistent GPU. [H,V] |
| 2.5 | **Summary** (p. 65) | validate all three matrix mappings on rectangular and partial sizes; complete all chapter exercises. [L,M] |

### Chapter 3: Cuda Execution Model — p. 67

Proposed module family: `src/ch03/` with `execution_model.cu / reduction.cu / dynamic_parallelism.cu`.

| ID | Book topic (printed page) | Theory, experiment, and evidence |
|---|---|---|
| 3.0 | CUDA EXECUTION MODEL (p. 67) | connect blocks and warps to SM scheduling and resource limits. [L,O] |
| 3.1 | **Introducing the CUDA Execution Model** (p. 67) | separate logical launch geometry from physical residency with a block-count sweep. [L,O] |
| 3.1.1 | GPU Architecture Overview (p. 68) | draw Orin SM, schedulers, registers, shared/L1, L2, and DRAM; map a simple kernel to each. [C,M] |
| 3.1.2 | The Fermi Architecture (p. 71) | study historical SM organization and scheduling; contrast the diagram with queried Orin limits, without claiming Fermi measurements. [H,O] |
| 3.1.3 | The Kepler Architecture (p. 73) | explain historical architectural changes and Hyper-Q; compare the model with present launch/resource observations. [H,O] |
| 3.1.4 | Profile-Driven Optimization (p. 78) | predict one bottleneck, capture a baseline, change one variable, and retain or reject it from evidence. [T,C,M] |
| 3.2 | **Understanding the Nature of Warp Execution** (p. 80) | map linearized block threads into 32-lane warps; predict partial-warp behavior. [L,D] |
| 3.2.1 | Warps and Thread Blocks (p. 80) | compare 31/32/33-thread blocks and multidimensional blocks; verify linear lane mapping. [L,O] |
| 3.2.2 | Warp Divergence (p. 82) | compare uniform, alternating-lane, and warp-aligned branches with equal useful work; inspect predication/SASS. [D,I] |
| 3.2.3 | Resource Partitioning (p. 87) | independently vary register live ranges and dynamic shared bytes; observe occupancy limit transitions. [O] |
| 3.2.4 | Latency Hiding (p. 90) | compare dependent instruction chains with independent accumulators and more resident warps. [W,I] |
| 3.2.5 | Occupancy (p. 93) | compare runtime occupancy predictions and achieved occupancy across legal block sizes; test whether time improves. [O,T] |
| 3.2.6 | Synchronization (p. 97) | compare correct block barriers and stream completion; use sanitizer on isolated invalid-barrier demonstrations rather than risking a hang. [V,W] |
| 3.2.7 | Scalability (p. 98) | sweep grid size from underfilled to many waves; identify fixed-work saturation. [L,T] |
| 3.3 | **Exposing Parallelism** (p. 98) | vary independent work and grid size while holding total output constant. [L,W] |
| 3.3.1 | Checking Active Warps with nvprof (p. 100) | translate active-warps evidence to achieved occupancy and scheduler views in ncu-ui. [O,W] |
| 3.3.2 | Checking Memory Operations with nvprof (p. 100) | translate historical memory metrics to L1/L2 sectors, bytes, and request behavior. [M] |
| 3.3.3 | Exposing More Parallelism (p. 101) | compare one-output/thread with multiple independent outputs/thread; watch registers and eligible warps. [O,W,I] |
| 3.4 | **Avoiding Branch Divergence** (p. 104) | keep a reduction baseline while changing the active-lane pattern. [D] |
| 3.4.1 | The Parallel Reduction Problem (p. 104) | define sum identity, partial blocks, and multistage completion; validate against a wide CPU accumulator. [V,L] |
| 3.4.2 | Divergence in Parallel Reduction (p. 106) | implement neighbor-pair reduction with legal synchronization and padded identities. [D,W] |
| 3.4.3 | Improving Divergence in Parallel Reduction (p. 110) | reorganize active lanes contiguously; compare branch activity at equal size. [D,I] |
| 3.4.4 | Reducing with Interleaved Pairs (p. 112) | compare the book’s interleaved-pair formulation with neighbor pairs; verify indexing and instruction cost. [D,I] |
| 3.5 | **Unrolling Loops** (p. 114) | separate reduced loop overhead from added work/thread and register pressure. [I,O] |
| 3.5.1 | Reducing with Unrolling (p. 115) | aggregate 2/4/8 inputs per thread with tail checks; compare bandwidth and instructions. [M,I] |
| 3.5.2 | Reducing with Unrolled Warps (p. 117) | translate historical volatile warp-synchronous code into explicit safe synchronization; test partial participating warps. [V,I] |
| 3.5.3 | Reducing with Complete Unrolling (p. 119) | specialize legal block sizes and compare generated instructions against looped reduction. [I,O] |
| 3.5.4 | Reducing with Template Functions (p. 120) | instantiate block-size templates and verify launch/compile-time contracts. [I,L] |
| 3.6 | **Dynamic Parallelism** (p. 122) | compare device-launched work with host launches; check installed runtime and profiler support first. [X,T] |
| 3.6.1 | Nested Execution (p. 123) | draw parent/child ordering and visibility; use current CDP semantics and a continuation instead of old device synchronization. [X,V] |
| 3.6.2 | Nested Hello World on the GPU (p. 124) | bound recursion and launches; validate parent/child records rather than printf order. [X,L] |
| 3.6.3 | Nested Reduction (p. 128) | compare a modern supported child/continuation reduction with host multistage reduction; avoid parent reads of unfinished child output. [X,T] |
| 3.7 | **Summary** (p. 132) | explain scheduling, divergence, reduction correctness, and CDP differences; complete all chapter exercises. [O,D,V] |

### Chapter 4: Global Memory — p. 135

Proposed module family: `src/ch04/` with `memory_spaces.cu / access_patterns.cu / transpose.cu`.

| ID | Book topic (printed page) | Theory, experiment, and evidence |
|---|---|---|
| 4.0 | GLOBAL MEMORY (p. 135) | distinguish address spaces, physical backing, and traffic at each hierarchy level. [M] |
| 4.1 | **Introducing the CUDA Memory Model** (p. 136) | map every memory space to scope, lifetime, and hardware; compare streaming and reuse kernels. [M] |
| 4.1.1 | Benefits of a Memory Hierarchy (p. 136) | sweep working set and reuse count; predict transitions in cache hit behavior. [M] |
| 4.1.2 | CUDA Memory Model (p. 137) | run the detailed memory-space sublessons listed below, including register, local, texture, and global storage. [M,O] |
| 4.2 | **Memory Management** (p. 145) | compare allocation/transfer strategies with identical output and explicit synchronization. [H,T] |
| 4.2.1 | Memory Allocation and Deallocation (p. 146) | measure allocation separately from steady-state kernels; verify lifetime and zero-size handling. [H,V] |
| 4.2.2 | Memory Transfer (p. 146) | compare copy size/direction and complete pipeline costs on shared physical DRAM. [H,T] |
| 4.2.3 | Pinned Memory (p. 148) | compare pageable and pinned host buffers; record CPU caching/coherency effects and bounded allocation size. [H,T] |
| 4.2.4 | Zero-Copy Memory (p. 150) | test mapped host storage with one-pass and repeated GPU access; verify mapping support and ownership. [H,M] |
| 4.2.5 | Unified Virtual Addressing (p. 156) | inspect pointer attributes and distinguish shared address interpretation from automatic migration. [H] |
| 4.2.6 | Unified Memory (p. 157) | compare managed and explicit allocations with legal host/device access phases; query capabilities before prefetch/advice. [H,T] |
| 4.3 | **Memory Access Patterns** (p. 158) | isolate lane stride, base offset, instruction width, and data layout. [M,I] |
| 4.3.1 | Aligned and Coalesced Access (p. 158) | sweep scalar offsets and strides without invalid vector alignment; predict useful bytes per sector. [M] |
| 4.3.2 | Global Memory Reads (p. 160) | compare offset and stride read kernels, reuse, cache policies, and read-only paths supported by the compiler. [M,I] |
| 4.3.3 | Global Memory Writes (p. 169) | compare contiguous, offset, and strided stores with deterministic scatter validation. [M] |
| 4.3.4 | Array of Structures versus Structure of Arrays (p. 171) | access one field and all fields in AoS/SoA; compare traffic and instruction counts. [M,I] |
| 4.3.5 | Performance Tuning (p. 176) | sweep read-only annotations, vector widths, and legal cache options one at a time; check SASS and tails. [M,I,O] |
| 4.4 | **What Bandwidth Can a Kernel Achieve?** (p. 179) | define logical traffic separately from measured cache/DRAM bytes; compare copy and transpose. [M,T] |
| 4.4.1 | Memory Bandwidth (p. 179) | sweep size beyond cache and compute logical GB/s from events; correlate with per-level profiler traffic. [M,T] |
| 4.4.2 | Matrix Transpose Problem (p. 180) | implement copy, naive read/write-coalesced transpose, diagonal mapping, and unrolled variants; test non-square edges. [M,L] |
| 4.5 | **Matrix Addition with Unified Memory** (p. 195) | reuse the chapter-2 matrix reference; compare explicit and managed allocation without assuming discrete migration. [H,M,T] |
| 4.6 | **Summary** (p. 199) | explain every address space and access-pattern result; complete all chapter exercises. [M,V] |

**Deeper body subsections, read within the matching section by page:**

| ID | Body subsection (printed page) | Focused sublesson |
|---|---|---|
| 4.b01 | Registers (p. 138) | Vary live accumulator count; compare register allocation, occupancy, and SASS. [O,I] |
| 4.b02 | Local Memory (p. 139) | Use runtime-indexed per-thread arrays; inspect local loads/stores and possible spilling without assuming all local storage is a spill. [M,I,O] |
| 4.b03 | Shared Memory (p. 139) | Exchange deterministic values within a block and validate scope/lifetime and a convergent barrier. [S,V] |
| 4.b04 | Constant Memory (p. 140) | Compare a uniform coefficient address with per-lane coefficient addresses. [I,M] |
| 4.b05 | Texture Memory (p. 141) | Use a supported texture object for 2D reads, addressing, and filtering; compare an ordinary global-read control. [M,I,V] |
| 4.b06 | Global Memory (p. 141) | Compare allocated buffers and global symbols; explain lifetime, visibility, and race-free writes. [M,V] |
| 4.b07 | GPU Caches (p. 142) | Sweep working set/reuse to distinguish L1, L2, and DRAM evidence. [M] |
| 4.b08 | CUDA Variable Declaration Summary (p. 142) | Build a scope/lifetime/storage table and validate one representative access per declaration. [V,I] |
| 4.b09 | Static Global Memory (p. 143) | Upload/read back a device symbol and compare with explicit allocation. [H,V] |
| 4.b10 | Cached Loads (p. 161) | Compare supported cache-policy variants on a reusable working set; inspect final instructions. [M,I] |
| 4.b11 | Uncached Loads (p. 163) | Test supported bypass policies and explain which cache level is bypassed; avoid assuming no caching anywhere. [M,I] |
| 4.b12 | Example of Misaligned Reads (p. 164) | Sweep legal scalar offsets at fixed work and count sectors per useful byte. [M] |
| 4.b13 | Read-Only Cache (p. 168) | Compare const/restrict and supported read-only intrinsics; inspect generated read paths. [M,I] |
| 4.b14 | Example of Misaligned Writes (p. 170) | Sweep store offsets with aligned allocation and validate all destinations. [M,V] |
| 4.b15 | Example: Simple Math with the AoS Data Layout (p. 172) | Compute one field and all fields; measure extra traffic for unused fields. [M,I] |
| 4.b16 | Example: Simple Math with the SoA Data Layout (p. 175) | Repeat equal arithmetic with separate field arrays and compare traffic. [M,I] |
| 4.b17 | Unrolling Techniques (p. 176) | Compare fixed unroll factors with safe tails and equal useful work. [I,O] |
| 4.b18 | Exposing More Parallelism (p. 177) | Increase independent work/grid coverage while tracking eligible warps and live registers. [W,O] |
| 4.b19 | Setting An Upper and Lower Performance Bound for Transpose Kernels (p. 181) | Use contiguous copy and a deliberately strided control as empirical comparison bounds, not universal guarantees. [M,T] |
| 4.b20 | Naive Transpose: Reading Rows versus Reading Columns (p. 185) | Swap which side is coalesced; validate rectangular transpose and sector counts. [M,V] |
| 4.b21 | Unrolling Transpose: Reading Rows versus Reading Columns (p. 187) | Repeat both mappings with equal unroll factors and tail coverage. [M,I] |
| 4.b22 | Diagonal Transpose: Reading Rows versus Reading Columns (p. 189) | Remap block order, validate coverage, and test whether historical partition effects appear on Orin. [M,L] |
| 4.b23 | Expose More Parallelism with Thin Blocks (p. 193) | Sweep thin block shapes at equal work; compare memory efficiency and grid waves. [L,M,O] |

### Chapter 5: Shared Memory And Constant Memory — p. 203

Proposed module family: `src/ch05/` with `shared_layout.cu / reduction.cu / transpose.cu / stencil.cu / shuffle.cu`.

| ID | Book topic (printed page) | Theory, experiment, and evidence |
|---|---|---|
| 5.0 | SHARED MEMORY AND CONSTANT MEMORY (p. 203) | study reuse, bank organization, broadcast, and safe communication. [S,M] |
| 5.1 | **Introducing CUDA Shared Memory** (p. 204) | establish shared-memory scope, lifetime, and tradeoffs with L1 capacity and occupancy. [S,O] |
| 5.1.1 | Shared Memory (p. 204) | compare cooperative reuse with repeated global reads; count traffic saved versus barrier cost. [S,M,W] |
| 5.1.2 | Shared Memory Allocation (p. 206) | compare static and dynamic allocations at equal size; validate per-block independence and limits. [S,O] |
| 5.1.3 | Shared Memory Banks and Access Mode (p. 206) | sweep bank strides, broadcasts, and data widths; explain historical modes versus current hardware. [S] |
| 5.1.4 | Configuring the Amount of Shared Memory (p. 212) | query supported carveout/opt-in limits and compare legal settings; treat preferences as hints. [S,O] |
| 5.1.5 | Synchronization (p. 214) | produce/consume shared tiles with convergent block barriers; verify with racecheck and synccheck. [V,W] |
| 5.2 | **Checking the Data Layout of Shared Memory** (p. 216) | predict bank indices before comparing layouts. [S] |
| 5.2.1 | Square Shared Memory (p. 217) | compare row, column, broadcast, padded, and dynamic square layouts; validate permutation output. [S] |
| 5.2.2 | Rectangular Shared Memory (p. 225) | repeat bank analysis for rectangular tiles and changed block geometry. [S,L] |
| 5.3 | **Reducing Global Memory Access** (p. 232) | contrast global-intermediate and shared-intermediate reductions. [M,S] |
| 5.3.1 | Parallel Reduction with Shared Memory (p. 232) | implement safe shared reduction plus a separate final stage; validate partial blocks. [S,M,V] |
| 5.3.2 | Parallel Reduction with Unrolling (p. 236) | unroll loads and reduction steps while tracking shared traffic and registers. [S,I,O] |
| 5.3.3 | Parallel Reduction with Dynamic Shared Memory (p. 238) | size the workspace from launch parameters and test legal limits and tails. [S,O,V] |
| 5.3.4 | Effective Bandwidth (p. 239) | report logical bytes and actual memory traffic separately; account for intermediate stages. [M,T] |
| 5.4 | **Coalescing Global Memory Accesses** (p. 239) | use shared tiles to reconcile coalesced reads with coalesced writes. [M,S] |
| 5.4.1 | Baseline Transpose Kernel (p. 240) | reproduce naive transpose with a CPU reference and a copy-bandwidth control. [M,T] |
| 5.4.2 | Matrix Transpose with Shared Memory (p. 241) | transpose through a synchronized tile; predict improved global transactions and possible bank conflicts. [M,S] |
| 5.4.3 | Matrix Transpose with Padded Shared Memory (p. 245) | add one column of padding; predict fewer conflicts, with slightly larger resource usage. [S,O] |
| 5.4.4 | Matrix Transpose with Unrolling (p. 246) | process multiple tile elements per thread and check register/resource tradeoffs. [I,O,M] |
| 5.4.5 | Exposing More Parallelism (p. 249) | sweep tile/block geometry and grid coverage for fixed matrix dimensions. [L,O,T] |
| 5.5 | **Constant Memory** (p. 250) | contrast uniform broadcast with per-lane addresses; validate uploaded coefficients. [I,M] |
| 5.5.1 | Implementing a 1D Stencil with Constant Memory (p. 250) | define halo rules, upload coefficients, and compare global versus constant coefficients. [M,I,V] |
| 5.5.2 | Comparing with the Read-Only Cache (p. 253) | compare constant, ordinary const/restrict, and supported read-only loads; vary coefficient uniformity. [M,I] |
| 5.6 | **The Warp Shuffle Instruction** (p. 255) | move values through registers without shared staging, with explicit participation masks. [I,V] |
| 5.6.1 | Variants of the Warp Shuffle Instruction (p. 256) | test sync, up, down, xor, width, and source-lane semantics with known lane patterns. [I,V] |
| 5.6.2 | Sharing Data within a Warp (p. 258) | compare safe shuffle and shared-memory exchange for full and partial warps. [S,I,V] |
| 5.6.3 | Parallel Reduction Using the Warp Shuffle Instruction (p. 262) | build warp then block then grid reduction; validate masks and non-power-of-two input. [I,S,O] |
| 5.7 | **Summary** (p. 264) | justify shared/constant/shuffle choices from evidence and finish all chapter exercises. [S,M,V] |

**Deeper body subsections, read within the matching section by page:**

| ID | Body subsection (printed page) | Focused sublesson |
|---|---|---|
| 5.b01 | Memory Banks (p. 206) | Derive bank indices for each lane and compare unit-stride versus bank-stride access. [S] |
| 5.b02 | Bank Conflict (p. 207) | Compare distinct addresses in one bank with a same-address broadcast. [S] |
| 5.b03 | Access Mode (p. 208) | Compare supported data widths and explain historical 4/8-byte bank modes without requiring a removed setting. [S,I] |
| 5.b04 | Memory Padding (p. 211) | Add one element to the row stride and measure conflict changes. [S] |
| 5.b05 | Access Mode Configuration (p. 212) | Query/support-check historical configuration behavior; compare only legal current settings. [S,H] |
| 5.b06 | Weakly-Ordered Memory Model (p. 214) | Draw producer/consumer ordering and validate a correctly synchronized exchange. [V] |
| 5.b07 | Explicit Barrier (p. 214) | Use a convergent block barrier and run synccheck on a separate bounded misuse example. [V,W] |
| 5.b08 | Memory Fence (p. 215) | Distinguish ordering from rendezvous; validate a publication protocol with proper atomics/synchronization. [V,I] |
| 5.b09 | Volatile Qualifier (p. 216) | Inspect access generation while demonstrating why volatile alone cannot replace synchronization. [I,V] |
| 5.b10 | Accessing Row-Major versus Column-Major (p. 218) | Predict bank mapping and compare row/column reads with identical deterministic outputs. [S] |
| 5.b11 | Writing Row-Major and Reading Column-Major (p. 220) | Separate producer and consumer with a barrier; measure transpose-like bank conflicts. [S,V] |
| 5.b12 | Dynamic Shared Memory (p. 221) | Repeat the layout experiment with launch-sized storage and verified byte counts. [S,O] |
| 5.b13 | Padding Statically Declared Shared Memory (p. 223) | Pad compile-time shared row pitch and compare conflicts and resource use. [S,O] |
| 5.b14 | Padding Dynamically Declared Shared Memory (p. 223) | Compute padded pitch/bytes at runtime and verify all indices and conflicts. [S,V] |
| 5.b15 | Comparing the Performance of the Square Shared Memory Kernels (p. 225) | Compare all square variants at equal work with conflict counts and repeated timings. [S,T] |
| 5.b16 | Accessing Row-Major versus Accessing Column-Major (p. 226) | Repeat row/column bank mapping for rectangular geometry. [S,L] |
| 5.b17 | Writing Row-Major and Reading Column-Major (p. 227) | Separate producer and consumer with a barrier; measure transpose-like bank conflicts. [S,V] |
| 5.b18 | Dynamically Declared Shared Memory (p. 228) | Use runtime-sized rectangular shared storage with explicit strides and validated bounds. [S,V] |
| 5.b19 | Padding Statically Declared Shared Memory (p. 229) | Pad compile-time shared row pitch and compare conflicts and resource use. [S,O] |
| 5.b20 | Padding Dynamically Declared Shared Memory (p. 230) | Compute padded pitch/bytes at runtime and verify all indices and conflicts. [S,V] |
| 5.b21 | Comparing the Performance of the Rectangular Shared Memory Kernels (p. 231) | Compare all rectangular variants at equal work and launch resources. [S,L,T] |
| 5.b22 | Broadcast of a Value across a Warp (p. 258) | Broadcast a known source lane with a correct participation mask. [I,V] |
| 5.b23 | Shift Up within a Warp (p. 258) | Validate lane-wise up-shift and unchanged boundary-lane semantics. [I,V] |
| 5.b24 | Shift Down within a Warp (p. 259) | Validate down-shift and source-lane validity, including partial warps. [I,V] |
| 5.b25 | Shift within a warp with Wrap Around (p. 259) | Implement the stated wrap indexing explicitly and verify every lane. [I,V] |
| 5.b26 | Butterfly Exchange across the Warp (p. 260) | Test XOR masks and subgroup widths against CPU lane permutations. [I,V] |
| 5.b27 | Exchange Values of an Array across a Warp (p. 260) | Exchange per-lane array values via safe shuffles; compare shared staging. [I,S,V] |
| 5.b28 | Exchange Values Using Array Indices Across a Warp (p. 261) | Derive source lane/component from an array index and validate partial participation. [I,V] |

### Chapter 6: Streams And Concurrency — p. 267

Proposed module family: `src/ch06/` with `streams.cu / pipeline.cu`.

| ID | Book topic (printed page) | Theory, experiment, and evidence |
|---|---|---|
| 6.0 | STREAMS AND CONCURRENCY (p. 267) | distinguish ordering guarantees from possible overlap; measure the whole pipeline. [H] |
| 6.1 | **Introducing Streams and Events** (p. 268) | draw command DAGs and validate buffer ownership at completion points. [H,V] |
| 6.1.1 | CUDA Streams (p. 269) | compare ordered work in one stream with independent streams; verify identical outputs. [H] |
| 6.1.2 | Stream Scheduling (p. 271) | vary issue order and record events; explain why independent work need not overlap. [H] |
| 6.1.3 | Stream Priorities (p. 273) | query priority range and compare long/short work; treat priority as a scheduling hint. [H] |
| 6.1.4 | CUDA Events (p. 273) | use timing and dependency events; distinguish elapsed GPU intervals from CPU enqueue time. [T,H] |
| 6.1.5 | Stream Synchronization (p. 275) | compare event, stream, and device waits with the same required dependency graph. [H,V] |
| 6.2 | **Concurrent Kernel Execution** (p. 279) | pair resource-light kernels then resource-heavy kernels; predict resource contention. [O,H] |
| 6.2.1 | Concurrent Kernels in Non-NULL Streams (p. 279) | launch independent buffers in nonblocking streams; validate isolation and possible overlap. [H,O] |
| 6.2.2 | False Dependencies on Fermi GPUs (p. 281) | analyze the historical queue limitation, then test issue order on Orin without asserting Fermi behavior. [H] |
| 6.2.3 | Dispatching Operations with OpenMP (p. 283) | compare single-thread and multiple host dispatchers; use standard C++ threads locally if OpenMP is unavailable and retain the OpenMP tool-gated exercise. [H,T] |
| 6.2.4 | Adjusting Stream Behavior Using Environment Variables (p. 284) | compare supported connection settings in separate processes; validate runtime applicability and avoid assuming overlap. [H] |
| 6.2.5 | Concurrency-Limiting GPU Resources (p. 286) | independently raise registers, shared bytes, and blocks; predict less opportunity for co-residency. [O,H] |
| 6.2.6 | Blocking Behavior of the Default Stream (p. 287) | contrast legacy default, explicit nonblocking streams, and supported per-thread semantics. [H,V] |
| 6.2.7 | Creating Inter-Stream Dependencies (p. 288) | use record/wait events to enforce producer→consumer ordering without a global wait. [H,V] |
| 6.3 | **Overlapping Kernel Execution and Data Transfer** (p. 289) | chunk buffers and compare against a serial reference; inspect device copy capabilities. [H,T] |
| 6.3.1 | Overlap Using Depth-First Scheduling (p. 289) | enqueue copy→kernel→copy per chunk; predict the DAG and measure completed pipeline time. [H,T] |
| 6.3.2 | Overlap Using Breadth-First Scheduling (p. 293) | enqueue transfers/kernels by phase; compare fixed work and equal chunk sizes. [H,T] |
| 6.4 | **Overlapping GPU and CPU Execution** (p. 294) | execute independent CPU work while a stream runs; compare pipeline wall time and ownership safety. [H,T] |
| 6.5 | **Stream Callbacks** (p. 295) | explain the legacy callback and implement a supported host-function continuation with no CUDA API calls inside it. [H,V] |
| 6.6 | **Summary** (p. 297) | validate every dependency and compare pipeline schedules; finish all chapter exercises. [H,V] |

**Deeper body subsections, read within the matching section by page:**

| ID | Body subsection (printed page) | Focused sublesson |
|---|---|---|
| 6.b01 | False Dependencies (p. 272) | Draw queue-induced ordering and compare independent versus accidentally ordered commands. [H] |
| 6.b02 | Hyper-Q (p. 272) | Explain historical multiple work queues; test independent submissions without inferring physical queue counts. [H] |
| 6.b03 | Creation and Destruction (p. 273) | Use checked event ownership, complete outstanding work, and exclude setup from steady timing. [H,V] |
| 6.b04 | Recording Events and Measuring Elapsed Time (p. 274) | Bracket work in one stream and compare with synchronized wall time. [T,H] |
| 6.b05 | Blocking and Non-Blocking Streams (p. 276) | Compare legacy default-stream interaction with explicit nonblocking streams. [H,V] |
| 6.b06 | Implicit Synchronization (p. 276) | Identify book-listed implicit waits and test applicable calls in controlled sequences. [H] |
| 6.b07 | Explicit Synchronization (p. 277) | Compare event, stream, and device completion with the same dependency requirement. [H,V] |
| 6.b08 | Configurable Events (p. 278) | Compare timing-enabled, timing-disabled, and supported host-wait flags. [H,T] |

### Chapter 7: Tuning Instruction-Level Primitives — p. 299

Proposed module family: `src/ch07/` with `numerics.cu / math_functions.cu / atomics.cu`.

| ID | Book topic (printed page) | Theory, experiment, and evidence |
|---|---|---|
| 7.0 | TUNING INSTRUCTION-LEVEL PRIMITIVES (p. 299) | connect instruction selection to throughput, accuracy, and contention. [I,C] |
| 7.1 | **Introducing CUDA Instructions** (p. 300) | inspect PTX and final SASS for the same arithmetic workload. [I] |
| 7.1.1 | Floating-Point Instructions (p. 301) | compare FMA and separate multiply/add on cancellation and rounding-sensitive inputs. [I,V] |
| 7.1.2 | Intrinsic and Standard Functions (p. 303) | compare standard math with intrinsics over an explicit input domain and error budget. [I,V] |
| 7.1.3 | Atomic Instructions (p. 304) | compare atomic accumulation with a race-free staged reference and explain scope/ordering. [A,V] |
| 7.2 | **Optimizing Instructions for Your Application** (p. 306) | establish correctness/accuracy constraints before instruction tuning. [I,V] |
| 7.2.1 | Single-Precision vs. Double-Precision (p. 306) | benchmark equal algorithms and report absolute/relative error against a high-precision CPU reference. [C,I,V] |
| 7.2.2 | Standard vs. Intrinsic Functions (p. 309) | compare selected math and fast-math builds including special inputs; inspect SASS and numerical changes. [I,V] |
| 7.2.3 | Understanding Atomic Instructions (p. 315) | sweep same-address, distributed, and locally aggregated updates; predict contention scaling. [A] |
| 7.2.4 | Bringing It All Together (p. 322) | optimize a validated arithmetic/atomic workload with one independent change per step. [A,I,T] |
| 7.3 | **Summary** (p. 324) | document speed/accuracy/ordering tradeoffs and complete all chapter exercises. [I,V] |

**Deeper body subsections, read within the matching section by page:**

| ID | Body subsection (printed page) | Focused sublesson |
|---|---|---|
| 7.b01 | Summary (p. 308) | Review this primitive’s accuracy, instruction, and performance tradeoffs before the next subsection. [I,V,T] |
| 7.b02 | Visualizing Standard and Intrinsic Functions (p. 309) | Plot or tabulate error over a defined domain and correlate with instruction differences. [I,V] |
| 7.b03 | Manipulating Instruction Generation (p. 311) | Compare normal and narrowly scoped fast-math/intrinsic variants, including FMA and special values. [I,V] |
| 7.b04 | Summary (p. 315) | Review this primitive’s accuracy, instruction, and performance tradeoffs before the next subsection. [I,V,T] |
| 7.b05 | From the Ground Up (p. 315) | Contrast an intentionally raced update with an atomic and a staged reduction in isolated runs. [A,V] |
| 7.b06 | Built-In CUDA Atomic Functions (p. 317) | Test supported add/exchange/CAS and relevant type/scope semantics against deterministic invariants. [A,V] |
| 7.b07 | The Cost of Atomic Operations (p. 318) | Sweep contention and useful work per update; report serialization trends. [A,T] |
| 7.b08 | Limiting the Performance Cost of Atomic Operations (p. 319) | Aggregate within warp/block before global updates; count operations and resource costs. [A,S,O] |
| 7.b09 | Atomic Floating-Point Support (p. 320) | Query supported types, validate tolerance and nondeterministic addition order, and explain CAS fallback historically. [A,V] |
| 7.b10 | Summary (p. 321) | Review this primitive’s accuracy, instruction, and performance tradeoffs before the next subsection. [I,V,T] |

### Chapter 8: Gpu-Accelerated Cuda Libraries And Openacc — p. 327

Proposed module family: `src/ch08/` with `sparse.cu / blas.cu / fft.cu / random.cu; tool-gated OpenACC companion`.

| ID | Book topic (printed page) | Theory, experiment, and evidence |
|---|---|---|
| 8.0 | GPU-ACCELERATED CUDA LIBRARIES AND OPENACC (p. 327) | compare APIs, layouts, accuracy, and complete application costs. [B] |
| 8.1 | **Introducing the CUDA Libraries** (p. 328) | identify installed library versions and workloads before writing wrappers. [B] |
| 8.1.1 | Supported Domains for CUDA Libraries (p. 329) | map sparse/dense algebra, FFT, and RNG to representative tasks and data access. [B] |
| 8.1.2 | A Common Library Workflow (p. 330) | separate handle/plan setup, workspace, execution, synchronization, and cleanup. [B,V] |
| 8.2 | **The CUSPARSE Library** (p. 332) | compare sparse operations with a dense/CPU reference using current supported APIs. [B,M] |
| 8.2.1 | cuSPARSE Data Storage Formats (p. 333) | construct COO/CSR/CSC examples and validate indexing, duplicates, and empty rows. [B,V] |
| 8.2.2 | Formatting Conversion with cuSPARSE (p. 337) | round-trip supported formats; count conversion time and compare recovered coordinates. [B,T,V] |
| 8.2.3 | Demonstrating cuSPARSE (p. 338) | run deterministic CSR SpMV using current descriptors and a CPU reference. [B,M] |
| 8.2.4 | Important Topics in cuSPARSE Development (p. 340) | vary sparsity pattern, index width, workspace, and supported algorithm; separate conversion/setup. [B,M] |
| 8.2.5 | cuSPARSE Summary (p. 341) | explain when sparse storage pays off and record API differences from the book. [B] |
| 8.3 | **The cuBLAS Library** (p. 341) | compare handwritten GEMM with a library baseline under matched math mode. [B,C] |
| 8.3.1 | Managing cuBLAS Data (p. 342) | validate row/column-major interpretation, leading dimensions, transpose flags, and pointer modes. [B,V] |
| 8.3.2 | Demonstrating cuBLAS (p. 343) | compare small CPU GEMM and scalable GPU GEMM, including non-square dimensions. [B,C] |
| 8.3.3 | Important Topics in cuBLAS Development (p. 345) | test handle/stream binding and explicit precision/math choices; distinguish Tensor Core use from assumed use. [B,I] |
| 8.3.4 | cuBLAS Summary (p. 346) | report setup, kernel, and pipeline costs under equal numerical requirements. [B,T] |
| 8.4 | **The cuFFT Library** (p. 346) | connect FFT decomposition, memory layout, and plan/workspace costs. [B] |
| 8.4.1 | Using the cuFFT API (p. 347) | create/reuse a supported plan; validate dimensions, layout, and normalization conventions. [B,V] |
| 8.4.2 | Demonstrating cuFFT (p. 348) | use impulse, sinusoid, and forward/inverse tests; compare a small CPU DFT and reconstruction error. [B,V] |
| 8.4.3 | cuFFT Summary (p. 349) | distinguish planning from steady execution and document scale/stride effects. [B,T] |
| 8.5 | **The cuRAND Library** (p. 349) | compare host and device generation with reproducible seeds and stream ordering. [B] |
| 8.5.1 | Choosing Pseudo- or Quasi- Random Numbers (p. 349) | compare pseudo sequences and Sobol sampling on integration error versus sample count. [B,V] |
| 8.5.2 | Overview of the cuRAND Library (p. 350) | define generator/state/seed/subsequence ownership and verify deterministic replay. [B,V] |
| 8.5.3 | Demonstrating cuRAND (p. 354) | generate uniform/normal samples and estimate pi or an integral with confidence bounds. [B,C] |
| 8.5.4 | Important Topics in cuRAND Development (p. 357) | compare state initialization cost, state reuse, independent subsequences, and distribution statistics. [B,O,V] |
| 8.6 | **CUDA Library Features Introduced in CUDA 6** (p. 358) | identify historical features and current replacements; retain compatibility notes. [B] |
| 8.6.1 | Drop-In CUDA Libraries (p. 358) | analyze historical interception versus explicit supported library calls; reproduce equivalent math locally if the old facility is absent. [B,X] |
| 8.6.2 | Multi-GPU Libraries (p. 359) | analyze distribution and communication costs; run single-GPU controls locally and reserve genuine multi-device execution for suitable hardware. [X,B] |
| 8.7 | **A Survey of CUDA Library Performance** (p. 361) | reproduce fair timing methodology rather than expect the book’s hardware rankings. [B,T] |
| 8.7.1 | cuSPARSE versus MKL (p. 361) | compare matched SpMV and thread settings; use a portable CPU reference on ARM and defer literal MKL measurement to supported hardware. [B,X,T] |
| 8.7.2 | cuBLAS versus MKL BLAS (p. 362) | match GEMM dimensions, layout, precision, and CPU threads; retain the tool-gated MKL comparison. [B,X,T] |
| 8.7.3 | cuFFT versus FFTW versus MKL (p. 363) | compare equal FFT transforms, normalization, and plan reuse; run only available backends and mark missing measurements. [B,X,T] |
| 8.7.4 | CUDA Library Performance Summary (p. 364) | report setup and execution separately, variation, and platform limits. [B,T] |
| 8.8 | **Using OpenACC** (p. 365) | study compiler-directed parallelism; build a capability-gated directive version beside an equivalent CUDA control. [X,B] |
| 8.8.1 | Using OpenACC Compute Directives (p. 367) | cover parallel/kernels/loop, gang/worker/vector, private/reduction, and dependency correctness; compare generated work to explicit CUDA. [X,L,V] |
| 8.8.2 | Using OpenACC Data Directives (p. 375) | cover data regions, copy/copyin/copyout/create/present and update/lifetime; compare transfer counts and residency. [X,H] |
| 8.8.3 | The OpenACC Runtime API (p. 380) | inspect devices, initialization, async/wait, and supported data-management calls; verify equal output. [X,H,V] |
| 8.8.4 | Combining OpenACC and the CUDA Libraries (p. 382) | pass device pointers with supported interoperability and align stream ownership; compare explicit CUDA/library control. [X,B,V] |
| 8.8.5 | Summary of OpenACC (p. 384) | explain control/productivity tradeoffs and record compiler/platform prerequisites. [X,B] |
| 8.9 | **Summary** (p. 384) | validate all four libraries and every OpenACC topic; finish all chapter exercises, with unavailable execution explicitly pending. [B,X,V] |

**Deeper body subsections, read within the matching section by page:**

| ID | Body subsection (printed page) | Focused sublesson |
|---|---|---|
| 8.b01 | Stage 1: Creating a Library Handle (p. 331) | Create/reuse a checked handle and distinguish setup lifetime from execution. [B,T] |
| 8.b02 | Stage 2: Allocating Device Memory (p. 331) | Allocate bounded buffers with checked ownership and cleanup. [B,V] |
| 8.b03 | Stage 3: Converting Inputs to a Library-Supported Format (p. 331) | Validate shape, indexing, and conversion against a native-format reference. [B,V] |
| 8.b04 | Stage 4: Populating Device Memory with Inputs (p. 331) | Copy deterministic input and record ownership/completion boundaries. [B,H] |
| 8.b05 | Stage 5: Configuring the Library (p. 331) | Configure descriptors, algorithm, workspace, precision, and stream explicitly. [B,V] |
| 8.b06 | Stage 6: Executing (p. 332) | Execute with checked status and completion; identify actual library kernels. [B,T] |
| 8.b07 | Stage 7: Retrieving Results from Device Memory (p. 332) | Retrieve output after completion and separate transfer from compute time. [B,H] |
| 8.b08 | Stage 8: Converting Back to Native Format (p. 332) | Convert output to the native format and verify semantics and numerical tolerance. [B,V] |
| 8.b09 | Stage 9: Releasing CUDA Resources (p. 332) | Release handles/plans/workspaces/buffers using correct lifetime order. [B,V] |
| 8.b10 | Stage 10: Continuing with the Application (p. 332) | Validate the full application and report setup, steady-state, and pipeline costs. [B,T,V] |
| 8.b11 | Dense (p. 334) | Validate dense leading dimensions and zeros before sparse conversion. [B,V] |
| 8.b12 | Coordinate (COO) (p. 334) | Construct row/column/value triples and verify indexing, duplicates, and order. [B,V] |
| 8.b13 | Compressed Sparse Row (CSR) (p. 334) | Derive row offsets including empty rows and compare SpMV with the dense reference. [B,V] |
| 8.b14 | cuSPARSE Storage Formats Summary (p. 336) | Compare storage bytes and supported format tradeoffs for the same matrix. [B,M] |
| 8.b15 | A Simple cuBLAS Example (p. 343) | Validate a small supported BLAS operation before scaling dimensions. [B,V] |
| 8.b16 | Porting from BLAS (p. 344) | Translate layout, dimensions, strides, scalars, and status handling from CPU BLAS. [B,V] |
| 8.b17 | Covering the Concepts (p. 351) | Explain RNG seed, sequence, offset, distributions, and state ownership with reproducibility checks. [B,V] |
| 8.b18 | Comparing the Host and Device APIs (p. 353) | Compare equal distributions and include state setup/generation costs separately. [B,T] |
| 8.b19 | Replacing rand() (p. 354) | Replace a CPU sampling loop with a seeded generator; validate statistics rather than identical CPU sequences. [B,V] |
| 8.b20 | Generating Randomness for CUDA Kernels (p. 357) | Generate within a Monte Carlo kernel using disjoint state/subsequences and reusable state. [B,O,V] |
| 8.b21 | Using the kernels Directive (p. 367) | Study compiler-discovered parallelism and validate a tool-gated kernels region against CUDA. [X,L,V] |
| 8.b22 | Using the parallel Directive (p. 370) | Express known independence explicitly and compare the tool-gated result with the reference. [X,L,V] |
| 8.b23 | Using the loop Directive (p. 372) | Test gang/worker/vector mapping, private data, and reduction semantics with a compatible compiler. [X,L,V] |
| 8.b24 | OpenACC Compute Directives Summary (p. 375) | Explain each compute directive’s responsibility and verify the same numerical task. [X,V] |
| 8.b25 | Using the data Directive (p. 375) | Keep arrays resident across multiple regions and compare setup/transfer counts. [X,H] |
| 8.b26 | Adding Data Clauses to kernels and parallel Directives (p. 379) | Compare scoped clauses with persistent data regions and validate updates/lifetimes. [X,H,V] |

### Chapter 9: Multi-Gpu Programming — p. 387

Proposed module family: `src/ch09/` with `partition.cu / wave_stencil.cu; tool-gated MPI companion`.

| ID | Book topic (printed page) | Theory, experiment, and evidence |
|---|---|---|
| 9.0 | MULTI-GPU PROGRAMMING (p. 387) | study partitioning and communication despite the local single-GPU hardware limit. [X,H] |
| 9.1 | **Moving to Multiple GPUs** (p. 388) | query device count/topology; sketch data ownership and a one-device decomposition control. [X,H] |
| 9.1.1 | Executing on Multiple GPUs (p. 389) | design device-specific buffers, streams, and context selection; validate the local one-device fallback. [X,V] |
| 9.1.2 | Peer-to-Peer Communication (p. 391) | distinguish peer copy, remote dereference, host staging, and topology requirements. [X,H] |
| 9.1.3 | Synchronizing across Multi-GPUs (p. 392) | model per-device completion and supported cross-device event waits; use local streams only as a dependency exercise. [X,H,V] |
| 9.2 | **Subdividing Computation across Multiple GPUs** (p. 393) | partition vector work with an uneven remainder and compare to a whole-array reference. [X,V] |
| 9.2.1 | Allocating Memory on Multiple Devices (p. 393) | plan allocation ownership and cleanup per device; validate local ownership tracking. [X,V] |
| 9.2.2 | Distributing Work from a Single Host Thread (p. 394) | describe device-switch dispatch order and exercise the one-device path. [X,H] |
| 9.2.3 | Compiling and Executing (p. 395) | keep the Make entry point and validate device count before multi-GPU launch; genuine scaling remains pending. [X,V] |
| 9.3 | **Peer-to-Peer Communication on Multiple GPUs** (p. 396) | plan staged-copy and peer baselines with identical payload sizes. [X,H] |
| 9.3.1 | Enabling Peer-to-Peer Access (p. 396) | query directional peer support before enabling; exercise unsupported/single-device handling. [X,V] |
| 9.3.2 | Peer-to-Peer Memory Copy (p. 396) | compare explicit peer copy with host staging on a suitable system; locally validate payload and reference logic. [X,H] |
| 9.3.3 | Peer-to-Peer Memory Access with Unified Virtual Addressing (p. 398) | separate addressability from permission and locality; reserve remote-pointer throughput for real peer hardware. [X,M] |
| 9.4 | **Finite Difference on Multi-GPU** (p. 400) | build a deterministic local 2D wave-equation solver with explicit halo ownership. [X,M,V] |
| 9.4.1 | Stencil Calculation for 2D Wave Equation (p. 400) | validate time-stepping, boundary conditions, and CPU/GPU numerical tolerance. [M,V] |
| 9.4.2 | Typical Patterns for Multi-GPU Programs (p. 401) | model decomposition, halo exchange, synchronization, and gather with local subdomains. [X,H] |
| 9.4.3 | 2D Stencil Computation with Multiple GPUs (p. 403) | compare partitioned local subdomains with the monolithic stencil; label this a decomposition test only. [X,M,V] |
| 9.4.4 | Overlapping Computation and Communication (p. 405) | split interior/boundary work and event dependencies; multi-device overlap requires external hardware. [X,H] |
| 9.4.5 | Compiling and Executing (p. 406) | retain make clean build run and compare partitioned correctness; defer real topology/scaling results. [X,V] |
| 9.5 | **Scaling Applications across GPU Clusters** (p. 409) | study ranks, transport, latency/bandwidth, and strong/weak scaling. [X,H] |
| 9.5.1 | CPU-to-CPU Data Transfer (p. 410) | plan MPI ping-pong and validate message payloads; local ranks teach semantics but do not measure network performance. [X,H,V] |
| 9.5.2 | GPU-to-GPU Data Transfer Using Traditional MPI (p. 413) | design device→host→MPI→host→device staging and synchronized ownership. [X,H] |
| 9.5.3 | GPU-to-GPU Data Transfer with CUDA-aware MPI (p. 416) | verify MPI GPU-buffer support before passing device pointers; compare with staged exchange on a cluster. [X,H,V] |
| 9.5.4 | Intra-Node GPU-to-GPU Data Transfer with CUDA-Aware MPI (p. 417) | relate rank/device binding to peer topology; preserve a genuine multi-GPU experiment as pending. [X,H] |
| 9.5.5 | Adjusting Message Chunk Size (p. 418) | sweep payload/chunk sizes in local controls and later network runs; distinguish latency amortization from bandwidth. [X,H,T] |
| 9.5.6 | GPU to GPU Data Transfer with GPUDirect RDMA (p. 419) | identify supported NIC, driver, topology, MPI, and registration requirements; no RDMA claim from local simulation. [X,H] |
| 9.6 | **Summary** (p. 422) | explain each communication path and complete all chapter exercises; retain external measurements as pending. [X,V] |

**Deeper body subsections, read within the matching section by page:**

| ID | Body subsection (printed page) | Focused sublesson |
|---|---|---|
| 9.b01 | Enabling Peer Access (p. 391) | Query actual directional support; record single-device inability without attempting invalid peer launches. [X,H] |
| 9.b02 | Peer-to-Peer Memory Copy (p. 392) | Validate payload controls locally; genuine peer copies await two compatible devices. [X,H,V] |
| 9.b03 | Implementing Inter-Node MPI Communication (p. 411) | Plan a checked ping-pong; local ranks validate semantics while inter-node timing remains pending. [X,H,V] |
| 9.b04 | CPU Affinity (p. 412) | Inspect CPU binding and compare dispatch/communication timing under explicit supported binding. [X,H] |
| 9.b05 | Affinity in MPI-CUDA Programs (p. 413) | Define rank↔CPU↔GPU binding; inspect topology on the eventual multi-device system. [X,H] |
| 9.b06 | Performing GPU-to-GPU Communication With MPI (p. 415) | Verify staged buffer completion and payload integrity before comparing GPU-aware transport. [X,H,V] |

### Chapter 10: Implementation Considerations — p. 425

Proposed module family: `src/ch10/` with `compilation.cu / diagnostics.cu / crypt.cu`.

| ID | Book topic (printed page) | Theory, experiment, and evidence |
|---|---|---|
| 10.0 | IMPLEMENTATION CONSIDERATIONS (p. 425) | integrate assessment, correctness, profiling, and reproducible deployment. [V,T] |
| 10.1 | **The CUDA C Development Process** (p. 426) | connect each development stage to evidence and a measurable acceptance criterion. [V,T] |
| 10.1.1 | APOD Development Cycle (p. 426) | assess, parallelize, optimize, deploy a bounded workload with one saved baseline per stage. [V,T] |
| 10.1.2 | Optimization Opportunities (p. 429) | apply Amdahl’s law, arithmetic intensity, data residency, and launch overhead to select the next change. [C,M,T] |
| 10.1.3 | CUDA Code Compilation (p. 432) | trace preprocessing, PTX/SASS, fatbinary, separate compilation, device linking, and architecture selection using make asm. [I,L] |
| 10.1.4 | CUDA Error Handling (p. 437) | use checked runtime/library calls, launch checks, completion checks, and RAII; test diagnostic paths. [V] |
| 10.2 | **Profile-Driven Optimization** (p. 438) | establish a hypothesis→measurement→change→validation ledger. [T,C,M] |
| 10.2.1 | Finding Optimization Opportunities Using nvprof (p. 439) | translate summary/trace/metric tasks into appropriate current tools; select kernel versus pipeline questions. [T,H] |
| 10.2.2 | Guiding Optimization Using nvvp (p. 443) | interpret current ncu-ui sections and optional timeline evidence rather than reproduce the obsolete UI. [T,M,W] |
| 10.2.3 | NVIDIA Tools Extension (p. 446) | annotate host stages with supported NVTX ranges and relate them to kernel naming and user captures. [H] |
| 10.3 | **CUDA Debugging** (p. 448) | isolate faults in dedicated diagnostic exercises and restore a passing default runner. [V] |
| 10.3.1 | Kernel Debugging (p. 448) | use existing cuda-debug target for breakpoints, indices, variables, and race/ordering reasoning on small inputs. [V] |
| 10.3.2 | Memory Debugging (p. 456) | translate cuda-memcheck work to Compute Sanitizer memcheck/racecheck/initcheck/synccheck; introduce and fix bounded faults. [V] |
| 10.3.3 | Debugging Summary (p. 462) | distinguish illegal access, uninitialized memory, shared races, bad barriers, and ordinary numeric mismatches. [V] |
| 10.4 | **A Case Study in Porting C Programs to CUDA C** (p. 462) | reproduce the book’s crypt case study with deterministic test vectors and a documented modern implementation. [I,V,T] |
| 10.4.1 | Assessing crypt (p. 463) | inspect the algorithm, CPU hotspots, independence, data structures, and reference outputs before porting. [T,V] |
| 10.4.2 | Parallelizing crypt (p. 464) | map independent items to GPU threads; preserve the algorithm and validate all known test vectors. [L,V] |
| 10.4.3 | Optimizing crypt (p. 465) | test memory layout, constants, instruction choices, and launch geometry individually; require unchanged results. [I,M,O] |
| 10.4.4 | Deploying Crypt (p. 472) | record target/toolchain/configuration, resource use, correctness, and kernel/end-to-end timings. [T,V] |
| 10.4.5 | Summary of Porting crypt (p. 475) | compare CPU, initial CUDA, and final CUDA versions; explain each measured change. [T,V] |
| 10.5 | **Summary** (p. 476) | finish every chapter exercise and deliver a reproducible report linking theory, implementation, and user-supplied profiles. [V,T] |

**Deeper body subsections, read within the matching section by page:**

| ID | Body subsection (printed page) | Focused sublesson |
|---|---|---|
| 10.b01 | Assessment (p. 427) | Identify the CPU hotspot and maximum possible application speedup before writing a kernel. [T] |
| 10.b02 | Parallelization (p. 427) | Implement the simplest correct independent work mapping and validate it. [L,V] |
| 10.b03 | Optimization (p. 428) | Change one measured limiting factor and retain the baseline. [T,M,I] |
| 10.b04 | Deployment (p. 429) | Record reproducible build/run settings and check complete application behavior. [T,V] |
| 10.b05 | Exposing Sufficient Parallelism (p. 430) | Sweep independent work and grid size with fixed algorithmic output. [L,W] |
| 10.b06 | Optimizing Memory Access (p. 430) | Apply traffic accounting, coalescing, reuse, and data residency to a measured hotspot. [M] |
| 10.b07 | Optimizing Instruction Execution (p. 432) | Compare final instruction mix and dependencies after one safe transformation. [I,W] |
| 10.b08 | Separate Compilation (p. 434) | Trace existing relocatable device compilation and device link with a cross-file device function exercise. [I,V] |
| 10.b09 | Sample Makefile (p. 434) | Map historical nvcc flags to the existing CMake-generated build; retain the repository Makefile. [H] |
| 10.b10 | Integrating CUDA Files into a C Project (p. 436) | Explain C/C++ linkage boundaries and use a narrow host wrapper; keep main.cpp and dedicated .cu files. [V] |
| 10.b11 | Profiling Modes (p. 439) | Map historical summary, trace, and metric modes to timing, timeline, and kernel-counter evidence. [T,H,M] |
| 10.b12 | Profiling Scope (p. 440) | Select kernels/ranges and exclude setup where appropriate; keep a separate whole-pipeline measurement. [T,H] |
| 10.b13 | Memory Bandwidth (p. 440) | Compare logical bandwidth with actual hierarchy traffic on the chosen hotspot. [M,T] |
| 10.b14 | Instruction Throughput (p. 443) | Inspect active pipelines and dependencies rather than treating utilization as a score. [C,I,W] |
| 10.b15 | Guided Analysis (p. 444) | Test a tool suggestion with a controlled variant and verify both correctness and time. [V,T] |
| 10.b16 | Unguided Analysis (p. 444) | Form an independent hypothesis from traffic/instructions and collect discriminating evidence. [M,I,T] |
| 10.b17 | Using cuda-gdb (p. 448) | Use make cuda-debug on a tiny deterministic kernel and inspect indices and device variables. [V] |
| 10.b18 | CUDA printf (p. 454) | Bound diagnostic output and show why order and instrumented timings are not reliable scheduling evidence. [V] |
| 10.b19 | CUDA assert (p. 455) | Trigger a bounded failed invariant in a separate process; rebuild/restore the passing exercise. [V] |
| 10.b20 | Kernel Debugging Summary (p. 456) | Classify logic, launch, execution, and synchronization faults with a minimal reproducer. [V] |
| 10.b21 | Compiling for cuda-memcheck (p. 456) | Translate debug/symbol requirements to installed Compute Sanitizer; separate debug and performance builds. [V] |
| 10.b22 | memcheck (p. 457) | Detect and repair an isolated out-of-bounds/misaligned access; review leaks/API error reporting. [V] |
| 10.b23 | racecheck (p. 458) | Detect and repair a shared-memory producer/consumer hazard; use synccheck/initcheck for their distinct questions. [V] |
| 10.b24 | Multi-GPU Crypt (p. 473) | Partition independent crypt items, validate a local decomposition control, and defer real multi-GPU scaling. [X,V,T] |
| 10.b25 | Hybrid OpenMP-CUDA Crypt (p. 473) | Study data/task-parallel host/GPU splits; retain an OpenMP-gated implementation plus a local C++-thread control if needed. [X,H,V] |

## Chapter exercises and completion ledger

All end-of-chapter exercises are required coverage, including every lettered subpart and requested variant. Work through them individually after the associated theory or at the chapter gate. Translate obsolete APIs/tools without deleting the original learning question. Each exercise gets its own record of theory, experiment, validation, predicted evidence, and your profile discussion where profiling applies. An unavailable-platform result remains pending rather than being marked passed.

| Chapter | Printed exercise pages | Exercise IDs to complete, including all subparts |
|---|---|---|
| 1 | 22 | 1–6: partitioning, parallel models, GPU platform, and introductory program reasoning |
| 2 | 65 | 1–5: launch geometry, timing, indexing, and program modifications |
| 3 | 132–133 | 1–9: unrolling, reduction, execution/resources, and nested work; include exercise 6 despite its unusual extracted numbering |
| 4 | 200–202 | 1–20: symbols, allocation types, memory access/layout, bandwidth, transpose, and managed memory |
| 5 | 265–266 | 1–15: bank mappings, padding, layouts, reduction, transpose, stencil, and warp exchange |
| 6 | 298 | 1–9: streams, scheduling, events, synchronization, and overlap |
| 7 | 324–325 | 1–10: instruction primitives, numerical behavior, intrinsics, and atomics |
| 8 | 385–386 | 1–14: library workflow, formats/APIs, random generation, and OpenACC |
| 9 | 422–424 | 1–16: multi-device timing, peer access, decomposition, stencil, MPI, and communication; hardware-dependent captures pending |
| 10 | 476 | 1–8: APOD, separate compilation, diagnostics, profiler roles, and integration into the development workflow |

For each chapter, maintain four separate statuses: **reading/theory**, **implementation/validation**, **user profiling/discussion**, and **exercises**. A chapter summary is a gate, not an automatic completion marker. Chapter 9 and tool-gated parts of Chapter 8 may finish local theory/control work while external measurements remain open.

## Appendix: Suggested Readings — pp. 477–480

The appendix has reading groups for **Chapter 1 through Chapter 10**. Review each group at its corresponding chapter gate: identify which architecture/tool/API generation the references describe, record useful supporting explanations, and use current NVIDIA documentation to resolve modern behavior. Preserve all ten groups in the learning ledger. Historical URLs may be unavailable; an unavailable link does not remove the topic. The index (p. 481 onward) is a lookup aid: use it to locate terms and cross-check unresolved concepts rather than treat it as a separate kernel exercise.

## Record template for each smallest subsection

```markdown
# Lesson <sequence> — <book topic>

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | <number — exact chapter title; starting printed page> |
| Section | <exact enclosing section title; starting printed page> |
| Subsection | <exact subsection title, or N/A for a section-level lesson> |
| Reading | <printed page range and stopping heading; prerequisite introductions> |
| Roadmap ID | <navigation ID and relative link to cuda-learning-path.md> |
| Experiment | <functional experiment name and actual kernel names> |
| Status | <draft / approved / validated / awaiting user profile / completed> |

Roadmap IDs are navigation labels, not book-assigned section numbers.
Use these headings consistently: Theory and GPU architecture; Implementation;
Experiment and correctness; Measurements; Expected GPU behavior;
Build and validation; User profiling and discussion; Completion gate.

Status: theory pending | implementation pending | validation pending | user profile pending
Theory and architecture connection:
Question and predicted GPU behavior:
Baseline/control and one independent variable:
Inputs, launch, memory budget, boundaries, reference, and tolerance:
main.cpp orchestration / dedicated .cu files / kernel names:
Build and run: make clean build run
Validation and unprofiled repeated timings:
Target, software, power/clock/temperature, and revision context:
Requested ncu-ui sections/metrics and expected trends:
User-provided report path or screenshots / capture configuration:
Observed evidence and interpretation:
Prediction confirmed/refuted; next discriminating experiment:
Related chapter exercise IDs and all subparts:
Capability limits and pending external work:
Completion discussion and decision to advance:
```

## First approved lesson

Start with **1.1.1, Sequential and Parallel Programming (p. 3)** after the Chapter 1 and Parallel Computing introductions (pp. 1–2). Use the existing scalar vector-add path to identify sequential CPU work, independent output elements, and the costs of dispatch and data handling. Derive a small-input result by hand and predict when GPU overhead dominates. Confirm device/toolchain context and agree on the single-variable size experiment before implementation. The existing float4 code stays a baseline for its later memory/instruction lessons; its presence does not advance the book sequence.

**Approval boundary:** this document proposes the complete path. Source code and build configuration remain unchanged until you approve it. After approval, implementation proceeds one subsection at a time, and kernel profiling remains yours in `ncu-ui`.

## Chapter 1 coverage checkpoint — 2026-11-06

Lessons 1–4 cover pp. 1–11; concise lessons 5–9 finish pp. 12–22, including all
remaining sections, the six exercise questions/subparts, and the Appendix's Chapter 1
reading-group orientation. See [chapter recap](chapter-01-foundations.md).
Current code demonstrates greeting, thread mapping, GPU addition, and CPU follow-up.
`make clean build run` and `make ptx` succeeded. User profiling and discussion remain
open where captures have not been supplied. No Chapter 2 implementation has started.

The user has authorized proceeding without per-lesson approval and prefers concise
coverage of introductory topics. Retain full topic coverage and simple code; spend
greater depth on important CUDA programming and GPU-behavior lessons. Keep PTX
annotations relevant and next to implementation, not invocation.

## Chapter 2 coverage checkpoint — 2026-11-07

Lessons 10–28 cover Chapter 2 in book order. See
[Chapter 2 recap](chapter-02-programming-model.md) for exercises, observed device
limits, and explicit adaptations. Main directly runs matrix mappings and pair/int
variants; all Chapter 1 modules and its combined entry point are preserved.
Automatic numerical checkers and in-program timers remain omitted by preference;
user profiling and best-configuration rankings remain pending. Read the timing and
verification topics conceptually rather than treating them as measured exercises.

## Focused source snapshots — 2026-11-09

The user has superseded the earlier preserve-all-source policy: each lesson commit
contains only its relevant source modules. Previous implementations are preserved in
Git history; Markdown is retained as reference. See [remaining chapter coverage](remaining-chapters-coverage.md)
for every roadmap heading, runnable representative snapshots, and open experiments.
Do not confuse theory/representative coverage with completed numerical, performance,
external-hardware, or full end-of-chapter validation.
