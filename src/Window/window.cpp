/*
I am facing difficulties in finsihing the command module, so temporarily I will code the copy and paste commands here
*/

#include "window.h"

// for existing files
Window :: Window(string fileName){
	m_buf = new TextBuffer;
	m_cb = new Clipboard;
	
	File file;
	file.m_fileName = fileName;
	file.m_buffer = m_buf;
	file.readData();
}	

// for new files
Window :: Window(){
	m_buf = new TextBuffer;
	m_cb = new Clipboard;
}

Window :: ~Window(){
	delete m_buf;
	delete m_cb;
}


TextBuffer*	Window :: getBufferRef(){
	return m_buf;
} 
Clipboard*	Window :: getClipboardRef(){
	return m_cb;
}

void Window :: startWin(){
	initscr();
	raw();
	addch('h');
	refresh();
	getch();
}

void Window :: endWin(){
	endwin();
}
