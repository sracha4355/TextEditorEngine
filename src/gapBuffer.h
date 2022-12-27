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
		friend class Tester;
		GapBuffer();
		GapBuffer(int, int);
		~GapBuffer();
		

		int moveLeft();
		int moveRight();
		
		void insert(char);
		void remove();
		
		
	private:
	
		char * m_buffer; // buffer array
		int m_cursor; // current pos of cursor might not end up using
		
		int m_gapSize; // size of gap
		int m_gapStartPos; // left pos of gap buffer
		int m_gapEndPos; // right pos of gap buffer
		int m_size; // the size of the whole buffer
		int m_occupied; // how many indices are occupied
		int m_indexOfLastElement;
		
		
		/* private helper functions*/
		int getStartPos();
		int getEndPos();
		void clearBuffer();
		void resize();
		void resizeBuffer();
		void updateGapLength();
		void updatePositionOfLastElement(string);
		bool full();
		
		void printAttributeInfo();
		void dump();
		void dump2();
		
		
};

#endif
