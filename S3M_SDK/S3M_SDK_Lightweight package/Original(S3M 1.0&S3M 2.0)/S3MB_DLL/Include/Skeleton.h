#ifndef  _SKELETON_H_
#define  _SKELETON_H_

#include <iostream>
#include <vector>
//#include <wtypesbase.h>
#include "MemoryStream.h"
using namespace std;
namespace S3MB
{

#define DBLMAX 1.7976931348623158e+308 /* max value */
#define DBLMIN 2.2250738585072014e-308 /* min positive value */
#define FLTMAX 3.402823466e+38F  /* max value */
#define FLTMIN 1.175494351e-38F  /* min positive value */

#ifndef IS0(x)
	//! \brief  ��Сֵ����
#define EP 1e-10
#define NEP -1e-10
#define IS0(x) (((x) < EP) && ((x) > NEP))
#endif // !IS0(x)

// ����������������
#define SMSCN_MAX_TEXTURE_COORD_SETS 8

#define SIZE_PER_INSTANCE 17
#define SIZE_PER_DM_INSTANCE  29
#define SIZE_PER_INSTANCEINFO 16

// ���ݻ��Ƶ�����
	enum VertexOptions
	{
		VO_NORMALS = 1,                  // GL_NORMAL_ARRAY + glNormalPointer()
		VO_TEXTURE_COORDS = 2,           // GL_TEXTURE_COORD_ARRAY + glTexCoordPointer()
		VO_DIFFUSE_COLOURS = 4,          // GL_COLOR_ARRAY + glColorPointer()
		VO_SPECULAR_COLOURS = 8,         // Secondary Color
		VO_BLEND_WEIGHTS = 16,
		VO_USE_SINGLE_COLOR = 32,        // use only one kind of color
		VO_USE_POINT_SMOOTHING = 64,     // �����㷴����
		VO_MATERIAL = 128,               // ʹ�ò���
		VO_TEXTURE_COLOR = 256,          // ʹ�ò���
		VO_VERTEX_DOUBLE = 512,          // ʹ��Double���͵Ķ���
		VO_TEXTURE_COORD_Z_IS_MATRIX = 1024,  // ��ʾ�������Ե�Zֵ��һ������
	};

	enum VertexCompressOptions
	{
		SVC_Vertex = 1,				//�����ѹ��
		SVC_Normal = 2,				//���ߴ�ѹ��
		SVC_VertexColor = 4,				//������ɫ��ѹ��
		SVC_SecondColor = 8,				//SecondColor��ѹ��
		SVC_TexutreCoord = 16,				//���������ѹ��
		SVC_TexutreCoordIsW = 32,  // ��ʾ��һ����������洢�����Wλ
	};

	// ����������
	enum VertexIndexType
	{
		IT_16BIT,
		IT_32BIT,
	};

	// ���ݻ��Ƶķ�ʽ
	enum OperationType
	{
		/// A list of points, 1 vertex per point
		OT_POINT_LIST = 1,
		/// A list of lines, 2 vertices per line
		OT_LINE_LIST = 2,
		/// A strip of connected lines, 1 vertex per line plus 1 start vertex
		OT_LINE_STRIP = 3,
		/// A list of triangles, 3 vertices per triangle
		OT_TRIANGLE_LIST = 4,
		/// A strip of triangles, 3 vertices for the first triangle, and 1 per triangle after that 
		OT_TRIANGLE_STRIP = 5,
		/// A fan of triangles, 3 vertices for the first triangle, and 1 per triangle after that
		OT_TRIANGLE_FAN = 6,

		OT_QUAD_STRIP = 8,

		OT_QUAD_LIST = 9,

		OT_POLYGON = 10,

		OT_PICTURE = 12,

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
		//4X4�����
		//����Ԫ��Ϊ��
		static const Matrix4d ZERO;
		//4X4 ��λ����
		//�Խ���Ԫ��Ϊ1������Ϊ0
		static const Matrix4d IDENTITY;

		//! \brief ����*����ɾ����������ˡ�
		//! \param &m2 ��������[in]��
		//! \return ������ɺ����
		Matrix4d operator * (const Matrix4d& m2) const;

		//! \brief ������ˡ�
		//! \param &m2 ����һ��4X4����[in]��
		//! \return ��������4X4����
		Matrix4d Concatenate(const Matrix4d& m2) const;

