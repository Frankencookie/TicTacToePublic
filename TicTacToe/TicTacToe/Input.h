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
	static void AttachClickObserver(IInputObserver* observer);
	static void DetachClickObserver(IInputObserver* observer);
	static void AttachKeyboardObserver(IInputObserver* observer);
	static void DetachKeyboardObserver(IInputObserver* observer);

	static void NotifyObserversClick(Vector2D position);
	static void NotifyObserversKey(SDL_Keycode keycode);


private:
	static std::vector<IInputObserver*> clickObservers;
	static std::vector<IInputObserver*> keyObservers;
};

class IInputObserver
{
public:
	virtual void OnClickEvent(Vector2D position);
	virtual void OnKeyboardEvent(SDL_Keycode keycode);
};
