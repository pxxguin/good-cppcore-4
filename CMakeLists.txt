cmake_minimum_required(VERSION 3.10)
project(lecture-04 CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing")

# Path to the cppcore checkout this project builds against.
set(CPPCORE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../jeon1/cppcore" CACHE PATH "Path to cppcore repo root")
set(CPPCORE_INC_DIR "${CPPCORE_ROOT}/Inc")
set(CPPCORE_LIB "${CPPCORE_ROOT}/Build/LinuxRelease/libcppcore.a")

if(NOT EXISTS "${CPPCORE_LIB}")
	message(FATAL_ERROR
		"libcppcore.a not found at ${CPPCORE_LIB}. "
		"Build cppcore first: cmake -S ${CPPCORE_ROOT} -B ${CPPCORE_ROOT}/build && cmake --build ${CPPCORE_ROOT}/build")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Build)

add_subdirectory(lecture-04-lib)

add_executable(${PROJECT_NAME} main.cpp pch.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/lecture-04-lib
	${CPPCORE_INC_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	lecture-04-lib
	${CPPCORE_LIB}
	pthread
	dl
)
