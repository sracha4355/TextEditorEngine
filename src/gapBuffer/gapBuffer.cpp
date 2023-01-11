#include "gapBuffer.h"

//init values
GapBuffer :: GapBuffer(int bufferSize, int gapSize){
	// buffer will have empty char's as place holders
	m_buffer = new char[bufferSize];
	for(int i = 0; i < bufferSize; i++){
		m_buffer[i] = 0;
	}
	
	m_size = bufferSize;
	m_occupied = 0;
	m_indexOfLastElement = 0;
	m_gapSize = gapSize;
	m_gapStartPos = 0;
	m_gapEndPos = gapSize - 1;
	
}

//uses default values contained in gapBuffer.h (MINSIZE, MINGAPSIZE)
GapBuffer :: GapBuffer(){	
	// buffer will have empty char's as place holders
	m_buffer = new char[MINSIZE];
	for(int i = 0; i < MINSIZE; i++){
		m_buffer[i] = 0;
	}
	m_size = MINSIZE;
	m_occupied = 0;
	
	m_indexOfLastElement = 0;
	m_gapSize = MINGAPSIZE;
	m_gapStartPos = 0;
	m_gapEndPos = m_gapSize - 1;
	
}

GapBuffer :: ~GapBuffer(){
	clearBuffer();
}

void GapBuffer :: printAttributeInfo(){
	cout << "m_gapStartPos: " << m_gapStartPos << endl;
	cout << "m_gapEndPos: " << m_gapEndPos << endl;
	cout << "m_indexOfLastElement: " << m_indexOfLastElement << endl;
	cout << "m_gapSize: " << m_gapSize << endl;
	cout << "m_occupied: " << m_occupied << endl;
	cout << "m_size: " << m_size << endl;  
}

void GapBuffer :: dump(){
	if(m_buffer != nullptr){
		for(int i = 0; i < m_size; i++){
			cout << i;
			if(i < 10){
				cout << "    ";
			} else if (i < 100){
				cout << "   ";
			} else if( i <  1000){
				cout << "  ";
			} else if( i < 10000){
				cout << " ";
			}
			
		} cout << endl;
		for(int i = 0; i < m_size; i++){
			cout << "-----";
		} cout << endl;
		
		for(int i = 0; i < m_size; i++){
			if(m_buffer[i] != (char) 0)
				cout << m_buffer[i] << " ";
			else {
				cout << "_ ";
			}
			cout << "   ";
		} cout << endl;
	}
}

void GapBuffer :: clearBuffer(){
	if(m_buffer != nullptr){
		delete [] m_buffer;
		m_buffer = nullptr;
	}
		
}

void GapBuffer :: emptyBuffer(){
	for(int i = 0; i < m_size; i++){
		m_buffer[i] = (char) 0;
	}
	m_occupied = 0;
	moveToStart();

}

void GapBuffer :: updatePositionOfLastElement(string Case) {

		if(Case == "insert"){
			//cout << "uple insert" << endl;
			if(m_gapStartPos > m_indexOfLastElement) 
				{m_indexOfLastElement = m_gapStartPos - 1;} 
		}
		else if(Case == "left"){
			//cout << "uple left" << endl;
			if(m_gapStartPos == m_indexOfLastElement) 
				{m_indexOfLastElement = m_gapEndPos + 1;}
		}
		else if(Case == "right"){
			//cout << "uple right" << endl;
			if(m_gapEndPos == m_indexOfLastElement) 
				{m_indexOfLastElement = m_gapStartPos - 1;}
		}
		else if(Case == "remove"){
			//cout << "uple remove" << endl;
			if(m_gapStartPos == m_indexOfLastElement) 
				{m_indexOfLastElement = m_gapStartPos - 1;}
		}


}

//function to insert into gap
void GapBuffer :: insert(char insertion){
	if(m_gapStartPos > m_gapEndPos) {
		//gap buffer is full need to resize
		resize();
	}
	
	//insert into start position
	m_buffer[m_gapStartPos] = insertion;
	
	//increment
	m_gapStartPos++;
	m_occupied++;
	
	updatePositionOfLastElement("insert");
	if(m_gapStartPos > m_gapEndPos) {
		//gap buffer is full need to resize
		resize();
	}
	
}

void GapBuffer :: insert(string word){
	for(int i = 0; i < word.length(); i++){
		char insertion = (char) word[i];
		insert(insertion);

	}
}

string GapBuffer :: toString(){
	string gb  = "";
	string letter;
	for(int i = 0; i < m_size; i++){
		if(m_buffer[i] != (char) 0){
			gb.push_back(m_buffer[i]);
		}
	}

	return gb;
}

//remove based on current cursor position (m_gapEndPos)
int GapBuffer :: remove(){
	if(m_gapStartPos == 0) {
		/*Cannot delete because cursor is the beginning, deletion would cause cursor to go 
		out of bounds, therefore we return -1 to indicate an error*/
		return -1;
	}
	
	//clear the index
	m_gapStartPos--;
	m_buffer[m_gapStartPos] = (char) 0;
	
	//update m_occupied and update the index of the last element
	m_occupied--;
	updatePositionOfLastElement("remove");

	
	//return new start position of buffer
	return m_gapStartPos;
	

}

