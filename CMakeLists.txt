cmake_minimum_required(VERSION 3.0.0)
project(Laba_1 VERSION 0.1.0)

# Settings compilers
set(CMAKE_CXX_COMPILER "/usr/bin/x86_64-w64-mingw32-g++")
set(CMAKE_C_COMPILER "/usr/bin/x86_64-w64-mingw32-gcc")
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CXX_COVERAGE_LINK_FLAGS "")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories("/usr/x86_64-w64-mingw32/sys-root/mingw/include/")
include(CTest)
enable_testing()

#-------------------- Create a library -----------------------------------------
#Generate the shared library from the library sources
#-------------------------------------------------------------------------------

add_library(Graph SHARED 
	./src/Libraries/src/graph.cpp
)

target_include_directories( Graph
	PUBLIC
		 ${PROJECT_SOURCE_DIR}/Libraries
)

add_library(GraphMath SHARED
	./src/Libraries/src/graph_math.cpp
	./src/Libraries/src/graph.cpp
	./src/Libraries/src/special_structures/dsu.cpp
)

target_include_directories( GraphMath
	PUBLIC
		 ${PROJECT_SOURCE_DIR}/Libraries
)

#------------------- Create an executable --------------------------------------

add_executable(
	HexGame WIN32 
	src/main.cpp
	src/Controllers/PlaygraundController.cpp
	src/Controllers/GameSettingController.cpp
	src/GameState.cpp
	src/PlayerState.cpp
)

target_link_libraries(HexGame 
	PRIVATE
		Graph
	-lgdi32
)
target_link_libraries(HexGame
	PRIVATE
		GraphMath
)