# Lesson 11 — Managing Memory

## Book location

| Field | Reference |
|---|---|
| Book | Professional CUDA C Programming (2014) |
| Chapter | 2 — CUDA Programming Model |
| Section | Introducing the CUDA Programming Model |
| Subsection | Managing Memory |
| Printed pages | 26–29 |
| Roadmap ID | 2.1.2 — [roadmap](cuda-learning-path.md) |
| Status | Topic covered; build/run record in chapter summary; user profiling pending where applicable |

## Concept and code connection

Host std::vector storage and device allocations are distinct in this program. Sizes passed to cudaMalloc/cudaMemcpy are bytes, not element counts: count * sizeof(float). Copy direction names describe API ownership even on shared physical Orin DRAM. DeviceBuffer releases its allocation at scope exit. Run exercises/chapter-02/memory_roundtrip.cpp to print 1 2 3 4 after an explicit allocation/copy/free round trip. Empty input should bypass a zero-grid launch. Keep buffers valid until GPU use finishes. No forced allocation-failure or numerical comparison code is added.

## Expected observations

A kernel report cannot time a host allocation or attribute pipeline copy costs. No GPU kernel is needed for a memory-copy API exercise.

## Hands-on step and evidence

Read the named implementation or preserved standalone exercise. Main uses direct
calls and printed outputs; each kernel remains in a separate functional .cu file.
Generate `make ptx` and relate only the annotated instructions to their statements.
There are no source timers or numerical result-comparison loops. Visual output and
successful completion do not certify correctness. Small shapes teach indexing;
performance conclusions require your matching captures at appropriate sizes.

## User profiling

Kernel(s): None: host-only round trip. See the [handout](../ncu-profiling/lesson-11-managing-memory.md).
Your profiling/discussion is still open. Move to the next subsection after you can
explain this topic; the chapter summary tracks coverage separately from captures.
