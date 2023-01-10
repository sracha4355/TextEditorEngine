#include "file.h"
#include <iostream>
// #include "gtest/gtest.h"

int main(){
	cout << "reading an writing to buffer tests" << endl;
	string fileName = "test.cpp";
	TextBuffer buf;

	File file;
	file.m_fileName = fileName;
	file.m_buffer = &buf;
	//file.setFile(fileName);
	//file.setBuffer(&buf);
	file.readData();	

	buf.getInfo();
	buf.dump();
	
	buf.insert("#include <iostream>");
	buf.createNewLine();
	buf.insert("int main() { std::  cout << \"Hello World \" << std:: endl; return 0;}");

	file.writeData();
	
	cout << endl;
	buf.getInfo();
	buf.dump();
	return 0;
}

