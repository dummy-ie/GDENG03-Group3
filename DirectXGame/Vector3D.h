#pragma once
#include <cmath>
#include <ostream>
#include <string>
#include <reactphysics3d/mathematics/Vector3.h>

namespace gdeng03
{
	class Vector3D
	{
	public:
		Vector3D() : x(0), y(0), z(0) {}
		Vector3D(const float n) : x(n), y(n), z(n) {}
		Vector3D(const float x, const float y) : x(x), y(y), z(0) {}
		Vector3D(const float x, const float y, const float z) : x(x), y(y), z(z) {}
		// Vector3D(const int x, const int y, const int z) : x(x), y(y), z(z) {}
		Vector3D(const Vector3D& vector) : x(vector.x), y(vector.y), z(vector.z) {}
		Vector3D(const reactphysics3d::Vector3& vector) : x(vector.x), y(vector.y), z(vector.z) {}
		~Vector3D() = default;

		std::string toString() const
		{
			return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
		}

		float magnitude() const
		{
			return sqrt((x * x + y * y + z * z));
		}

		Vector3D normalize() const
		{
			const float mag = this->magnitude();
			return *this / mag;
			// return this->scaleVector3D((1 / this->magnitude()));
		}

		static Vector3D linearInterpolate(const Vector3D& start, const Vector3D& end, const float delta)
		{
			Vector3D v;
			v.x = start.x * (1.0f - delta) + end.x * (delta);
			v.y = start.y * (1.0f - delta) + end.y * (delta);
			v.z = start.z * (1.0f - delta) + end.z * (delta);
			return v;
		}

		static Vector3D absolute(const Vector3D& vector)
		{
			return { abs(vector.x), abs(vector.y), abs(vector.z) };
		}

		Vector3D operator+(const Vector3D& addend) const
		{
			return { this->x + addend.x, this->y + addend.y, this->z + addend.z };
		}

		Vector3D operator-(const Vector3D& subtrahend) const
		{
			return { this->x - subtrahend.x, this->y - subtrahend.y, this->z - subtrahend.z };
		}

		Vector3D operator*(const Vector3D& crossMultiplier) const
			// cross product w/ vector3D
		{
			return {
				(this->y * crossMultiplier.z) - (this->z * crossMultiplier.y),
				(this->z * crossMultiplier.x) - (this->x * crossMultiplier.z),
				(this->x * crossMultiplier.y) - (this->y * crossMultiplier.x) };
		}


		Vector3D operator*(const float scalar) const
			// scalar multiplication
		{
			return { this->x * scalar, this->y * scalar, this->z * scalar };
		}

		Vector3D operator/(const float denominator) const
			// scalar division
		{
			return { this->x / denominator, this->y / denominator, this->z / denominator };
		}

		Vector3D& operator+=(const Vector3D& addend)
		{
			this->x += addend.x;
			this->y += addend.y;
			this->z += addend.z;
			return *this;
		}

		Vector3D& operator-=(const Vector3D& subtrahend)
		{
			this->x -= subtrahend.x;
			this->y -= subtrahend.y;
			this->z -= subtrahend.z;
			return *this;
		}

		bool operator==(const Vector3D& vector) const
		{
			return
				fabs(this->x - vector.x) > DBL_EPSILON &&
				fabs(this->y - vector.y) > DBL_EPSILON &&
				fabs(this->z - vector.z) > DBL_EPSILON;
		}

		bool operator!=(const Vector3D& vector) const
		{
			return !(*this == vector);
		}

		Vector3D operator/(const Vector3D& divisor) const
		{
			return {
				divisor.x != 0 ? this->x / divisor.x : 0,
				divisor.y != 0 ? this->y / divisor.y : 0,
				divisor.z != 0 ? this->z / divisor.z : 0
			};
		}

		//Vector3D& operator*=(const Vector3D& multiplier)
		//{
		//	this->x *= multiplier.x;
		//	this->y *= multiplier.y;
		//	this->z *= multiplier.z;
		//	return *this;
		//}

		//Vector3D& operator/=(const Vector3D& divisor)
		//{
		//	this->x /= divisor.x;
		//	this->y /= divisor.y;
		//	this->z /= divisor.z;
		//	return *this;
		//}

		//friend void swap(Vector3D& first, Vector3D& second) noexcept
		//{
		//	// enable ADL (not necessary in our case, but good practice)
		//	using std::swap;

		//	// by swapping the members of two objects,
		//	// the two objects are effectively swapped
		//	swap(first.x, second.x);
		//	swap(first.y, second.y);
		//	swap(first.z, second.z);
		//}

		friend std::ostream& operator<<(std::ostream& os, const Vector3D& vec)
		{
			os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
			return os;
		}
	public:
		float x, y, z;

		static const Vector3D zero;
	};
}
