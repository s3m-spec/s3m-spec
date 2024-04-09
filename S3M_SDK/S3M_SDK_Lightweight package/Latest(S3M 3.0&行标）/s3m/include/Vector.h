#if !defined(S3MBVECTOR_H__DE49880B_94AC_4D46_9EA5_BC28C4905284__INCLUDED_)
#define S3MBVECTOR_H__DE49880B_94AC_4D46_9EA5_BC28C4905284__INCLUDED_

#pragma once
#include "stdafx.h"
#include "Matrix.h"

namespace S3MB
{
	class Matrix4d;
	// ��ά����
	class S3MB_API Vector3d
	{
	public:
		Vector3d();

		Vector3d(double fx, double fy, double fz);

		// ���ص�ȡֵ�������ȡ����i���ķ���
		double operator [] (const unsigned i) const;

		// ���ص�ȡֵ�������ȡ����i���ķ���������
		double& operator [] (const unsigned i);

		// ���صļӷ������������������֮��
		Vector3d operator + (const Vector3d& vec) const;

		// ���صļ��������������������֮��
		Vector3d operator - (const Vector3d& vec) const;

		// ���صĳ˷�������������һ�����Ľ��
		Vector3d operator * (const double fScale) const;

		// ���صĳ���������������һ�����Ľ��
		Vector3d operator / (const double fScale) const;
		
		// �����������ĵ��
		double DotProduct(const Vector3d& vec) const;

		// �������ĳ���
		double Length() const;

		// �������ĳ��ȵ�ƽ��
		double Length2() const;

		// ȡ��������ÿ���������Сֵ�γ�һ���µ�����
		void MakeFloor(const Vector3d& cmp);

		// ȡ��������ÿ����������ֵ�γ�һ���µ�����
		void MakeCeil(const Vector3d& cmp);

		// �ó˷�֧��D3D��������
		// ��ϵͳ����ֱ��ʹ��
		Vector3d MultiplyMatrix(const Matrix4d& m) const;

		// ���ص�ȡ�����������������
		// ˵���� �������󷴾��Ƕ�ÿ��������
		Vector3d operator - () const;

		void Normalize();

		double x, y, z;
	};

	// ��ά����
	class S3MB_API Vector4d
	{
	public:
		Vector4d();

		Vector4d(const double fx, const double fy, const double fz, const double fw);

		// ���ص�ȡֵ�������ȡ����i���ķ���
		double operator [] (const unsigned i) const;

		// ���ص�ȡֵ�������ȡ����i���ķ���������
		double& operator [] (const unsigned i);

		double x, y, z, w;
	};
}

#endif