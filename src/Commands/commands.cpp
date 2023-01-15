 #include "commands.h"
 
 commandsContainer :: commandsContainer(Window * _win){
	m_win = _win;
}

bool commandsContainer :: isUndoEmpty(){return m_undo.empty();}
bool commandsContainer :: isRedoEmpty(){return m_redo.empty();}
int commandsContainer :: undoSize(){return m_undo.size();}
int commandsContainer :: redoSize(){return m_redo.size();}

void commandsContainer :: executeCommand(const string key, string cHeader, int cTail){
	Command * com = getCommand(key);
	com -> 	cbFunctions.first(m_win, cHeader, cTail);
	addToUndo(*com);
}

void commandsContainer :: insertCommand(const string key, const Command & com){
	if(m_commandList.count(key) == 1) return;
	m_commandList.insert({key, com});
}

bool commandsContainer :: removeCommand(const string key){
	if(m_commandList.count(key) == 0) return false;
	m_commandList.erase(key);
	return true;

}

Command * commandsContainer :: getCommand(const string key){
	if(m_commandList.count(key) == 0) return nullptr;
	return &(m_commandList.find(key) -> second);
}


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