		//! \brief ����[]��ȡ����Ӧ�С�
		//! \param iRow �кţ���Ч��ΧΪ�㵽��[in]��
		//! \return ����ָ��һ�����ݣ�����������ָ�롣
		double* operator[] (unsigned int iRow);

		//! \brief ȡ��ֻ�����������ݡ�
		//! \param iRow �кţ���Ч��ΧΪ�㵽��[in]��
		//! \return �����ݡ�
		const double* const operator [] (unsigned int iRow) const;

		//! \brief �ж����������Ƿ���ȡ�
		//! \param &m2 ����һ������[in]��
		//! \return ����ȷ���Ϊtrue����������򷵻�Ϊfalse��
		bool operator == (const Matrix4d& m2) const;

		//! \brief �ж����������Ƿ���ȡ�
		//! \param &m2 ����һ������[in]��
		//! \return ������ȷ���Ϊtrue�����򷵻�false��
		bool operator != (const Matrix4d& m2) const;

		double m[4][4];

		//! \brief ��ȡ�����ָ��
		double* GetPointer() { return (double*)&m; }
	};

	// ��ά����
	struct S3MB_API Vector3d
	{
		Vector3d() :
			x(0), y(0), z(0) {}

		Vector3d(double fx, double fy, double fz) :
			x(fx), y(fy), z(fz) {}

		//! \brief ���ص�ȡֵ�������ȡ����i���ķ���
		double operator [] (const unsigned i) const;

		//! \brief ���ص�ȡֵ�������ȡ����i���ķ���������
		double& operator [] (const unsigned i);

		//! \brief ���صļӷ������������������֮��
		Vector3d operator + (const Vector3d& vec) const;

		//! \brief ���صļ��������������������֮��
		Vector3d operator - (const Vector3d& vec) const;

		//! \brief �������ĳ���
		double Length() const;

		//! \brief �������ĳ��ȵ�ƽ��
		double Length2() const;

		//! \brief ȡ��������ÿ���������Сֵ�γ�һ���µ�����
		void MakeFloor(const Vector3d& cmp);

		//! \brief ȡ��������ÿ����������ֵ�γ�һ���µ�����
		void MakeCeil(const Vector3d& cmp);

		//! \brief �ó˷�֧��D3D��������
		//! \brief ��ϵͳ����ֱ��ʹ��
		Vector3d MultiplyMatrix(const Matrix4d& m) const;

		void Normalize();

		double x, y, z;
	};

	// ��ά����
	struct S3MB_API Vector4d
	{
		Vector4d();

		Vector4d(const double fx, const double fy, const double fz, const double fw) :
			x(fx), y(fy), z(fz), w(fw) {}

		//! \brief ���ص�ȡֵ�������ȡ����i���ķ���
		double operator [] (const unsigned i) const;

		//! \brief ���ص�ȡֵ�������ȡ����i���ķ���������
		double& operator [] (const unsigned i);

		double x, y, z, w;
	};

	class S3MB_API BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox(Vector3d vMin, Vector3d vMax);

		//! \brief �ж��Ƿ��ǺϷ�ʵ����
	//! \param dValue ʵ��[in]��
	//! \return trueΪ�Ϸ���falseΪ�Ƿ���
		bool IsRealNaN(double dValue);

		//! \brief �ж���Ч��
		//! \return ��Χ���Ƿ���Ч
		bool IsVaild();

		//! \brief ��������Χ�н��кϲ���
		//! \param BoundBox Ҫ���кϲ��İ�Χ��[in]��
		void Merge(const BoundingBox& BoundBox);

		//���ɰ�Χ�е���С������
		//! \brief ���ù��ɰ�Χ�е���С������
		//! \param vMin ���ɰ�Χ�е���С����[in]��
		void SetMin(Vector3d vMin);

		//! \brief ���ù��ɰ�Χ�е����������
		//! \param vMax ���ɰ�Χ�е��������[in]��
		void SetMax(Vector3d vMax);

		//! \brief ���ù��ɰ�Χ�е���С������
		//! \param x,y,z ���ɰ�Χ�е���С����[in]��
		void SetMin(double x, double y, double z);

		//! \brief ���ù��ɰ�Χ�е����������
		//! \param x,y,z ���ɰ�Χ�е��������[in]��
		void SetMax(double x, double y, double z);

