#pragma once
#include "buffer.h"
#include <fstream>
#include <string>

using namespace std;

// struct method implementation in file.cpp

/* Obj of the file module: perform read and write operations to a TextBuffer Object
 *
 *
 */
struct File{
	TextBuffer * m_buffer;
	string m_fileName;

	File() : m_buffer(nullptr), m_fileName(""){}
	// sets the buffer for which read and write operations will be performed
	bool readData();
	bool writeData();
	//bool clearFile();
};

/*
 *
	// sets the buffer for which read and write operations will be performed
	void setBuffer(TextBuffer*);
	// reads data from file and loads into m_buffer
	void setFile(string);
	void setLogActive(bool);
 *
 */
