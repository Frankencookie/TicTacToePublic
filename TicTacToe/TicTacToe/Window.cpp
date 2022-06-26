#include "Window.h"
#include "SpriteBank.h"

Window* Window::instance;

Window::Window()
{
	instance = this;
	InitWindow();
}

Window::~Window()
{
	SDL_DestroyRenderer(renderer_ptr);
	SDL_DestroyWindow(window_ptr);
	SDL_Quit();
}

void Window::InitWindow()
{
	//Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL setup failed, SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create Window
		window_ptr = SDL_CreateWindow("Tic Tac Toe", 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
		if (window_ptr == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Assign surface
			surface_ptr = SDL_GetWindowSurface(window_ptr);
		}

		//Create Renderer
		renderer_ptr = SDL_CreateRenderer(window_ptr, -1, SDL_RENDERER_PRESENTVSYNC);

		//Load Background
		SpriteBank::GetInstance().LoadSprite("Assets/background.png", "background");

		//Set background clear colour
		SDL_SetRenderDrawColor(renderer_ptr, 255, 0, 0, 255);

		DrawBackground();

		PresentRender();

		third = windowHeight / 3;
	}
}

SDL_Renderer* Window::GetRenderer()
{
	return renderer_ptr;
}

SDL_Window* Window::GetWindow()
{
	return window_ptr;
}

void Window::DrawSprite(Sprite* sprite, Vector2D location)
{
	//Set up render rect
	SDL_Rect screenLocation;
	screenLocation.x = location.X;
	screenLocation.y = location.Y;
	screenLocation.h = sprite->height;
	screenLocation.w = sprite->width;

	SDL_RenderCopy(renderer_ptr, sprite->image, NULL, &screenLocation);
}

void Window::DrawSprite(std::string name, Vector2D location)
{
	DrawSprite(SpriteBank::GetInstance().FindSpriteByName(name), location);
}

void Window::DrawBackground()
{
	DrawSprite(SpriteBank::GetInstance().FindSpriteByName("background"), Vector2D(0, 0));
}

void Window::ClearScreen()
{
	SDL_RenderClear(renderer_ptr);
}

void Window::PresentRender()
{
	SDL_RenderPresent(renderer_ptr);
}

int Window::GetWindowWidth()
{
	return windowWidth;
}

int Window::GetWindowHeight()
{
	return windowHeight;
}

int Window::GetScreenThird()
{
	return third;
}