		//! \brief ���ù��ɰ�Χ�е������С������
		//! \param vMin ���ɰ�Χ�е������С����[in]��
		//! \param vMax ���ɰ�Χ�е��������[in]��
		void SetExtents(const Vector3d& vMin, const Vector3d& vMax);

		//! \brief ���ù��ɰ�Χ�е������С������
		//! \param (minx,miny,minz) ���ɰ�Χ�е������С����[in]��
		//! \param (maxx,maxy,maxz) ���ɰ�Χ�е��������[in]��
		void SetExtents(double minx, double miny, double minz,
			double maxx, double maxy, double maxz);

		//! \brief ���ð�Χ��Ϊ��
		void SetNULL(void) { m_bNull = true; }

		//! \brief  �õ����ɰ�Χ�е���С����
		const Vector3d& GetMin(void) const;

		//! \brief �õ����ɰ�Χ�е��������
		const Vector3d& GetMax(void) const;

		//! \brief �õ���Χ�е����ĵ㡣
	//! \remarks ������ĵ��ǹ��ɰ�Χ�е���С���������������ƽ��ֵ��
		Vector3d GetCenter() const;

		//! \brief �԰�Χ�н��о���任
		//! \param matrix �԰�Χ�н��б任�ľ���[in]��
		void Transform(Matrix4d& matrix);
	protected:
		//! \brief ���������С�������°�Χ�е�8���ǵ㡣
		void UpdateCorners(void);
	private:
		Vector3d m_vMin
			;
		//���ɰ�Χ�е����������
		Vector3d m_vMax;

		//���ɰ�Χ��8���ǵ㡣
		Vector3d m_vCorner[8];

