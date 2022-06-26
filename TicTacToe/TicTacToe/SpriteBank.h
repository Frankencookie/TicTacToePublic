#pragma once
#include "Helpers.h"
#include "Window.h"
#include <list>

class SpriteBank
{
public:
	static SpriteBank& GetInstance();
protected:
	std::list<Sprite*> loadedSprites;
	SpriteBank();
	~SpriteBank();

public:
	Sprite* FindSpriteByAddress(std::string address);
	Sprite* FindSpriteByName(std::string name);

	Sprite* LoadSprite(std::string address, std::string name);

	static SpriteBank instance;
};

