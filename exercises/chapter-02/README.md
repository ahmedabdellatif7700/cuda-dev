# Chapter 2 standalone exercises

Run from the repository root after the normal `make clean build run`:

```bash
export PATH="/usr/local/cuda-13.2/bin:$PATH"
nvcc -std=c++20 exercises/chapter-02/memory_roundtrip.cpp -o build/memory_roundtrip
build/memory_roundtrip
nvcc -arch=sm_87 exercises/chapter-02/launch_errors.cu -o build/launch_errors
build/launch_errors
nvcc -std=c++20 -arch=sm_87 -Iinclude exercises/chapter-02/launch_sizes.cpp src/vector_add.cpp src/vector_add.cu src/vector_add_cyclic.cu src/vector_add_pairs.cu -o build/launch_sizes
build/launch_sizes
```

Observed 2026-11-07: memory round-trip printed `1 2 3 4`; zero-thread launch
reported `invalid argument`; legal completion reported `no error`; invalid-device
selection reported `invalid device ordinal`. Both 1023/1024-thread runs printed
first/last sums `3 3`. These are status/visual observations, not full numerical tests.
Capture those two kernels yourself to compare performance. Different tools/runtimes
can phrase error messages differently. Each standalone entry point stays outside
`src/` to avoid duplicate mains in the normal executable.
