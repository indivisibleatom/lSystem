#include "precomp.h"
#include "Turtle.h"

void Turtle::reset()
{
	m_position.set(0,0,0);
	m_left.set(1,0,0);
	m_heading.set(0,1,0);
}

void Turtle::translate(float amount)
{
	m_position.translate(amount, m_heading);
}

void Turtle::translate(float amount, const Vector3& direction)
{
	m_position.translate(amount, direction);
}
