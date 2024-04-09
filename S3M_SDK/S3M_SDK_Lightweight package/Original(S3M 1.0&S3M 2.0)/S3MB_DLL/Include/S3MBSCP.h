#pragma once
#include "Point3D.h"
#include "Skeleton.h"
#include <map>
#include "S3MBLayerInfos.h"
#include <string>
#include <fstream>

#define S3M_S3MB_VERSIONV1		1.0
#define S3M_S3MB_VERSIONV2		2.0
using namespace std;
namespace S3MB
{
	const double PI180 = 1.74532925199432957692369076848e-2;
	const double ONEPI = 3.14159265358979323846;
	const double TWOPI = 6.2831853071795864769;
	enum SCPSDataType
	{
		SDT_Unknown,
		SDT_ObliquePhoto,
		SDT_BIM,
		SDT_PointCloud,
		SDT_Vector,
		SDT_PipeLine,
		SDT_InstanceModel
	};
	enum SCPSPyramidSplitType
	{
		SSP_Unknown,
		SSP_Octree,
		SSP_QuadTree
	};
	enum SCPSLODType
	{
		SLT_Unknown,
		SLT_Add,
		SLT_Replace,
	};
	struct ExtensionObjectValue
	{
		// �ַ���
		wstring m_strName;
		wstring m_strType;
		// ˫����
		double m_dMax;
		double m_dMin;
	};
	enum PrjCoordSys
	{
		GCS_WGS_1984 = 4326,
	};
	class S3MB_API S3MBSCP
	{
	public:
		S3MBSCP(void);
		~S3MBSCP() {}
	public:
		void SetTiles(std::vector<wstring>& vecRootNames, std::vector<BoundingBox>& vecBBox);

		//! \brief �洢�����ļ�
		bool SaveToJsonFile(const wstring strS3MBProfile);
		//! \brief ����Json����
		void SaveToJson(JsonValue& jsonValue);

		bool Inverse(Point3D* pPoints);
		bool Forward(Point3D* pPoints);
		//! \brief ���ȹ��㵽(-PI--PI)
		double AdjLongitude(double lon);

		static wstring ToDataTypeString(const SCPSDataType enDataType);
		static SCPSDataType ToDataType(const wstring& strDataType);

		static wstring ToPyramidSplitTypeString(const SCPSPyramidSplitType enType);
		static SCPSPyramidSplitType ToPyramidSplitType(const wstring& strType);

		static wstring ToLODTypeString(const SCPSLODType enType);
		static SCPSLODType ToLODType(const wstring& strType);
	public:
		//! \brief ��������������Ϣ
		wstring m_strAsset;
		//! \brief �汾
		float m_fVersion;
		//! \brief �����ļ����ͣ���б������
		SCPSDataType m_enDataType;
		//! \brief �����ʷַ�ʽ
		SCPSPyramidSplitType m_enPyramidSplitType;
		//! \brief LOD�������ͣ���� or �滻
		SCPSLODType m_enLODType;

		//! \brief ��������ĵ���Χ
		Rect2D m_rcGeoBounds;
		//! \brief ���߶�
		double m_dbHeightMax;
		//! \brief ��С�߶�
		double m_dbHeightMin;
		//! \brief λ��
		Point3D m_pntPosition;
		//! \brief ����ϵ��Ϣ
		int m_prjCoordEPSG;
		bool m_bHasPrj;

		//! \brief wλ�ĺ���
		wstring m_strWCategory;
		double m_dbWMax;
		double m_dbWMin;

		//! \brief ������Ƿ�Ϊ��γ��
		bool m_bIsDegree;

		//! \brief ��Ƭ��Ϣ
		std::vector<wstring> m_vecRootNames;
		std::vector<BoundingBox> m_vecBBox;

		//==============  ��չ��Ϣ ================
			//! \brief ��չ��
		vector<ExtensionObjectValue> m_arrExtensionObjValues;

		//! \brief ��չ��Ϣ Tag <-> Value
		std::map<wstring, wstring> m_mapExtensions;

		//! \brief ����ļ�����
		std::vector<wstring> m_vecAttachFile;

		//! \brief ����ͼ����-bounds
		std::map<wstring, Rect2D> m_mapLayerNameRecBounds;

		//! \brief ����ͼ����
		std::vector<wstring> m_vecPointCloudLayer;

		//! \brief �㼶��Ϣ
		std::vector<int> m_vecGlobalLevel;
		//==============  ��չ��Ϣ ================
	};
}