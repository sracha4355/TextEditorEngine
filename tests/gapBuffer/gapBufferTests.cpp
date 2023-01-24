#include "gapBuffer.h"
#include <gtest/gtest.h>

class GapBufferTest : public :: testing :: Test {
	protected:
		void SetUp(){
			b1.insert('A');
			b1.insert('B');
			b1.insert('C');
			//b1 will move right five times
			for(int i = 0; i < 5; i++) b1.moveRight();
			
			b2.insert('A');
			b2.insert('B');
			b2.insert('C');
			
			b3.insert('V');
			b3.insert('B');
			b3.insert('C');
			b3.insert('A');
			
			b6.insert('A');
			b6.insert('B');
			b6.insert('C');
			b6.insert('D');
			b6.insert('E');
			b6.insert('F');
			b6.insert('G');
			
			for(int i = 0; i < 19; i++) b7.insert('G');
			for(int i = 0; i < 5; i++) b8.insert('I');
		}
	
		GapBuffer b1;
		GapBuffer b2;	
		GapBuffer b3;
		GapBuffer b4;
		GapBuffer b5;			
		GapBuffer b6;	
		GapBuffer b7;
		GapBuffer b8;
};

/*
	Test Suites:
		moveLeft tests the moveLeft function
		moveRight tests the moveRight function
*/

/*
TEST(moveLeft, moveLeftOnceFromStart){
	GapBuffer buffer;
	int result = buffer.moveLeft();
	ASSERT_EQ(result, -1);
	EXPECT_EQ(buffer.getStartPos(), 0);
	EXPECT_EQ(buffer.getEndPos(), buffer.getGapSize() - 1);
}

TEST(moveLeft, moveLeftAfterInsertion){
	GapBuffer buffer;
	buffer.insert('A');
	buffer.insert('B');
	buffer.insert('C');
		
	int originalLeftPos = buffer.getStartPos();
	int newPos = buffer.moveLeft();
	EXPECT_EQ(newPos, originalLeftPos - 1);
}

TEST(moveLeft, moveLeftUntilWeReachTheEdge){
	GapBuffer buffer;
	buffer.insert('A');
	buffer.insert('B');
	buffer.insert('C');
	buffer.insert('C');
	buffer.insert('C');
	
	int originalLeftPos = buffer.getStartPos();
	
	int finalLeftPos = buffer.moveLeft();
	while(finalLeftPos != -1){
		finalLeftPos = buffer.moveLeft();
	} 
	
	EXPECT_EQ(-1, finalLeftPos);
	EXPECT_NE(finalLeftPos, originalLeftPos);
	EXPECT_EQ(originalLeftPos, 5);
	
}

TEST_F(GapBufferTest, moveRightNormalCase){
	int originalPosition = b1.getEndPos();
	int originalLeftPosition = b1.getStartPos();

	EXPECT_EQ(originalPosition, b1.moveRight() - 1);
	EXPECT_EQ(originalLeftPosition, b1.getStartPos() -1);
 	
}

TEST_F(GapBufferTest, moveRightUntilWeReachTheEdge){
	int originalPos = b1.getEndPos();
	
	int finalPos = b1.moveRight();
	while(finalPos != -1){
		finalPos = b1.moveRight();
	}
	
	EXPECT_EQ(-1, finalPos);
	EXPECT_NE(finalPos, originalPos);

}

TEST_F(GapBufferTest, moveRightThrice){
	int originalPos = b1.getEndPos();
	for(int i = 0; i < 3; i++) b1.moveRight();
	EXPECT_EQ(originalPos + 3, b1.getEndPos());
}

TEST_F(GapBufferTest, testOccupiedCounter){
	EXPECT_EQ(b1.getOccupied(), 3);
	b1.remove();
	EXPECT_EQ(b1.getOccupied(), 2);
}

TEST_F(GapBufferTest, removeUntilBufferAtEdge){
	EXPECT_EQ(b2.getOccupied(), 3);
	b2.remove();
	b2.remove();
	b2.remove();
	EXPECT_EQ(b2.getStartPos(), 0);
	EXPECT_EQ(b2.remove(), -1);
	EXPECT_EQ(b2.getStartPos(), 0);
}

TEST_F(GapBufferTest, removeThenCheckOccupied){
	EXPECT_NE(b3.getOccupied(),3);
	EXPECT_EQ(b3.getOccupied(),4);
	b3.remove();
	b3.remove();
	b3.remove();
	EXPECT_EQ(b3.getOccupied(),1);
	
}

TEST_F(GapBufferTest, InsertTillFull){
	EXPECT_EQ(b4.getBufferSize(), 20);
	EXPECT_EQ(b4.getOccupied(), 0);
	for(int i = 0; i < 20; i++) b4.insert('C');

	EXPECT_NE(b4.getOccupied(), 0);
	EXPECT_NE(b4.getOccupied(), b4.getBufferSize() - 1);
}

//resizeTests failed
TEST_F(GapBufferTest, ResizeBuffer){
	for(int i = 0; i < 19; i++) b4.insert('C');
	EXPECT_EQ(b4.getOccupied(), 19);
	EXPECT_EQ(b4.getOccupied() + 1, b4.getBufferSize());
	
	int startPosOne = b4.getStartPos();
	EXPECT_EQ(startPosOne, b4.getEndPos());
	b4.insert('C');
	EXPECT_EQ(b4.getStartPos(), 20);
	EXPECT_EQ(40, b4.getBufferSize());
	EXPECT_EQ(b4.getOccupied(), 20);

	EXPECT_EQ(b4.getIndexOfLastElem(), 19);
	
}

TEST_F(GapBufferTest, ResizeBufferWhenGapWasMovedToTheMiddle){
	int origSize = b5.getBufferSize();
	for(int i = 0; i < 19; i++) b5.insert('P');
	int occupied = b5.getOccupied();
	for(int i = 0; i < 9; i++) b5.moveLeft();	
	
	b5.insert('Z');
	EXPECT_EQ(b5.getBufferSize(), origSize * 2);
	EXPECT_EQ(occupied + 1, b5.getOccupied());
		
}

TEST_F(GapBufferTest, checkIfIndexOfLastElemIsInRightSpotAfterMovingLeft){
	EXPECT_EQ(b6.getIndexOfLastElem(), 6);

	b6.moveLeft();
	b6.moveLeft();
	b6.moveLeft();
	EXPECT_EQ(b6.getIndexOfLastElem(), 7);
	
	
}

TEST_F(GapBufferTest, moveToStart){
	EXPECT_EQ(b7.getStartPos(), 19);
	b7.moveToStart();
	EXPECT_EQ(b7.getStartPos(), 0);

}

TEST_F(GapBufferTest, moveToEnd){
	int origEndPos = b8.getEndPos();
	b8.moveToEnd();
	EXPECT_NE(origEndPos, b8.getEndPos());
	EXPECT_EQ(b8.getEndPos(), b8.getBufferSize() - 1);

}

TEST_F(GapBufferTest, toStringMethodTest){
	GapBuffer buffer;
	for(int i = 65; i < 70; i++){
		buffer.insert( (char) i);
	}
	string word = buffer.toString();
	EXPECT_EQ(word, "ABCDE");
	/*
	buffer.dump();
	buffer.moveRight();
	buffer.moveRight(); 
	buffer.moveRight();
	cout << word << endl;
	buffer.insert('Z');
	word = buffer.toString();
	cout << word << endl;
	*/
