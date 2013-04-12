#include "precomp.h"
#include "Turtle.h"

void Turtle::reset()
{
	m_position.set(0,0,0);
	m_orientation.set(0,1,0,1,0,0,0,0,0);
}

void Turtle::translate(float amount)
{
	m_position.translate(amount, heading());
}

void Turtle::translate(float amount, const Vector3& direction)
{
	m_position.translate(amount, direction);
}

void Turtle::changeHeading(float angle)
{
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	Matrix3 headingRot(cosAngle, sinAngle, 0, -sinAngle, cosAngle, 0, 0, 0, 1);
	Matrix3 finalMatrix = headingRot * m_orientation;
	m_orientation.set(finalMatrix.get());
}
