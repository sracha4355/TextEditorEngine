add_library(Clipboard clipboard.cpp)

target_include_directories(Clipboard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Clipboard PUBLIC Buffer Commands File)
