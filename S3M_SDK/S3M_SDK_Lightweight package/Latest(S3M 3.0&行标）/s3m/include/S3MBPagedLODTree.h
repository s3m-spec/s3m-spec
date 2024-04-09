#if !defined(S3MBPAGEDLODTREE_H__5A40E348_CD07_4B4D_B8DB_7AA319481820__INCLUDED_)
#define S3MBPAGEDLODTREE_H__5A40E348_CD07_4B4D_B8DB_7AA319481820__INCLUDED_

#pragma once
#include "JsonValue.h"
#include "S3MBCommon.h"
#include "Variant.h"
#include "Shell.h"
#include <vector>

namespace S3MB
{
	class S3MB_API S3MBTileInfo
	{
	public:
		S3MBTileInfo();
		~S3MBTileInfo();

	public:
		// LOD���
		int m_nLODNum;
		// �����ļ���·��
		wstring m_strModelPath;
		// �������ļ���·��
		wstring m_strIndexFilePath;
		// LODѡȡģʽ
		wstring m_strRangeMode;
		// LODѡȡ��ֵ����
		double m_dRangeValue; 
		// �ӽڵ�Tile����Ϣ
		vector<S3MBTileInfo*> m_vecChildren;
		// �ӽڵ�Tile��״̬
		wstring m_strState;
		// �����Χ��
		OrientedBoundingBox m_OBB;
		// ��Χ�У����ݵͰ汾�����ݣ�
		BoundingBox m_AABB;
		// �Ƿ��Ǹ�Tile
		bool m_bRootTile;
	};

	class S3MB_API S3MBTileTree
	{
	public:
		S3MBTileTree();
		~S3MBTileTree();

		// �����Tile���ļ�·��
		bool LoadFromFile(const wstring& path);

	private:
		void GetTileInfos(RenderOperationGroup* pRootGroup, RenderOperationNode* pNode, const wstring& strDir, map<wstring, S3MBTileInfo*>& mapInfo);
		void SetPagedLODNodeMap(RenderOperationGroup* pGroup, const wstring& strDir, map<wstring, S3MBTileInfo*>& mapInfo);
		void GetGroupBoundingBox(RenderOperationGroup* pGroup, BoundingBox& boundingBox, map<wstring, S3MBTileInfo*>& mapInfo);
		void GetPagedLODBoundingBox(RenderOperationPagedLOD* pPagedLOD, BoundingBox& boundingBox, map<wstring, S3MBTileInfo*>& mapInfo);

	public:
		// ����
		wstring m_strName;
		// RootTile����Ϣ
		S3MBTileInfo* m_pRootTileInfo;
		// LOD�������
		int m_nLODCount;
		// Tile������
		int m_nTileCount;
	};

	class S3MB_API S3MBPagedLODTree
	{
	public:
		S3MBPagedLODTree();
		~S3MBPagedLODTree();

		// ���ļ�
		bool ReadFile(const wstring& path);

		// д�ļ�
		bool WriteFile(const wstring& path);

	public:
		// ����/��ȡTile�����ṹ
		void SetTileTree(S3MBTileTree* pTree, bool bOwn = false);
		const S3MBTileTree* GetTileTree() const;

	private:
		// ��ȡ�ռ��������ṹ
		bool ReadTileTree(const wstring& dir, JsonValue& jsonFile);
		// ��ȡǶ���ŵ��ļ�
		bool ReadNestedFile(const wstring& path, vector<S3MBTileInfo*>& vecInfo);
		// ��ȡTile��Ϣ
		bool ReadTileInfo(const wstring& dir, JsonValue& jsonInfo, S3MBTileInfo*& pInfo);

		// �ռ�������һ�����ļ������
		bool WriteWholeFile(const wstring& path);
		bool WriteTileInfo(S3MBTileInfo* pInfo, JsonValue& jsonTree);

	private:
		S3MBTileTree* m_pTileTree;
		bool m_bOwnTileTree;

		// ��Χ��ʹ��OBB����AABB
		bool m_bUseOBB;
	};
}

#endif