		//��־��Χ���Ƿ�Ϊ�ա�
		bool m_bNull;
	};

	class S3MB_API Rect2D
	{
	public:
		//! \brief ���캯��һ����ά���ζ���
		Rect2D() { left = right = top = bottom = 0; }
		Rect2D(double dLeft, double dTop, double dRight, double dBottom)
			:left(dLeft), top(dTop), right(dRight), bottom(dBottom) {}
	public:
		//! \brief ������߽�
		double left;
		//! \brief �����ϱ߽�
		double top;
		//! \brief �����ұ߽硣left<right
		double right;
		//! \brief �����±߽硣bottom < top
		double bottom;
	};
	// �����
	template<typename T>
	class VertexDataPackageTemplate
	{
	public:
		VertexDataPackageTemplate();
		~VertexDataPackageTemplate();
		void clear();
	public:
		//���ݻ�������
		int m_nVertexOptions;
		//����ѹ�����
		unsigned int m_nCompressOptions;
		//�Ƿ���ָ��ѹ����
		bool HasCompressOptions(VertexCompressOptions enOptions)
		{
			return (m_nCompressOptions & enOptions) == enOptions;
		}

		//�������
		unsigned int m_nVerticesCount;
		//����ά��
		unsigned short m_nVertexDimension;
		//����ƫ��
		unsigned short m_nVertexStride;
		//��������
		T* m_pVertices;
		//! \brief �������������Сֵ
		float m_minVerticesValue[4];
		//! \brief ����ѹ����һ������
		float m_fVertCompressConstant;

		//���߸���
		unsigned int m_nNormalCount;
		//����ά��
		unsigned short m_nNormalDimension;
		//����ƫ��
		unsigned short m_nNormalStride;
		//��������
		float* m_pNormals;

		//������ɫ����
		unsigned int m_nVertexColorCount;
		//������ɫƫ��
		unsigned short m_nVertexColorStride;
		//������ɫ����
		unsigned int* m_pVertexColor;

		//����ڶ���ɫ����
		unsigned int m_nSecondVertexColorCount;
		//����ڶ���ɫƫ��
		unsigned short m_nSecondVertexColorStride;
		//����ڶ���ɫ����
		unsigned int* m_pSecondVertexColor;

		//��ͼ������Ŀ
		unsigned int m_TexCoordCount[SMSCN_MAX_TEXTURE_COORD_SETS];

		//��ͼ�����ά��
		unsigned short m_nTexDimensions[SMSCN_MAX_TEXTURE_COORD_SETS];

		//ÿ����ͼ�����Stride
		unsigned short m_TexCoordStride[SMSCN_MAX_TEXTURE_COORD_SETS];

		//��ͼ��������
		float* m_pTexCoords[SMSCN_MAX_TEXTURE_COORD_SETS];

		//! \brief �����������������Сֵ
		float m_minTexCoordValue[SMSCN_MAX_TEXTURE_COORD_SETS][4];

		//! \brief ��������ѹ����һ������
		float m_texCoordCompressConstant[SMSCN_MAX_TEXTURE_COORD_SETS];

		void SetVertexNum(unsigned int nVertexCount, unsigned short nVertexStride = 0)
		{
			m_nVerticesCount = nVertexCount;
			if (m_pVertices != NULL)
			{
				delete[] m_pVertices;
				m_pVertices = NULL;
			}
			m_pVertices = new T[nVertexCount * m_nVertexDimension];
			memset(m_pVertices, 0, sizeof(T) * nVertexCount * m_nVertexDimension);
			m_nVertexStride = nVertexStride;
		}
		void SetNormalNum(unsigned int nNormalCount, unsigned short nNormalStride = 0)
		{
			m_nNormalCount = nNormalCount;
			if (m_pNormals != NULL)
			{
				delete[] m_pNormals;
				m_pNormals = NULL;
			}
			m_nNormalStride = nNormalStride;
			if (nNormalCount == 0)
			{
				return;
			}

			m_pNormals = new float[nNormalCount * m_nNormalDimension];
			memset(m_pNormals, 0, sizeof(float) * nNormalCount * m_nNormalDimension);
		}
		void SetColorNum(unsigned int nColorCount, unsigned short nColorStride = 0)
		{
			m_nVertexColorCount = nColorCount;
			if (m_pVertexColor != NULL)
			{
				delete[] m_pVertexColor;
				m_pVertexColor = NULL;
			}
			m_pVertexColor = new unsigned int[nColorCount];
			memset(m_pVertexColor, 0, sizeof(unsigned int) * nColorCount);
			m_nVertexColorStride = nColorStride;
		}
		void SetSecondColorNum(unsigned int nColorCount, unsigned short nColorStride = 0)
		{
			m_nSecondVertexColorCount = nColorCount;


			if (m_pSecondVertexColor != NULL)
			{
				delete[] m_pSecondVertexColor;
				m_pSecondVertexColor = NULL;
			}
			m_pSecondVertexColor = new unsigned int[nColorCount];
			memset(m_pSecondVertexColor, 0, sizeof(unsigned int) * nColorCount);

			m_nSecondVertexColorStride = nColorStride;
		}
		bool SetTexCoordsNum(unsigned short nTexUnit, unsigned int nTexCoordCount, unsigned short nTexCoordStride = 0)
		{
			if (nTexUnit >= SMSCN_MAX_TEXTURE_COORD_SETS)
			{
				return false;
			}
			m_TexCoordCount[nTexUnit] = nTexCoordCount;

			if (m_pTexCoords[nTexUnit] != NULL)
			{
				delete[] m_pTexCoords[nTexUnit];
				m_pTexCoords[nTexUnit] = NULL;
			}
			m_pTexCoords[nTexUnit] = new float[nTexCoordCount * m_nTexDimensions[nTexUnit]];
			memset(m_pTexCoords[nTexUnit], 0, sizeof(float) * nTexCoordCount * m_nTexDimensions[nTexUnit]);
			m_TexCoordStride[nTexUnit] = nTexCoordStride;
			return true;
		}
	};
	template<typename T>
	void VertexDataPackageTemplate<T>::clear()
	{
		if (m_pVertices != NULL)
		{
			delete[] m_pVertices;
			m_pVertices = NULL;
		}
		m_nVerticesCount = 0;

		if (m_pNormals != NULL)
		{
			delete[] m_pNormals;
			m_pNormals = NULL;
		}
		m_nNormalCount = 0;

		if (m_pVertexColor != NULL)
		{
			delete[] m_pVertexColor;
			m_pVertexColor = NULL;
		}
		if (m_pSecondVertexColor != NULL)
		{
			delete[] m_pSecondVertexColor;
			m_pSecondVertexColor = NULL;
		}

		m_nVertexColorCount = 0;
		m_nSecondVertexColorCount = 0;

		unsigned short i = 0;
		for (i = 0; i < SMSCN_MAX_TEXTURE_COORD_SETS; i++)
		{
			if (m_pTexCoords[i] != NULL)
			{
				delete[] m_pTexCoords[i];
				m_pTexCoords[i] = NULL;
			}
			m_TexCoordCount[i] = 0;
		}
	}
	template<typename T>
	VertexDataPackageTemplate<T>::VertexDataPackageTemplate()
	{
		m_nCompressOptions = 0;
		m_nVertexDimension = 3;
		m_nNormalDimension = 3;
		m_pVertices = NULL;
		m_nVerticesCount = 0;
		m_nVertexStride = 0;
		m_fVertCompressConstant = 0.0;
		m_pNormals = NULL;
		m_nNormalCount = 0;
		m_nNormalStride = 0;
		m_pVertexColor = NULL;
		m_pSecondVertexColor = NULL;
		m_nVertexColorCount = 0;
		m_nSecondVertexColorCount = 0;
		m_nVertexColorStride = 0;
		m_nSecondVertexColorStride = 0;

		m_nVertexOptions = sizeof(T) == sizeof(double) ? VO_VERTEX_DOUBLE : 0;
		m_nVertexOptions = m_nVertexOptions | VO_NORMALS | VO_DIFFUSE_COLOURS | VO_TEXTURE_COORDS;

		unsigned short i = 0;
		for (i = 0; i < SMSCN_MAX_TEXTURE_COORD_SETS; i++)
		{
			m_pTexCoords[i] = NULL;
			m_TexCoordStride[i] = 0;
			m_TexCoordCount[i] = 0;
			m_nTexDimensions[i] = 2;
			m_texCoordCompressConstant[i] = -1.0;
			m_minTexCoordValue[i][0] = m_minTexCoordValue[i][1] = m_minTexCoordValue[i][2] = m_minTexCoordValue[i][3] = 0.0;
		}
	}

	template<typename T>
	VertexDataPackageTemplate<T>::~VertexDataPackageTemplate()
	{
		clear();
	}

	// float���ȵĶ���
	typedef VertexDataPackageTemplate<float> VertexDataPackage;

	// double���ȵĶ���
	typedef VertexDataPackageTemplate<double> VertexDataPackageExact;

	//������
	struct S3MB_API IndexPackage
	{
		IndexPackage();
		~IndexPackage();
		//������Ŀ
		unsigned int m_nIndexesCount;

		//��������
		unsigned short* m_pIndexes;

		//�Ƿ�ʹ���޷�������������
		VertexIndexType m_enIndexType;

		//�Ƿ�ʹ������
		bool m_bUseIndex;

		//ʹ�õ�Pass����������
		vector<wstring> m_strPassName;

		//���ݻ��Ƶķ�ʽ
		OperationType m_OperationType;

		//����������Ϣ
		bool Load(MemoryStream& stream);
		void Save(MemoryStream& stream);
		void SetIndexNum(int nIndexNum);
	};

	class IDInfo
	{
	public:
		IDInfo() :m_nID(0) {};
		IDInfo(const IDInfo& other);
		IDInfo& operator = (const IDInfo& other);
		~IDInfo(){}

		unsigned int m_nID;
		std::vector<int> m_arrInstanceIndex;
		std::vector<std::pair<int, int> > m_arrVertexColorOffsetAndCount;
	};

	//�Ǽ���
	class S3MB_API Geometry
	{
	public:
		Geometry();
		~Geometry();
		//����
		wstring m_strGeoName;

		//ģ�Ͷ�����Ϣ
		VertexDataPackage* m_pVertexDataPackage;

		//������Ϣ
		vector<IndexPackage*> m_arrIndexPackage;

		//�Ƿ���һ��ʵ������
		bool m_bInstanceBatch;

		//������
		wstring m_strMaterialName
			;
		//�����Ƿ���Ҫѹ��
		bool m_bNormalDecode;

		//λ�þ���
		Matrix4d m_matWorldView;

		//��������
		int m_nUseIndex;

		//��Χ��
		BoundingBox m_BoundingBox;

		//�����Χ��
		void ComputerBoundingBox();

		//����InstanceInfo
		bool CreateInstanceInfo(std::vector<Matrix4d>& vecMats, std::vector<unsigned int>& vecIDs);

		//��ȡInstanceInfo
		bool GetInstanceInfo(std::vector<Matrix4d>& vecMats, std::vector<unsigned int>& vecIDs, BoundingBox& box);

		//Fill IDInfo
		void AddIDInfo(const IDInfo& iDInfo);

		//ͨ��IDInfo���������
		void SplitIndexPackageByIDInfo();
	private:
		std::vector<IDInfo> m_arrIDInfo;
	};
}
#endif