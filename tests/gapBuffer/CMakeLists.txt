#cmake tests/gapBuffer

add_executable(gbufferTests gapBufferTests.cpp)

target_link_libraries(gbufferTests LINK_PUBLIC 	
	GapBuffer
	GTest::gtest
)
