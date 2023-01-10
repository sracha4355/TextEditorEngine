add_executable(controllerTests controllerTests.cpp)

target_link_libraries(controllerTests
	Controller
	GTest::gtest
)
