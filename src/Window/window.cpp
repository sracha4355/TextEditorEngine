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

void Window :: initWin() {
	initscr();
	raw();
	
	getmaxyx(stdscr, m_rows, m_cols);
}

void Window :: endWin(){
	t_win.freeWindow();
	delwin(i_win);
	endwin();
}

void Window :: initTextWin(){
	t_win.initWindow(m_rows - 1 , m_cols, 0, 0, true, m_buf, m_cb);	

}

void Window :: infoWin(){	
	int rows, cols;
	getmaxyx(stdscr, rows, cols);
	
	i_win = newwin(1, cols, rows - 1, 0);

	//wbkgd(i_win, COLOR_PAIR(1) | ' ');
	
	mvwaddstr(i_win, 0, 0, "SIM.CPP");
	wrefresh(i_win);

	
}

void Window :: debug(){
	cout << "Terminal Dimensions, rows: " <<  m_rows << " cols: " << m_cols << '\n';
	t_win.printAttr();
}

void Window :: eventLoop(){
	m_buf -> setCurrentLine(1);
	t_win.renderText();
	/*
		t_win.renderText();
		t_win.moveDown();
		t_win.moveDown();
		t_win.moveDown();
		t_win.moveDown();
		t_win.moveDown();
		t_win.moveUp();
				t_win.moveUp();
		for(int i = 0; i < 10; i++) 				t_win.moveUp();
	*/
		for(int i = 0; i < 100; i++)t_win.moveRight();
	/* 
	
	t_win.moveLeft();
	for(int i = 0; i < 100; i++)t_win.moveLeft();
	for(int i = 0; i < 100; i++)t_win.moveRight();

	for(int i = 0; i < 1000; i++)t_win.moveLeft();
	for(int i = 0; i < 1000; i++)t_win.moveRight();
	t_win.moveDown();
	t_win.moveDown();
	t_win.moveDown();
	t_win.moveDown();
	t_win.moveDown();
	for(int i = 0; i < 1000; i++)t_win.moveRight();	
	for(int i = 0; i < 1000; i++)t_win.moveDown();
	
		for(int i = 0; i < 1000; i++)t_win.movevi CRight();
			for(int i = 0; i < 1000; i++)t_win.moveLeft();
					for(int i = 0; i < 1000; i++)t_win.moveRight();
	*/


	wrefresh(t_win.win);
	char userInput = wgetch(t_win.win);
	while(userInput != 'q'){

		wrefresh(t_win.win);
		userInput = wgetch(t_win.win);
		wrefresh(t_win.win);

	}
	endWin();
}






