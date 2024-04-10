#if !defined(BOUNDINGSPHERE_H__65D8FD01_BA25_482B_9F73_6754CC922D09__INCLUDED_)
#define BOUNDINGSPHERE_H__65D8FD01_BA25_482B_9F73_6754CC922D09__INCLUDED_

#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "BoundingBox.h"

namespace S3MB
{
	class S3MB_API BoundingSphere
	{
	public:
		BoundingSphere();

		BoundingSphere(const BoundingBox& box);

		~BoundingSphere(void);

	public:
		// �жϰ�Χ���Ƿ���Ч
		bool valid() const;

		// ��ȡ��Χ��
		BoundingBox GetBoundingBox() const;

		// ��ȡ���ĵ�
		Vector3d GetCenter() const;

		// ��ȡ�뾶
		double GetRadius() const;

		// ���ݸ����İ�Χ������չ�����ġ��뾶���ı�
		// ����չ����
		void ExpandBy(const BoundingSphere& bs);

	public:
		Vector3d m_center;
		double m_radius;
	};
}

#endif