//} 
/*
TEST(insertWord, insertWordThenUseToString){
	GapBuffer buffer;
	buffer.insert("Hello World");

	string word = buffer.toString();
	EXPECT_EQ(word, "Hello World");

}

TEST(deleteRightSideOfGap, deleteNonEmptyRightSide){
	GapBuffer gb;
	gb.insert("Hello World");
	gb.moveLeft();
	gb.moveLeft();
	gb.moveLeft();
	gb.dump();
	string rs = gb.getRightSideOfGap();
	int length = rs.length();
	gb.printAttributeInfo();
	cout << rs << " length of rs: " << length << endl;
	gb.deleteRightSideOfGap();
	gb.dump();
	gb.printAttributeInfo();
	gb.moveRight();
	gb.dump(); gb.printAttributeInfo();
	gb.moveLeft(); gb.moveLeft(); gb.moveLeft();
	gb.dump(); gb.printAttributeInfo();
	gb.moveToEnd();
	gb.dump(); gb.printAttributeInfo();
	
}
*/

TEST_F(GapBufferTest, setPoint){
	b6.dump();
	b6.printAttributeInfo();
	b6.moveToPoint(4);
	b6.dump();
	b6.printAttributeInfo();
	b6.insert('l');
	b6.dump();
	
	b6.moveToPoint(15);
	b6.dump();
	b6.printAttributeInfo();
}


int main(){	
	// supresses cout statements from member functions
	// for now, the cout statements were there for debugging, will remove later.
	//auto old_buffer = std :: cout.rdbuf(nullptr);
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
