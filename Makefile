# Modern C++ and CUDA development.

.DEFAULT_GOAL := build

BUILD_TYPE ?= Release
BUILD_DIR  ?= build
BIN_DIR    ?= bin
JOBS       ?= 4
ARGS       ?=

GPU_CUDA_ARCHITECTURES ?= 87

BINARY := $(BIN_DIR)/main

.PHONY: clean configure build run debug cuda-debug sass

clean:
	@echo "Cleaning C++ and CUDA build artifacts..."
	@rm -rf -- "$(BUILD_DIR)" "$(BIN_DIR)"

configure:
	@cmake -S . -B "$(BUILD_DIR)" -G Ninja \
		-DCMAKE_BUILD_TYPE="$(BUILD_TYPE)" \
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY="$(abspath $(BIN_DIR))" \
		-DGPU_CUDA_ARCHITECTURES="$(GPU_CUDA_ARCHITECTURES)"

build: configure
	@echo
	@echo "Building C++ / CUDA application..."
	@cmake --build "$(BUILD_DIR)" --parallel "$(JOBS)"

run: build
	@echo
	@echo "Running C++ / CUDA application..."
	@"$(abspath $(BINARY))" $(ARGS)

debug:
	@echo
	@echo "Debugging host code with GDB..."
	@$(MAKE) build BUILD_TYPE=Debug
	@gdb --args "$(abspath $(BINARY))" $(ARGS)

cuda-debug:
	@echo
	@echo "Debugging CUDA code with cuda-gdb..."
	@$(MAKE) build BUILD_TYPE=Debug
	@cuda-gdb --args "$(abspath $(BINARY))" $(ARGS)

sass: configure
	@echo
	@echo "Extracting GPU SASS..."
	@cmake --build "$(BUILD_DIR)" --target sass --parallel "$(JOBS)"