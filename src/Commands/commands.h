// objective of this module:
/* Module defines commands that the user can use to alter text
	- The commands are built on the top of the functions provided by the TextBuffer class
	- If there is a command that is difficult to implement with the given TextBuffer functions,then changes need to be made in sim/src/TextBuffer/TextBuffer.h & TextBuffer.cpp
	- Commands will be able to access a clipboard use for copying and pasting
	- thinking of also making this the interface where user input is taken to edit text, giving that job to another module might complicate things, so keeping user input and commands together might make the code easier to understand
	
*/

#pragma once
#include "buffer.h"
#include "clipboard.h"
#include <set>
#include <string>

using namespace std;

struct Command{
	string fullCommand;
	// the combinations of keys that invokes the command
	
	string keybinding;
	int keyBindingLength;
	string commmandDescrip;
	
	void (*callback) (TextBuffer&, string);
	void behavior(TextBuffer & buf, string _fullCommand){
			callback(buf, _fullCommand);
	}
	
};

// cc 0  "cc" is the keybinding "cc0" is the full command
// we should and pass the full command title into the callback
// this would restrict creating new commands to command identifer first then number
// reserve zero as a do nothing command

/*	Basic Commands I need to implement
	Copy, Paste, Cut, Delete : make command versions that do this for n lines
	Undo, Redo, Find
*/

class Commands {
	public:
		Commands();
        ~Commands();
        
        Command * initCommand(string, int, string, void (*callback)(TextBuffer&, string));
        
        bool insertCommand(Command&);
        void getCommandDetails(string keyBinding);
        void executeCommand(string fullCommand);
  		void removeCommand(string);
  		void printAllCommands();
  		
  		void setCommandBehavior(string keyBinding, void (*callback)(TextBuffer&, string));
  		
        
  private:
		map <string, Command> m_commandList;
		int m_numOfCommands;

};





