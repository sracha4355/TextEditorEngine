add_library(Controller controller.cpp)

target_include_directories(Controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Controller PUBLIC Buffer File)

