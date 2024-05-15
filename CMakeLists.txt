# general setup
cmake_minimum_required(VERSION 3.0.0)
project(Terminecraft LANGUAGES CXX)

include(CTest)
enable_testing()

# include header files
include_directories(src)
include_directories(include)

# main
add_executable(
	${PROJECT_NAME} 
	src/main.cpp
)

# catch
add_library(Catch INTERFACE)
target_include_directories(Catch
	INTERFACE
		test/
)

add_executable(
	tests
	test/test_game.cpp
	test/test_vec3.cpp
	test/test_vecs.cpp
)