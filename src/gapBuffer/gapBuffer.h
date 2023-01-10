#ifndef GAPBUFFER_H
#define GAPBUFFER_H
#include <iostream>
#include <exception>
#include <string>

using namespace std;
#define MAXSIZE 100 
#define MINSIZE 20
#define MINGAPSIZE 8
/*
	gapBuffer implementation needs:
	- track current position in buffer
	- move the buffer left and right
	- copy characters in the buffer properly
	- resize buffer gap
	- throw an error if we pass the max buffer size, and resize the buffer
	- memory deallocation

*/

class GapBuffer {
	public:
		friend class GapBufferTest;
		GapBuffer();
		GapBuffer(int, int);
		~GapBuffer();
		

		int moveLeft();
		int moveRight();
		
		void insert(char);
		void insert(string);

		int remove();
		int moveToStart();
		int moveToEnd();

		//gets info from gapbuffer and stores into a string
		string toString();
				
		// getters
		int getStartPos();
		int getEndPos();
		int getBufferSize();
		int getOccupied();
		int getIndexOfLastElem();
		int getGapSize();
		void dump();
		char getValueAt(int);
		void emptyBuffer();

		string getRightSideOfGap();
		void deleteRightSideOfGap();

		void printAttributeInfo(); // move to private later
	private:
	
		char * m_buffer; // buffer array
		
		int m_gapSize; // size of gap
		int m_gapStartPos; // left pos of gap buffer
		int m_gapEndPos; // right pos of gap buffer
		int m_size; // the size of the whole buffer
		int m_occupied; // how many indices are occupied
		int m_indexOfLastElement;
		
		
		/* private helper functions*/
		void clearBuffer();
		void resize();
		void resizeBuffer();
		void updatePositionOfLastElement(string);
		bool full();


		
		
};

#endif
