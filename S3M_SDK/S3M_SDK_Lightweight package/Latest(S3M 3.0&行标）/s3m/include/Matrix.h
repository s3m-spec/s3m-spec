#if !defined(S3MBMATRIX_H__2D0D4C17_EA53_489F_80E2_EFF9D6F6A23C__INCLUDED_)
#define S3MBMATRIX_H__2D0D4C17_EA53_489F_80E2_EFF9D6F6A23C__INCLUDED_

#pragma once
#include "stdafx.h"
#include "S3MBCommon.h"

namespace S3MB
{
	class Vector3d;
	class S3MB_API Matrix3d
	{
	public:
		Matrix3d();

		// ��ֵ���������׾���
		Matrix3d(
			double m00, double m01, double m02,
			double m10, double m11, double m12,
			double m20, double m21, double m22);

		// 3X3�����
		// ����Ԫ��Ϊ��
		static const Matrix3d ZERO;
		// 3X3 ��λ����
		// �Խ���Ԫ��Ϊ1������Ϊ0
		static const Matrix3d IDENTITY;

		// ���ص�����ȡֵ��������
		// iRow ��������[in]��
		double* operator[] (int iRow) const;

		// ���صĳ˷��������������������˽����
		Matrix3d operator* (const Matrix3d& rkMatrix) const;

		// ��þ���ĳ�����������ɵ�������
		// iCol ��[in]��
		// return ������
		Vector3d GetColumn(int iCol) const;

		// ���þ���ĳ��������
		// iCol ��[in]��
		// vec ����[in]��
		void SetColumn(int iCol, const Vector3d& vec);
		
		// ������������ת�Ƕȹ�����ת����
		// xAxis ��x����ת�ĽǶ�[in]��
		// yAxis ��y����ת�ĽǶ�[in]��
		// zAxis ��z����ת�ĽǶ�[in]��
		void FromAxes(const Vector3d& xAxis, const Vector3d& yAxis, const Vector3d& zAxis);

		// ����Գƾ������������������ֵ
		void EigenDecomposition(Matrix3d& matUnitary, Matrix3d& matDiagonal, double dTolerance = EP) const;

		// ������ת�þ���
		// return �����ת�þ���
		Matrix3d Transpose() const;

	private:
		// Forbenius norm
		double FrobeniusNorm() const;

		// �ǶԽǵ�Forbenius norm
		// ˵���� ��������ǶԳƵ�
		double OffDiagonalFrobeniusNorm() const;

		// �Գ�Schur Decomposition
		void SchurDecomposition(Matrix3d& matResult, double dTolerance = EP);
		
	protected:
		double m[3][3];
		// for faster access
		friend class Matrix4d;
	};

	// ��ά����
	class S3MB_API Matrix4d
	{
	public:
		Matrix4d();
		Matrix4d(
			double m00, double m01, double m02, double m03,
			double m10, double m11, double m12, double m13,
			double m20, double m21, double m22, double m23,
			double m30, double m31, double m32, double m33);
		// 4X4�����
		// ����Ԫ��Ϊ��
		static const Matrix4d ZERO;
		// 4X4 ��λ����
		// �Խ���Ԫ��Ϊ1������Ϊ0
		static const Matrix4d IDENTITY;

		// ����*����������ֵ��ˡ�
		// scalar ��ֵ[in]��
		Matrix4d operator*(double scalar);

		// ����*����ɾ����������ˡ�
		// &m2 ��������[in]��
		Matrix4d operator * (const Matrix4d& m2) const;

		// ������ˡ�
		// &m2 ����һ��4X4����[in]��
		Matrix4d Concatenate(const Matrix4d& m2) const;

		// ����[]��ȡ����Ӧ�С�
		// iRow �кţ���Ч��ΧΪ�㵽��[in]��
		double* operator[] (unsigned int iRow);

		// ȡ��ֻ�����������ݡ�
		// iRow �кţ���Ч��ΧΪ�㵽��[in]��
		const double* const operator [] (unsigned int iRow) const;

		// �ж����������Ƿ���ȡ�
		// &m2 ����һ������[in]��
		bool operator == (const Matrix4d& m2) const;

		// �ж����������Ƿ���ȡ�
		// &m2 ����һ������[in]��
		bool operator != (const Matrix4d& m2) const;

		// �������İ������
		Matrix4d Adjoint() const;

		// �����������ʽֵ��
		double Determinant() const;

		// ��������������
		// return ���������
		Matrix4d Invert() const;

		// ����4x4������3x3�Ӿ�������ʽ��
		// m 4x4����[in]��
		// r0 ��һ���к�[in]��
		// r1 �ڶ����к�[in]��
		// r2 �������к�[in]��
		// c0 ��һ���к�[in]��
		// c1 �ڶ����к�[in]��
		// c2 �������к�[in]��
		double MINOR(const Matrix4d& m, const int r0, const int r1, const int r2,
			const int c0, const int c1, const int c2) const;

		// ���þ���ƽ�Ʋ���, [3][0], [3][1], [3][2]��ֵ��
		// v ƽ������[in]��
		void SetTrans(const Vector3d& v);

		// ��ȡ����ƽ�Ʋ���, [3][0], [3][1], [3][2]��ֵ��
		// v ƽ������[in]��
		Vector3d GetTrans() const;

		double m[4][4];

		// ��ȡ�����ָ��
		double* GetPointer();
	};
}

#endif