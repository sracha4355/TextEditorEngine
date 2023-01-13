// objective of this module:
/* Module defines commands that the user can use to alter text
	- The commands are built on the top of the functions provided by the TextBuffer class
	- If there is a command that is difficult to implement with the given TextBuffer functions,then changes need to be made in sim/src/TextBuffer/TextBuffer.h & TextBuffer.cpp
	- Commands will be able to access a clipboard use for copying and pasting
	- thinking of also making this the interface where user input is taken to edit text, giving that job to another module might complicate things, so keeping user input and commands together might make the code easier to understand
	
*/

/*
	Where I left: I am thinking of restructing the Command Struct
	- the command struct will have a undo function and a execute function
	- and I add fields to link a TextBuffer and Clipboard
	- The class Commands will manage the undo and redo functionality
	- my previous idea was using a system of callback functions and function pointers
	- but what I am thinking of now may be simplier
*/

#pragma once
#include "window.h"
#include "clipboard.h"
#include "buffer.h"

#include <functional>
#include <set>
#include <string>
#include <stack>

using namespace std;

// typedef function <void(TextBuffer&, Clipboard&, string, int)> Callback;
// typedef function <void(TextBuffer&, Clipboard&, string, int)> UndoCallback;

typedef void (*Callback) (TextBuffer*, Clipboard*, string, int);
typedef void (*UndoCallback) (TextBuffer*, Clipboard*, string, int);

struct Command {
	/*Command information*/
	string commandHeader;
	int commandTail;

	//Window object contains references to a TextBuffer and Clipboard
	Window * win;
	
	// the callback functions
	Callback cb = nullptr;
	UndoCallback ub = nullptr;
	

	void callCallback(){
		if(cb != nullptr && win != nullptr){
			cb(win -> getBufferRef(), win -> getClipboardRef(), commandHeader, commandTail);
		}
	}
	
	void callUndoCallback(){
		if(ub != nullptr && win != nullptr){
			ub(win -> getBufferRef(), win -> getClipboardRef(), commandHeader, commandTail);
		}
	}	
};





// cc 0  "cc" is the keybinding "cc0" is the full command
// we should and pass the full command title into the callback
// this would restrict creating new commands to command identifer first then number
// reserve zero as a do nothing command

/*	
	Basic Commands I need to implement
	Copy, Paste, Cut, Delete : make command versions that do this for n lines
	Undo, Redo, Find
*/

class Commands {
	public:
		Commands(Window*);
        ~Commands();
        
        bool insertCommand(string, Command);
        bool removeCommand(string);
        Command * findCommand(string);
        
        
        void addToUndo(Command);
       	void addToRedo(Command);
       	void undo();
       	void redo();
      
  		  
	private:
	
		Window * m_win;
		map <string, Command> m_commandList;
		// Possibly will bind the callbacks to the std :: function objects in the stacks?
		stack <Command> m_undo;
		stack <Command> m_redo;
};
 
 



