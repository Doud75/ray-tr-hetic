cmake_minimum_required(VERSION 3.28.3)

project(raytrhetic VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(raytrhetic main.cpp)

#[[there is cMakeList in those directories]]
add_subdirectory(lib/lodepng)
add_subdirectory(src/image)


target_link_libraries(raytrhetic PUBLIC image)