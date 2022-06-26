#include "SpriteBank.h"

SpriteBank SpriteBank::instance;

SpriteBank& SpriteBank::GetInstance()
{
    return instance;
}

SpriteBank::SpriteBank()
{
    int flag = IMG_INIT_PNG;
    int initted = IMG_Init(flag);
    if ((initted & flag) != flag)
    {
        printf("PNG Failed. \n");
        printf("IMG_Init: %s\n", IMG_GetError());
        return;
    }

    printf("Images Initted successfully \n");
}

SpriteBank::~SpriteBank()
{
    for (Sprite* i : loadedSprites)
    {
        SDL_DestroyTexture(i->image);
        i->image = nullptr;
    }
    loadedSprites.clear();

    printf("Quitting Images \n");
    IMG_Quit();
}

Sprite* SpriteBank::FindSpriteByAddress(std::string address)
{
    Sprite* returnSprite = nullptr;
    for (Sprite* sprite : loadedSprites)
    {
        if (sprite->address == address)
        {
            returnSprite = sprite;
            break;
        }
    }

    return returnSprite;
}

Sprite* SpriteBank::FindSpriteByName(std::string name)
{
    Sprite* returnSprite = nullptr;
    for (Sprite* sprite : loadedSprites)
    {
        if (sprite->name == name)
        {
            returnSprite = sprite;
            break;
        }
    }

    return returnSprite;
}

Sprite* SpriteBank::LoadSprite(std::string address, std::string name)
{
    //See if sprite is already loaded
    Sprite* returnSprite = FindSpriteByAddress(address);

    //If sprite already exists, return it
    if (returnSprite != nullptr)
    {
        return returnSprite;
    }

    //Load sprite
    SDL_Surface* tempSurf = IMG_Load(address.c_str());
    if (!tempSurf)
    {
        printf("%s\n", SDL_GetError());
        return nullptr;
    }

    Sprite* newSprite = new Sprite;
    newSprite->address = address;
    newSprite->name = name;
    newSprite->width = tempSurf->w;
    newSprite->height = tempSurf->h;

    newSprite->image = SDL_CreateTextureFromSurface(Window::instance->GetRenderer(), tempSurf);
    SDL_FreeSurface(tempSurf);

    printf("Sprite loaded successfully. \n");

    //Add to list
    loadedSprites.push_back(newSprite);

    return newSprite;
}