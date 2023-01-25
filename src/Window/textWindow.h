#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <utility> 
#include <memory>


#include "ncurses.h"
#include "buffer.h"
#include "clipboard.h"



struct Bounds{
	int LEFT, RIGHT, TOP, BOTTOM;
};

struct Line{
	int length = 0;
	int lastCharPos [2] {0,0};
	int startPos [2] {0,0};
	int bufferPos = 0;
	int currPos[2] {0, 0};
	
	void debug();
	void setPosition(){
		currPos[0] = startPos[0];
		currPos[0] = startPos[1];
	}
};

//initscr needs to be called before TextWindow can be used
struct TextWindow{
	WINDOW * win;
	TextBuffer * tbuf;
	Clipboard * cb;
	
	//vector<pair<int, unique_ptr<Line>> > lines;
	map<int, unique_ptr<Line>> lines;
	
	int winCurrentLine;	

	int dimensions[2];
	int cursor[2] {0, 0};
	int lineWrapCol;
	
	int winTabsize;
	
	Bounds bounds; 
	bool drawBox;
	
	void setupWithBox();
	void setupWithoutBox();
	void printAttr(); // for debugging
	void freeWindow();


	bool spaceLeftForText(int, string);
	
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void advanceCursor();
	void advanceCursorInLine(int (&arr)[2]);
	void moveCursorInLineBack(int (&arr)[2]);
	
	void insert(char);
	void remove();
	
	//test method
	bool renderLine(int, bool);
	bool spaceLeftForText2(int, int);
	
	int getLength(string);
	void renderText(bool);

	void updateWindow();
	void updateLine();
	

	
	void clearText();
	
	unique_ptr<Line>& getLinePair(int);

	void initWindow(int _rows, int _cols, int startY, int startX, bool 
	_drawBox, TextBuffer * _buf, Clipboard * _cb){
		TABSIZE = 4; //ncurses macro from ncurses.h
		winTabsize = TABSIZE;
		
		win = newwin(_rows, _cols, startY, startX);
		tbuf = _buf;
		cb = _cb;
		getmaxyx(win, dimensions[0], dimensions[1]);
		drawBox = _drawBox;
		drawBox ? setupWithBox() : setupWithoutBox();
		wrefresh(win);
					
	}
	
};
	
	


