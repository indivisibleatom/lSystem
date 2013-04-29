#include "precomp.h"
#include <GL\glew.h>
#include <SDL\SDL.h>
#include "Renderer.h"
#include "Drawable.h"

Renderer::Renderer(int screenX, int screenY, int bpp) : m_screenSize(screenX, screenY), m_bpp(bpp), m_camera(Vector3(0,10,-100), Vector3(0,0,0), Vector3(0,1,0))
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);
}

bool Renderer::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		m_pScreen = SDL_SetVideoMode(std::get<0>(m_screenSize), std::get<1>(m_screenSize), m_bpp, SDL_HWSURFACE | SDL_OPENGL);	
		return true;
	}
	return false;
}

void Renderer::flip()
{
	SDL_GL_SwapBuffers();
}

bool Renderer::draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 800/600, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixf(m_camera.getMultMatrix());

	//DEBUG
	/*glColor3f(1,0,0);
	glBegin(GL_QUADS);
		glVertex3f(0,0,0);
		glVertex3f(50,0,0);
		glVertex3f(50,50,0);
		glVertex3f(0,50,0);
	glEnd();*/

	for (std::list<std::unique_ptr<IDrawable>>::const_iterator drawable = m_drawableList.cbegin(); drawable != m_drawableList.cend(); drawable++)
	{
		(*drawable)->draw();
	}

	return true;
}

void Renderer::addDrawable(std::unique_ptr<IDrawable> m_pDrawable)
{
	m_drawableList.push_back(std::move(m_pDrawable));
}

/*void Renderer::applyTransFormation(const Matrix4& matrix)
{
	glMultMatrixf(matrix.getTranspose());	
}*/