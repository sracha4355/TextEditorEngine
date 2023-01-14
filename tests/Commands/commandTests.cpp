#include "commands.h"
#include <sstream>

#include <gtest/gtest.h>

void tCB(Window * win, string ch, int ct){
	cout << "tCB ch: " << ch << " ct: " << ct << endl;
}

void tUB(Window * win, string ch, int ct){
	cout << "tUB ch: " << ch << " ct: " << ct << endl;
}


TEST(undoRedo, insertingCallbacksIntoStack){
	Window win;
	commandsContainer cont(&win);
	Command testCom;
	testCom.cbFunctions = make_pair(tCB, tUB);
	
	
	callbackFunc ptr1 = testCom.cbFunctions.first;
	callbackFunc ptr2 = testCom.cbFunctions.second;

	cont.addToUndo(testCom);
	
	cont.undo();
	cont.redo();
	
	EXPECT_EQ(true, cont.isRedoEmpty());
	EXPECT_EQ(false, cont.isUndoEmpty());
	cout << cont.undoSize() << endl;
	cout << cont.redoSize() << endl;	
}	

TEST(undoRedo, insertingMultipleTimesIntoUndoAndRedo){
	Window win;
	commandsContainer cont(&win);
	Command testCom;
	testCom.cbFunctions = make_pair(tCB,tUB);
	
	cont.addToUndo(testCom);
	cont.addToUndo(testCom);
	cont.addToUndo(testCom);
	EXPECT_EQ(cont.undoSize(), 3);
	
	cont.undo();
	EXPECT_EQ(cont.undoSize(), 2);
	EXPECT_EQ(cont.redoSize(), 1);
	cont.redo();
	EXPECT_EQ(cont.undoSize(), 3);
	EXPECT_EQ(cont.redoSize(), 0);
	

}

int main(){
	cout << "Command Tests" << endl;
	testing::InitGoogleTest();
	return RUN_ALL_TESTS() ;
}
