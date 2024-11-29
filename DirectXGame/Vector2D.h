#pragma once
#include <cmath>
#include <ostream>
#include <windef.h>

namespace mrlol
{
	class Vector2D
	{
	public:
		Vector2D() : x(0), y(0) {}
		Vector2D(const float n) : x(n), y(n) {}
		Vector2D(const float x, const float y) : x(x), y(y) {}
		Vector2D(const Vector2D& vector) : x(vector.x), y(vector.y) {}
		Vector2D(const POINT& point) : x(static_cast<float>(point.x)), y(static_cast<float>(point.y)) {}
		~Vector2D() = default;

		float magnitude() const
		{
			return sqrt((x * x + y * y));
		}

		Vector2D normalize() const
		{
			const float mag = this->magnitude();
			return *this / mag;
			// return this->scaleVector2D((1 / this->magnitude()));
		}

		static Vector2D linearInterpolate(const Vector2D& start, const Vector2D& end, const float delta)
		{
			Vector2D v;
			v.x = start.x * (1.0f - delta) + end.x * (delta);
			v.y = start.y * (1.0f - delta) + end.y * (delta);
			return v;
		}

		// Vector2D& operator=(const POINT& point)
		// {
		// 	this->x = static_cast<float>(point.x);
		// 	this->y = static_cast<float>(point.y);
		//
		// 	return *this;
		// }

		bool operator==(const Vector2D& vector) const
		{
			return this->x == vector.x && this->y == vector.y;
		}

		bool operator!=(const Vector2D& vector) const
		{
			return this->x != vector.x || this->y != vector.y;
		}

		Vector2D operator+(const Vector2D& addend) const
		{
			return { this->x + addend.x, this->y + addend.y };
		}

		// Vector2D operator+(const POINT& subtrahend) const
		// {
		// 	return { this->x + static_cast<float>(subtrahend.x), this->y + static_cast<float>(subtrahend.y) };
		// }

		Vector2D operator-(const Vector2D& subtrahend) const
		{
			return { this->x - subtrahend.x, this->y - subtrahend.y };
		}

		// Vector2D operator-(const POINT& subtrahend) const
		// {
		// 	return { this->x - static_cast<float>(subtrahend.x), this->y - static_cast<float>(subtrahend.y) };
		// }

		// Vector2D operator*(const Vector2D& crossMultiplier) const
		// 	// cross product w/ Vector2D
		// {
		// 	return {
		// 		(this->y * crossMultiplier.z) - (this->z * crossMultiplier.y),
		// 		(this->z * crossMultiplier.x) - (this->x * crossMultiplier.z),
		// 		(this->x * crossMultiplier.y) - (this->y * crossMultiplier.x) };
		// }

		// Vector2D operator*(const Matrix& m) // cross product w/ matrix
		// {
		// 	float mult[4] = { this->x, this->y, this->z, 1 };
		// 	float result[4] = { 0, 0, 0, 1 };
		//
		// 	if (m.getSize().at(1) != 4)
		// 		return Vector2D();
		//
		// 	for (size_t i = 0; i < (size_t)m.getSize().at(0); i++)
		// 	{
		// 		for (size_t j = 0; j < 4; j++)
		// 		{
		// 			result[i] += (m.getData(i, j) * mult[j]);
		// 			// std::cout << result[i] << " += " << m.getData(i, j) << " * " << mult[j];
		// 			// std::cout << ", ";
		// 		}
		// 		// std::cout << "\n";
		// 	}
		//
		// 	return Vector2D(result[0], result[1], result[2]);
		// }

		Vector2D operator*(const float scalar) const
			// scalar multiplication
		{
			return { this->x * scalar, this->y * scalar };
		}

		Vector2D operator/(const float denominator) const
			// scalar division
		{
			return { this->x / denominator, this->y / denominator };
		}

		Vector2D& operator+=(const Vector2D& addend)
		{
			this->x += addend.x;
			this->y += addend.y;
			return *this;
		}

		Vector2D& operator-=(const Vector2D& subtrahend)
		{
			this->x -= subtrahend.x;
			this->y -= subtrahend.y;
			return *this;
		}

		//Vector2D& operator*=(const Vector2D& multiplier)
		//{
		//	this->x *= multiplier.x;
		//	this->y *= multiplier.y;
		//	this->z *= multiplier.z;
		//	return *this;
		//}

		//Vector2D& operator/=(const Vector2D& divisor)
		//{
		//	this->x /= divisor.x;
		//	this->y /= divisor.y;
		//	this->z /= divisor.z;
		//	return *this;
		//}

		friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec)
		{
			os << "(" << vec.x << ", " << vec.y << ")";
			return os;
		}
	public:
		float x, y;
	};
}

