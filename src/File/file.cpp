#include "file.h"

/*
void File :: setBuffer(TextBuffer * buf) { m_buffer = buf; }

void File :: setFile(string file){ m_fileName = file; }

void File :: setLogActive(bool flag) { m_writeFromLog = flag; }
*/
bool File :: readData(){
	cout << "Accessing file " << m_fileName << endl;
	ifstream file(m_fileName);
	
	if(!file){
	       	cout << "file could not be accessed" << endl;
		return false;
	}
	
	string line;
	while(getline(file , line)) {
		m_buffer -> insert(line);
		m_buffer -> createNewLine();
	} 
	file.close();
	return true;
}



bool File :: optimizedWrite(){
	return true;
}

bool File :: writeData(){
	// if true an optimized version of write will activate
	if(m_writeFromLog) return optimizedWrite();

	ofstream file(m_fileName);
	if(!file) {
		cout << "file could not be accessed for writing purposes" << endl;
		return false;
 	}
	for(int i = 1; i <= m_buffer -> getNumOfLines(); i++){
		string content = m_buffer -> getLine(i) -> toString();
		file << content  << '\n';
	}

	file.close();
	return true;
}

bool File :: clearFile(){
	ofstream file(m_fileName);
	if(!file){
		cout << "file could not be accessed for clearing" << endl;
		return false;
	}
	file.close();
	return true;
}
