# Detailed coverage and historical snapshot record

Start with the [10-unit crash course](README.md). The lesson numbers below are
historical Git snapshot IDs, not separate mandatory review lessons. Each commit
preserves its source; the chapter guides consolidate the current review material.

**This is representative teaching coverage, not a claim that every optimization, exercise, or profiling comparison is complete.**

## Lesson snapshots

| Lesson | Chapter / topic | Commit | Execution status |
|---|---|---|---|
| 29 | 3: Execution Architecture | `44603b2` | Runnable representative experiment; user profiling pending |
| 30 | 3: Warp Execution and Resources | `db0a586` | Runnable representative experiment; user profiling pending |
| 31 | 3: Exposing Parallelism | `8529a73` | Runnable representative experiment; user profiling pending |
| 32 | 3: Reduction and Divergence | `aa87fb6` | Runnable representative experiment; user profiling pending |
| 33 | 3: Reduction Unrolling | `aa24c98` | Runnable representative experiment; user profiling pending |
| 34 | 3: Dynamic Parallelism | `f7e1af0` | Runnable representative experiment; user profiling pending |
| 35 | 3: Chapter 3 Review | `bc55848` | Runnable representative experiment; user profiling pending |
| 36 | 4: CUDA Memory Spaces | `2cc3a1a` | Runnable representative experiment; user profiling pending |
| 37 | 4: Memory Management | `0e76e31` | Runnable representative experiment; user profiling pending |
| 38 | 4: Global Access Patterns | `edb5fdd` | Runnable representative experiment; user profiling pending |
| 39 | 4: Bandwidth and Matrix Transpose | `333c835` | Runnable representative experiment; user profiling pending |
| 40 | 4: Matrix Addition with Unified Memory | `c0b2474` | Runnable representative experiment; user profiling pending |
| 41 | 4: Chapter 4 Review | `de11959` | Runnable representative experiment; user profiling pending |
| 42 | 5: Introducing Shared Memory | `7242677` | Runnable representative experiment; user profiling pending |
| 43 | 5: Shared Memory Layout | `cd11149` | Runnable representative experiment; user profiling pending |
| 44 | 5: Reducing Global Access | `f36a737` | Runnable representative experiment; user profiling pending |
| 45 | 5: Coalesced Shared Transpose | `df09b3a` | Runnable representative experiment; user profiling pending |
| 46 | 5: Constant Memory Stencil | `25d368d` | Runnable representative experiment; user profiling pending |
| 47 | 5: Warp Shuffle Communication | `4463541` | Runnable representative experiment; user profiling pending |
| 48 | 5: Chapter 5 Review | `3f9a4ff` | Runnable representative experiment; user profiling pending |
| 49 | 6: Streams Events and Dependencies | `241fceb` | Runnable representative experiment; user profiling pending |
| 50 | 6: Concurrent Kernel Execution | `4ba6307` | Runnable representative experiment; user profiling pending |
| 51 | 6: Transfer and Kernel Pipelines | `08ce89f` | Runnable representative experiment; user profiling pending |
| 52 | 6: CPU GPU Cooperation | `6a3fdaa` | Runnable representative experiment; user profiling pending |
| 53 | 6: Stream Host Functions | `fbaf6be` | Runnable representative experiment; user profiling pending |
| 54 | 6: Chapter 6 Review | `3c226d5` | Runnable representative experiment; user profiling pending |
| 55 | 7: CUDA Instruction Primitives | `90cda0b` | Runnable representative experiment; user profiling pending |
| 56 | 7: Tuning Math and Atomics | `5c6bfcf` | Runnable representative experiment; user profiling pending |
| 57 | 7: Chapter 7 Review | `8014e3f` | Runnable representative experiment; user profiling pending |
| 58 | 8: CUDA Library Workflow | `7422d5f` | Local library call ran; comparative/user profiling pending |
| 59 | 8: Sparse Linear Algebra | `aa0fa3b` | Local library call ran; comparative/user profiling pending |
| 60 | 8: Dense Linear Algebra | `01b743f` | Local library call ran; comparative/user profiling pending |
| 61 | 8: Fourier Transforms | `e8dad0d` | Local library call ran; comparative/user profiling pending |
| 62 | 8: Random Number Generation | `5869243` | Local library call ran; comparative/user profiling pending |
| 63 | 8: Historical CUDA Library Features | `5055d87` | Local library call ran; comparative/user profiling pending |
| 64 | 8: Fair Library Comparisons | `9747236` | Local library call ran; comparative/user profiling pending |
| 65 | 8: OpenACC Directives and Interoperability | `5a7d6ba` | Theory and preserved directive source; OpenACC GPU execution pending |
| 66 | 8: Chapter 8 Review | `9a890d3` | Local library call ran; comparative/user profiling pending |
| 67 | 9: Moving to Multiple GPUs | `5dec539` | Local control/capability evidence; genuine multi-GPU/cluster execution unavailable |
| 68 | 9: Partitioning Across Devices | `d550b35` | Local control/capability evidence; genuine multi-GPU/cluster execution unavailable |
| 69 | 9: Peer Access and UVA | `810f021` | Local control/capability evidence; genuine multi-GPU/cluster execution unavailable |
| 70 | 9: Wave Equation and Halo Exchange | `6435674` | Local control/capability evidence; genuine multi-GPU/cluster execution unavailable |
| 71 | 9: MPI and GPU Clusters | `feb3b79` | Local control/capability evidence; genuine multi-GPU/cluster execution unavailable |
| 72 | 9: Chapter 9 Review | `f8f1b2f` | Local control/capability evidence; genuine multi-GPU/cluster execution unavailable |
| 73 | 10: CUDA Development Process | `3c4a357` | Representative local code ran; full case-study and diagnostic/performance comparisons remain open |
| 74 | 10: Profile Driven Optimization | `a048914` | Representative local code ran; full case-study and diagnostic/performance comparisons remain open |
| 75 | 10: Debugging CUDA | `74843a3` | Representative local code ran; full case-study and diagnostic/performance comparisons remain open |
| 76 | 10: Porting the IDEA Crypt Case Study | `d85f25d` | Representative local code ran; full case-study and diagnostic/performance comparisons remain open |
| 77 | 10: Chapter 10 and Book Review | `84aba61` | Representative local code ran; full case-study and diagnostic/performance comparisons remain open |

