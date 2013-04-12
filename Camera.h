#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Vectors.h"
#include "Matrices.h"

class Camera
{
private:
	Matrix4 m_state;

public:
	Camera(const Vector3& eye, const Vector3& center, const Vector3& up) throw();
	void rotateX(float angle) throw();
	void rotateY(float angle) throw();
	void rotateZ(float angle) throw();
	const Matrix4& getState() const throw() { return m_state; }
	const float* getMultMatrix() const throw() {return m_state.getTranspose(); }
};


#endif//_CAMERA_H_