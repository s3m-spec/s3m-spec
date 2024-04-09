#if !defined(SKELETON_H__78795D40_559B_470C_94B5_A3B47837A1D0__INCLUDED_)
#define SKELETON_H__78795D40_559B_470C_94B5_A3B47837A1D0__INCLUDED_

#pragma once
#include "S3MBCommon.h"
#include "Matrix.h"
#include "BoundingBox.h"
#include <iostream>
#include <vector>
#include <string.h>
#include "MemoryStream.h"

namespace S3MB
{

	struct InstanceInfo
	{
		InstanceInfo()
		{
			nCount = 0;
			pMatrixValues = nullptr;
		}
		~InstanceInfo()
		{
			if (pMatrixValues != nullptr)
			{
				delete pMatrixValues;
				pMatrixValues = nullptr;
			}
		}
		// ȡֵΪ16
		unsigned short nCount;
		float* pMatrixValues;
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
		// ���ݻ�������
		int m_nVertexOptions;
		// ����ѹ�����
		unsigned int m_nCompressOptions;
		// �Ƿ���ָ��ѹ����
		bool HasCompressOptions(VertexCompressOptions enOptions)
		{
			return (m_nCompressOptions & enOptions) == enOptions;
		}

		// �������
		unsigned int m_nVerticesCount;
		// ����ά��
		unsigned short m_nVertexDimension;
		// ����ƫ��
		unsigned short m_nVertexStride;
		// ��������
		T* m_pVertices;
		// �������������Сֵ
		float m_minVerticesValue[4];
		// ����ѹ����һ������
		float m_fVertCompressConstant;

		// ���߸���
		unsigned int m_nNormalCount;
		// ����ά��
		unsigned short m_nNormalDimension;
		// ����ƫ��
		unsigned short m_nNormalStride;
		// ��������
		float* m_pNormals;

		// ��������
		float* m_pTangents;
		// ������Ŀ
		unsigned int m_nTangentCount;
		//! ����ά��
		unsigned short m_nTangentDimension;
		// ��������ƫ�� 
		unsigned short m_nTangentStride;

		// ������ɫ����
		unsigned int m_nVertexColorCount;
		// ������ɫƫ��
		unsigned short m_nVertexColorStride;
		// ������ɫ����
		unsigned int* m_pVertexColor;

		// ��ͼ������Ŀ
		unsigned int m_TexCoordCount[SMSCN_MAX_TEXTURE_COORD_SETS];

		// ��ͼ�����ά��
		unsigned short m_nTexDimensions[SMSCN_MAX_TEXTURE_COORD_SETS];

		// ÿ����ͼ�����Stride
		unsigned short m_TexCoordStride[SMSCN_MAX_TEXTURE_COORD_SETS];

		// ��ͼ��������
		float* m_pTexCoords[SMSCN_MAX_TEXTURE_COORD_SETS];

		// �����������������Сֵ
		float m_minTexCoordValue[SMSCN_MAX_TEXTURE_COORD_SETS][4];

		// ��������ѹ����һ������
		float m_texCoordCompressConstant[SMSCN_MAX_TEXTURE_COORD_SETS];

		std::vector<InstanceInfo*> m_vecInstanceInfo;

		// ������Ŀ
		unsigned int m_nVertexAttCount;
		// ����������Ϣ�Ͷ�Ӧ����
		std::map<wstring,int> m_mapVertexAttributeDescript;
		// ����������Ŀ������
		std::vector<unsigned int> m_vecVertexAttDataCount;
		// ��������ά��������
		std::vector<unsigned short> m_vecVertexAttDataDimension;
		// �����������͵�����
		std::vector<VertexAttributeType> m_vecVertexAttDataType;
		// �������ݵ�����
		std::vector<void*> m_vecVertexAttData;

