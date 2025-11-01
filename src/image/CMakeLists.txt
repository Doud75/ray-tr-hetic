add_library(image Image.cpp)
target_include_directories(image PUBLIC ${CMAKE_SOURCE_DIR}/include/image)

target_link_libraries(image PRIVATE raymath)
target_link_libraries(image PUBLIC lodepng)