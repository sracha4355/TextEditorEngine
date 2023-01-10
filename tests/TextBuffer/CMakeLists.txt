add_executable(tBufferTests textBufferTests.cpp)

target_link_libraries(tBufferTests 
	Buffer
	GTest::gtest
)
