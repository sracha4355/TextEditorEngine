add_executable(winTests windowTests.cpp)

target_link_libraries(winTests
	Window
	GTest::gtest)
