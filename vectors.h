#pragma once

//Vector2
class Vector2
{
public:
	float x, y;
	Vector2()
	{
		x = y = 0.f;
	}

	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

//Vector3
class Vector3
{
public:
	float x, y, z;
	Vector3()
	{
		x = y = z = 0.f;
	}

	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3 operator+(const Vector3& v) {
		return Vector3{ x + v.x, y + v.y, z + v.z };
	}

	Vector3 operator-(const Vector3& v) {
		return Vector3{ x - v.x, y - v.y, z - v.z };
	}

	Vector3 operator*(const float v) {
		return Vector3{ x * v, y * v, z * v };
	}

	Vector3 operator/(const float fl) const {
		return Vector3(x / fl, y / fl, z / fl);
	}
};

//Vector4
class Vector4
{
public:
	float x, y, z, w;
	Vector4()
	{
		x = y = z = w = 0.f;
	}

	Vector4(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
};