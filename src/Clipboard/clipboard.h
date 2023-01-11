#pragma once
#include "buffer.h"
#include <vector>

using namespace std;

class Clipboard {
	public:
		Clipboard();
		void insertLines(string*, int);
		bool clearClipboard();
		
	private:

		vector <string> content;
		int m_numOfLines;
		
};