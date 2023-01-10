add_library(UndoRedo undoRedo.cpp)
target_include_directories(UndoRedo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(UndoRedo PUBLIC Buffer Clipboard Commands)

