add_executable(clipboardTests clipboardTests.cpp)
target_link_libraries(clipboardTests
	GTest::gtest
	Clipboard
)
