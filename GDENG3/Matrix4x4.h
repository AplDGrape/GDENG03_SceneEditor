#pragma once
#include <memory>
#include "Vector3D.h"
#include "Vector4D.h"
#include <cmath>

class Matrix4x4
{
public:
	Matrix4x4()
	{

	}

	void setIdentity()
	{
		::memset(m_mat, 0, sizeof(float) * 16);
		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}
	void setTranslation(const Vector3D& translation)
	{
		//setIdentity();
		m_mat[3][0] = translation.m_x;
		m_mat[3][1] = translation.m_y;
		m_mat[3][2] = translation.m_z;
	}
	void setScale(const Vector3D& scale)
	{
		//setIdentity();
		m_mat[0][0] = scale.m_x;
		m_mat[1][1] = scale.m_y;
		m_mat[2][2] = scale.m_z;
	}

	void setRotationX(float x)
	{
		//setIdentity();
		m_mat[1][1] = cos(x);
		m_mat[1][2] = sin(x);
		m_mat[2][1] = -sin(x);
		m_mat[2][2] = cos(x);
	}
	void setRotationY(float y)
	{
		//setIdentity();
		m_mat[0][0] = cos(y);
		m_mat[0][2] = -sin(y);
		m_mat[2][0] = sin(y);
		m_mat[2][2] = cos(y);
	}
	void setRotationZ(float z)
	{
		//setIdentity();
		m_mat[0][0] = cos(z);
		m_mat[0][1] = sin(z);
		m_mat[1][0] = -sin(z);
		m_mat[1][1] = cos(z);
	}
	float getDeterminant()
	{
		Vector4D minor, v1, v2, v3;
		float det;

		v1 = Vector4D(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
		v2 = Vector4D(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
		v3 = Vector4D(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);


		minor.cross(v1, v2, v3);
		det = -(this->m_mat[0][3] * minor.m_x + this->m_mat[1][3] * minor.m_y + this->m_mat[2][3] * minor.m_z +
			this->m_mat[3][3] * minor.m_w);
		return det;
	}
	void getInverse()
	{
		int a, i, j;
		Matrix4x4 out;
		Vector4D v, vec[3];
		float det = 0.0f;

		det = this->getDeterminant();
		if (!det) return;
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (j != i)
				{
					a = j;
					if (j > i) a = a - 1;
					vec[a].m_x = (this->m_mat[j][0]);
					vec[a].m_y = (this->m_mat[j][1]);
					vec[a].m_z = (this->m_mat[j][2]);
					vec[a].m_w = (this->m_mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_mat[0][i] = pow(-1.0f, i) * v.m_x / det;
			out.m_mat[1][i] = pow(-1.0f, i) * v.m_y / det;
			out.m_mat[2][i] = pow(-1.0f, i) * v.m_z / det;
			out.m_mat[3][i] = pow(-1.0f, i) * v.m_w / det;
		}

		this->setMatrix(out);
	}

	/*Matrix4x4 multiplyTo(const Matrix4x4& other) const
	{
		Matrix4x4 result;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result.m_mat[i][j] =
					m_mat[i][0] * other.m_mat[0][j] +
					m_mat[i][1] * other.m_mat[1][j] +
					m_mat[i][2] * other.m_mat[2][j] +
					m_mat[i][3] * other.m_mat[3][j];
			}
		}
		return result;
	}*/
	Matrix4x4 multiplyTo(Matrix4x4 in)
	{
		Matrix4x4 result;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				result.m_mat[i][j] =
					m_mat[i][0] * in.m_mat[0][j] + m_mat[i][1] * in.m_mat[1][j] +
					m_mat[i][2] * in.m_mat[2][j] + m_mat[i][3] * in.m_mat[3][j];
			}
		}

		return result;
	}

	void operator*=(const Matrix4x4& matrix)
	{
		Matrix4x4 out;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				out.m_mat[i][j] =
					m_mat[i][0] * matrix.m_mat[0][j] + m_mat[i][1] * matrix.m_mat[1][j] +
					m_mat[i][2] * matrix.m_mat[2][j] + m_mat[i][3] * matrix.m_mat[3][j];
			}
		}
		setMatrix(out);
	}

	void setMatrix(const Matrix4x4& matrix)
	{
		::memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
	}
	void setMatrix(float matrix[4][4])
	{
		::memcpy(m_mat, matrix, sizeof(float) * 16);
	}

	Vector3D getXDirection()
	{
		return Vector3D(m_mat[0][0], m_mat[0][1], m_mat[0][2]);
	}
	Vector3D getZDirection()
	{
		return Vector3D(m_mat[2][0], m_mat[2][1], m_mat[2][2]);
	}
	Vector3D getTranslation()
	{
		return Vector3D(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
	}

	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
		setIdentity();
		float yscale = 1.0f / tan(fov / 2.0f);
		float xscale = yscale / aspect;
		m_mat[0][0] = xscale;
		m_mat[1][1] = yscale;
		m_mat[2][2] = zfar / (zfar - znear);
		m_mat[2][3] = 1.0f;
		m_mat[3][2] = (-znear * zfar) / (zfar - znear);
	}
	void setOrthoLH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();
		m_mat[0][0] = 2.0f / width;
		m_mat[1][1] = 2.0f / height;
		m_mat[2][2] = 1.0f / (far_plane - near_plane);
		m_mat[3][2] = -(near_plane / (far_plane - near_plane));
	}

	Matrix4x4 getScalar(int constant)
	{
		Matrix4x4 Scalar;
		Scalar.setIdentity();
		Scalar.m_mat[0][0] *= constant;
		Scalar.m_mat[1][1] *= constant;
		Scalar.m_mat[2][2] *= constant;
		Scalar.m_mat[3][3] *= constant;

		return Scalar;
	}

	/*void setLookAtLH(const Vector3D& eye, const Vector3D& target, const Vector3D& up)
	{
		Vector3D zaxis = (target - eye).normalize();             // Forward
		Vector3D xaxis = up.cross(zaxis).normalize();            // Right
		Vector3D yaxis = zaxis.cross(xaxis);                     // Up (recomputed to ensure orthogonality)

		m_mat[0][0] = xaxis.m_x; m_mat[0][1] = yaxis.m_x; m_mat[0][2] = zaxis.m_x; m_mat[0][3] = 0.0f;
		m_mat[1][0] = xaxis.m_y; m_mat[1][1] = yaxis.m_y; m_mat[1][2] = zaxis.m_y; m_mat[1][3] = 0.0f;
		m_mat[2][0] = xaxis.m_z; m_mat[2][1] = yaxis.m_z; m_mat[2][2] = zaxis.m_z; m_mat[2][3] = 0.0f;

		m_mat[3][0] = -xaxis.dot(eye);
		m_mat[3][1] = -yaxis.dot(eye);
		m_mat[3][2] = -zaxis.dot(eye);
		m_mat[3][3] = 1.0f;
	}*/
	static Matrix4x4 lookAt(Vector3D eye, Vector3D center, Vector3D up)
	{
		Matrix4x4 view;
		view.setIdentity();
		Vector3D X, Y, Z;

		Vector3D forward = eye - center;
		forward = Vector3D::normalize(forward);

		Vector3D left = Vector3D::cross(up, forward);
		left = Vector3D::normalize(left);

		Vector3D upDirection = Vector3D::cross(forward, left);


		view.m_mat[0][0] = left.m_x;
		view.m_mat[1][0] = upDirection.m_x;
		view.m_mat[2][0] = forward.m_x;
		view.m_mat[3][0] = 0.0f;
		view.m_mat[0][1] = left.m_y;
		view.m_mat[1][1] = upDirection.m_y;
		view.m_mat[2][1] = forward.m_y;
		view.m_mat[3][1] = 0.0f;
		view.m_mat[0][2] = left.m_z;
		view.m_mat[1][2] = upDirection.m_z;
		view.m_mat[2][2] = forward.m_z;
		view.m_mat[3][2] = 0.0f;
		view.m_mat[0][3] = -left.m_x * eye.m_x - left.m_y * eye.m_y - left.m_z * eye.m_z;
		view.m_mat[1][3] = -up.m_x * eye.m_x - up.m_y * eye.m_y - up.m_z * eye.m_z;
		view.m_mat[2][3] = -forward.m_x * eye.m_x - forward.m_y * eye.m_y - forward.m_z * eye.m_z;
		view.m_mat[3][3] = 1.0f;

		return view;
	}

	~Matrix4x4()
	{

	}
public:
	float m_mat[4][4] = {};
};