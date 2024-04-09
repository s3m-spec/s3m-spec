#if !defined(POINT3D_H__1E4E26C1_2BB4_465E_A4B4_DD47ECC4B9F4__INCLUDED_)
#define POINT3D_H__1E4E26C1_2BB4_465E_A4B4_DD47ECC4B9F4__INCLUDED_

#pragma once
#include "stdafx.h"
#include <vector>

namespace S3MB
{
	class S3MB_API Point3D
	{
	public:
		//  	Ĭ�Ϲ��캯��
		Point3D();
		//  	ȱʡ��������
		~Point3D();
		//  ���������캯��
		Point3D(double xx, double yy, double zz);

	public:
		// 		���� = 
		Point3D& operator=(const Point3D& s);
		// 		���� += 
		Point3D& operator+=(const Point3D& p);
		// 		���� -= 
		Point3D& operator-=(const Point3D& p);
		// 		���� *= 
		Point3D& operator*=(double c);
		// 		���� /= 
		Point3D& operator/=(double c);
		// 		���� - ����
		Point3D operator-() const;
		// 		���� == 
		friend S3MB_API bool operator==(const Point3D& p, const Point3D& q);
		// 		���� !=
		friend S3MB_API bool operator!=(const Point3D& p, const Point3D& q);

	public:
		// ���x������
		double x;
		// ���y������
		double y;
		// ���z������
		double z;
	};

	typedef vector<Point3D> Point3Ds;
}

#endif
