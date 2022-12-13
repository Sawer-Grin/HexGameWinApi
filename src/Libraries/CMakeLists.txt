cmake_minimum_required(VERSION 3.0.0)
project(GraphMath VERSION 0.1.0)

set(CMAKE_CXX_COMPILER "/usr/bin/x86_64-w64-mingw32-g++")
set(CMAKE_C_COMPILER "/usr/bin/x86_64-w64-mingw32-gcc")
include_directories("/usr/x86_64-w64-mingw32/sys-root/mingw/include/")
link_directories("/usr/x86_64-w64-mingw32/sys-root/mingw/lib/")


set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CXX_COVERAGE_LINK_FLAGS "")
include(CTest)
enable_testing()

add_library(Graph SHARED 
	./src/graph.cpp
)

add_library(GraphMath SHARED
	./src/graph_math.cpp
	./src/graph.cpp
	./src/special_structures/dsu.cpp
)
