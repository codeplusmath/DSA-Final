#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Morse.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define FPS 25
#define DELAY_TIME 1000.0f/FPS

/* Graphical interface of the Software */
int Graphic_Interface(Tree tree);

/* Initialization of SDL2, IMG and TTF */
int SDLnIMGnTTF_Initialize();

/* Checking Region */
bool isInRegion(int x, int y, int xInf, int xSup, int yInf, int ySup);

/* Load texture */
SDL_Texture * Load_Texture(const char * file, SDL_Renderer * renderer);

/* Copy the text to the rendering */
SDL_Texture * Render_Text(const char * text, const char * fontName, SDL_Color color, int fontSize, SDL_Renderer * renderer);

/* Copy the texture clipped to the rendering */
void Render_Texture_Clip(SDL_Texture * texture, SDL_Renderer *renderer, SDL_Rect dest,SDL_Rect *clip);

/* Copy the texture to the rendering */
void Render_Texture(SDL_Texture * texture, SDL_Renderer * renderer, int x, int y, SDL_Rect * clip);

/* Clean all */
void Clean_Up(SDL_Window * window, SDL_Renderer * renderer);

#endif // GRAPHIC_H_INCLUDED
