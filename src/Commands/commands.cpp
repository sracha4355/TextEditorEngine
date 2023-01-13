#include "commands.h"

Commands :: Commands(Window * _win){
	m_win = _win;
}


bool Commands :: insertCommand(string key, Command com){
	if(m_commandList.count(key) == 1) {
		cerr << " Commands :: insertCommand -> key already exists in map" << endl;
		return false;
	}
	
	m_commandList[key] = com;
	return true;
}
bool Commands :: removeCommand(string key){
	if(m_commandList.count(key) == 0) {
		cerr << " Commands :: removeCommand -> key does not exist in map" << endl;
		return false;
	}
	m_commandList.erase(key);
	return true;
	
}
Command * Commands :: findCommand(string key){
	auto com = m_commandList.find(key);
	if(com != m_commandList.end()) return &(com -> second);
	cerr << "Commands :: findCommand(key) -> value for " << key <<" not found " << endl;
	return nullptr;
	
}
        

void Commands :: addToUndo(Command com){
	m_undo.push(com);
}

void Commands :: addToRedo(Command com){
	m_redo.push(com);
}

void Commands :: undo(){
	Command top = m_undo.top();
	top.callUndoCallback();
	addToRedo(top);
}

void Commands :: redo(){
	Command top = m_redo.top();
	top.callCallback();
	addToUndo(top);
}
