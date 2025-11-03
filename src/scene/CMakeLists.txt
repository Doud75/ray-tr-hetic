add_library(scene Scene.cpp Camera.cpp)
target_include_directories(scene PUBLIC ${CMAKE_SOURCE_DIR}/include/scene)