#pragma once
#include <window.h>
#include <string>
#include <functional>
#include <utility>
#include <stack>

using namespace std;

typedef void (*Callback)(Window*,string,int);
typedef void (*undoCallback)(Window*,string,int);

typedef function<void(Window*,string,int)> callbackFunc;

struct Command{
	// pair holds callback and undoCallback
	pair <callbackFunc,callbackFunc> cbFunctions;
};

class commandsContainer{
	public:
		commandsContainer(Window *);

		void addToUndo(const Command & com);
		void addToRedo(const Command & com);
		void undo();
		void redo();
		bool isUndoEmpty();
		bool isRedoEmpty();
		int undoSize();
		int redoSize();
		
		stack < pair <callbackFunc, callbackFunc> >  m_undo;
		stack < pair <callbackFunc, callbackFunc> >  m_redo;
		Window * m_win;
		
		map <string, Command> m_commandList;
		
		
};

commandsContainer :: commandsContainer(Window * _win){
	m_win = _win;
}

bool commandsContainer :: isUndoEmpty(){return m_undo.empty();}
bool commandsContainer :: isRedoEmpty(){return m_redo.empty();}
int commandsContainer :: undoSize(){return m_undo.size();}
int commandsContainer :: redoSize(){return m_redo.size();}


void commandsContainer :: addToUndo(const Command & com){
	if(com.cbFunctions.second == nullptr) return;
	m_undo.push(com.cbFunctions);		
}

void commandsContainer :: addToRedo(const Command & com){
	if(com.cbFunctions.first == nullptr) return;
	m_redo.push(com.cbFunctions);		
}

void commandsContainer :: undo(){
	if(m_undo.empty()) {
		cerr << "undo stack is empty" << endl;
		return;
	}
	//pair <callbackFunc, callbackFunc>
	auto functions = m_undo.top();
	functions.second(m_win, "dummy header ", 55);
	m_redo.push(functions);
	m_undo.pop();
}

void commandsContainer :: redo(){
	if(m_redo.empty()){
		cerr << "redo stack is empty" << endl;
		return;
	}
	auto functions = m_redo.top();
	functions.first(m_win, "dummy header", 33);
	m_undo.push(functions);
	m_redo.pop();

}








