add_library(Commands commands.cpp)

target_include_directories(Commands PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Commands PUBLIC Buffer)
