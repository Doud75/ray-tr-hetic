add_library(raymath Color.cpp Vector.cpp Ray.cpp)
target_include_directories(raymath PUBLIC ${CMAKE_SOURCE_DIR}/include/raymath)