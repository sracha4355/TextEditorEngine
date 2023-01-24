find_package(Curses REQUIRED)
add_library(Window window.cpp textWindow.cpp )
target_include_directories(Window PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} 
	${CURSES_INCLUDE_DIR})
target_link_libraries(Window PUBLIC Buffer Clipboard Commands 
	File ${CURSES_LIBRARIES})


