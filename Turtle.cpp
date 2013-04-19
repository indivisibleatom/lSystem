#include "precomp.h"
#include "Turtle.h"

void Turtle::reset()
{
	m_state.set(1,0,0,0,
			    0,1,0,0,
			    0,0,1,0,
			    0,0,0,1);
}

void Turtle::translate(float amount) throw()
{
	translate(amount, heading());
}

void Turtle::translate(float amount, const Vector3& direction) throw()
{
	Vector3 directionNormal = direction;
	directionNormal.normalize();
	Vector3 componentWiseTranslation(amount * directionNormal.dot(left()), amount * directionNormal.dot(up()), amount * directionNormal.dot(heading()));

	Matrix4 translationMat(1,0,0,componentWiseTranslation.x,
						   0,1,0,componentWiseTranslation.y,
						   0,0,1,componentWiseTranslation.z,
						   0,0,0,1);
	m_state *= translationMat;
}

void Turtle::changeHeading(float angle) throw()
{
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	Matrix4 headingRot(cosAngle, 0, sinAngle, 0,
				       0, 1, 0, 0,
				      -sinAngle, 0, cosAngle, 0,
				       0, 0, 0, 1);
	m_state *= headingRot;
}

void Turtle::changePitch(float angle) throw()
{
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	Matrix4 pitchRot(1, 0, 0, 0,
				     0, cosAngle, -sinAngle, 0,
				     0, sinAngle, cosAngle, 0,
				     0, 0, 0, 1);
	m_state *= pitchRot;
}

void Turtle::changeRoll(float angle) throw()
{
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	Matrix4 rollRot(cosAngle, -sinAngle, 0, 0,
				    sinAngle, cosAngle, 0, 0,
				    0, 0, 1, 0,
				    0, 0, 0, 1);
	m_state *= rollRot;
}