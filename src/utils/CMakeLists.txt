add_library(utils
    Logger.cpp
    PerformanceTimer.cpp
    MemoryMonitor.cpp
    RenderMetrics.cpp
    SceneParser.cpp
)

target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include/utils)
target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include/scene)
target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include/raymath)
target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include/materials)
target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include/shapes)
target_link_libraries(utils PUBLIC nlohmann_json)

if(WIN32)
    target_link_libraries(utils PRIVATE psapi)
endif()


