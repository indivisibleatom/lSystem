#include "precomp.h"
#include <GL\glew.h>
#include <SDL\SDL.h>
#include "Renderer.h"
#include "Drawable.h"

Renderer::Renderer(int screenX, int screenY, int bpp) : m_screenSize(screenX, screenY), m_bpp(bpp)
{
}

bool Renderer::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		SDL_SetVideoMode(std::get<0>(m_screenSize), std::get<1>(m_screenSize), m_bpp, SDL_HWSURFACE | SDL_OPENGL);	
		return true;
	}
	return false;
}

/*bool Renderer::draw(const IDrawable& drawable)
{
	
}
*/
/*void Renderer::applyTransFormation(const Matrix4& matrix)
{
	glMultMatrixf(matrix.getTranspose());	
}*/