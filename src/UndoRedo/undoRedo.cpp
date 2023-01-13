#include "undoRedo.h"


/*
	Calls the UndoCallback function on top of the m_undo stack and then places the 
	Callback function within UndoCallback into the m_redo stack
*/

UndoRedo :: UndoRedo(TextBuffer * _tb, Clipboard *_cb){
	m_tb = _tb;
	m_cb = _cb;
}

void UndoRedo :: undo() {
	
}

/*
	Calls the CallBack Function on top of the m_redo
*/
void UndoRedo :: redo(){


}
		
// add callbacks to the respective stacks
void UndoRedo :: addToUndo(UndoCallback uCallback) { 
	
	m_undo.push(uCallback);

}

void UndoRedo :: addToRedo() {

}