		void SetVertexNum(unsigned int nVertexCount, unsigned short nVertexStride = 0)
		{
			m_nVerticesCount = nVertexCount;
			if (m_pVertices != NULL)
			{
				delete[] m_pVertices;
				m_pVertices = NULL;
			}
			if (nVertexCount == 0)
			{
				return;
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
		void SetTangentNum(unsigned int nTangentCount, unsigned short nTangentStride = 0)
		{
			m_nTangentCount = nTangentCount;
			if (m_pTangents != NULL)
			{
				delete[] m_pTangents;
				m_pTangents = NULL;
			}
			m_nTangentStride = nTangentStride;
			if (nTangentCount == 0)
			{
				return;
			}

			m_pTangents = new float[nTangentCount * m_nTangentDimension];

			memset(m_pTangents, 0, sizeof(float) * nTangentCount * m_nTangentDimension);
		}
		void SetColorNum(unsigned int nColorCount, unsigned short nColorStride = 0)
		{
			m_nVertexColorCount = nColorCount;
			if (m_pVertexColor != NULL)
			{
				delete[] m_pVertexColor;
				m_pVertexColor = NULL;
			}
			if (nColorCount == 0)
			{
				return;
			}
			m_pVertexColor = new unsigned int[nColorCount];
			memset(m_pVertexColor, 0, sizeof(unsigned int) * nColorCount);
			m_nVertexColorStride = nColorStride;
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
			if (nTexCoordCount == 0)
			{
				return true;
			}
			m_pTexCoords[nTexUnit] = new float[nTexCoordCount * m_nTexDimensions[nTexUnit]];
			memset(m_pTexCoords[nTexUnit], 0, sizeof(float) * nTexCoordCount * m_nTexDimensions[nTexUnit]);
			m_TexCoordStride[nTexUnit] = nTexCoordStride;
			return true;
		}

		bool SetAttDataNum(unsigned int nAttDataCount, \
			unsigned short nAttDataDimension, VertexAttributeType eAttDataType)
		{
			if (nAttDataCount == 0)
			{
				return true;
			}
			if (eAttDataType == AT_32BIT)
			{
				unsigned int* pAttData = new unsigned int[nAttDataCount * nAttDataDimension];
				memset(pAttData, 0, sizeof(unsigned int) * nAttDataCount * nAttDataDimension);
				m_vecVertexAttData.push_back(pAttData);
			}
			else if (eAttDataType == AT_FLOAT)
			{
				float* pAttData = new float[nAttDataCount * nAttDataDimension];
				memset(pAttData, 0, sizeof(float) * nAttDataCount * nAttDataDimension);
				m_vecVertexAttData.push_back(pAttData);
			}
			else if (eAttDataType == AT_DOUBLE)
			{
				double* pAttData = new double[nAttDataCount * nAttDataDimension];
				memset(pAttData, 0, sizeof(double) * nAttDataCount * nAttDataDimension);
				m_vecVertexAttData.push_back(pAttData);
			}
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

		if (m_pTangents != NULL)
		{
			delete[] m_pTangents;
			m_pTangents = NULL;
		}
		m_nTangentCount = 0;

		if (m_pVertexColor != NULL)
		{
			delete[] m_pVertexColor;
			m_pVertexColor = NULL;
		}

		m_nVertexColorCount = 0;

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

		for (auto& iInfo : m_vecInstanceInfo)
		{
			if (iInfo != nullptr)
			{
				delete iInfo;
				iInfo = nullptr;
			}
		}

		m_nVertexAttCount = 0;
		m_vecVertexAttDataCount.clear();
		m_vecVertexAttDataDimension.clear();
		m_vecVertexAttDataType.clear();
		for (unsigned int i = 0; i < m_vecVertexAttData.size(); i++)
		{
			delete[] m_vecVertexAttData[i];
			m_vecVertexAttData[i] = NULL;
		}
		m_vecVertexAttData.clear();
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
		m_nVertexColorCount = 0;
		m_nVertexColorStride = 0;
		m_pTangents = NULL;
		m_nTangentCount = 0;
		m_nTangentStride = 0;

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

		m_nVertexAttCount = 0;
		m_vecVertexAttDataCount.clear();
		m_vecVertexAttDataDimension.clear();
		m_vecVertexAttDataType.clear();
		for (unsigned int i = 0; i < m_vecVertexAttData.size(); i++)
		{
			delete[] m_vecVertexAttData[i];
			m_vecVertexAttData[i] = NULL;
		}
		m_vecVertexAttData.clear();
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

	// ������
	struct S3MB_API IndexPackage
	{
		IndexPackage();
		~IndexPackage();
		// ������Ŀ
		unsigned int m_nIndexesCount;

		// ��������
		unsigned short* m_pIndexes;

		// �Ƿ�ʹ���޷�������������
		VertexIndexType m_enIndexType;

		// �Ƿ�ʹ������
		bool m_bUseIndex;

		// ʹ�õ�Pass����������
		vector<wstring> m_strPassName;

		// ���ݻ��Ƶķ�ʽ
		OperationType m_OperationType;

		// ����������Ϣ
		bool Load(MemoryStream& stream);
		void Save(MemoryStream& stream);
		void SetIndexNum(int nIndexNum);
	};

	class S3MB_API IDInfo
	{
	public:
		IDInfo();
		IDInfo(const IDInfo& other);
		IDInfo& operator = (const IDInfo& other);
		~IDInfo();

		unsigned int m_nID;
		// ��������vector��ͬʱ��ֵ
		std::vector<int> m_arrInstanceIndex;
		std::vector<std::pair<int, int> > m_arrVertexColorOffsetAndCount;
	};

	// �Ǽ���
	class S3MB_API Skeleton
	{
	public:
		Skeleton();
		~Skeleton();

		// �����Χ��
		void ComputerBoundingBox();

		// ����InstanceInfo
		bool SetInstanceInfoAndIDInfo(std::vector<Matrix4d>& vecMats, std::vector<unsigned int>& vecIDs);

		// Fill IDInfo
		void AddIDInfo(IDInfo* pIDInfo);

		// ͨ��IDInfo���������
		void SplitIndexPackageByIDInfo();

	public:
		// ����
		wstring m_strGeoName;

		// ģ�Ͷ�����Ϣ
		VertexDataPackage* m_pVertexDataPackage;

		// ������Ϣ
		vector<IndexPackage*> m_arrIndexPackage;

		// �Ƿ���һ��ʵ������
		bool m_bInstanceBatch;

		// ������
		wstring m_strMaterialName;

		// λ�þ���
		Matrix4d m_matLocalView;

		// ��Χ��
		BoundingBox m_BoundingBox;

		// �����Χ��
		OrientedBoundingBox m_OBB;

		// ID��Ϣ
		std::vector<IDInfo*> m_arrIDInfo;
	};
}
#endif