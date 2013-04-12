#include "precomp.h"
#include "Camera.h"

Camera::Camera(const Vector3& position, const Vector3& center, const Vector3& up) throw()
{
	m_state.setColumn(3, Vector4(position.x, position.y, position.z, 1));
	//TODO msati3: derive x, y and z from center and up vectors using Euler angles
	Vector3 left = up.cross(center);
	left.normalize();
	const float x[] = {1, 0, 0, 0};
	const float y[] = {0, 1, 0, 0};
	const float z[] = {0, 0, 1, 0};
	m_state.setColumn(0, x);
	m_state.setColumn(1, y);
	m_state.setColumn(2, z);
}

void Camera::rotateX(float angle) throw()
{
	Matrix4 multX(1, 0, 0, 0,
				   0, cos(angle), -sin(angle), 0,
				   0, sin(angle), cos(angle), 0,
				   0, 0, 0, 1);
	m_state *= multX;
}

void Camera::rotateY(float angle) throw()
{
	Matrix4 multY(cos(angle), 0, sin(angle), 0,
				   0, 1, 0, 0,
				  -sin(angle), 0, cos(angle), 0,
				   0, 0, 0, 1);
	m_state *= multY;
}

void Camera::rotateZ(float angle) throw()
{
	Matrix4 multZ(cos(angle), -sin(angle), 0, 0,
				   sin(angle), cos(angle), 0, 0,
				   0, 0, 1, 0,
				   0, 0, 0, 1);
	m_state *= multZ;
}