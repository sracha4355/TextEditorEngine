add_executable(commandsTests commandTests.cpp)

target_link_libraries( commandsTests
	GTest::gtest
	Commands
)
