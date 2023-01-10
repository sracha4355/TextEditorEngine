add_library(Buffer buffer.cpp)

target_include_directories(Buffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Buffer PUBLIC GapBuffer )


