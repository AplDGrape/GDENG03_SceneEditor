#pragma once

#include "AGameObject.h"
#include "EditorAction.h"
#include <stack>

class EditorAction;
class AGameObject;

class ActionHistory
{
public:
	typedef std::stack<EditorAction*> ActionStack;

	static  ActionHistory* getInstance();

	static void initialize();
	static void destroy();

	void recordAction(AGameObject* gameObject);
	bool hasRemainingUndoActions();
	bool hasRemainingRedoActions();

	EditorAction* undoAction();
	EditorAction* redoAction();

	void clear();
private:
	ActionHistory();
	~ActionHistory();

	ActionHistory(ActionHistory const&) {};				// Copy constructor is private
	ActionHistory& operator=(ActionHistory const&) {};	// Assignment operator is private

	static ActionHistory* sharedInstance;

	ActionStack actionsPerformed;
	ActionStack actionsCancelled;
};