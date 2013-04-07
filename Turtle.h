#ifndef _TURTLE_H_
#define _TURTLE_H_

#include <stack>

class Turtle
{
private:
	Point3Df m_position;
	Matrix3 m_orientation;
	const Matrix3& getMatrixForState() const;

public:
	Turtle() : m_position(0,0,0), m_orientation(0,1,0,1,0,0,0,0,0) {}
	void reset();
	void translate(float amount);
	void translate(float amount, const Vector3& direction);
	const Vector3 heading() const throw() { const float* data = m_orientation.get(); return Vector3(data[0], data[3], data[6]); }
	const Vector3 left() const throw() { const float* data = m_orientation.get(); return Vector3(data[1], data[4], data[7]); }
	const Point3Df& position() const throw() { return m_position; }
	void changeHeading(float angle);
};

#endif//_TURTLE_H_