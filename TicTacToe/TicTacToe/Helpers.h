#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>

//A place to put commonly used structures, data types, helper functions, or algorithms

struct Sprite
{
	SDL_Texture* image;
	std::string name;
	std::string address;

	int width;
	int height;
};

//2d coordinate
struct Vector2D
{
	Vector2D(int x, int y);
	int X;
	int Y;
};