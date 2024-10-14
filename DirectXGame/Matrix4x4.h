#pragma once
#include <memory>

#include "Vector3D.h"

class Matrix4x4
{
public:
	Matrix4x4() = default;

	~Matrix4x4() = default;

	void setIdentity()
	{
		::memset(mat, 0, sizeof(float) * 16);
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void setTranslation(const Vector3D& translation)
	{
		setIdentity();
		mat[3][0] = translation.x;
		mat[3][1] = translation.y;
		mat[3][2] = translation.z;
	}

	void setScale(const Vector3D& translation)
	{
		setIdentity();
		mat[0][0] = translation.x;
		mat[1][1] = translation.y;
		mat[2][2] = translation.z;
	}

	void setRotationX(const float x)
	{
		setIdentity();
		mat[1][1] = cos(x);
		mat[1][2] = sin(x);
		mat[2][1] = -sin(x);
		mat[2][2] = cos(x);
	}

	void setRotationY(const float y)
	{
		setIdentity();
		mat[0][0] = cos(y);
		mat[0][2] = -sin(y);
		mat[2][0] = sin(y);
		mat[2][2] = cos(y);
	}

	void setRotationZ(const float z)
	{
		setIdentity();
		mat[0][0] = cos(z);
		mat[0][1] = sin(z);
		mat[1][0] = -sin(z);
		mat[1][1] = cos(z);
	}

	void setOrthographicProjection(const float width, const float height, const float nearPlane, const float farPlane)
	{
		setIdentity();
		mat[0][0] = 2.0f / width;
		mat[1][1] = 2.0f / height;
		mat[2][2] = 1.0f / (farPlane - nearPlane);
		mat[3][2] = -(nearPlane / (farPlane - nearPlane));
	}

	void setPerspectiveProjection(const float fov, const float aspect, const float zNear, const float zFar)
	{
		setIdentity();
		const float yScale = 1.0f / tan(fov / 2.0f);
		const float xScale = yScale / aspect;
		mat[0][0] = xScale;
		mat[1][1] = yScale;
		mat[2][2] = zFar / (zFar - zNear);
		mat[2][3] = 1.0f;
		mat[3][2] = (-zNear * zFar) / (zFar - zNear);
	}


	void setMatrix(const Matrix4x4& matrix)
	{
		::memcpy(mat, matrix.mat, sizeof(float) * 16);
	}

	void operator *=(const Matrix4x4& matrix)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j] + mat[i][3] * matrix.mat[3][j];
			}
		}
		setMatrix(out);
	}

	Matrix4x4 multiplyTo(const Matrix4x4& matrix) const
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				out.mat[i][j] =
					this->mat[i][0] * matrix.mat[0][j] + this->mat[i][1] * matrix.mat[1][j] +
					this->mat[i][2] * matrix.mat[2][j] + this->mat[i][3] * matrix.mat[3][j];
			}
		}

		return out;
	}

	Matrix4x4 operator*(const Matrix4x4& matrix) const
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j] + mat[i][3] * matrix.mat[3][j];
			}
		}
		return out;
	}

public:
	float mat[4][4] = {};
};
