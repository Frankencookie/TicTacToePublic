#include "Input.h"

std::vector<IInputObserver*> Input::observers;

void Input::UpdateInput()
{
	while (SDL_PollEvent(&InputEvent))
	{
		switch (InputEvent.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				NotifyObserversClick(Vector2D(InputEvent.button.x, InputEvent.button.y));
				break;
			default:
				break;
		}
	}
}

void Input::AttachObserver(IInputObserver* observer)
{
	observers.push_back(observer);
}

void Input::DetachObserver(IInputObserver* observer)
{
	observers.erase(std::find(observers.begin(), observers.end(), observer));
}

void Input::NotifyObserversClick(Vector2D position)
{
	/*
	for (auto const& item : observers)
	{
		item->OnClickEvent(position);
	}
	*/
	/*
	std::list<IInputObserver*>::iterator it = observers.begin();
	while (it != observers.end())
	{
		(*it)->OnClickEvent(position);
		++it;
	}
	*/

	for (auto item : observers)
	{
		item->OnClickEvent(position);
	}

}

void IInputObserver::OnClickEvent(Vector2D position)
{

}
