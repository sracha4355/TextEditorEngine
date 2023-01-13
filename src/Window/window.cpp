#include "window.h"

Window :: Window(string fileName){
	File file;
	file.m_fileName = fileName;
	file.m_buffer = m_buf;
	file.readData();
}	

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
