add_library(shapes Sphere.cpp Plane.cpp Cube.cpp)
target_include_directories(shapes PUBLIC ${CMAKE_SOURCE_DIR}/include/shapes)
target_link_libraries(shapes PUBLIC raymath)