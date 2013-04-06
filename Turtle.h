#ifndef _TURTLE_H_
#define _TURTLE_H_

#include <stack>

class Turtle
{
private:
	Point3Df m_position;
	Vector3 m_heading;
	Vector3 m_left;

public:
	Turtle() : m_position(0,0,0), m_heading(0,1,0), m_left(1,0,0) {}
	void reset();
	void translate(float amount);
	void translate(float amount, const Vector3& direction);
	const Vector3& heading() const throw() { return m_heading; }
	const Vector3& left() const throw() { return m_left; }
	const Point3Df& position() const throw() { return m_position; }
};

#endif//_TURTLE_H_