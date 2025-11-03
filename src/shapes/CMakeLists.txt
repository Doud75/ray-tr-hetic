add_library(shapes Sphere.cpp)
# Expose les headers via le dossier include/
target_include_directories(shapes PUBLIC ${CMAKE_SOURCE_DIR}/include/shapes)
#target_link_libraries(shapes PUBLIC raymath)
