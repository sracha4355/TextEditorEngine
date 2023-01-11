#include "clipboard.h"

Clipboard :: Clipboard (){
	m_numOfLines = 0;
}

void Clipboard ::  insertLines(string * array, int numOfLines){
	for(int i = 0; i < numOfLines; i++) content.push_back(array[i]);
	m_numOfLines = numOfLines;
}

bool Clipboard ::  clearClipboard(){
	if((int) content.size() == 0) {
		cout << "Empty clipboard, nothing to clear" << endl;
		return false;
	}	
	
	content.clear();
	return true;

}


