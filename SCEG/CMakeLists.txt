cmake_minimum_required(VERSION 2.6)
project(SCEG)

file(GLOB SCEG_SRC "src/*.cpp")
file(COPY media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(SFML 2.5 COMPONENTS window system graphics audio REQUIRED)

include_directories("include")
include_directories(${SFML_INCLUDE_DIRS})

if(DEFINED CMAKE_BUILD_TYPE)
	if(CMAKE_BUILD_TYPE STREQUAL CMAKE_BUILD_TYPE)
		add_definitions(-DLOGGER_TO_STDOUT)
	endif(CMAKE_BUILD_TYPE STREQUAL CMAKE_BUILD_TYPE)
endif(DEFINED CMAKE_BUILD_TYPE)

add_executable(SCEG ${SCEG_SRC})
target_link_libraries(SCEG sfml-system sfml-window sfml-graphics sfml-audio)