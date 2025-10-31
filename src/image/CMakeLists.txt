add_library(image ${CMAKE_CURRENT_SOURCE_DIR}/Image.cpp)

target_include_directories(image PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(image PUBLIC lodepng)