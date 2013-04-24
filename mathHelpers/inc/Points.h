#ifndef _POINT_H_
#define _POINT_H_

struct Vector3;

template<class T>
class Point3D
{
private:
	T m_x;
	T m_y;
	T m_z;
public:
	Point3D(T x, T y, T z) throw() : m_x(x), m_y(y), m_z(z) {}
	Point3D(const Point3D& other) throw() { m_x = other.m_x; m_y = other.m_y; m_z = other.m_z; }
	Point3D(const Point3D& init, float amount, const Vector3& vector) throw() { m_x = init.m_x; m_y = init.m_y; m_z = init.m_z; this->translate(amount, vector); }
	T X() const throw() { return m_x; }
	T Y() const throw() { return m_y; }
	T Z() const throw() { return m_z; }
	void set(T x, T y, T z) throw() { m_x = x; m_y = y; m_z = z; }
	Point3D operator+= (const Vector3& vector) throw() { m_x += vector.x; m_y += vector.y; mz += vector.z; return *this; }
	void translate(float amount, const Vector3& vector) throw() { Vector3 normAlong = vector; normAlong.normalize(); m_x += amount*normAlong.x; m_y += amount*normAlong.y; m_z += amount*normAlong.z; }
};

typedef Point3D<float> Point3Df;

#endif//_POINT_H_