#pragma once
#include "clipboard.h"
#include "buffer.h"
#include "ncurses.h"
#include "file.h"
#include <cmath>
#include "textWindow.h"




//This will be window where text is rendered and edited


class Window{
	public:
		Window(string);
		Window();
		~Window();
	
	
	
		void initTextWin();
		void debug();
		
		
		// window handling methods
		void initWin();
		void endWin();
		void eventLoop();
		void infoWin();
		
	
		TextBuffer*	getBufferRef();	
		Clipboard*	getClipboardRef();	
		
	private:
		TextBuffer * m_buf;
		Clipboard * m_cb;
		
		TextWindow t_win;
		
		WINDOW * i_win;
		
		int m_rows;
		int m_cols;
					

};


