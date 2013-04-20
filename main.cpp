#include "precomp.h"
#include <iostream>
#include <GL\glew.h>
#include <SDL\SDL.h>
#include "LSystem.h"
#include "LSystemController.h"
#include "Renderer.h"

int main(int argc, char *argv[])
{
	Renderer renderer(800,600,32);
	renderer.init();

	std::unique_ptr<LSystem> pSystem = LSystemBuilder::buildLSystem("C:\\Development\\openSource\\lSystem\\lSystem\\lSystemDescription.txt");
	LSystemController systemController(std::move(pSystem), renderer);
	
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
	while (true)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type)
			{
				case SDL_QUIT: return false;
					break;
				case SDL_KEYDOWN: SDL_keysym keysym = event.key.keysym;
					if (keysym.sym == 'a')
					{
						renderer.getCamera().rotateX(PI/180);
					}
					else if (keysym.sym == 's')
					{
						renderer.getCamera().rotateY(PI/180);
					}
					else if (keysym.sym == 'q')
					{
						renderer.getCamera().rotateZ(PI/180);
					}
					else if (keysym.sym == 'z')
					{
						renderer.getCamera().zoom(2);
					}
					else if (keysym.sym == 'x')
					{
						renderer.getCamera().zoom(-2);
					}
					break;
			}
		}
		systemController.onUpdate();
		renderer.draw();
		renderer.flip();
	}
	return 0;
}