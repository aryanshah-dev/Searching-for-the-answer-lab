
cmake_minimum_required(VERSION 3.20)

project(InvertedFileIndex)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(InvertedIndex main.cpp)

add_executable(InvertedBenchmark benchmark.cpp)

target_link_libraries(
        InvertedBenchmark
        PRIVATE Catch2::Catch2WithMain
)
