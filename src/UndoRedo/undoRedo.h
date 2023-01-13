#pragma once

#include "clipboard.h"
#include "buffer.h"

#include <stack>
#include <functional>

using namespace std;
typedef function <void(TextBuffer&, Clipboard&, string)> Callback;
typedef function <void(TextBuffer&, Clipboard&, string, Callback)> UndoCallback;

/*
typedef void (*Callback) (TextBuffer&, Clipboard&, string);
typedef void (*UndoCallback) (TextBuffer&, Clipboard&, string, Callback func);
*/


class UndoRedo {
	public:
		UndoRedo(TextBuffer*, Clipboard*);
		
		// calls the callback on top of the undo stack
		void undo();
		// calls the callback on top of the redo stack
		void redo();
		
		// add callbacks to the respective stacks
		void addToUndo(UndoCallback);
		void addToRedo();
		
	private:
		//The stacks store callbacks
		stack <UndoCallback> m_undo;
		stack <Callback> m_redo;
		
		TextBuffer * m_tb;
		Clipboard * m_cb;

};
