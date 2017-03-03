#pragma once

#include "general.h"

class Vector
{
public:
	GLfloat x, y, z;

	explicit Vector() : x(0), y(0), z(0) {}
	explicit Vector(float i) : x(i), y(i), z(i) {}
	explicit Vector(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

	inline Vector& operator=(Vector const& v) { x = v.x; y = v.y; z = v.z; return *this; }
	inline bool operator==(Vector const& v) { return (x == v.x && y == v.y && z == v.z); }
	inline bool operator!=(Vector const& v) { return (x != v.x || y != v.y || z != v.z); }
	/*! Warning slow operation */
	inline Vector operator+(float f) const { return Vector(x + f, y + f, z + f); }
	inline Vector operator+(Vector const& v) const { return Vector(x + v.x, y + v.y, z + v.z); }
	inline Vector operator-(void) const { return Vector(-x, -y, -z); }
	inline Vector operator-(float f) const { return Vector(x - f, y - f, z - f); }
	inline Vector operator-(Vector const& v) const { return Vector(x - v.x, y - v.y, z - v.z); }
	inline Vector operator*(float f) const { return Vector(x * f, y * f, z * f); }
	inline Vector operator*(Vector const& v) const { return Vector(x * v.x, y * v.y, z * v.z); }
	inline Vector operator/(float f) const { return Vector(x / f, y / f, z / f); }
	inline Vector operator/(Vector const& v) const { return Vector(x / v.x, y / v.y, z / v.z); }
	inline Vector& operator+=(float f) { x += f; y += f; z += f; return *this; }
	inline Vector& operator+=(Vector const& v) { x += v.x; y += v.y; z += v.z; return *this; }
	inline Vector& operator-=(float f) { x -= f; y -= f; z -= f; return *this; }
	inline Vector& operator-=(Vector const& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	inline Vector& operator*=(float f) { x *= f; y *= f; z *= f; return *this; }
	inline Vector& operator*=(Vector const& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
	inline Vector& operator/=(float f) { x /= f; y /= f; z /= f; return *this; }
	inline Vector& operator/=(Vector const& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
	inline void		Negate() { x = -x; y = -y; z = -z; return; }
	inline float	Lenght() const { return sqrt(x * x + y * y + z * z); }
	inline float	DistTo(Vector const& v) const { Vector Delta = *this - v; return Delta.Lenght(); }
	static inline float	DotProduct(Vector const& v1, Vector const& v2) { return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z); }
	static inline Vector	CrossProduct(Vector const& v1, Vector const& v2) { return Vector(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x); }
};