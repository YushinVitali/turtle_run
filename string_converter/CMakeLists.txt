cmake_minimum_required(VERSION 3.5)

project(string_converter VERSION 1.0.0 LANGUAGES CXX DESCRIPTION "String conversion application")

set(CMAKE_BUILD_TYPE			Debug)

set(CMAKE_CXX_STANDARD			17)
set(CMAKE_CXX_STANDARD_REQUIRED	ON)
set(CMAKE_CXX_FLAGS				"${CMAKE_CXX_FLAGS} -Wextra -Werror")

set(CMAKE_SOURCE_DIR			${CMAKE_CURRENT_SOURCE_DIR}/source)

file(GLOB_RECURSE MAIN_SOURCE	${CMAKE_SOURCE_DIR}/*.cpp)


add_executable(${PROJECT_NAME})


target_sources(${PROJECT_NAME}
	PRIVATE ${MAIN_SOURCE})

target_include_directories(${PROJECT_NAME}
	PUBLIC	${CMAKE_SOURCE_DIR})

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
