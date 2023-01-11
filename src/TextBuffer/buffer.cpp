#include <buffer.h>
#include <stdexcept>

// initialize our TextBuffer
TextBuffer :: TextBuffer(){
	m_numOfLines = 0;
	m_currentLine = 0;
	createNewLine();
}

TextBuffer :: ~TextBuffer(){}

/* Print the TextBuffer in this format
	line number: contents
	ex: 1: H e l l o _ _ w o r l d
		2: _ _ _ _ _ _ _ _
		
	This is for debugging purposes, a new line character will be printed as *
*/
void TextBuffer :: dump(){
	cout << "Text Buffer dump, num of lines: " << m_numOfLines << endl;
	for(int i = 1; i <= m_numOfLines; i++){
		auto buf = buffer.find(i);
		GapBuffer * gb = &(buf -> second);
		cout << i << ": ";
		for(int j = 0; j < gb -> getBufferSize(); j++){
			if(gb -> getValueAt(j) == (char) 0){
				cout << "_ ";
			}
			else if(gb -> getValueAt(j) == '\n') cout << "* ";
			else {
				cout << gb -> getValueAt(j) << " ";
			}
			
		}
		cout << endl;
	}
	
}

// insert char into the current line's gap buffer, using the gapBuffer's insert method
bool TextBuffer :: insert(char insertion){
	buffer[m_currentLine].insert(insertion);
	return true;
}

// insert string into the current line's gap buffer, using the gapBuffer's insert method
bool TextBuffer :: insert(string insertion){
	buffer[m_currentLine].insert(insertion);
	return true;
}


// set the current line, function will validate if line exists
void TextBuffer :: setCurrentLine(int line){
	if(line > m_numOfLines) throw invalid_argument("line does not exist, or cannot exist");
	m_currentLine = line;
}

// validate if line exists
bool TextBuffer :: isValidLine(int line){
	if(line == 0) return false;
	else if (line > m_numOfLines) return false;
	return true;
}
 
void TextBuffer :: clearLine(int line){
	// validate line and use the gapBuffer that represents the line's emptyBuffer() method
	if(isValidLine(line)) buffer[line].emptyBuffer();
}

//creates a new line and set the current line to that line
void TextBuffer :: createNewLine(){
	buffer[m_numOfLines + 1];
	m_numOfLines ++;
	m_currentLine = m_numOfLines;	
		
}


string TextBuffer :: getLineContents(int line){
	/* query the m_buffer map to get a gapBuffer reference, then get the contents of that
		gapBuffer in string format */
	if(!isValidLine(line)) return "";
	return getLine(line) -> toString();
}

/* shiftLinesUp() will delete the current line and shift all lines below it up by */
void TextBuffer :: shiftLinesUp(){
	if(m_currentLine == 1) {
		cout << "cannot shift up" << endl;	
		return;
	}

	// erase current line and shift all lines below by 1
	buffer.erase(m_currentLine);
	for(int i = m_currentLine + 1; i < m_numOfLines + 1; i++){
		// std :: map's extract allows us to remove a key value pair and reinsert back into the map
		auto gapB = buffer.extract(i);
		// update key value for the shift
		gapB.key() = i - 1;
		// reinsert
		buffer.insert(move(gapB));		
	}

	m_numOfLines--;
	m_currentLine--;
	
}


// remove based on current line and where the gap is in the current line's gap buffer
bool TextBuffer :: remove(){
	// gb: gapBuffer
	int result = buffer[m_currentLine].remove();	
	/* if result = -1 then we are at the start of the gb, and no characters were removed in the gb */
	
	// cannot combine currentLine with a line above because in this case we are on the first line
	if(result == -1 && m_currentLine == 1) return false;
	if(result == -1){
		// get the currentLine's gb contents in string format and clear the gb
		string insertion = getLine(m_currentLine) -> toString();
		getLine(m_currentLine) -> emptyBuffer();

		/* move to the end of the gb belonging to the line above the currentLine and insert
		 the contents from the line below */
		GapBuffer * gb = getLine(m_currentLine - 1);
		gb -> moveToEnd();
		gb -> insert(insertion);
		// move the insertion point 
		for(int i = 0; i < insertion.length(); i++) gb -> moveLeft();
		
		//shift all the lines below the line we cleared up by one
		buffer.erase(m_currentLine);
		for(int i = m_currentLine + 1; i < m_numOfLines + 1; i++){
			// extract key value pair, edit key value, then reinsert
			auto gapB = buffer.extract(i);
			gapB.key() = i - 1;
			buffer.insert(move(gapB));		
		}

		m_numOfLines--;
		m_currentLine--;
	}

	return true;
}

void TextBuffer :: shiftLinesDown(){
	/* extract a line starting from the bottom and increment the key by one
	 to indicate a shift of line down in the buffer */
	for(int i = m_numOfLines; i != m_currentLine; i--){
		auto nh = buffer.extract(i);
		nh.key() = i + 1;
		buffer.insert(move(nh));
	}
	
	/* create a new line at the point of the shift because that value for a key
	 is now empty due to the shift in all lines down by 1 below the currentLine*/
	buffer[m_currentLine + 1];
	m_currentLine++;
	m_numOfLines++;

}

// nlEscSeq param meaning:  new line escape sequence
void TextBuffer :: shiftLines(char nlEscSeq){		
	// lines after current line are shifted down by 1
	for(int i = m_numOfLines; i != m_currentLine; i--){
		auto gb = buffer.extract(i);
		gb.key() = i + 1;
		buffer.insert(move(gb));
	}
	m_numOfLines ++;

	/* get the current line's contents and get the contents of the right side of position
	 where we are currently editing */
	auto node = buffer.find(m_currentLine);
	GapBuffer * gb  = &(node -> second);
	string insertion = gb -> getRightSideOfGap();
	
	// created empty line after point of shift
	// set curr line to that
	// copy right side of gap of the gapBuffer we are breaking from
	
	/* created a new line below the current line and inserted the contents of the right side of position
	 where we are currently editing */
	 
	buffer[m_currentLine + 1];
	setCurrentLine(m_currentLine + 1);
	insert(insertion);

	// delete the contents we copied to another line
	gb -> deleteRightSideOfGap();
		
}

/* methods to move around in the TextBuffer */
int TextBuffer :: moveLeft(){
	GapBuffer * gb = getLine(m_currentLine);
	int result = gb -> moveLeft();
	return result;
}

int TextBuffer :: moveRight(){
	GapBuffer * gb = getLine(m_currentLine);
	int result = gb -> moveRight();
	return result;
}

int TextBuffer :: moveUp(){
	if(!isValidLine(m_currentLine) && m_currentLine != 1){
		return -1;
	}
	setCurrentLine(m_currentLine);	
	return m_currentLine;
}


int TextBuffer :: moveDown(){
	if(!isValidLine(m_currentLine + 1) && m_currentLine != m_numOfLines){
		return -1;
	}

	setCurrentLine(m_currentLine + 1);
	return m_currentLine;

}

// get gb ptr
GapBuffer* TextBuffer ::  getLine(int line){
	auto it = buffer.find(line);
	return &(it -> second);
}

int TextBuffer :: getCurrentLine() {return m_currentLine;}
int TextBuffer :: getNumOfLines() {return m_numOfLines;}

// for debugging
void TextBuffer :: getInfo(){
	cout << "The current line: " << m_currentLine << endl;
	cout << "The total number of lines: " << m_numOfLines << endl;

}
