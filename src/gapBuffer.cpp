#include "gapBuffer.h"

//where I left off: working on resizing buffer and resizing gap, I was considering how to deal with edge cases: when there are less than ideal units to shift within the buffer
	// for when I am resizing gap buffer


GapBuffer :: GapBuffer(int bufferSize, int gapSize){
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

GapBuffer :: GapBuffer(){	
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
	cout << "m_gapStartPos " << m_gapStartPos << endl;
	cout << "m_gapEndPos " << m_gapEndPos << endl;
	cout << "m_indexOfLastElement " << m_indexOfLastElement << endl;
	cout << "m_gapSize " << m_gapSize << endl;
	cout << "m_occupied " << m_occupied << endl;
	cout << "m_size " << m_size << endl;  
}

void GapBuffer :: dump(){
	if(m_buffer != nullptr){
		for(int i = 0; i < m_size; i++){
			cout << i << " ";
		} cout << endl;		
		
		for(int i = 0; i < m_size; i++){
			if(m_buffer[i] != (char) 0)
				cout << m_buffer[i] << " ";
			else {
				cout << "_ ";}
		} cout << endl;
	}
}

void GapBuffer :: dump2(){
	if(m_buffer != nullptr){

	}
}

void GapBuffer :: clearBuffer(){
	if(m_buffer != nullptr){
		delete [] m_buffer;
		m_buffer = nullptr;
	}
		
}

void GapBuffer :: updatePositionOfLastElement(string Case) {

		if(Case == "insert"){
			cout << "uple insert" << endl;
			if(m_gapStartPos > m_indexOfLastElement) m_indexOfLastElement = m_gapStartPos - 1; 
		}
		else if(Case == "left"){
			cout << "uple left" << endl;
			if(m_gapStartPos == m_indexOfLastElement) m_indexOfLastElement = m_gapEndPos + 1;
		}
		else if(Case == "right"){
			cout << "uple right" << endl;
			if(m_gapEndPos == m_indexOfLastElement) m_indexOfLastElement = m_gapStartPos - 1;
		}
		else if(Case == "remove"){
			cout << "uple remove" << endl;
			if(m_gapStartPos == m_indexOfLastElement) m_indexOfLastElement = m_gapStartPos - 1;
		}


}

//function to insert into gap
void GapBuffer :: insert(char insertion){
	if(m_gapStartPos > m_gapEndPos) {
		cout << "gap buffer is full need to resize" << endl;
		resize();
	}
	
	//insert into start position
	m_buffer[m_gapStartPos] = insertion;
	
	//update position of last element in the buffer, may need to tweak for other cases
	
	//increment
	m_gapStartPos++;
	m_occupied++;
	
	updatePositionOfLastElement("insert");
	//updateGapLength();	
}

//remove based on current cursor position (m_gapEndPos)
void GapBuffer :: remove(){
	if(m_gapStartPos == 0) {
		cout << "Cannot delete because cursor is the beginning, deletion would cause cursor to go out of bounds" << endl;
		return;
	}
	m_gapStartPos--;
	
	m_buffer[m_gapStartPos] = (char) 0;
	
	m_occupied--;
	updatePositionOfLastElement("remove");
	//updateGapLength();
	

}

//move buffer left
int GapBuffer :: moveRight(){
	if(m_gapEndPos == m_size - 1) { 
		cout << "Cannot move right within this buffer because the gap is at the end of the buffer" << endl;
		return -1;
	}
	
	if(m_gapEndPos < m_gapStartPos){
		cout << "Need to resize" << endl;
		resize();
	}
	
	char temp =  m_buffer[m_gapEndPos + 1];
	m_buffer[m_gapStartPos] = temp;
	m_gapEndPos += 1;
	m_gapStartPos += 1;
	m_buffer[m_gapEndPos] = (char) 0;	
	updatePositionOfLastElement("right");

	return m_gapEndPos;
}

//move buffer right
int GapBuffer :: moveLeft(){
	if(m_gapStartPos == 0) {
		cout << "Cannot move left within this buffer because the gap is at the beginning of the buffer" << endl;
		return -1;
	}
	
	if(m_gapEndPos < m_gapStartPos){
		cout << "Need to resize" << endl;
		resize();
	}
	
	char temp =  m_buffer[m_gapStartPos - 1];
	m_buffer[m_gapEndPos] = temp;
	m_gapEndPos -= 1;
	m_gapStartPos -= 1;
	m_buffer[m_gapStartPos] = (char) 0;
	updatePositionOfLastElement("left");
	
	return m_gapStartPos;
}

int GapBuffer :: getStartPos(){
	return m_gapStartPos;
}

int GapBuffer :: getEndPos(){
	return m_gapEndPos;
}

// may be a useless function, might delete
void GapBuffer :: updateGapLength(){
	m_gapSize = (m_gapEndPos - m_gapStartPos) + 1;
}

bool GapBuffer :: full(){
	return m_occupied == m_size;
}

void GapBuffer:: resize(){
	if(full()){
		resizeBuffer();
	}
		//dump();
	// changed m_gapSize to m_gapSize + 1
	//now changed back to m_gapSize: line 206
	int units = (m_size - 1 - m_indexOfLastElement) > m_gapSize ? 
	m_gapSize: m_size - 1 - m_indexOfLastElement;
	cout << units << " :units" << endl;
	for(int i = m_indexOfLastElement; i != m_gapEndPos; i--){
		cout << m_buffer[i] << i << " here" << endl;
		m_buffer[i + units] = m_buffer[i];
		cout << m_buffer[i] << " here" << endl;
		m_buffer[i] = (char) 0;
		cout << m_buffer[i] << " curr here" << endl;
	}
	
	m_gapEndPos += units;
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

