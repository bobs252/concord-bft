# Use Google Benchmark as a benchmarking library: https://github.com/google/benchmark
#
# Note: Benchmarks are not officially supported yet and are optional. Use QUIET to
# silence CMake in case Google Benchmark is not installed.
find_package(benchmark QUIET)

if(benchmark_FOUND)
    add_executable(sparse_merkle_benchmark sparse_merkle_benchmark.cpp )
    target_link_libraries(sparse_merkle_benchmark PUBLIC
        benchmark
        util
        corebft
        kvbc
    )
endif()
