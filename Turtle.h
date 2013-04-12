#ifndef _TURTLE_H_
#define _TURTLE_H_

#include <stack>

class Turtle
{
private:
	Matrix4 m_state;
	const Matrix3& getMatrixForState() const;

public:
	Turtle() : m_state(1,0,0,0,
					   0,1,0,0,
					   0,0,1,0,
					   0,0,0,1) {}

	void reset();
	void translate(float amount);
	void translate(float amount, const Vector3& direction);
	const Vector3 left() const throw() { const float* data = m_state.get(); return Vector3(data[0], data[4], data[8]); }
	const Vector3 up() const throw() { const float* data = m_state.get(); return Vector3(data[1], data[5], data[9]); }
	const Vector3 heading() const throw() { const float* data = m_state.get(); return Vector3(data[2], data[6], data[10]); }
	const Point3Df position() const throw() { const float* data = m_state.get(); return Point3Df(data[3], data[7], data[11]); }
	void changeHeading(float angle);
	void changePitch(float angle);
	void changeRoll(float angle);
};

#endif//_TURTLE_H_