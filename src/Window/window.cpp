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


/*
void Window :: renderText(){
	
		int currRow = 1;
		int maxRow, maxCols;
		getmaxyx(m_win, maxRow, maxCols);
		int line = 1;
		int maxLines = m_buf -> getNumOfLines();
		
		while (currRow <= maxRow - 2 && line <= maxLines){
			renderLine(line);
			int cr, cc;
			getyx(m_win, cr, cc);
			wmove(m_win, cr + 1, 1);
			line++;
		}
	
		
}


void Window :: renderLine(int line){
	// y, x : row, col
	int row, col;
	getmaxyx(m_win, row, col);

	int numLines = m_buf -> getNumOfLines();
	int maxNumberLength = int(log10(numLines) + 1);
	int lnNumOfDigits = int(log10(line) + 1);
	
	for(int i = 0; i < maxNumberLength - lnNumOfDigits; i++){
		waddch(m_win, '*');
	}
	

	waddstr(m_win,  (to_string(line) + " ").c_str() );
	// number rendered, so render line contents
	int currY, currX;
	getyx(m_win, currY, currX);
	wmove(m_win, currY, currX + 1);
	getyx(m_win, currY, currX);
	setCursor(currY, currX);
	
	string lineContents = m_buf -> getLineContents(line);
	for(int i = 0; i < lineContents.length(); i++){
		if(cursor[1] == col - 2){
			moveCursor(1, 0);
			setCol(maxNumberLength + 3);
		}
		wmove(m_win, cursor[0], cursor[1]);
		waddch(m_win, lineContents[i]);
		moveCursor(0,1);
	}

	
	
}	
*/

void Window :: eventLoop(){
	/*
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
	*/	
	
	t_win.renderText();
	wgetch(t_win.win);
	endWin();
}






