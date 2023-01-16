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

void Window :: infoWin(){
	//start_color();
	//init_pair(1, COLOR_BLUE, COLOR_BLUE);
	
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	
	i_win = newwin(1, cols, rows - 1, 0);

	//wbkgd(i_win, COLOR_PAIR(1) | ' ');
	
	mvwaddstr(i_win, 0, 0, "SIM.CPP");
	wrefresh(i_win);

	
}

void Window :: mainWin(){
	// rows: y cols: x
	int rows;
	int cols;
	getmaxyx(stdscr, rows, cols);
	m_win = newwin(rows - 1, cols, 0, 0);
	box(m_win, 0, 0);
	
	mvwaddstr(m_win, 0, 3, "SIM");
	
	setCursor(1,1);
	wmove(m_win, cursor[0], cursor[1]); 
	wrefresh(m_win);
}

void Window :: renderText(){
	
}


void Window :: eventLoop(){
	getmaxyx(m_win, m_rows, m_cols);
	
	char userInput;
	do { 
		userInput = wgetch(m_win);
		moveCursor(0, 1);
		wmove(m_win, cursor[0], cursor[1]);
		if(cursor[1] == m_cols - 2){
			moveCursor(1,0);
			setCol(0);
		}
		
		
	} while (userInput != 'q');
	endWin();
}

void Window :: endWin(){
	delwin(m_win);
	delwin(i_win);
	endwin();
}

void Window :: initWin() {
	initscr();
	raw();
}

void Window :: setCursor(int y, int x){
	cursor[0] = y;
	cursor[1] = x;
}

void Window :: moveCursor(int y, int x){
	cursor[0] += y;
	cursor[1] += x;

}

void Window :: setCol(int x){
	cursor[1] = x;
}

void Window :: setRow(int y){
	cursor[0] = y;
}
