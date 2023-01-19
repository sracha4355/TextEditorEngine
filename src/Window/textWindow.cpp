#include "textWindow.h"

using std :: cout, std :: endl;

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
	if(tbuf -> getNumOfLines() < 1) return;
	bool cont = true;
	int i = 1;
	while (cont && i <= tbuf -> getNumOfLines()){
		cont = renderLine(i);
		i++;
	}
	wrefresh(win);
	wmove(win, 1, lineWrapCol);
	getyx(win, cursor[0], cursor[1]);

}

bool TextWindow :: renderLine(int line){
	// line 41 newline
	if(cursor[0] == bounds.BOTTOM + 1) return false;
	
	int numLines = tbuf -> getNumOfLines();
	int mnumOfDigits = int(log10(numLines) + 1); 
	int lnumOfDigits = int(log10(line) + 1); 
	
	//replace 4 with mnum later
	for(int i = 0; i < mnumOfDigits - lnumOfDigits; i++) waddch(win, ' ');
	waddstr(win, (to_string(line) + " ").c_str());
	getyx(win, cursor[0], cursor[1]);
	
	string content = tbuf -> getLineContents(line);
	
	// lines 45 through 51 new code that could cld break function
	lineWrapCol = cursor[1];
	if(!spaceLeftForText(lineWrapCol, content)){
		waddstr(win, "...");
		getyx(win, cursor[0], cursor[1]);
		return false; // no more space to render
	}
	
	for(char s: content){
		waddch(win, s);
		getyx(win, cursor[0], cursor[1]);
		if(cursor[1] > bounds.RIGHT) {
			cursor[1] = lineWrapCol;
			cursor[0] += 1;
			wmove(win, cursor[0], cursor[1]);
		}
	}

	// move the cursor to the beginning
	cursor[0] += 1;
	cursor[1] = 1;
	wmove(win, cursor[0], cursor[1]);
	return true;
}

bool TextWindow :: spaceLeftForText(int nlwrap, string contents){
	
	
	
	return ( ((bounds.BOTTOM + 1) - cursor[0]) 
			* (bounds.RIGHT - nlwrap) ) >= contents.length();
}


void TextWindow :: printAttr(){
	cout << "LEFT " << bounds.LEFT << '\n'
	<< "RIGHT " << bounds.RIGHT << '\n'
	<< "TOP " << bounds.TOP << '\n'
	<< "BOTTOM " << bounds.BOTTOM << '\n'
	<< "Dimensions: " << dimensions[0] << " " << dimensions[1]
	<< "\n" << "Cursor: " << cursor[0] << " " << cursor[1] << "\n";
}

void TextWindow :: freeWindow(){
	delwin(win);
}
