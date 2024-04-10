#if !defined(S3MBPARSER_H__F79E86C1_5023_429B_9053_0CF43CAD63F3__INCLUDED_)
#define S3MBPARSER_H__F79E86C1_5023_429B_9053_0CF43CAD63F3__INCLUDED_

#pragma once
#include "stdafx.h"
#include "BoundingBox.h"
#include "BoundingSphere.h"
#include "Matrix.h"
#include "Shell.h"
#include "Point3D.h"

#include "prettywriter.h"
#include "stringbuffer.h"

#include <string>

namespace S3MB
{
	typedef rapidjson::Writer<rapidjson::StringBuffer>* WriterPtr;

	class STK_API S3MBParser
	{
	public:
		S3MBParser();
		~S3MBParser();

		void SetThreadNum(int nNum);
		bool ParseSCP(const std::wstring& strPath);
		bool GenerateTilesetAndB3DM(const std::wstring& strPath, const std::wstring& strOutputDir);
		void GenerateTileset(const std::wstring& strPath, const std::wstring& strOutputDir);

	private:
		void BoxToSphere(BoundingBox& box, BoundingSphere& sphere, Matrix4d mat = Matrix4d::IDENTITY);

		void CalPrjCoordMatrix(Point3D pos, BoundingBox& box, Matrix4d& mat, bool bNEU);

		static void GetFileList(std::vector<std::wstring>& vecFile, const std::wstring& strPath, const std::vector<std::wstring>& vecFileExt, bool bDir);

		static double GetGeometryError(const BoundingSphere& sphere, double dDis, RangeMode nMode = Pixel_Size_OnScreen);

		static void WriteAsset(WriterPtr pWriter, const std::string& strVersion);
		static void WriteProperties(WriterPtr pWriter, const BoundingBox& box);
		static void WriteGeometricError(WriterPtr pWriter, double dError);
		void WriteRoot(WriterPtr pWriter);
		static void WriteBoundingVolume(WriterPtr pWriter, BoundingSphere& sphere);
		static void WriteChild(WriterPtr pWriter, BoundingSphere& sphere, const std::string& strURL, double dError);
		static void WriteContent(WriterPtr pWriter, const std::string& strURL);
		static void WriteRefine(WriterPtr pWriter, const std::string& strRefine);
		static void WriteTransform(WriterPtr pWriter, const Matrix4d& mat);
		static void WriteFile(const std::wstring& strOutputPath, const std::string& strContent);
		// LOD
		void ProcessPagedMatchInfo(WriterPtr pWriter, std::vector<std::wstring>& vecTilePath, double geometryError, Matrix4d mat = Matrix4d::IDENTITY, const std::wstring& strExt = U("b3dm"));

	private:
		int m_nThreadNum;
		//! \brief ����
		Matrix4d m_mat;
		//! \brief λ��
		Point3D m_pos;
		//! \brief ����Χ
		BoundingBox m_box;
		//! \brief �ܵİ�Χ��
		BoundingSphere m_sphere;
		//�л�����
		double m_dDis;
		//! \brief �Ƿ�������
		bool m_bEllip;
		Matrix4d m_matViewSphere;
		Matrix4d m_matLocalView;
		//! \brief ���ڵ���Ƭ��·��
		std::vector<std::wstring> m_vecTilePath;
		//! \brief ���ڵ���Ƭ�İ�Χ��
		std::vector<BoundingSphere> m_vecTileSphere;
		//! \brief ���ڵ���Ƭ�İ�Χ��
		std::vector<BoundingBox> m_vecTileBox;
	};
}

#endif