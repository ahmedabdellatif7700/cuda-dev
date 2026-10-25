cmake_minimum_required(VERSION 3.25)

set(GPU_CUDA_ARCHITECTURES "87" CACHE STRING "CUDA GPU architectures")
set(CMAKE_CUDA_ARCHITECTURES "${GPU_CUDA_ARCHITECTURES}")

project(cpp LANGUAGES CXX CUDA)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/bin"
    CACHE PATH "Executable output directory"
)

find_package(CUDAToolkit REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cu"
)

add_executable(main ${SOURCES})

target_include_directories(main PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# target_link_libraries(main PRIVATE
#     CUDA::cudart
#     CUDA::cublas
# )

set_target_properties(main PROPERTIES
    CUDA_ARCHITECTURES "${GPU_CUDA_ARCHITECTURES}"
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_RESOLVE_DEVICE_SYMBOLS ON
)

target_compile_options(main PRIVATE
    # Host C++ compiler options.
    "$<$<COMPILE_LANGUAGE:CXX>:-Wall;-Wextra;-Wpedantic>"
    "$<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Debug>>:-g;-O0>"
    "$<$<AND:$<COMPILE_LANGUAGE:CXX>,$<CONFIG:Release>>:-O3>"

    # NVIDIA CUDA compiler options.
    "$<$<AND:$<COMPILE_LANGUAGE:CUDA>,$<CONFIG:Debug>>:-g;-G;-O0>"
    "$<$<AND:$<COMPILE_LANGUAGE:CUDA>,$<CONFIG:Release>>:-O3>"
)

# Extract GPU SASS from the compiled executable.
find_program(CUOBJDUMP_EXECUTABLE
    NAMES cuobjdump
    HINTS "${CUDAToolkit_BIN_DIR}"
)

set(SASS_DIR "${CMAKE_BINARY_DIR}/sass")
set(SASS_FILE "${SASS_DIR}/main.sass")
set(SASS_SCRIPT "${CMAKE_BINARY_DIR}/dump_sass-$<CONFIG>.cmake")

file(GENERATE
    OUTPUT "${SASS_SCRIPT}"
    CONTENT "
if(NOT EXISTS \"${CUOBJDUMP_EXECUTABLE}\")
    message(FATAL_ERROR \"cuobjdump was not found. Install CUDA binary utilities and reconfigure.\")
endif()

file(MAKE_DIRECTORY \"${SASS_DIR}\")

execute_process(
    COMMAND \"${CUOBJDUMP_EXECUTABLE}\"
        --dump-sass \"$<TARGET_FILE:main>\"
    OUTPUT_FILE \"${SASS_FILE}\"
    COMMAND_ERROR_IS_FATAL ANY
)

message(STATUS \"SASS file: ${SASS_FILE}\")
"
)

add_custom_target(sass
    COMMAND "${CMAKE_COMMAND}" -P "${SASS_SCRIPT}"
    DEPENDS main
    VERBATIM
)

message(STATUS "")
message(STATUS "C++ / CUDA Configuration")
message(STATUS "CMake            : ${CMAKE_VERSION}")
message(STATUS "Generator        : ${CMAKE_GENERATOR}")
message(STATUS "System           : ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "Build type       : ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ compiler     : ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ standard     : C++${CMAKE_CXX_STANDARD}")
message(STATUS "CUDA compiler    : ${CMAKE_CUDA_COMPILER}")
message(STATUS "CUDA standard    : C++${CMAKE_CUDA_STANDARD}")
message(STATUS "CUDA toolkit     : ${CUDAToolkit_VERSION}")
message(STATUS "CUDA architecture: ${GPU_CUDA_ARCHITECTURES}")
message(STATUS "Target           : main")
message(STATUS "Executable       : ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/main")
message(STATUS "")