#include "precomp.h"
#include "Turtle.h"

void Turtle::reset()
{
	m_orientation.set(1,0,0,0,
			          0,1,0,0,
			          0,0,1,0,
			          0,0,0,1);
	m_position.set(50,0,50);
}

void Turtle::translate(float amount) throw()
{
	translate(amount, heading());
}

void Turtle::translate(float amount, const Vector3& direction) throw()
{
	Vector3 directionNormal = direction;
	directionNormal.normalize();
	Vector3 componentWiseTranslation(amount * directionNormal.dot(left()), amount * directionNormal.dot(heading()), amount * directionNormal.dot(up()));

	m_position += m_orientation * componentWiseTranslation;
}

void Turtle::changeHeading(float angle) throw()
{
	angle = PI*angle/180;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	Matrix4 headingRot(cosAngle, -sinAngle, 0, 0,
				    sinAngle, cosAngle, 0, 0,
				    0, 0, 1, 0,
				    0, 0, 0, 1);
	m_orientation = headingRot * m_orientation;
}

void Turtle::changePitch(float angle) throw()
{
	angle = PI*angle/180;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	Matrix4 pitchRot(1, 0, 0, 0,
				     0, cosAngle, -sinAngle, 0,
				     0, sinAngle, cosAngle, 0,
				     0, 0, 0, 1);
	m_orientation = pitchRot * m_orientation;
}

void Turtle::changeRoll(float angle) throw()
{
	angle = PI*angle/180;
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	Matrix4 rollRot(cosAngle, 0, sinAngle, 0,
				       0, 1, 0, 0,
				      -sinAngle, 0, cosAngle, 0,
				       0, 0, 0, 1);
	m_orientation = rollRot * m_orientation;
}