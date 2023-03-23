#include "maze.h"

/**
 * initSDL: initialize sdl
 *
 * Return: True on success, False on failure
 */

bool initSDL(void)
{
	window = NULL;
	renderer = NULL;

	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n",
		       SDL_GetError());
		success = false;
	}
	window = SDL_CreateWindow("milka",SDL_WINDOWPOS_UNDEFINED,
			          SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			  	  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("window  could not be created! SDL Error: %s\n",
                       SDL_GetError());
                success = false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n",
		       SDL_GetError());
		success = false;
	}

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
			       	    SDL_TEXTUREACCESS_STREAMING,
				    SCREEN_WIDTH, SCREEN_HEIGHT);

	if (texture == NULL)
	{
		printf("Texture  could not initialize! SDL_Error: %s\n",
                       SDL_GetError());
                success = false;
	}
	return (success);
}
/**
 * updateRenderer - updates renderer with updated buffer / texture
 * @textured: True if user enabled textures, otherwise False
 * Return: void
 */
void updateRenderer(bool textured)
{
	int x, y; /* loop counters */

	if (textured)
	{
		SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * 4);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
	
		for (x = 0; x < SCREEN_WIDTH; x++)
		{
			for (y = 0; y < SCREEN_HEIGHT; y++)
			{
				buffer[y][x] = 0;
			}
		}
	}

	SDL_RenderPresent(renderer);
}


/**
 * closeSDL - closes texture, renderer, and window
 * Return: void
 */
void closeSDL(void)
{
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
