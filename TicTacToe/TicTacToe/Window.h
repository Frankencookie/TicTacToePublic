#pragma once
#include <SDL.h>
#include <stdio.h>
#include "Helpers.h"

class SpriteBank;

class Window
{
public:
	Window();
	~Window();

protected:

	SDL_Window* window_ptr = nullptr;
	SDL_Surface* surface_ptr = nullptr;
	SDL_Renderer* renderer_ptr = nullptr;

	void InitWindow();

	int windowWidth = 512;
	int windowHeight = 512;
	int third = 0;

public:
	static Window* instance;

	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();

	void DrawSprite(Sprite* sprite, Vector2D location);
	void DrawSprite(std::string name, Vector2D location);

	void DrawBackground();

	void ClearScreen();

	void PresentRender();

	int GetWindowWidth();
	int GetWindowHeight();

	int GetScreenThird();
};

