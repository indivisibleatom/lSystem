#include "precomp.h"
#include "Skybox.h"
#include "GL\glew.h"
#include "GL\glut.h"

Skybox::Skybox()
{
}

void Skybox::draw() const
{
	glutSolidSphere(100, 20, 20);
}