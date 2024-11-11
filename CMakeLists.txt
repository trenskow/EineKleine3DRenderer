cmake_minimum_required(VERSION 3.10...3.31)

project(EineKleine3DRenderer DESCRIPTION "A very tiny 3D renderer.")

add_library(EineKleine3DRenderer SHARED
	src/Camera.cpp
	src/Face.cpp
	src/Matrix.cpp
	src/Renderer.cpp
	src/Vertex.cpp)

set(ARCH_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE}/${CMAKE_SYSTEM_PROCESSOR}")

set_target_properties(EineKleine3DRenderer
	PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY "${ARCH_OUTPUT_DIR}/lib"
	RUNTIME_OUTPUT_DIRECTORY "${ARCH_OUTPUT_DIR}/bin")

target_compile_features(EineKleine3DRenderer PRIVATE cxx_std_17)
