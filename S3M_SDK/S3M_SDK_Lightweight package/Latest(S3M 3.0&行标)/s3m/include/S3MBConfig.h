#if !defined(S3MBConfig_H__D894A2D3_CDC8_4B18_BC13_96B71C8ABA83__INCLUDED_)
#define S3MBConfig_H__D894A2D3_CDC8_4B18_BC13_96B71C8ABA83__INCLUDED_

#pragma once
#include "BoundingBox.h"
#include "JsonValue.h"
#include "Point3D.h"
#include "S3MBCommon.h"

namespace S3MB
{
	class S3MB_API S3MBConfig
	{
	public:
		S3MBConfig(void);
		~S3MBConfig();

	public:
		bool ReadFile(const wstring& strFilePath);

		// �洢�����ļ�
		bool WriteFile(const wstring& strS3MBProfile);
	public:

		// ����/��ȡ������Ϣ
		void SetAsset(const wstring& strAsset);
		wstring GetAsset();

		// ����/��ȡ�汾��
		void SetVersion(const float& version);
		float GetVersion();

		// ����/��ȡ�����ʷ�����
		void SetSplitType(const SCPSPyramidSplitType& splitType);
		SCPSPyramidSplitType GetSplitType();

		// ����/��ȡ��������
		void SetDataType(const SCPSDataType& dataType);
		SCPSDataType GetDataType();

		// ����/��ȡLod�л�����
		void SetLodType(const SCPSLODType& lodType);
		SCPSLODType GetLodType();

		// ����/��ȡBounds
		void SetBounds(const Rect2D& bounds);
		Rect2D GetBounds();

		// ����/��ȡ���߶�
		void SetHeightMax(const double& dMax);
		double GetHeightMax();

		// ����/��ȡ��С�߶�
		void SetHeightMin(const double& dMin);
		double GetHeightMin();

		// ����/��ȡλ��
		void SetPosition(const Point3D& position);
		Point3D GetPosition();

		// ����/��ȡ����ϵepsg
		void SetEPSGCode(const int& nEpsg);
		int GetEPSGCode();

		// ����/��ȡ����ϵepsg
		void SetIsDegree(const bool& isDegree);
		bool GetIsDegree();

		// ����/��ȡ���ڵ���Ϣ
		void SetTiles(std::vector<wstring>& vecRootNames, std::vector<OrientedBoundingBox>& vecBBox);
		void GetTiles(std::vector<wstring>& vecRootNames, std::vector<OrientedBoundingBox>& vecBBox);

		// ����/��ȡ�������Ժ���������Ϣ����ֵ��Χ
		void SetVertexAttributeDescripts(std::vector<CategoryDescript>& vecDescript);
		void GetVertexAttributeDescripts(std::vector<CategoryDescript>& vecDescript);

		// ����/��ȡ��չ��Ϣ
		void SetExtension(const wstring& strKey, const wstring& strValue);
		bool HasExtension(const wstring& strKey);
		wstring GetExtension(const wstring& strKey);

	public:
		// ��������< - >�ַ���
		static wstring ToDataTypeString(const SCPSDataType& enDataType);
		static SCPSDataType ToDataType(const wstring& strDataType);
		// �ʷ�����< - >�ַ���
		static wstring ToPyramidSplitTypeString(const SCPSPyramidSplitType& enType);
		static SCPSPyramidSplitType ToPyramidSplitType(const wstring& strType);
		// Lod�л�����< - >�ַ���
		static wstring ToLODTypeString(const SCPSLODType& enType);
		static SCPSLODType ToLODType(const wstring& strType);
		// ��������< - >�ַ���
		static std::wstring FromTextureCompressionType(const TextureCompressType& nType);
		static TextureCompressType ToTextureCompressionType(const wstring& strType);
		// ����ѹ������< - >�ַ���
		static std::wstring FromVertexCompressionType(const S3MBVertexTag& eType);
		static S3MBVertexTag ToVertexCompressionType(const wstring& strType);

	private:
		// ����Json����
		void SaveToJson(JsonValue& jsonValue);
	private:
		// ��������������Ϣ
		wstring m_strAsset;
		// �汾
		float m_fVersion;
		// �����ļ����ͣ���б������
		SCPSDataType m_enDataType;
		// �����ʷַ�ʽ
		SCPSPyramidSplitType m_enPyramidSplitType;
		// LOD�������ͣ���� or �滻
		SCPSLODType m_enLODType;

		// ��������ĵ���Χ
		Rect2D m_rcGeoBounds;
		// ���߶�
		double m_dbHeightMax;
		// ��С�߶�
		double m_dbHeightMin;
		// λ��
		Point3D m_pntPosition;
		// ����ϵ��Ϣ
		int m_prjCoordEPSG;
		bool m_bHasPrj;

		// wλ�ĺ���
		wstring m_strWCategory;
		double m_dbWMax;
		double m_dbWMin;

		// ������Ƿ�Ϊ��γ��
		bool m_bIsDegree;

		// ��Ƭ��Ϣ
		std::vector<wstring> m_vecRootNames;
		std::vector<BoundingBox> m_vecBBox;
		std::vector<OrientedBoundingBox> m_vecOBB;

		// ==============  ��չ��Ϣ ================
			// ��չ��
		vector<ExtensionObjectValue> m_arrExtensionObjValues;

		// ��չ��Ϣ Tag <-> Value
		std::map<wstring, wstring> m_mapExtensions;

		// ����ͼ����-bounds
		std::map<wstring, Rect2D> m_mapLayerNameRecBounds;

		// ����ͼ����
		std::vector<wstring> m_vecPointCloudLayer;

		// ==============  ��չ��Ϣ ================

		// �������Ժ���������Ϣ����ֵ��Χ
		std::vector<CategoryDescript> m_vecVertexAttributeDescript;
	};
}

#endif