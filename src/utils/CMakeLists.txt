add_library(utils
    Logger.cpp
    PerformanceTimer.cpp
    MemoryMonitor.cpp
    RenderMetrics.cpp
)

target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/include/utils)

# Platform-specific libraries for memory monitoring
if(WIN32)
    target_link_libraries(utils PRIVATE psapi)
endif()