//move buffer right
int GapBuffer :: moveRight(){
	if(m_gapEndPos == m_size - 1) { 
		/*Cannot move right within this buffer 
		because the gap is at the end of the buffer, return -1 to indicate error */
		return -1;
	}
	
	if(m_gapEndPos < m_gapStartPos){
		//Need to resize because the index
		// which tracks the start of the gap is past the
		// index which tracks the end of the gap
		resize();
	}

	if(m_buffer[m_gapEndPos + 1] == (char) 0){
		// we return -1 to indicate error because 
		// we cannot cannot move the gap right if there is nothing on the right side
		// because then it would leave an empty char on the left side, which interferes with buffer operations
		return -1;
	}
	
	// update indexes and move the characters
	char temp =  m_buffer[m_gapEndPos + 1];
	m_buffer[m_gapStartPos] = temp;
	m_gapEndPos += 1;
	m_gapStartPos += 1;
	m_buffer[m_gapEndPos] = (char) 0;	
	updatePositionOfLastElement("right");

	//send back end index of gap
	return m_gapEndPos;
}

//move buffer left
int GapBuffer :: moveLeft(){
	if(m_gapStartPos == 0) {
		/*Cannot move left within this buffer 
		because the gap is at the start of the buffer, return -1 to indicate error */
		return -1;
	}
	
	if(m_gapEndPos < m_gapStartPos){
		//Need to resize because the index
		// which tracks the start of the gap is past the
		// index which tracks the end of the gap
		resize();
	}
	
	// update indexes and move the characters
	char temp =  m_buffer[m_gapStartPos - 1];
	m_buffer[m_gapEndPos] = temp;
	m_gapEndPos -= 1;
	m_gapStartPos -= 1;
	m_buffer[m_gapStartPos] = (char) 0;
	updatePositionOfLastElement("left");
	
	return m_gapStartPos;
}

int GapBuffer ::  moveToStart(){
	int finalPos = moveLeft();
	while(finalPos != -1){
		finalPos = moveLeft();
	}

	return m_gapStartPos;
}


int GapBuffer :: moveToEnd(){
	int finalPos = moveRight();
	while(finalPos != -1){
		finalPos = moveRight();
	}

	return m_gapEndPos;
}



/* getters and setters */

int GapBuffer :: getStartPos() { return m_gapStartPos;}

int GapBuffer :: getEndPos() { return m_gapEndPos;}

int GapBuffer :: getGapSize() { return m_gapSize;}

int GapBuffer :: getBufferSize(){ return m_size;}

int GapBuffer :: getOccupied() { return m_occupied;}

int GapBuffer :: getIndexOfLastElem() { return m_indexOfLastElement;}

bool GapBuffer :: full(){
	return m_occupied == m_size;
}

char GapBuffer :: getValueAt(int index){
	if(index >= m_size) throw ("invalid index");
	return m_buffer[index]; 
}

string GapBuffer :: getRightSideOfGap(){
	string result = "";
	for(int i = m_gapEndPos + 1; i < m_size; i++){
		if(m_buffer[i] != (char) 0)
			result.push_back(m_buffer[i]);
	}

	/*
	if(m_gapStartPos == m_gapEndPos + 1){
		for(int i = m_gapStartPos; i < m_size; i++)
			result.push_back(m_buffer[i]);
	}else{	
		for(int i = m_gapStartPos + 1; i < m_size; i++)
			result.push_back(m_buffer[i]);
	}
	*/
	return result;
}

void GapBuffer :: deleteRightSideOfGap(){
	int origStartPos = m_gapStartPos;
	int origEndPos = m_gapEndPos;
	
	for(int i = m_size - 1; i != m_gapEndPos; i--){
		if(m_buffer[i] != (char) 0){
			m_buffer[i] = (char) 0;
			m_occupied--;
		}
	}
	
	m_indexOfLastElement = m_gapStartPos  - 1;	
		

	/*	
	if(moveRight() == -1) return;
	moveToEnd();
	while(m_gapStartPos != origStartPos){
		remove();
	}
	*/
	
			
	
}

void GapBuffer:: resize(){
	// in the case of a full buffer we will resize the gap after
	// resizing the whole the buffer
	if(full()){
		resizeBuffer();
	}

	// Note to self: changed m_gapSize to m_gapSize + 1
	// now changed back to m_gapSize: line 206
	
	// units will contain the amounts of indices all the characters
	// on the right will be shifted
	// if the available space in the array is less than m_gapSize
	// we shift m_size - 1 - m_indexOfLastElement else m_gapSize
	int units = (m_size - 1 - m_indexOfLastElement) > m_gapSize ? 
	m_gapSize: m_size - 1 - m_indexOfLastElement;
	
	//shift all elements on the right side of the gap
	for(int i = m_indexOfLastElement; i != m_gapEndPos; i--){
		m_buffer[i + units] = m_buffer[i];
		m_buffer[i] = (char) 0;
	}
	
	// adjust gap end index
	m_gapEndPos += units;
	// if the gap is at the end of the buffer or the next
	// or the next value after the end of the buffer is empty
	// the index of the last element is shifted 0 units/indices
	if(m_gapEndPos == m_size - 1 || m_buffer[m_gapEndPos + 1] == (char) 0) units = 0;
	m_indexOfLastElement += units;

	
}

void GapBuffer:: resizeBuffer(){
		char * newBuffer = new char[m_size * 2];
		for(int i = 0; i < m_size; i++){
			newBuffer[i] = m_buffer[i];
		}
		for(int i = m_size; i < m_size * 2; i++){
			newBuffer[i] = (char) 0;
		}
		
		delete [] m_buffer;

		m_buffer = newBuffer;
	
		m_size = m_size * 2;
		
}

