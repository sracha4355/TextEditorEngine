#pragma once
#include "clipboard.h"
#include "buffer.h"

#include "ncurses.h"
#include "file.h"

//This will be window where text is rendered and edited


class Window{
	public:
		Window(string);
		Window();
		~Window();
		
		
		// window handling methods
		void initWin();
		void mainWin();
		void endWin();
		void eventLoop();
		void infoWin();
		void renderText();
		
		
		
		TextBuffer*	getBufferRef();	
		Clipboard*	getClipboardRef();	
		
	private:
		TextBuffer * m_buf;
		Clipboard * m_cb;
		WINDOW * m_win;
		WINDOW * i_win;
		
		int m_rows;
		int m_cols;
			
// coordinates represent (line number, position in gapBuffer of line)
		int cursor[2] {1 , 0};
		
		void setCursor(int, int);
		void moveCursor(int, int);
		void setCol(int);
		void setRow(int);	
};


