cmake_minimum_required(VERSION 3.8)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
include(FetchContent)
message(STATUS "Downloading SFML...")
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 7223a5d)
FetchContent_MakeAvailable(SFML)

project(Fractal)

add_executable(Fractal "src/main.cpp")
target_compile_features(Fractal PRIVATE cxx_std_20)
target_link_libraries(Fractal PRIVATE sfml-graphics)