#pragma once
#include <vector>
#include "stdafx.h"
using namespace std;
namespace S3MB
{
#ifndef IS0(x)
	//! \brief  ��Сֵ����
#define EP 1e-10
#define NEP -1e-10
#define IS0(x) (((x) < EP) && ((x) > NEP))
#endif // !IS0(x)

#ifndef EQUAL(X,Y)
#define EQUAL(X,Y) IS0(X-Y)
#endif // !EQUAL(X,Y)


	class S3MB_API Point3D
	{
	public:
		//! \brief ���x������
		double x;
		//! \brief ���y������
		double y;
		//! \brief ���z������
		double z;
	public:
		//! \brief  	Ĭ�Ϲ��캯��
		Point3D();
		//! \brief  	ȱʡ��������
		~Point3D();

		//! \brief  ���������캯��
		Point3D(double xx, double yy, double zz);
			

	public:
		//! \brief 		���� = 
		Point3D& operator=(const Point3D& s);
		//! \brief 		���� += 
		Point3D& operator+=(const Point3D& p);
		//! \brief 		���� -= 
		Point3D& operator-=(const Point3D& p);
		//! \brief 		���� *= 
		Point3D& operator*=(double c);
		//! \brief 		���� /= 
		Point3D& operator/=(double c);
		//! \brief 		���� - ����
		Point3D operator-() const;
		//! \brief 		���� == 
		friend  bool operator==(const Point3D& p, const Point3D& q);
		//! \brief 		���� !=
		friend  bool operator!=(const Point3D& p, const Point3D& q);

	};

	typedef vector<Point3D> Point3Ds;
}
