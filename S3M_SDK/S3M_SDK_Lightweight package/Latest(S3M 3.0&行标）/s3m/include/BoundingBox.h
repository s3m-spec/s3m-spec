#if !defined(BOUNDINGBOX_H__7B747118_DB94_4FC7_9ED4_016DA765BD9A__INCLUDED_)
#define BOUNDINGBOX_H__7B747118_DB94_4FC7_9ED4_016DA765BD9A__INCLUDED_

#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "Matrix.h"
#include <vector>

namespace S3MB
{
	class BoundingBox;
	class S3MB_API OrientedBoundingBox
	{
	public:

		struct HullVertice
		{
			std::vector<char*> data;
		};

		static std::vector<HullVertice> m_arrHullVertice;

		// ���캯��
		OrientedBoundingBox();

		OrientedBoundingBox(Vector3d vCenter, Matrix3d matHalfAxes);

		OrientedBoundingBox& operator = (const OrientedBoundingBox& boundingBox);

		// �õ���Χ�е����ĵ�
		Vector3d GetCenter() const;

		// �õ���Χ�еı任����
		Matrix3d GetHalfAxes() const;

		// ��־��Χ���Ƿ�Ϊ�ա�
		bool IsNULL() const { return m_bNull; }

		// ��������Χ�н��кϲ���
		// OrientedBoundingBox Ҫ���кϲ��İ�Χ��[in]��
		void Merge(const OrientedBoundingBox& obb);

		// ��ȡ�����Χ��
		void FromPoints(const std::vector<Vector3d>& vecPosition);

		// obbתBoundingBox
		void ToBoundingBox(BoundingBox& BBOX);

	private:
		// ���ĵ�
		Vector3d m_vCenter;

		// �任����
		Matrix3d m_matHalfAxes;

		// ��־��Χ���Ƿ�Ϊ�ա�
		bool m_bNull;

		// �Ƿ����ͶӰ
		bool m_bBoxAreaError;

		void UpdateBBox();

		std::vector<Vector3d> m_arrBox;

		Vector3d m_vecU;
		Vector3d m_vecV;
		Vector3d m_vecW;

		Vector3d m_posMin;
		Vector3d m_posMax;
		double m_dHalfDiagonalLine;
	};

	class S3MB_API BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox(Vector3d vMin, Vector3d vMax);

		// �ж��Ƿ��ǺϷ�ʵ����
		// dValue ʵ��[in]��
		// return trueΪ�Ϸ���falseΪ�Ƿ���
		bool IsRealNaN(double dValue);

		// �ж���Ч��
		// return ��Χ���Ƿ���Ч
		bool IsVaild();

		// ��������Χ�н��кϲ���
		// BoundBox Ҫ���кϲ��İ�Χ��[in]��
		void Merge(const BoundingBox& BoundBox);

		// ���ɰ�Χ�е���С������
		// ���ù��ɰ�Χ�е���С������
		// vMin ���ɰ�Χ�е���С����[in]��
		void SetMin(Vector3d vMin);

		// ���ù��ɰ�Χ�е����������
		// vMax ���ɰ�Χ�е��������[in]��
		void SetMax(Vector3d vMax);

		// ���ù��ɰ�Χ�е���С������
		// x,y,z ���ɰ�Χ�е���С����[in]��
		void SetMin(double x, double y, double z);

		// ���ù��ɰ�Χ�е����������
		// x,y,z ���ɰ�Χ�е��������[in]��
		void SetMax(double x, double y, double z);

		// ���ù��ɰ�Χ�е������С������
		// vMin ���ɰ�Χ�е������С����[in]��
		// vMax ���ɰ�Χ�е��������[in]��
		void SetExtents(const Vector3d& vMin, const Vector3d& vMax);

		// ���ù��ɰ�Χ�е������С������
		// (minx,miny,minz) ���ɰ�Χ�е������С����[in]��
		// (maxx,maxy,maxz) ���ɰ�Χ�е��������[in]��
		void SetExtents(double minx, double miny, double minz,
			double maxx, double maxy, double maxz);

		// ���ð�Χ��Ϊ��
		void SetNULL(void);

		// �жϰ�Χ���Ƿ�Ϊ��
		bool IsNULL(void) const;

		//  �õ����ɰ�Χ�е���С����
		const Vector3d& GetMin(void) const;

		// �õ����ɰ�Χ�е��������
		const Vector3d& GetMax(void) const;

		// �õ����ɰ�Χ�е�8���㡣
		const Vector3d* GetCorners() const;

		// �õ���Χ�е����ĵ㡣
		// ˵���� ������ĵ��ǹ��ɰ�Χ�е���С���������������ƽ��ֵ��
		Vector3d GetCenter() const;

		// �԰�Χ�н��о���任
		// matrix �԰�Χ�н��б任�ľ���[in]��
		void Transform(Matrix4d& matrix);

		// ת��OBB��Χ��
		void ToOrientedBoundingBox(OrientedBoundingBox& OBB);

	protected:
		// ���������С�������°�Χ�е�8���ǵ㡣
		void UpdateCorners(void);
	private:
		Vector3d m_vMin
			;
		// ���ɰ�Χ�е����������
		Vector3d m_vMax;

		// ���ɰ�Χ��8���ǵ㡣
		Vector3d m_vCorner[8];

		// ��־��Χ���Ƿ�Ϊ�ա�
		bool m_bNull;
	};
}

#endif