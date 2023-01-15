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
		void insertCommand(const string, const Command&);
		bool removeCommand(const string);
		Command * getCommand(const string);
		void executeCommand(const string, string, int);
		
		
		bool isUndoEmpty();
		bool isRedoEmpty();
		int undoSize();
		int redoSize();
		
		stack < pair <callbackFunc, callbackFunc> >  m_undo;
		stack < pair <callbackFunc, callbackFunc> >  m_redo;
		Window * m_win;
		
		map <string, Command> m_commandList;
		
		
};









