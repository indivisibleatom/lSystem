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

	systemController.onUpdate();

	while (true)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type)
			{
				case SDL_QUIT: return false;
					break;
			}
		}
		systemController.onUpdate();
		renderer.draw();
		renderer.flip();
	}
	return 0;
}