## Every remaining roadmap heading

| Chapter / roadmap ID | Book topic and printed page | Covered by |
|---|---|---|
| 3 / 3.0 | CUDA EXECUTION MODEL (p. 67) | lesson 29 |
| 3 / 3.1 | Introducing the CUDA Execution Model (p. 67) | lesson 29 |
| 3 / 3.1.1 | GPU Architecture Overview (p. 68) | lesson 29 |
| 3 / 3.1.2 | The Fermi Architecture (p. 71) | lesson 29 |
| 3 / 3.1.3 | The Kepler Architecture (p. 73) | lesson 29 |
| 3 / 3.1.4 | Profile-Driven Optimization (p. 78) | lesson 29 |
| 3 / 3.2 | Understanding the Nature of Warp Execution (p. 80) | lesson 30 |
| 3 / 3.2.1 | Warps and Thread Blocks (p. 80) | lesson 30 |
| 3 / 3.2.2 | Warp Divergence (p. 82) | lesson 30 |
| 3 / 3.2.3 | Resource Partitioning (p. 87) | lesson 30 |
| 3 / 3.2.4 | Latency Hiding (p. 90) | lesson 30 |
| 3 / 3.2.5 | Occupancy (p. 93) | lesson 30 |
| 3 / 3.2.6 | Synchronization (p. 97) | lesson 30 |
| 3 / 3.2.7 | Scalability (p. 98) | lesson 30 |
| 3 / 3.3 | Exposing Parallelism (p. 98) | lesson 31 |
| 3 / 3.3.1 | Checking Active Warps with nvprof (p. 100) | lesson 31 |
| 3 / 3.3.2 | Checking Memory Operations with nvprof (p. 100) | lesson 31 |
| 3 / 3.3.3 | Exposing More Parallelism (p. 101) | lesson 31 |
| 3 / 3.4 | Avoiding Branch Divergence (p. 104) | lesson 32 |
| 3 / 3.4.1 | The Parallel Reduction Problem (p. 104) | lesson 32 |
| 3 / 3.4.2 | Divergence in Parallel Reduction (p. 106) | lesson 32 |
| 3 / 3.4.3 | Improving Divergence in Parallel Reduction (p. 110) | lesson 32 |
| 3 / 3.4.4 | Reducing with Interleaved Pairs (p. 112) | lesson 32 |
| 3 / 3.5 | Unrolling Loops (p. 114) | lesson 33 |
| 3 / 3.5.1 | Reducing with Unrolling (p. 115) | lesson 33 |
| 3 / 3.5.2 | Reducing with Unrolled Warps (p. 117) | lesson 33 |
| 3 / 3.5.3 | Reducing with Complete Unrolling (p. 119) | lesson 33 |
| 3 / 3.5.4 | Reducing with Template Functions (p. 120) | lesson 33 |
| 3 / 3.6 | Dynamic Parallelism (p. 122) | lesson 34 |
| 3 / 3.6.1 | Nested Execution (p. 123) | lesson 34 |
| 3 / 3.6.2 | Nested Hello World on the GPU (p. 124) | lesson 34 |
| 3 / 3.6.3 | Nested Reduction (p. 128) | lesson 34 |
| 3 / 3.7 | Summary (p. 132) | lesson 35 |
| 4 / 4.0 | GLOBAL MEMORY (p. 135) | lesson 36 |
| 4 / 4.1 | Introducing the CUDA Memory Model (p. 136) | lesson 36 |
| 4 / 4.1.1 | Benefits of a Memory Hierarchy (p. 136) | lesson 36 |
| 4 / 4.1.2 | CUDA Memory Model (p. 137) | lesson 36 |
| 4 / 4.2 | Memory Management (p. 145) | lesson 37 |
| 4 / 4.2.1 | Memory Allocation and Deallocation (p. 146) | lesson 37 |
| 4 / 4.2.2 | Memory Transfer (p. 146) | lesson 37 |
| 4 / 4.2.3 | Pinned Memory (p. 148) | lesson 37 |
| 4 / 4.2.4 | Zero-Copy Memory (p. 150) | lesson 37 |
| 4 / 4.2.5 | Unified Virtual Addressing (p. 156) | lesson 37 |
| 4 / 4.2.6 | Unified Memory (p. 157) | lesson 37 |
| 4 / 4.3 | Memory Access Patterns (p. 158) | lesson 38 |
| 4 / 4.3.1 | Aligned and Coalesced Access (p. 158) | lesson 38 |
| 4 / 4.3.2 | Global Memory Reads (p. 160) | lesson 38 |
| 4 / 4.3.3 | Global Memory Writes (p. 169) | lesson 38 |
| 4 / 4.3.4 | Array of Structures versus Structure of Arrays (p. 171) | lesson 38 |
| 4 / 4.3.5 | Performance Tuning (p. 176) | lesson 38 |
| 4 / 4.4 | What Bandwidth Can a Kernel Achieve? (p. 179) | lesson 39 |
| 4 / 4.4.1 | Memory Bandwidth (p. 179) | lesson 39 |
| 4 / 4.4.2 | Matrix Transpose Problem (p. 180) | lesson 39 |
| 4 / 4.5 | Matrix Addition with Unified Memory (p. 195) | lesson 40 |
| 4 / 4.6 | Summary (p. 199) | lesson 41 |
| 4 / 4.b01 | Registers (p. 138) | lesson 36 |
| 4 / 4.b02 | Local Memory (p. 139) | lesson 36 |
| 4 / 4.b03 | Shared Memory (p. 139) | lesson 36 |
| 4 / 4.b04 | Constant Memory (p. 140) | lesson 36 |
| 4 / 4.b05 | Texture Memory (p. 141) | lesson 36 |
| 4 / 4.b06 | Global Memory (p. 141) | lesson 36 |
| 4 / 4.b07 | GPU Caches (p. 142) | lesson 36 |
| 4 / 4.b08 | CUDA Variable Declaration Summary (p. 142) | lesson 36 |
| 4 / 4.b09 | Static Global Memory (p. 143) | lesson 36 |
| 4 / 4.b10 | Cached Loads (p. 161) | lesson 38 |
| 4 / 4.b11 | Uncached Loads (p. 163) | lesson 38 |
| 4 / 4.b12 | Example of Misaligned Reads (p. 164) | lesson 38 |
| 4 / 4.b13 | Read-Only Cache (p. 168) | lesson 38 |
| 4 / 4.b14 | Example of Misaligned Writes (p. 170) | lesson 38 |
| 4 / 4.b15 | Example: Simple Math with the AoS Data Layout (p. 172) | lesson 38 |
| 4 / 4.b16 | Example: Simple Math with the SoA Data Layout (p. 175) | lesson 38 |
| 4 / 4.b17 | Unrolling Techniques (p. 176) | lesson 38 |
| 4 / 4.b18 | Exposing More Parallelism (p. 177) | lesson 38 |
| 4 / 4.b19 | Setting An Upper and Lower Performance Bound for Transpose Kernels (p. 181) | lesson 39 |
| 4 / 4.b20 | Naive Transpose: Reading Rows versus Reading Columns (p. 185) | lesson 39 |
| 4 / 4.b21 | Unrolling Transpose: Reading Rows versus Reading Columns (p. 187) | lesson 39 |
| 4 / 4.b22 | Diagonal Transpose: Reading Rows versus Reading Columns (p. 189) | lesson 39 |
| 4 / 4.b23 | Expose More Parallelism with Thin Blocks (p. 193) | lesson 39 |
| 5 / 5.0 | SHARED MEMORY AND CONSTANT MEMORY (p. 203) | lesson 42 |
| 5 / 5.1 | Introducing CUDA Shared Memory (p. 204) | lesson 42 |
| 5 / 5.1.1 | Shared Memory (p. 204) | lesson 42 |
| 5 / 5.1.2 | Shared Memory Allocation (p. 206) | lesson 42 |
| 5 / 5.1.3 | Shared Memory Banks and Access Mode (p. 206) | lesson 42 |
| 5 / 5.1.4 | Configuring the Amount of Shared Memory (p. 212) | lesson 42 |
| 5 / 5.1.5 | Synchronization (p. 214) | lesson 42 |
| 5 / 5.2 | Checking the Data Layout of Shared Memory (p. 216) | lesson 43 |
| 5 / 5.2.1 | Square Shared Memory (p. 217) | lesson 43 |
| 5 / 5.2.2 | Rectangular Shared Memory (p. 225) | lesson 43 |
| 5 / 5.3 | Reducing Global Memory Access (p. 232) | lesson 44 |
| 5 / 5.3.1 | Parallel Reduction with Shared Memory (p. 232) | lesson 44 |
| 5 / 5.3.2 | Parallel Reduction with Unrolling (p. 236) | lesson 44 |
| 5 / 5.3.3 | Parallel Reduction with Dynamic Shared Memory (p. 238) | lesson 44 |
| 5 / 5.3.4 | Effective Bandwidth (p. 239) | lesson 44 |
| 5 / 5.4 | Coalescing Global Memory Accesses (p. 239) | lesson 45 |
| 5 / 5.4.1 | Baseline Transpose Kernel (p. 240) | lesson 45 |
| 5 / 5.4.2 | Matrix Transpose with Shared Memory (p. 241) | lesson 45 |
| 5 / 5.4.3 | Matrix Transpose with Padded Shared Memory (p. 245) | lesson 45 |
| 5 / 5.4.4 | Matrix Transpose with Unrolling (p. 246) | lesson 45 |
| 5 / 5.4.5 | Exposing More Parallelism (p. 249) | lesson 45 |
| 5 / 5.5 | Constant Memory (p. 250) | lesson 46 |
| 5 / 5.5.1 | Implementing a 1D Stencil with Constant Memory (p. 250) | lesson 46 |
| 5 / 5.5.2 | Comparing with the Read-Only Cache (p. 253) | lesson 46 |
| 5 / 5.6 | The Warp Shuffle Instruction (p. 255) | lesson 47 |
| 5 / 5.6.1 | Variants of the Warp Shuffle Instruction (p. 256) | lesson 47 |
| 5 / 5.6.2 | Sharing Data within a Warp (p. 258) | lesson 47 |
| 5 / 5.6.3 | Parallel Reduction Using the Warp Shuffle Instruction (p. 262) | lesson 47 |
| 5 / 5.7 | Summary (p. 264) | lesson 48 |
| 5 / 5.b01 | Memory Banks (p. 206) | lesson 42 |
| 5 / 5.b02 | Bank Conflict (p. 207) | lesson 42 |
| 5 / 5.b03 | Access Mode (p. 208) | lesson 42 |
| 5 / 5.b04 | Memory Padding (p. 211) | lesson 42 |
| 5 / 5.b05 | Access Mode Configuration (p. 212) | lesson 42 |
| 5 / 5.b06 | Weakly-Ordered Memory Model (p. 214) | lesson 42 |
| 5 / 5.b07 | Explicit Barrier (p. 214) | lesson 42 |
| 5 / 5.b08 | Memory Fence (p. 215) | lesson 42 |
| 5 / 5.b09 | Volatile Qualifier (p. 216) | lesson 43 |
| 5 / 5.b10 | Accessing Row-Major versus Column-Major (p. 218) | lesson 43 |
| 5 / 5.b11 | Writing Row-Major and Reading Column-Major (p. 220) | lesson 43 |
| 5 / 5.b12 | Dynamic Shared Memory (p. 221) | lesson 43 |
| 5 / 5.b13 | Padding Statically Declared Shared Memory (p. 223) | lesson 43 |
| 5 / 5.b14 | Padding Dynamically Declared Shared Memory (p. 223) | lesson 43 |
| 5 / 5.b15 | Comparing the Performance of the Square Shared Memory Kernels (p. 225) | lesson 43 |
| 5 / 5.b16 | Accessing Row-Major versus Accessing Column-Major (p. 226) | lesson 43 |
| 5 / 5.b17 | Writing Row-Major and Reading Column-Major (p. 227) | lesson 43 |
| 5 / 5.b18 | Dynamically Declared Shared Memory (p. 228) | lesson 43 |
| 5 / 5.b19 | Padding Statically Declared Shared Memory (p. 229) | lesson 43 |
| 5 / 5.b20 | Padding Dynamically Declared Shared Memory (p. 230) | lesson 43 |
| 5 / 5.b21 | Comparing the Performance of the Rectangular Shared Memory Kernels (p. 231) | lesson 43 |
| 5 / 5.b22 | Broadcast of a Value across a Warp (p. 258) | lesson 47 |
| 5 / 5.b23 | Shift Up within a Warp (p. 258) | lesson 47 |
| 5 / 5.b24 | Shift Down within a Warp (p. 259) | lesson 47 |
| 5 / 5.b25 | Shift within a warp with Wrap Around (p. 259) | lesson 47 |
| 5 / 5.b26 | Butterfly Exchange across the Warp (p. 260) | lesson 47 |
| 5 / 5.b27 | Exchange Values of an Array across a Warp (p. 260) | lesson 47 |
| 5 / 5.b28 | Exchange Values Using Array Indices Across a Warp (p. 261) | lesson 47 |
| 6 / 6.0 | STREAMS AND CONCURRENCY (p. 267) | lesson 49 |
| 6 / 6.1 | Introducing Streams and Events (p. 268) | lesson 49 |
| 6 / 6.1.1 | CUDA Streams (p. 269) | lesson 49 |
| 6 / 6.1.2 | Stream Scheduling (p. 271) | lesson 49 |
| 6 / 6.1.3 | Stream Priorities (p. 273) | lesson 49 |
| 6 / 6.1.4 | CUDA Events (p. 273) | lesson 49 |
| 6 / 6.1.5 | Stream Synchronization (p. 275) | lesson 49 |
| 6 / 6.2 | Concurrent Kernel Execution (p. 279) | lesson 50 |
| 6 / 6.2.1 | Concurrent Kernels in Non-NULL Streams (p. 279) | lesson 50 |
| 6 / 6.2.2 | False Dependencies on Fermi GPUs (p. 281) | lesson 50 |
| 6 / 6.2.3 | Dispatching Operations with OpenMP (p. 283) | lesson 50 |
| 6 / 6.2.4 | Adjusting Stream Behavior Using Environment Variables (p. 284) | lesson 50 |
| 6 / 6.2.5 | Concurrency-Limiting GPU Resources (p. 286) | lesson 50 |
| 6 / 6.2.6 | Blocking Behavior of the Default Stream (p. 287) | lesson 50 |
| 6 / 6.2.7 | Creating Inter-Stream Dependencies (p. 288) | lesson 50 |
| 6 / 6.3 | Overlapping Kernel Execution and Data Transfer (p. 289) | lesson 51 |
| 6 / 6.3.1 | Overlap Using Depth-First Scheduling (p. 289) | lesson 51 |
| 6 / 6.3.2 | Overlap Using Breadth-First Scheduling (p. 293) | lesson 51 |
| 6 / 6.4 | Overlapping GPU and CPU Execution (p. 294) | lesson 52 |
| 6 / 6.5 | Stream Callbacks (p. 295) | lesson 53 |
| 6 / 6.6 | Summary (p. 297) | lesson 54 |
| 6 / 6.b01 | False Dependencies (p. 272) | lesson 49 |
| 6 / 6.b02 | Hyper-Q (p. 272) | lesson 49 |
| 6 / 6.b03 | Creation and Destruction (p. 273) | lesson 49 |
| 6 / 6.b04 | Recording Events and Measuring Elapsed Time (p. 274) | lesson 49 |
| 6 / 6.b05 | Blocking and Non-Blocking Streams (p. 276) | lesson 49 |
| 6 / 6.b06 | Implicit Synchronization (p. 276) | lesson 49 |
| 6 / 6.b07 | Explicit Synchronization (p. 277) | lesson 49 |
| 6 / 6.b08 | Configurable Events (p. 278) | lesson 49 |
| 7 / 7.0 | TUNING INSTRUCTION-LEVEL PRIMITIVES (p. 299) | lesson 55 |
| 7 / 7.1 | Introducing CUDA Instructions (p. 300) | lesson 55 |
| 7 / 7.1.1 | Floating-Point Instructions (p. 301) | lesson 55 |
| 7 / 7.1.2 | Intrinsic and Standard Functions (p. 303) | lesson 55 |
| 7 / 7.1.3 | Atomic Instructions (p. 304) | lesson 55 |
| 7 / 7.2 | Optimizing Instructions for Your Application (p. 306) | lesson 56 |
| 7 / 7.2.1 | Single-Precision vs. Double-Precision (p. 306) | lesson 56 |
| 7 / 7.2.2 | Standard vs. Intrinsic Functions (p. 309) | lesson 56 |
| 7 / 7.2.3 | Understanding Atomic Instructions (p. 315) | lesson 56 |
| 7 / 7.2.4 | Bringing It All Together (p. 322) | lesson 56 |
| 7 / 7.3 | Summary (p. 324) | lesson 57 |
| 7 / 7.b01 | Summary (p. 308) | lesson 56 |
| 7 / 7.b02 | Visualizing Standard and Intrinsic Functions (p. 309) | lesson 56 |
| 7 / 7.b03 | Manipulating Instruction Generation (p. 311) | lesson 56 |
| 7 / 7.b04 | Summary (p. 315) | lesson 56 |
| 7 / 7.b05 | From the Ground Up (p. 315) | lesson 56 |
| 7 / 7.b06 | Built-In CUDA Atomic Functions (p. 317) | lesson 56 |
| 7 / 7.b07 | The Cost of Atomic Operations (p. 318) | lesson 56 |
| 7 / 7.b08 | Limiting the Performance Cost of Atomic Operations (p. 319) | lesson 56 |
| 7 / 7.b09 | Atomic Floating-Point Support (p. 320) | lesson 56 |
| 7 / 7.b10 | Summary (p. 321) | lesson 56 |
| 8 / 8.0 | GPU-ACCELERATED CUDA LIBRARIES AND OPENACC (p. 327) | lesson 58 |
| 8 / 8.1 | Introducing the CUDA Libraries (p. 328) | lesson 58 |
| 8 / 8.1.1 | Supported Domains for CUDA Libraries (p. 329) | lesson 58 |
| 8 / 8.1.2 | A Common Library Workflow (p. 330) | lesson 58 |
| 8 / 8.2 | The CUSPARSE Library (p. 332) | lesson 59 |
| 8 / 8.2.1 | cuSPARSE Data Storage Formats (p. 333) | lesson 59 |
| 8 / 8.2.2 | Formatting Conversion with cuSPARSE (p. 337) | lesson 59 |
| 8 / 8.2.3 | Demonstrating cuSPARSE (p. 338) | lesson 59 |
| 8 / 8.2.4 | Important Topics in cuSPARSE Development (p. 340) | lesson 59 |
| 8 / 8.2.5 | cuSPARSE Summary (p. 341) | lesson 59 |
| 8 / 8.3 | The cuBLAS Library (p. 341) | lesson 60 |
| 8 / 8.3.1 | Managing cuBLAS Data (p. 342) | lesson 60 |
| 8 / 8.3.2 | Demonstrating cuBLAS (p. 343) | lesson 60 |
| 8 / 8.3.3 | Important Topics in cuBLAS Development (p. 345) | lesson 60 |
| 8 / 8.3.4 | cuBLAS Summary (p. 346) | lesson 60 |
| 8 / 8.4 | The cuFFT Library (p. 346) | lesson 61 |
| 8 / 8.4.1 | Using the cuFFT API (p. 347) | lesson 61 |
| 8 / 8.4.2 | Demonstrating cuFFT (p. 348) | lesson 61 |
| 8 / 8.4.3 | cuFFT Summary (p. 349) | lesson 61 |
| 8 / 8.5 | The cuRAND Library (p. 349) | lesson 62 |
| 8 / 8.5.1 | Choosing Pseudo- or Quasi- Random Numbers (p. 349) | lesson 62 |
| 8 / 8.5.2 | Overview of the cuRAND Library (p. 350) | lesson 62 |
| 8 / 8.5.3 | Demonstrating cuRAND (p. 354) | lesson 62 |
| 8 / 8.5.4 | Important Topics in cuRAND Development (p. 357) | lesson 62 |
| 8 / 8.6 | CUDA Library Features Introduced in CUDA 6 (p. 358) | lesson 63 |
| 8 / 8.6.1 | Drop-In CUDA Libraries (p. 358) | lesson 63 |
| 8 / 8.6.2 | Multi-GPU Libraries (p. 359) | lesson 63 |
| 8 / 8.7 | A Survey of CUDA Library Performance (p. 361) | lesson 64 |
| 8 / 8.7.1 | cuSPARSE versus MKL (p. 361) | lesson 64 |
| 8 / 8.7.2 | cuBLAS versus MKL BLAS (p. 362) | lesson 64 |
| 8 / 8.7.3 | cuFFT versus FFTW versus MKL (p. 363) | lesson 64 |
| 8 / 8.7.4 | CUDA Library Performance Summary (p. 364) | lesson 64 |
| 8 / 8.8 | Using OpenACC (p. 365) | lesson 65 |
| 8 / 8.8.1 | Using OpenACC Compute Directives (p. 367) | lesson 65 |
| 8 / 8.8.2 | Using OpenACC Data Directives (p. 375) | lesson 65 |
| 8 / 8.8.3 | The OpenACC Runtime API (p. 380) | lesson 65 |
| 8 / 8.8.4 | Combining OpenACC and the CUDA Libraries (p. 382) | lesson 65 |
| 8 / 8.8.5 | Summary of OpenACC (p. 384) | lesson 65 |
| 8 / 8.9 | Summary (p. 384) | lesson 66 |
| 8 / 8.b01 | Stage 1: Creating a Library Handle (p. 331) | lesson 58 |
| 8 / 8.b02 | Stage 2: Allocating Device Memory (p. 331) | lesson 58 |
| 8 / 8.b03 | Stage 3: Converting Inputs to a Library-Supported Format (p. 331) | lesson 58 |
| 8 / 8.b04 | Stage 4: Populating Device Memory with Inputs (p. 331) | lesson 58 |
| 8 / 8.b05 | Stage 5: Configuring the Library (p. 331) | lesson 58 |
| 8 / 8.b06 | Stage 6: Executing (p. 332) | lesson 59 |
| 8 / 8.b07 | Stage 7: Retrieving Results from Device Memory (p. 332) | lesson 59 |
| 8 / 8.b08 | Stage 8: Converting Back to Native Format (p. 332) | lesson 59 |
| 8 / 8.b09 | Stage 9: Releasing CUDA Resources (p. 332) | lesson 59 |
| 8 / 8.b10 | Stage 10: Continuing with the Application (p. 332) | lesson 59 |
| 8 / 8.b11 | Dense (p. 334) | lesson 59 |
| 8 / 8.b12 | Coordinate (COO) (p. 334) | lesson 59 |
| 8 / 8.b13 | Compressed Sparse Row (CSR) (p. 334) | lesson 59 |
| 8 / 8.b14 | cuSPARSE Storage Formats Summary (p. 336) | lesson 59 |
| 8 / 8.b15 | A Simple cuBLAS Example (p. 343) | lesson 60 |
| 8 / 8.b16 | Porting from BLAS (p. 344) | lesson 60 |
| 8 / 8.b17 | Covering the Concepts (p. 351) | lesson 62 |
| 8 / 8.b18 | Comparing the Host and Device APIs (p. 353) | lesson 62 |
| 8 / 8.b19 | Replacing rand() (p. 354) | lesson 62 |
| 8 / 8.b20 | Generating Randomness for CUDA Kernels (p. 357) | lesson 62 |
| 8 / 8.b21 | Using the kernels Directive (p. 367) | lesson 65 |
| 8 / 8.b22 | Using the parallel Directive (p. 370) | lesson 65 |
| 8 / 8.b23 | Using the loop Directive (p. 372) | lesson 65 |
| 8 / 8.b24 | OpenACC Compute Directives Summary (p. 375) | lesson 65 |
| 8 / 8.b25 | Using the data Directive (p. 375) | lesson 65 |
| 8 / 8.b26 | Adding Data Clauses to kernels and parallel Directives (p. 379) | lesson 65 |
| 9 / 9.0 | MULTI-GPU PROGRAMMING (p. 387) | lesson 67 |
| 9 / 9.1 | Moving to Multiple GPUs (p. 388) | lesson 67 |
| 9 / 9.1.1 | Executing on Multiple GPUs (p. 389) | lesson 67 |
| 9 / 9.1.2 | Peer-to-Peer Communication (p. 391) | lesson 67 |
| 9 / 9.1.3 | Synchronizing across Multi-GPUs (p. 392) | lesson 67 |
| 9 / 9.2 | Subdividing Computation across Multiple GPUs (p. 393) | lesson 68 |
| 9 / 9.2.1 | Allocating Memory on Multiple Devices (p. 393) | lesson 68 |
| 9 / 9.2.2 | Distributing Work from a Single Host Thread (p. 394) | lesson 68 |
| 9 / 9.2.3 | Compiling and Executing (p. 395) | lesson 68 |
| 9 / 9.3 | Peer-to-Peer Communication on Multiple GPUs (p. 396) | lesson 69 |
| 9 / 9.3.1 | Enabling Peer-to-Peer Access (p. 396) | lesson 69 |
| 9 / 9.3.2 | Peer-to-Peer Memory Copy (p. 396) | lesson 69 |
| 9 / 9.3.3 | Peer-to-Peer Memory Access with Unified Virtual Addressing (p. 398) | lesson 69 |
| 9 / 9.4 | Finite Difference on Multi-GPU (p. 400) | lesson 70 |
| 9 / 9.4.1 | Stencil Calculation for 2D Wave Equation (p. 400) | lesson 70 |
| 9 / 9.4.2 | Typical Patterns for Multi-GPU Programs (p. 401) | lesson 70 |
| 9 / 9.4.3 | 2D Stencil Computation with Multiple GPUs (p. 403) | lesson 70 |
| 9 / 9.4.4 | Overlapping Computation and Communication (p. 405) | lesson 70 |
| 9 / 9.4.5 | Compiling and Executing (p. 406) | lesson 70 |
| 9 / 9.5 | Scaling Applications across GPU Clusters (p. 409) | lesson 71 |
| 9 / 9.5.1 | CPU-to-CPU Data Transfer (p. 410) | lesson 71 |
| 9 / 9.5.2 | GPU-to-GPU Data Transfer Using Traditional MPI (p. 413) | lesson 71 |
| 9 / 9.5.3 | GPU-to-GPU Data Transfer with CUDA-aware MPI (p. 416) | lesson 71 |
| 9 / 9.5.4 | Intra-Node GPU-to-GPU Data Transfer with CUDA-Aware MPI (p. 417) | lesson 71 |
| 9 / 9.5.5 | Adjusting Message Chunk Size (p. 418) | lesson 71 |
| 9 / 9.5.6 | GPU to GPU Data Transfer with GPUDirect RDMA (p. 419) | lesson 71 |
| 9 / 9.6 | Summary (p. 422) | lesson 72 |
| 9 / 9.b01 | Enabling Peer Access (p. 391) | lesson 67 |
| 9 / 9.b02 | Peer-to-Peer Memory Copy (p. 392) | lesson 67 |
| 9 / 9.b03 | Implementing Inter-Node MPI Communication (p. 411) | lesson 71 |
| 9 / 9.b04 | CPU Affinity (p. 412) | lesson 71 |
| 9 / 9.b05 | Affinity in MPI-CUDA Programs (p. 413) | lesson 71 |
| 9 / 9.b06 | Performing GPU-to-GPU Communication With MPI (p. 415) | lesson 71 |
| 10 / 10.0 | IMPLEMENTATION CONSIDERATIONS (p. 425) | lesson 73 |
| 10 / 10.1 | The CUDA C Development Process (p. 426) | lesson 73 |
| 10 / 10.1.1 | APOD Development Cycle (p. 426) | lesson 73 |
| 10 / 10.1.2 | Optimization Opportunities (p. 429) | lesson 73 |
| 10 / 10.1.3 | CUDA Code Compilation (p. 432) | lesson 73 |
| 10 / 10.1.4 | CUDA Error Handling (p. 437) | lesson 73 |
| 10 / 10.2 | Profile-Driven Optimization (p. 438) | lesson 74 |
| 10 / 10.2.1 | Finding Optimization Opportunities Using nvprof (p. 439) | lesson 74 |
| 10 / 10.2.2 | Guiding Optimization Using nvvp (p. 443) | lesson 74 |
| 10 / 10.2.3 | NVIDIA Tools Extension (p. 446) | lesson 74 |
| 10 / 10.3 | CUDA Debugging (p. 448) | lesson 75 |
| 10 / 10.3.1 | Kernel Debugging (p. 448) | lesson 75 |
| 10 / 10.3.2 | Memory Debugging (p. 456) | lesson 75 |
| 10 / 10.3.3 | Debugging Summary (p. 462) | lesson 75 |
| 10 / 10.4 | A Case Study in Porting C Programs to CUDA C (p. 462) | lesson 76 |
| 10 / 10.4.1 | Assessing crypt (p. 463) | lesson 76 |
| 10 / 10.4.2 | Parallelizing crypt (p. 464) | lesson 76 |
| 10 / 10.4.3 | Optimizing crypt (p. 465) | lesson 76 |
| 10 / 10.4.4 | Deploying Crypt (p. 472) | lesson 76 |
| 10 / 10.4.5 | Summary of Porting crypt (p. 475) | lesson 76 |
| 10 / 10.5 | Summary (p. 476) | lesson 77 |
| 10 / 10.b01 | Assessment (p. 427) | lesson 73 |
| 10 / 10.b02 | Parallelization (p. 427) | lesson 73 |
| 10 / 10.b03 | Optimization (p. 428) | lesson 73 |
| 10 / 10.b04 | Deployment (p. 429) | lesson 73 |
| 10 / 10.b05 | Exposing Sufficient Parallelism (p. 430) | lesson 73 |
| 10 / 10.b06 | Optimizing Memory Access (p. 430) | lesson 73 |
| 10 / 10.b07 | Optimizing Instruction Execution (p. 432) | lesson 73 |
| 10 / 10.b08 | Separate Compilation (p. 434) | lesson 73 |
| 10 / 10.b09 | Sample Makefile (p. 434) | lesson 73 |
| 10 / 10.b10 | Integrating CUDA Files into a C Project (p. 436) | lesson 73 |
| 10 / 10.b11 | Profiling Modes (p. 439) | lesson 74 |
| 10 / 10.b12 | Profiling Scope (p. 440) | lesson 74 |
| 10 / 10.b13 | Memory Bandwidth (p. 440) | lesson 74 |
| 10 / 10.b14 | Instruction Throughput (p. 443) | lesson 74 |
| 10 / 10.b15 | Guided Analysis (p. 444) | lesson 74 |
| 10 / 10.b16 | Unguided Analysis (p. 444) | lesson 74 |
| 10 / 10.b17 | Using cuda-gdb (p. 448) | lesson 75 |
| 10 / 10.b18 | CUDA printf (p. 454) | lesson 75 |
| 10 / 10.b19 | CUDA assert (p. 455) | lesson 75 |
| 10 / 10.b20 | Kernel Debugging Summary (p. 456) | lesson 75 |
| 10 / 10.b21 | Compiling for cuda-memcheck (p. 456) | lesson 75 |
| 10 / 10.b22 | memcheck (p. 457) | lesson 75 |
| 10 / 10.b23 | racecheck (p. 458) | lesson 75 |
| 10 / 10.b24 | Multi-GPU Crypt (p. 473) | lesson 76 |
| 10 / 10.b25 | Hybrid OpenMP-CUDA Crypt (p. 473) | lesson 76 |

