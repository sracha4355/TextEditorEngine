#ifndef TEXTBUFFER_H
#define TEXTBUFFER_H

#include <gapBuffer.h>
#include <map>
#include <string>

using namespace std;
class TextBuffer {
	public:
		TextBuffer();
		~TextBuffer();
		
		// insertions for both input types
		bool insert(char);
		bool insert(string);
		
		// important method: most edits will be made based on the current line
		void setCurrentLine(int);
		
		/*
		 based on the current location in the textbuffer, remove can 
		 append two lines into one
		 or remove a character on the currentLine
		 if the beginning of the gap is at the beginning of the 
		 gap buffer array, then logically, the current line will be 	
		 merged with the line above it
		 Ex:
		 Hello world
		 Hello next line
		 - if the gap buffer's gap of line 2 is at the beginning, a 
		 remove operation will result in 
		 Hello worldHello next line
		 given the current line at the time of the operation was line 2
		*/		
		bool remove();
			
		void createNewLine();
		
		/* shifts a portion of text onto a line under the currentLine, how much of the text depends
		on the position in buffer */
		void shiftLines(char nlEscSeq = '\n');
		
		/* Need to be implemented but it will be used to read and write the buffer to a file */
		void readInFile(string);
		void writeToFile(string);
	
		// empties content of line
		void clearLine(int);
		
		// move position in the buffer
		int moveRight();
		int moveLeft();
		int moveUp();
		int moveDown();
		
		//move to private later
		int getNumOfLines();
		int getCurrentLine();	
		void dump();		
		void getInfo();
		
		/* get the reference to the gapBuffer that represents a line in our TextBuffer */
		GapBuffer* getLine(int);
			
		// shifts all line up by 1 with respect to the current line
		void shiftLinesUp();
		// shifts all down up by 1 with respect to the current line
		void shiftLinesDown();
		
		// get the contents of a line in string format
		string getLineContents(int);

	private:
		map <int, GapBuffer> buffer;
		int m_numOfLines;
		int m_currentLine;
		
		// Helper functions
		
		//validates if a line exists in our TextBuffer
		bool isValidLine(int);
		
};


#endif
