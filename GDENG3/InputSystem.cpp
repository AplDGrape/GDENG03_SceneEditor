#include "InputSystem.h"

InputSystem* InputSystem::sharedInstance = NULL;
InputSystem::InputSystem()
{
	
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

InputSystem* InputSystem::getInstance()
{
	if(sharedInstance != NULL)
	{
		return sharedInstance;
	}
}

void InputSystem::destroy()
{
	if(sharedInstance != NULL)
	{
		delete sharedInstance;
	}
}

void InputSystem::addListener(InputListener* listener)
{
	this->InputListeners.push_back(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	int index = -1;
	for(int i = 0; i < this->InputListeners.size(); i++)
	{
		if(this->InputListeners[i] == listener)
		{
			index = i;
			this->InputListeners.erase(this->InputListeners.begin() + index);
			break;
		}
	}

}

void InputSystem::update()
{
	POINT currentMousePosition = {};
	::GetCursorPos(&currentMousePosition);

	

	if(this->firstTime)
	{
		this->firstTime = false;
		this->oldMousePosition = Point(currentMousePosition.x, currentMousePosition.y);
	}

	if (currentMousePosition.x != oldMousePosition.m_x || currentMousePosition.y != oldMousePosition.m_y)
	{
		Point deltaPosition = Point(currentMousePosition.x - oldMousePosition.m_x, currentMousePosition.y - oldMousePosition.m_y);
		this->callOnMouseMove(deltaPosition);
	}

	this->oldMousePosition = Point(currentMousePosition.x, currentMousePosition.y);

	if(::GetKeyboardState(m_keys_state))
	{
		for(unsigned int i = 0; i < 256; i++)
		{
			if(m_keys_state[i] & 0x80 && m_keys_state[i] != m_old_keys_state[i])
			{
				if(i == VK_LBUTTON && m_keys_state[i] != m_old_keys_state[i])
				{
					Point deltaPosition = Point(currentMousePosition.x - oldMousePosition.m_x, currentMousePosition.y - oldMousePosition.m_y);
					this->callOnLeftMouseDown(deltaPosition);
				}
				else if (i == VK_RBUTTON && m_keys_state[i] != m_old_keys_state[i])
				{
					Point deltaPosition = Point(currentMousePosition.x - oldMousePosition.m_x, currentMousePosition.y - oldMousePosition.m_y);
					this->callOnRightMouseDown(deltaPosition);
				}
				else
				{
					this->callOnKeyDown(i);
				}
			}
			else if(m_keys_state[i] != m_old_keys_state[i])
			{
				if (i == VK_LBUTTON && m_keys_state[i] != m_old_keys_state[i])
				{
					Point deltaPosition = Point(currentMousePosition.x - oldMousePosition.m_x, currentMousePosition.y - oldMousePosition.m_y);
					this->callOnLeftMouseUp(deltaPosition);
				}
				else if (i == VK_RBUTTON && m_keys_state[i] != m_old_keys_state[i])
				{
					Point deltaPosition = Point(currentMousePosition.x - oldMousePosition.m_x, currentMousePosition.y - oldMousePosition.m_y);
					this->callOnRightMouseUp(deltaPosition);
				}
				else
				{
					this->callOnKeyUp(i);
				}
			}

		}
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::setCursorPosition(const Point& position)
{
	::SetCursorPos(position.m_x, position.m_y);
}

void InputSystem::showCursor(bool show)
{
	::ShowCursor(show);
}

bool InputSystem::isKeyDown(int key)
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keys_state[i] & 0x80 && i == key) {
			return true;
		}

		else if (i == key)
		{
			return false;
		}
	}
}

bool InputSystem::isKeyUp(int key)
{
	for (int i = 0; i < 256; i++)
	{
		if(!(m_keys_state[i] & 0x80) && i == key){
			return true;
		}

		else if(i == key)
		{
			return false;
		}
	}
}

void InputSystem::callOnKeyDown(int key)
{
	for(int i = 0; i < InputListeners.size(); i++)
	{
		InputListeners[i]->onKeyDown(key);
	}
}

void InputSystem::callOnKeyUp(int key)
{
	for (int i = 0; i < InputListeners.size(); i++)
	{
		InputListeners[i]->onKeyUp(key);
	}
}

void InputSystem::callOnMouseMove(Point delta)
{
	for(int i = 0; i < InputListeners.size(); i++)
	{
		InputListeners[i]->onMouseMove(delta);
	}
}

void InputSystem::callOnLeftMouseDown(Point delta)
{
	for (int i = 0; i < InputListeners.size(); i++)
	{
		InputListeners[i]->onLeftMouseDown(delta);
	}
}

void InputSystem::callOnRightMouseDown(Point delta)
{
	for (int i = 0; i < InputListeners.size(); i++)
	{
		InputListeners[i]->onRightMouseDown(delta);
	}
}

void InputSystem::callOnLeftMouseUp(Point delta)
{
	for (int i = 0; i < InputListeners.size(); i++)
	{
		InputListeners[i]->onLeftMouseUp(delta);
	}
}

void InputSystem::callOnRightMouseUp(Point delta)
{
	for (int i = 0; i < InputListeners.size(); i++)
	{
		InputListeners[i]->onRightMouseUp(delta);
	}
}


InputSystem::~InputSystem()
{
}



