#pragma once
#include "ncurses.h"
#include "buffer.h"
#include "clipboard.h"
#include <iostream>
#include <cmath>

struct Bounds{
	int LEFT, RIGHT, TOP, BOTTOM;
};


//initscr needs to be called before TextWindow can be used
struct TextWindow{
	WINDOW * win;
	TextBuffer * tbuf;
	Clipboard * cb;
	
	int dimensions[2];
	int cursor[2] {0, 0};
	int lineWrapCol;
	int buffPos[2] {0, 0}; 
	
	
	//0s are placeholders, renderText sets to proper position
	
	Bounds bounds; 
	bool drawBox;
	
	void setupWithBox();
	void setupWithoutBox();
	void printAttr();
	void freeWindow();
	bool renderLine(int);
	void renderText();
	bool spaceLeftForText(int, string);

	
	void initWindow(int _rows, int _cols, int startY, int startX, bool 
	_drawBox, TextBuffer * _buf, Clipboard * _cb){
		TABSIZE = 8; //ncurses macro from ncurses.h
		win = newwin(_rows, _cols, startY, startX);
		tbuf = _buf;
		cb = _cb;
		getmaxyx(win, dimensions[0], dimensions[1]);
		drawBox = _drawBox;
		drawBox ? setupWithBox() : setupWithoutBox();
		wrefresh(win);
					
	}
	
};
	
	


