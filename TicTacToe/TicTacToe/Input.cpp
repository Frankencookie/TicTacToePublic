#include "Input.h"

std::vector<IInputObserver*> Input::clickObservers;
std::vector<IInputObserver*> Input::keyObservers;

void Input::UpdateInput()
{
	while (SDL_PollEvent(&InputEvent))
	{
		switch (InputEvent.type)
		{
			case SDL_MOUSEBUTTONDOWN:
				NotifyObserversClick(Vector2D(InputEvent.button.x, InputEvent.button.y));
				break;
			case SDL_KEYDOWN:
				NotifyObserversKey(InputEvent.key.keysym.sym);
				break;
			default:
				break;
		}
	}
}

void Input::AttachClickObserver(IInputObserver* observer)
{
	clickObservers.push_back(observer);
}

void Input::DetachClickObserver(IInputObserver* observer)
{
	clickObservers.erase(std::find(clickObservers.begin(), clickObservers.end(), observer));
}

void Input::AttachKeyboardObserver(IInputObserver* observer)
{
	keyObservers.push_back(observer);
}

void Input::DetachKeyboardObserver(IInputObserver* observer)
{
	keyObservers.erase(std::find(keyObservers.begin(), keyObservers.end(), observer));
}

void Input::NotifyObserversClick(Vector2D position)
{
	for (auto item : clickObservers)
	{
		item->OnClickEvent(position);
	}
}

void Input::NotifyObserversKey(SDL_Keycode keycode)
{
	for (auto item : keyObservers)
	{
		item->OnKeyboardEvent(keycode);
	}
}

void IInputObserver::OnClickEvent(Vector2D position)
{
}

void IInputObserver::OnKeyboardEvent(SDL_Keycode keycode)
{
}
