#pragma once
#include "Helpers.h"
#include <list>
#include <vector>

class IInputObserver;

class Input
{
private:
	SDL_Event InputEvent;
public:
	void UpdateInput();

	//Observer pattern methods
	static void AttachObserver(IInputObserver* observer);
	static void DetachObserver(IInputObserver* observer);

	static void NotifyObserversClick(Vector2D position);


private:
	static std::vector<IInputObserver*> observers;
};

class IInputObserver
{
public:
	virtual void OnClickEvent(Vector2D position);
};
