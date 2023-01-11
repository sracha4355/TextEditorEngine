add_library(Window window.cpp)
target_include_directories(Window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(Window PUBLIC Buffer Clipboard Commands UndoRedo File)
