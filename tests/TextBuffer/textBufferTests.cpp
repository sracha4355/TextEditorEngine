#include <buffer.h>



void di(TextBuffer&);
void deleteLineTests(){
	TextBuffer bu;
	bu.insert("line");
	di(bu);
	bu.getLine(1) -> printAttributeInfo();
	bu.shiftLines();
	di(bu);	
	bu.getLine(1) -> printAttributeInfo();
	cout << endl;
	bu.getLine(2) -> printAttributeInfo();
	
	bu.insert("Hello World");
	di(bu);
	bu.getLine(2) -> moveToStart();
	di(bu);
	bu.remove();
	di(bu);
	bu.insert('Z');
	di(bu);
	bu.createNewLine();
	bu.createNewLine();
	di(bu);
	bu.remove();
	di(bu);
	bu.insert("hello");
	di(bu);
	bu.createNewLine();
	bu.insert("kshsk");
	bu.createNewLine();
	bu.insert("ZZZZ");
	di(bu);
	bu.setCurrentLine(2);
	bu.insert('h');
	di(bu);
	bu.remove();
	di(bu);
	bu.getLine(bu.getCurrentLine()) -> moveToStart();
	di(bu);
	bu.remove();
	di(bu);
	bu.insert('j');
	di(bu);
	bu.setCurrentLine(2);
	bu.getLine(2) -> moveToStart();
	di(bu);
	bu.remove();
	di(bu);
	bu.insert("hhjj");
	di(bu);
	bu.insert("hhjj");
	di(bu);
	
	bu.insert("hhjj");
	di(bu);

	bu.shiftLinesDown();
	di(bu);
	bu.setCurrentLine(1);
	bu.insert('k');
	di(bu);
	bu.setCurrentLine(2);
	bu.insert("Hello line 2");
	di(bu);
	bu.shiftLinesDown();
	di(bu);
	bu.shiftLinesUp();
	bu.insert("kkk");
	di(bu);

	cout << bu.getLineContents(2) << endl;
	cout << "line 5: " << bu.getLineContents(5) << endl;

	cout << bu.getLineContents(1) << endl;

	bu.setCurrentLine(1);
	bu.shiftLinesUp();
	di(bu);
	bu.setCurrentLine(3);
	bu.shiftLinesDown();
	di(bu);
	bu.insert("klsl");
	di(bu);
	bu.moveLeft();
	bu.insert("hhhh");
	for(int i = 0; i < 100; i++){
		bu.moveLeft();
	}
	di(bu);
	bu.insert("LK");
	di(bu);
	for(int i = 0; i < 100; i++){
		bu.moveRight();
	}
	di(bu);
	bu.insert("LK");
	di(bu);
}
void tests4(){
	TextBuffer bu;
	bu.insert("line 1 in here");
	bu.moveLeft();
	bu.moveLeft();
	bu.moveLeft();
	bu.moveLeft();
	bu.shiftLines();
	di(bu);
	bu.getLine(1) -> printAttributeInfo();
	bu.getLine(1) -> dump();
	bu.setCurrentLine(1);
	bu.insert('H');
	di(bu);

	bu.getLine(1) -> printAttributeInfo();
	bu.getLine(1) -> dump();

}

void shiftLineTests3(){
	TextBuffer bu;
	bu.insert("hello");
	bu.createNewLine();
	bu.setCurrentLine(1);
	bu.insert('L');
	bu.moveLeft();
	bu.moveLeft();
	di(bu);
	bu.shiftLines();
	di(bu);
	bu.setCurrentLine(1);
	bu.insert('X');
	bu.setCurrentLine(2);
	bu.insert('Y');
	di(bu);
	bu.setCurrentLine(1);
	bu.moveLeft();
	di(bu);
	bu.setCurrentLine(2);
	bu.insert('P');
	di(bu);
	bu.setCurrentLine(1);
	bu.insert("DDDDDDDD");
	bu.insert("h");

	di(bu);
	bu.insert("MMMMMM");

	di(bu);
	bu.insert("H");
	bu.insert('9');
	bu.moveLeft(), bu.moveLeft();
	bu.shiftLines();
	bu.insert("inseinto curr line");
	bu.moveLeft(), bu.moveLeft();
	bu.moveLeft(), bu.moveLeft();
	di(bu);
	bu.shiftLines();
	bu.insert('m');
	di(bu);

	bu.insert(9);
	di(bu);

	bu.shiftLines();

	di(bu);

	bu.setCurrentLine(5);
	bu.remove();
	di(bu);
	bu.remove(), bu.remove(), bu.remove();
	di(bu);
	bu.remove();
	int result = bu.remove();
	cout << "res: "<< result << endl;
	bu.insert('g');
	di(bu);	
	bu.remove();
	bu.remove();
	bu.remove();
	cout << bu.remove() << endl;
	di(bu);
	bu.getLine(5) -> printAttributeInfo();
}
void shiftLineTests2(){
	TextBuffer buf;
	buf.insert("On line 1");
	buf.createNewLine();
	buf.insert("On line 2");
	buf.createNewLine();
	buf.insert("On line 3");
	di(buf);
	buf.setCurrentLine(2);
	buf.moveLeft();
	buf.moveLeft();
	buf.insert('B');
	di(buf);	

	buf.shiftLines('\n');
	di(buf);
}
void shiftLineTests1(){
	TextBuffer buffer;
	buffer.insert("line 1");
	buffer.createNewLine();
	buffer.insert("line 2");
	buffer.createNewLine();
	buffer.insert("line 3");
	buffer.createNewLine();

	buffer.insert("line 4");
	buffer.createNewLine();

	buffer.insert("line 5");
	buffer.dump();
	buffer.setCurrentLine(2);
	buffer.insert("On 2 Still");
	buffer.dump();
	buffer.shiftLines('\n');
	buffer.dump();
	buffer.getInfo();
	buffer.insert("on the new line 3");
	buffer.dump();
	buffer.setCurrentLine(2);
	buffer.insert("ABC");
	buffer.dump();
}

int main(){
	cout << "TextBuffer Tests " << endl;
	TextBuffer * bu = new TextBuffer;
	for(int i = 0; i < 5; i++) bu -> createNewLine();
	delete bu;
	//deleteLineTests();

//	tests4();
	//shiftLineTests();
	//shiftLineTests2();
//	shiftLineTests3();


	/*	
	TextBuffer buffer;
	di(buffer);
	buffer.createNewLine();
	di(buffer);
	buffer.createNewLine();
	di(buffer);
	buffer.insert("Hello world");
	di(buffer);
	buffer.createNewLine();
	buffer.insert("HHHH");
	di(buffer);
	buffer.setCurrentLine(2);
	buffer.insert("I am on line 2");
	di(buffer);	
	for(int i = 0; i < 5; i++) buffer.remove();
	di(buffer);
	buffer.setCurrentLine(2);
	buffer.shiftLines('A');
	di(buffer);
	buffer.setCurrentLine(3);
	buffer.clearLine(3);
	buffer.insert('A');
	di(buffer);
	*/


}

void di(TextBuffer &buf ){
	buf.getInfo();
	buf.dump();
}
