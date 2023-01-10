add_executable(fileRWTests fileRWTests.cpp)

target_link_libraries(fileRWTests
	LINK_PUBLIC
	File
	GTest::gtest

)


