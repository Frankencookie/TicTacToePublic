#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class Helpers
{
};

struct Sprite
{
	SDL_Texture* image;
	std::string name;
	std::string address;

	int width;
	int height;
};

struct Vector2D
{
	Vector2D(int x, int y);
	int X;
	int Y;
};