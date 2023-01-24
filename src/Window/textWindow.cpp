#include "textWindow.h"

using std :: cout, std :: endl;

/*
	- Rendered window, and kept text inside the box 
	- add code to move around in the window
*/


void TextWindow :: setupWithBox(){
	bounds.LEFT = 1;
	bounds.RIGHT = dimensions[1] - 2;
	bounds.TOP = 1;
	bounds.BOTTOM = dimensions[0] - 2 ;
	
	box(win, 0, 0);
	cursor[0] = cursor[1] = 1;
	wmove(win, 1, 1);

}

void TextWindow :: setupWithoutBox(){
	bounds.LEFT = 0;
	bounds.RIGHT = dimensions[1] - 1;
	bounds.TOP = 0;
	bounds.BOTTOM = dimensions[0] - 1 ;
	
	cursor[0] = cursor[1] = 0;
	wmove(win, 0, 0);

}



void TextWindow :: renderText(){
	if (dimensions[0] == 2) return;

	lines.clear();
	
	if(tbuf -> getNumOfLines() < 1) return;
	bool cont = true;
	
	//tbuf -> setCurrentLine(startLine);
	
	// sets the current line in the buffer to the top line we render
	// might have to change later
	int i = tbuf -> getCurrentLine();
	while (cont && i <= tbuf -> getNumOfLines()){
		cont = renderLine(i);
		i++;
	}
	wrefresh(win);
	

	wmove(win, 1, lineWrapCol);
	getyx(win, cursor[0], cursor[1]);
}



void TextWindow :: advanceCursor(){
	cursor[1] += 1;
	if(cursor[1] == bounds.RIGHT + 1){
		cursor[1] = lineWrapCol;
		cursor[0] += 1;
	}
	wmove(win, cursor[0], cursor[1]);

}

bool TextWindow :: renderLine(int line){

	if(cursor[0] == bounds.BOTTOM + 1) return false;

	tbuf -> getLine(line) -> moveToStart();
	
	
	int numLines = tbuf -> getNumOfLines();
	int mnumOfDigits = int(log10(numLines) + 1); 
	int lnumOfDigits = int(log10(line) + 1); 
	
	for(int i = 0; i < mnumOfDigits - lnumOfDigits; i++) 
		waddch(win, ' ');
		
	waddstr(win, (to_string(line) + " ").c_str());
	getyx(win, cursor[0], cursor[1]);
	lineWrapCol = cursor[1];
	
	string content = tbuf -> getLineContents(line);
	int lineLength = getLength(content);
	
	auto text_line = make_unique<Line>();
	text_line -> startPos[0] = cursor[0];
	text_line -> startPos[1] = lineWrapCol;
	text_line -> currPos[0] = cursor[0];
	text_line -> currPos[1] = lineWrapCol;
	text_line -> length = lineLength;


	
	if(!spaceLeftForText2(lineWrapCol, lineLength)){
		waddstr(win, "...");
		getyx(win, cursor[0], cursor[1]);
		return false; // no more space to render
	}
	
	for(char s: content){
		if(s == '\t'){
			for(int i = 0; i < winTabsize; i++){
				waddch(win, ' ');
			}	
		} else waddch(win, s);
		getyx(win, cursor[0], cursor[1]);
		if(cursor[1] > bounds.RIGHT) {
			cursor[1] = lineWrapCol;
			cursor[0] += 1;
			wmove(win, cursor[0], cursor[1]);
		}
		
	}
	
	text_line -> lastCharPos [0] = cursor[0];
	text_line -> lastCharPos [1] = cursor[1] - 1;
	lines.insert({line, move(text_line)});	
	
	// sets currentPosition to the line startPosition

	// move the cursor to the beginning
	cursor[0] += 1;
	cursor[1] = 1;
	wmove(win, cursor[0], cursor[1]);
	return true;

}

int TextWindow ::  getLength(string content){
	int len = 0;
	for(char ch: content){
		if(ch == '\t') len += winTabsize;
		else len += 1;
	} return len;
}


bool TextWindow :: spaceLeftForText(int nlwrap, string contents){
	int length = 0;
	for(char c: contents){
		if(c == '\t') length += winTabsize;
		else length++;
	}

	return ( ((bounds.BOTTOM + 1) - cursor[0]) 
			* (bounds.RIGHT - nlwrap) ) >= length;
}

bool TextWindow :: spaceLeftForText2(int nlwrap, int length){	
	return ( ((bounds.BOTTOM + 1) - cursor[0]) 
			* (bounds.RIGHT - nlwrap) ) >= length;
}

void TextWindow :: advanceCursorInLine(int (&_cursor)[2]){
	_cursor[1] += 1;
	if(_cursor[1] == bounds.RIGHT + 1){
		_cursor[1] = lineWrapCol;
		_cursor[0] += 1;
	}
	wmove(win, _cursor[0], _cursor[1]);

}

