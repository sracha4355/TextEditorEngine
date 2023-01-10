add_library(File file.cpp)
target_include_directories(File PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(File PUBLIC Buffer)

