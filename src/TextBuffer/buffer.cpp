#include <buffer.h>
#include <stdexcept>


TextBuffer :: TextBuffer(){
	m_numOfLines = 0;
	m_currentLine = 0;
	createNewLine();
}

TextBuffer :: ~TextBuffer(){}

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

// insert char into currentline's gap buffer
bool TextBuffer :: insert(char insertion){
	buffer[m_currentLine].insert(insertion);
	return true;
}

// insert string into currentline's gap buffer 
bool TextBuffer :: insert(string insertion){
	buffer[m_currentLine].insert(insertion);
	return true;
}


//set the currentLine function will validate if line exists
void TextBuffer :: setCurrentLine(int line){
	if(line > m_numOfLines) throw invalid_argument("line does not exist, or cannot exist");
	m_currentLine = line;
}


bool TextBuffer :: isValidLine(int line){
	if(line == 0) return false;
	else if (line > m_numOfLines) return false;
	return true;
}

void TextBuffer :: clearLine(int line){
	if(isValidLine(line)) buffer[line].emptyBuffer();
}


void TextBuffer :: createNewLine(){
	buffer[m_numOfLines + 1];
	m_numOfLines ++;
	m_currentLine = m_numOfLines;	
		
}

string TextBuffer :: getLineContents(int line){
	if(!isValidLine(line)) return "";
	return getLine(line) -> toString();
}

// shiftLinesUp() will delete the current line and shift all lines below it up by
// the current line will be still be the same as it points to the line below it which was shifted up by one

void TextBuffer :: shiftLinesUp(){
	if(m_currentLine == 1) {
		
		cout << "cannot shift up" << endl;	
		return;
	}

	buffer.erase(m_currentLine);
	for(int i = m_currentLine + 1; i < m_numOfLines + 1; i++){
		cout << "in loop" << endl;
		auto gapB = buffer.extract(i);
		gapB.key() = i - 1;
		buffer.insert(move(gapB));		
	}

	m_numOfLines--;
	m_currentLine--;
	
}


// remove based on current line and where the gap is in the current line's gap buffer
bool TextBuffer :: remove(){
	int result = buffer[m_currentLine].remove();
	// if result = -1 then we are at the start of the gb
	// gb: gapBuffer
	if(result == -1 && m_currentLine == 1) return false;
	if(result == -1){
		
		// get the currentLine's gb contents in string format and clear the gb
		string insertion = getLine(m_currentLine) -> toString();
		getLine(m_currentLine) -> emptyBuffer();

		// move to the end of the gb belonging to the line above and insert
		// the contents from the line below
		GapBuffer * gb = getLine(m_currentLine - 1);
		gb -> moveToEnd();
		gb -> insert(insertion);
		for(int i = 0; i < insertion.length(); i++) gb -> moveLeft();
		//shift all the lines below the line we cleared up by one
		buffer.erase(m_currentLine);
		for(int i = m_currentLine + 1; i < m_numOfLines + 1; i++){
			//cout << "in loop" << endl;
			auto gapB = buffer.extract(i);
			gapB.key() = i - 1;
			buffer.insert(move(gapB));		
		}
		m_numOfLines--;
		m_currentLine--;
		


		//shiftLinesUp();
	}

	return true;
}

void TextBuffer :: shiftLinesDown(){
/*	if(m_currentLine == m_numOfLines) {
		cout << "cannot shift down" << endl;
		return;
	}*/
	for(int i = m_numOfLines; i != m_currentLine; i--){
		auto nh = buffer.extract(i);
		nh.key() = i + 1;
		buffer.insert(move(nh));
	}

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

	auto node = buffer.find(m_currentLine);
	GapBuffer * gb  = &(node -> second);
	//gb -> insert(nlEscSeq);
	string insertion = gb -> getRightSideOfGap();
	// created empty line after point of shift
	// set curr line to that
	// copy right side of gap of the gapBuffer we are breaking from
	buffer[m_currentLine + 1];
	setCurrentLine(m_currentLine + 1);
	insert(insertion);

	gb -> deleteRightSideOfGap();
		
}

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

GapBuffer* TextBuffer ::  getLine(int line){
	auto it = buffer.find(line);
	return &(it -> second);
}

int TextBuffer :: getCurrentLine() {return m_currentLine;}
int TextBuffer :: getNumOfLines() {return m_numOfLines;}

void TextBuffer :: getInfo(){
	cout << "The current line: " << m_currentLine << endl;
	cout << "The total number of lines: " << m_numOfLines << endl;

}
