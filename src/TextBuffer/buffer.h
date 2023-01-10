#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <gapBuffer.h>
#include <set>
#include <map>
#include <string>

using namespace std;
class TextBuffer {
	public:

		TextBuffer();
		~TextBuffer();
		bool insert(char);
		bool insert(string);

		void setCurrentLine(int);
		bool remove();
		void createNewLine();
		void shiftLines(char nlEscSeq = '\n');
		
		void readInFile(string);
		void writeToFile(string);
	
		void clearLine(int);
		
		int moveRight();
		int moveLeft();
		int moveUp();
		int moveDown();
		
		//move to private later
		int getNumOfLines();
		int getCurrentLine();	
		void dump();		
		void getInfo();

		GapBuffer* getLine(int);
			

		// called by shiftLines
		void shiftLinesUp();
		// called by remove
		void shiftLinesDown();
		
		string getLineContents(int);

	private:
		map <int, GapBuffer> buffer;
		int m_numOfLines;
		int m_currentLine;
		
		// Helper function
		
		bool isValidLine(int);
		
};


#endif
