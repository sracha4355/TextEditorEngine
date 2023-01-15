#include "commands.h"
#include <sstream>

#include <gtest/gtest.h>

void tCB(Window * win, string ch, int ct){
	cout << "tCB ch: " << ch << " ct: " << ct << endl;
}

void tUB(Window * win, string ch, int ct){
	cout << "tUB ch: " << ch << " ct: " << ct << endl;
}


TEST(commandListTests, testInsert){
	Window win;
	commandsContainer cont(&win);
	Command testCom;		
	testCom.cbFunctions = make_pair(tCB, tUB);
	
	Command testCom2;		
	testCom2.cbFunctions = make_pair(tCB, tUB);
	
	cont.insertCommand("c", testCom);
	cont.insertCommand("p", testCom2);
	
	EXPECT_NE(cont.getCommand("c"), nullptr);
	EXPECT_NE(cont.getCommand("p"), nullptr);
	
}


TEST(commandListTests, testRemove){
	Window win;
	commandsContainer cont(&win);
	Command testCom;		
	testCom.cbFunctions = make_pair(tCB, tUB);
	
	Command testCom2;		
	testCom2.cbFunctions = make_pair(tCB, tUB);
	
	cont.insertCommand("c", testCom);
	cont.insertCommand("p", testCom2);
	
	EXPECT_EQ(cont.removeCommand("c"), true);
	EXPECT_EQ(cont.removeCommand("p"), true);
	EXPECT_EQ(cont.removeCommand("p"), false);
	
}

TEST(commandListTests, testExecuteCommand){
	Window win;
	commandsContainer cont(&win);
	Command testCom;
	stringstream ss;
	streambuf * coutbuf = cout.rdbuf();
	//redirect cout to ss
	cout.rdbuf(ss.rdbuf());
	
	string dummyHeader = "dummy header";
	string dummyTail = "55";
	int dummyTAIL = 55;
	string expected = "tCB ch: " + dummyHeader + " ct: " + (dummyTail)+ "\n";

	testCom.cbFunctions = make_pair(tCB, tUB);
	cont.insertCommand("c", testCom);
	cont.executeCommand("c", dummyHeader, dummyTAIL);
		
	cout.rdbuf(coutbuf);
	
	string output = ss.str();
	EXPECT_EQ(output, expected);
	
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
