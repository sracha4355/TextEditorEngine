#include "clipboard.h"
#include <gtest/gtest.h>

class ClipboardTest : public :: testing :: Test{
	protected:
		void SetUp() override{
			buf.insert("Hello line 1");
			buf.createNewLine();
			buf.insert("Hello line 2");
			buf.createNewLine();
			buf.insert("	Hello line 3");
		}
			
		TextBuffer buf;
		

};

TEST_F(ClipboardTest, testInsertLines){
	Clipboard cb;
	int numLines = 3;
	string * content = new string[numLines];
	
	// i + 1 in getLineContents because the TextBuffer has no line 0
	for(int i = 0; i < numLines; i++) content[i] = buf.getLineContents(i + 1);
	cb.insertLines(content, numLines);
	for(int i = 0; i < (int) cb.getContent().size(); i++) EXPECT_EQ(cb.getContent()[i], content[i]);
		
	delete [] content;
	
}

TEST_F(ClipboardTest, testClearClipboard){
	Clipboard cb;
	int numLines = 3;
	string * content = new string[numLines];
	
	// i + 1 in getLineContents because the TextBuffer has no line 0
	for(int i = 0; i < numLines; i++) content[i] = buf.getLineContents(i + 1);
	cb.insertLines(content, numLines);
	
	int origSize = (int) cb.getContent().size();
	
	cb.clearClipboard();
	
	int newSize = (int) cb.getContent().size();

	EXPECT_EQ(newSize, 0);
	EXPECT_EQ(origSize, numLines);
	EXPECT_NE(newSize, origSize);
	
	
	delete [] content;

}

int main(){
	cout << "clipboard tests" << endl;
	::testing :: InitGoogleTest();
	return RUN_ALL_TESTS();
}
