add_library(materials Lambertian.cpp Metal.cpp)
target_include_directories(materials PUBLIC ${CMAKE_SOURCE_DIR}/include/materials)
target_link_libraries(materials PUBLIC raymath)