void TextWindow :: moveCursorInLineBack(int (&_cursor)[2]){
	_cursor[1] -=1;
	if(_cursor[1] == lineWrapCol - 1){
		_cursor[0] -= 1;
		_cursor[1] = bounds.RIGHT;
	}
	wmove(win, _cursor[0], _cursor[1]);

}

void TextWindow ::  moveRight(){
	int currentLine = tbuf -> getCurrentLine();
	auto& text_line = getLinePair(currentLine);
	wmove(win, text_line -> currPos[0], text_line -> currPos[1]);
	GapBuffer * gb = tbuf -> getLine(currentLine);
	
	int res = gb -> moveRight();
	if(res == -1) return;
	char ch = gb -> getValueAt(text_line -> bufferPos);
	
	if(ch == '\t'){
		getyx(win, cursor[0], cursor[1]);
		for(int i = 0; i < winTabsize; i++) 
			advanceCursorInLine(text_line -> currPos);	
	} else advanceCursorInLine(text_line -> currPos);	
	
	text_line -> bufferPos += 1;
	
	
}
void TextWindow ::  moveLeft(){		
	int currentLine = tbuf -> getCurrentLine();
	auto& text_line = getLinePair(currentLine);
	wmove(win, text_line -> currPos[0], text_line -> currPos[1]);
	GapBuffer * gb = tbuf -> getLine(currentLine);
	
	text_line -> bufferPos -= 1;

	char ch = gb -> getValueAt(text_line -> bufferPos);
	int res = gb -> moveLeft();
	if(res == -1) {
		text_line -> bufferPos += 1;
		return;
	}

	if(ch == '\t'){
		getyx(win, cursor[0], cursor[1]);
		for(int i = 0; i < winTabsize; i++){
			moveCursorInLineBack(text_line -> currPos);
		}
	} else moveCursorInLineBack(text_line -> currPos);	

	
}
void TextWindow :: moveUp(){
	if(lines.empty()) return;
	if(tbuf -> getCurrentLine() == 1) return;
	int topLine = lines.begin() -> first;
	int currLine = tbuf -> getCurrentLine();
	tbuf -> setCurrentLine(currLine - 1);
	if(currLine == topLine){
		clearText();
		renderText();
		return;
	} else{
		auto & text_line = getLinePair(tbuf -> getCurrentLine());
		wmove(win, text_line -> currPos[0], text_line -> currPos[1]);
	}	
	

	
}
void TextWindow ::  moveDown(){
	if(lines.empty()) return;
	int currLine = tbuf -> getCurrentLine();
	if(currLine == tbuf -> getNumOfLines()) return;
	int lastLine = lines.rbegin() -> first;
	tbuf -> setCurrentLine(currLine + 1);	
	if(currLine == lastLine){
		clearText();
		renderText();
	}else{
		auto & text_line = getLinePair(tbuf -> getCurrentLine());
		wmove(win, text_line -> currPos[0], text_line -> currPos[1]);
	}
	
	

}

void TextWindow :: insert(char ch){
	int currentLine = tbuf -> getCurrentLine();
	auto & text_line = getLinePair(tbuf -> getCurrentLine());
	GapBuffer * gb = tbuf -> getLine(currentLine);
	gb -> insert(ch);
	
	advanceCursorInLine(text_line -> currPos);
	
}


unique_ptr<Line>& TextWindow :: getLinePair(int line){
 	auto it = lines.find(line);
    if (it != lines.end()) {
        return it->second;
    }
    throw std::out_of_range("Line not found");
}


void TextWindow :: printAttr(){
	cout << "LEFT " << bounds.LEFT << '\n'
	<< "RIGHT " << bounds.RIGHT << '\n'
	<< "TOP " << bounds.TOP << '\n'
	<< "BOTTOM " << bounds.BOTTOM << '\n'
	<< "Dimensions: " << dimensions[0] << " " << dimensions[1]
	<< "\n" << "Cursor: " << cursor[0] << " " << cursor[1] << "\n";
	/*
	for(auto pair: linePositions){
		cout << pair.first << ": " << pair.second << "\n";
	}
	cout << "currLinePos" << ": " << currLinePos.first << ": " << currLinePos.second << "\n" ;
	*/
	cout << "lineWrapCol: " << lineWrapCol << "\n"<< "\n";
	
	cout << "current cursor pos " << cursor[0] << " : " << cursor[1] << "\n"; 
	
	for(const auto&[key, value] : lines){
		cout << key << ": " << "\n";
		value -> debug();
		cout << endl;
		
	}
	
}

void TextWindow :: freeWindow(){
	delwin(win);
}

void TextWindow :: clearText(){
	lines.clear();
	cursor[0] = bounds.LEFT;
	cursor[1] = bounds.TOP;
	werase(win);
	setupWithBox();
}


void Line :: debug() {
	cout << "Line length: " << length << "\n"
	<< "lastCharPos: " << lastCharPos[0] << " " << lastCharPos[1] << 
	"\n"
	<< "startPos: " << startPos[0] << " " << startPos[1] << 
	"\n"
	<< "currPos: " << currPos[0] << " " << currPos[1] << "\n"
	<< "bufferPos: " << bufferPos << "\n";
}


