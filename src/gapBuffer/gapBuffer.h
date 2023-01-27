#ifndef GAPBUFFER_H
#define GAPBUFFER_H
#include <iostream>
#include <exception>
#include <string>

using namespace std;
#define MAXSIZE 100 
#define MINSIZE 20
#define MINGAPSIZE 8

class GapBuffer {
	public:
		GapBuffer();
		GapBuffer(int, int);
		~GapBuffer();
				
		// moves the gap left or right by one, adjusting the characters around the gap
		int moveLeft();
		int moveRight();
		
		// insertions for both types
		void insert(char);
		void insert(string);

		// remove's a character based on the m_gapStartPos position
		int remove();
		
		// move to the beginning or end of the gapBuffer
		int moveToStart();
		int moveToEnd();
		int moveToPoint(int);

		//gets info from gapbuffer and stores into a string
		string toString();
				
		// getters for member variables
		int getStartPos();
		int getEndPos();
		int getBufferSize();
		int getOccupied();
		int getIndexOfLastElem();
		int getGapSize();
		
		// print gapBuffer for debugging purposes
		void dump();
		
		// get letter at index
		char getValueAt(int);
		
		//clear contents
		void emptyBuffer();

		// get or delete whatever is on the right side of the gap
		string getRightSideOfGap();
		void deleteRightSideOfGap();

		// print gapBuffer member variables for debugging purposes
		void printAttributeInfo(); // move to private later
	private:
	
		char * m_buffer; // buffer array
		
		int m_gapSize; // size of gap
		int m_gapStartPos; // left pos of gap buffer
		int m_gapEndPos; // right pos of gap buffer
		int m_size; // the size of the whole buffer
		int m_occupied; // how many indices are occupied
		int m_indexOfLastElement; // tracks the index of the last filled position in the the gap buffer
		
		
		/* private helper functions*/
		void clearBuffer();
		// resize the gap
		void resize();
		//resize the buffer array
		void resizeBuffer();
		// track the pos of the last element, important for resizing
		void updatePositionOfLastElement(string);
		// tells us if the buffer has space for insertion
		bool full();


		
		
};

#endif
