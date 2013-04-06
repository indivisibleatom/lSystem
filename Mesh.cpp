#include "precomp.h"
#include "Mesh.h"
#include "GL\glew.h"

void Mesh::draw() const
{
	glBegin(GL_TRIANGLES);
	
	for (std::vector<Vertex<float>>::const_iterator vertex = m_vertices.cbegin(); vertex != m_vertices.cend(); vertex++)
	{
		glVertex3f(vertex->point().X(), vertex->point().Y(), vertex->point().Z());
	}

	glEnd();
}

int Mesh::addVertex(Vertex<float> vertex)
{
	m_vertices.push_back(vertex);
	return m_vertices.size();
}

int Mesh::addTriangle(int c1, int c2, int c3)
{
	m_corners.push_back(c1);
	m_corners.push_back(c2);
	m_corners.push_back(c3);
	return m_corners.size()/3;
}