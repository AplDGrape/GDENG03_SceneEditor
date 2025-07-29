#include "ActionHistory.h"
#include "EngineBackEnd.h"

ActionHistory* ActionHistory::sharedInstance = NULL;

ActionHistory::ActionHistory()
{
}

ActionHistory* ActionHistory::getInstance()
{
	return sharedInstance;
}

void ActionHistory::initialize()
{
	sharedInstance = new ActionHistory();
}

void ActionHistory::destroy()
{
	delete sharedInstance;
}

void ActionHistory::recordAction(AGameObject* gameObject)
{
	if(EngineBackEnd::getInstance()->getMode() == EngineBackEnd::EditorMode::EDITOR)
	{
		EditorAction* editorAction = new EditorAction(gameObject);
		this->actionsPerformed.push(editorAction);
	}
}

bool ActionHistory::hasRemainingUndoActions()
{
	return !this->actionsPerformed.empty();
}

bool ActionHistory::hasRemainingRedoActions()
{
	return !this->actionsCancelled.empty();
}

EditorAction* ActionHistory::undoAction()
{
	if(EngineBackEnd::getInstance()->getMode() != EngineBackEnd::EditorMode::EDITOR)
	{
		return NULL;
	}

	if(this->hasRemainingUndoActions())
	{
		EditorAction* action = this->actionsPerformed.top();
		this->actionsPerformed.pop();
		this->actionsCancelled.push(action);
		return action;
	}
	else
	{
		return NULL;
	}

}

EditorAction* ActionHistory::redoAction()
{
	if (EngineBackEnd::getInstance()->getMode() != EngineBackEnd::EditorMode::EDITOR)
	{
		return NULL;
	}

	if (this->hasRemainingRedoActions())
	{
		EditorAction* action = this->actionsCancelled.top();
		this->actionsCancelled.pop();
		this->actionsPerformed.push(action);
		return action;
	}
	else
	{
		return NULL;
	}
}

void ActionHistory::clear()
{
	while (this->hasRemainingUndoActions()) 
	{
		EditorAction* action = this->actionsPerformed.top();
		delete action;
		this->actionsPerformed.pop();
	}

	while (this->hasRemainingRedoActions()) 
	{
		EditorAction* action = this->actionsCancelled.top();
		delete action;
		this->actionsCancelled.pop();
	}
}

ActionHistory::~ActionHistory()
{
	this->clear();
}