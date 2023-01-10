add_executable(undoRedoTests undoRedoTests.cpp)
target_link_libraries(undoRedoTests 
	UndoRedo
	GTest::gtest
)
