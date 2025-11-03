cmake_minimum_required(VERSION 3.28.3)

project(raytrhetic VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(raytrhetic main.cpp)

add_subdirectory(lib/lodepng)
add_subdirectory(src/image)
add_subdirectory(src/raymath)
add_subdirectory(src/utils)
add_subdirectory(src/shapes)      # <--- AJOUT

target_include_directories(raytrhetic PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)

# Link : ajoute geometry (et raymath si besoin)
target_link_libraries(raytrhetic PUBLIC image utils shapes raymath)