## What is still open

- All unsupplied ncu-ui captures, matched performance comparisons, throughput/latency claims, and configuration rankings.
- Full numerical reference/error-domain/statistical validation, deliberately not inserted into the simple teaching programs.
- Every requested end-of-chapter extension that is not explicitly implemented by its representative source. Chapters 3–10 have 9, 20, 15, 9, 10, 14, 16, and 8 questions respectively. Their measured optimization tasks are not marked passed.
- Historical Fermi/Kepler measurements and removed API/UI behaviors; discuss the model without claiming Orin reproduces the hardware.
- Actual OpenACC GPU compilation/offload, MKL comparisons, real multi-GPU/P2P, network scaling, CUDA-aware MPI and GPUDirect RDMA.
- The complete downloaded legacy IDEA crypt application, decryption key schedule, file pipeline, and hybrid/multi-GPU deployment. The final implementation is a focused encryption adaptation.

## Appendix and index

The suggested-reading appendix (pp. 477–480) has groups for all ten chapters.
Review each as supporting material; historical links/tool versions are not commands
to execute. The index beginning p. 481 is a lookup resource rather than another
kernel exercise. Keep core concepts, representative code, and pending experiments
as separate statuses when returning to these topics.

## Checkout convention

To study a prior lesson, use its commit from the table in a separate worktree or
clean checkout. Do not restore every old source into the latest branch. Source links
in historical Markdown may refer to that lesson snapshot. The current source stays
small and focused. Kernel profiling is performed by the user, never automatically.

## Final local diagnostic attempt — 2026-11-09

The final IDEA snapshot printed `11fb ed2b 0198 6de5` for the documented input/key.
This is an observed output, not a full encryption/decryption validation suite.
`compute-sanitizer --tool memcheck ./bin/main` reported that GPU debugging features
are disabled and emitted an error summary. The program still printed its result,
but **memcheck validation is unavailable**, not passed. No profiler was run.
