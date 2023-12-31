cmake_minimum_required(VERSION 2.8...3.13)
project(find_shortest_path)

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")
set (CMAKE_BUILD_TYPE Debug)

option(WITH_ASAN "Enabled AddressSanitizer to detect memory faults" OFF)
if(WITH_ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined" )
endif()


# create the main executable
## add additional .cpp files if needed
add_executable(main main.cpp helpers.cpp MyGraph.cpp BFStree.cpp)

# create the executable for tests
add_executable(tests test.cpp helpers.cpp MyGraph.cpp BFStree.cpp)
