# Chapter 1 standalone greeting exercises

These preserve the exact sources and observations used for printed p. 22,
exercises 2–4. Each has its own main, so they live outside `src/` and do not
change the application's Make/CMake build. Launch-order output is not guaranteed.

Run from the repository root (outputs stay under ignored `build/`):

```bash
export PATH="/usr/local/cuda-13.2/bin:$PATH"
mkdir -p build/chapter-01-exercises
nvcc -arch=sm_87 exercises/chapter-01/no_wait.cu -o build/chapter-01-exercises/no_wait
nvcc -arch=sm_87 exercises/chapter-01/synchronize.cu -o build/chapter-01-exercises/synchronize
nvcc -arch=sm_87 exercises/chapter-01/reset.cu -o build/chapter-01-exercises/reset
nvcc exercises/chapter-01/default_arch.cu -o build/chapter-01-exercises/default_arch
build/chapter-01-exercises/no_wait
build/chapter-01-exercises/synchronize
build/chapter-01-exercises/reset
build/chapter-01-exercises/default_arch
```

`observations-2026-11-06.json` records the original run, not universal outcomes.
No-wait may finish without flushing device printf. Reset is intentionally isolated
in a separate process and is not called on the main application's live resources.
Keep explicit architecture 87 for the normal repository build.

The main application's sources retain scalar/cyclic addition, thread mapping,
and the greeting wrapper. To revisit cyclic addition, call `VectorAddCyclic` with
the same arrays and a positive grid cap; no lesson selector is introduced.

## Revisit the Chapter 1 combined program

`combined_main.cpp` preserves the greeting/mapping/addition/CPU-sum program:

```bash
nvcc -std=c++20 -arch=sm_87 -Iinclude exercises/chapter-01/combined_main.cpp src/gpu_greeting.cu src/thread_mapping.cpp src/thread_mapping.cu src/vector_add.cpp src/vector_add.cu src/vector_add_cyclic.cu src/vector_add_pairs.cu -o build/chapter1_combined
build/chapter1_combined
```
