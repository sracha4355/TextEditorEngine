#pragma once
#include "buffer.h"
#include "commands.h"
#include <stack>

class UndoRedo {
	public:

	private:
		//The stack needs to store callbacks
		stack< > m_redo;
		stack< > m_undo;
};
