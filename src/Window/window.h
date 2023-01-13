#pragma once
#include "clipboard.h"
#include "buffer.h"
#include "ncurses.h"
#include "file.h"


class Window{
	public:
		Window(string);
		Window();
		~Window();
		void startWin();
		void endWin();
		TextBuffer*	getBufferRef();	
		Clipboard*	getClipboardRef();	
		
		
	private:
	
		TextBuffer * m_buf;
		Clipboard * m_cb;
		
		// our ncurses window
		WINDOW * m_win;
		
		

};

