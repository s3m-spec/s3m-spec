#if !defined(THREEDTILESPARSER_H__5D64F3B8_6A6C_4023_AB97_3F7733A44AB9__INCLUDED_)
#define THREEDTILESPARSER_H__5D64F3B8_6A6C_4023_AB97_3F7733A44AB9__INCLUDED_

#pragma once
#include "stdafx.h"
#include "BoundingSphere.h"
#include "Common.h"
#include "GLTFContent.h"
#include "Palette.h"
#include "Point3D.h"
#include "S3MBEnums.h"
#include "S3MBLayerInfos.h"
#include "Vector.h"

#include "document.h"
#include "istreamwrapper.h"
#include "prettywriter.h"
#include "stringbuffer.h"

#include <map>
#include <string>
#include <vector>

namespace S3MB
{
	struct BatchIDInfo
	{
		int m_nCount;
		int m_nOffset;
		BatchIDInfo()
		{
			m_nCount = 0;
			m_nOffset = 0;
		}
	};

	class STK_API ThreeDTilesParser
	{
	public:
		ThreeDTilesParser();
		~ThreeDTilesParser();

		void SetIsNEU(bool bNEU);
		bool GetIsNEU() const;

		void SetPosCenter(const Point3D& pos);
		const Point3D& GetPosCenter() const;

		const Point3D& GetPosExtract() const;

		const Matrix4d& GetGlobalMat() const;

		void SetGLTFNode(unsigned int i, GLTFTreeNode* pNode);
		const std::vector<GLTFTreeNode*>& GetGLTFNodes() const;

		void ResetFieldInfos();
		const S3MBFieldInfos& GetFieldInfos() const;

		void SetBatchIDNum(unsigned int nNum);
		unsigned int GetBatchIDNum() const;

		void AddFeature(Feature* pFeature);
		const std::vector<Feature*>& GetFeatures() const;
		void ClearFeatures();

		bool GetIsAddMode() const;

		bool GetIsDistanceChange() const;

		bool GetIsValidPosition() const;

		void SetTextureCompressType(TextureCompressType nType);
		TextureCompressType GetTextureCompressType() const;

		void SetBufferSize(unsigned int nSize);
		unsigned int GetBufferSize() const;

		const I3DMIDInfo& GetI3DMInfo() const;

		void AddAttributeIndexInfo(const std::wstring& strKey, GLTFAttributeIndexInfo& info);
		const std::map<std::wstring, std::vector<GLTFAttributeIndexInfo> >& GetAttributeIndexInfos() const;

#pragma region glTF 1.0
		const std::map<std::wstring, std::vector<std::wstring> >& GetMeshSets_V1();
		const GLTFMesh& GetMesh(const std::wstring& strKey);
		const Matrix4d& GetMeshToLocalViewMatrix(const std::wstring& strKey);
		const GLTFAccessor& GetAccessor(const std::wstring& strKey);
		const GLTFBufferView& GetBufferView(const std::wstring& strKey);
		const GLTFMaterial& GetMaterial(const std::wstring& strKey);
		const GLTFTexture& GetTexture(const std::wstring& strKey);
		const GLTFImage& GetImage(const std::wstring& strKey);
#pragma endregion

#pragma region glTF 2.0
		const std::map<unsigned int, std::vector<unsigned int> >& GetMeshSets();
		const GLTFMesh& GetMesh(unsigned int nKey);
		const Matrix4d& GetMeshToLocalViewMatrix(unsigned int nKey);
		const GLTFAccessor& GetAccessor(unsigned int nKey);
		const GLTFBufferView& GetBufferView(unsigned int nKey);
		const GLTFBuffer& GetBuffer(unsigned int nKey);
		const std::vector<GLTFMaterial>& GetMaterials(unsigned int nKey);
		const GLTFTexture& GetTexture(unsigned int nKey);
		const GLTFImage& GetImage(unsigned int nKey);
#pragma endregion

		//! \brief ����Tileset
		bool ParseTileset(std::wstring strPath, GLTFTreeNode* pParentNode, int nLod, Matrix4d matParent);
		//! \brief ����ת������
		void ComputeTransMat();
		//! \brief ����ʵ������Ϣ
		bool ParseInstanceInfo(rapidjson::Document& doc, unsigned char* buffer);
		void ResetInstanceInfo();
		// ��GLTF�õ��������ݰ���������תԲ��任
		void ConvertPoint(GLTFTreeNode* pNode, float* pPosData, const unsigned int nVertexCount, const unsigned int nPosDim, const Matrix4d matLocal, const Point3D& pntCenter);

		void Clear();

		bool ParseGLTF_V1(unsigned char*& pBuffer, unsigned int jsonLength, std::wstring strOutputDir, Point3D& pntCenter);
		bool ParseGLTF(GLTFTreeNode* pNode, unsigned char*& buffer, unsigned int jsonLength, std::wstring strOutDir, Point3D& ptTileCenter);

	private:
		//! \brief ����root
		bool ParseRoot(rapidjson::Document& doc, std::wstring strDir, GLTFTreeNode* pParentNode, int nLod, Matrix4d matParent);
		bool ParseInnerRoot(rapidjson::Value& doc, std::wstring strDir, GLTFTreeNode* pParentNode, int nLod, Matrix4d matParent);
		bool ParseChildren(rapidjson::Value& value, std::wstring strDir, GLTFTreeNode* pParentNode, int nLod, Matrix4d matParent);

#pragma region GLTF1.0
		bool ParseScene_V1(rapidjson::Document& doc);
		bool ParseNode_V1(rapidjson::Document& doc, const char* nodeName);
		void ProcessGLTFNode_V1(rapidjson::Value& nodes, const char* nodeName, Matrix4d& matGeode, std::wstring parentName);
		bool ParseMesh_V1(rapidjson::Document& doc);
		bool ParseAccessors_V1(rapidjson::Document& doc);
		bool ParseBufferViews_V1(rapidjson::Document& doc);
		bool ParseMaterials_V1(rapidjson::Document& doc);
		bool ParseTextures_V1(rapidjson::Document& doc);
		bool ParseImages_V1(rapidjson::Document& doc);
		bool ParseBuffers_V1(rapidjson::Document& doc);
		bool ParseExtensions_V1(rapidjson::Document& doc, Point3D& center);
		void* GetAttributeData_V1(unsigned char* &buffer, std::wstring &strName, int & nDim);
#pragma endregion

#pragma region GLTF2.0
		bool ParseNode(rapidjson::Document& doc);
		void ProcessGLTFNode(rapidjson::Value& value, int index, Matrix4d& matGeode, unsigned int parentIndex);
		bool ParseMesh(rapidjson::Document& doc);
		bool ParseAccessors(rapidjson::Document& doc);
		bool ParseBufferViews(rapidjson::Document& doc);
		bool ParseMaterials(rapidjson::Document& doc);
		bool ParseTextures(rapidjson::Document& doc);
		bool ParseImages(rapidjson::Document& doc);
		bool ParseBuffers(rapidjson::Document& doc);
#pragma endregion

		//! \brief �ݹ����ת������
		void RecurComputerRelatMat(GLTFTreeNode* pNode);
		void ProcessTextureCompressType(GLTFImage gltfImage);
		void DealGLTFFilePath(GLTFImage& gltfImage, std::wstring strFilePath);
		Vector3d GetDecodeNormal(unsigned short normalX, unsigned short normalY);

	private:
		// �û�ѡ���3dtiles����������orԲ��
		bool m_bIsNEU;
		//! \brief ȫ���ڵ�
		std::vector<GLTFTreeNode*> m_vecGLTFNodes;
		//! \brief ���ڵ������
		int m_nRootCount;
		//�Ƿ��в��������
		bool m_bValidPosition;
		//! \brief ����������
		AxisUpType m_nAxisUpType;
		//! \brief ��γ���µĲ����
		Point3D m_posCenter;
		Point3D m_posExtract;
		//! \brief ���ݵİ�Χ��
		BoundingSphere m_boundingSphere;
		//! \brief ����
		std::map<std::wstring, int> m_mapFieldIndex;
		std::vector<S3MBFieldInfo> m_vecFieldInfo;
		S3MBFieldInfos m_fieldInfos;
		std::vector<Feature*> m_vecFeature;
		// �滻����׷��ģʽ
		bool m_bAddMode;
		//! \brief �ⲿjson����(�����)
		Matrix4d m_matGlobalMat;
		Matrix4d m_matENUWorldView;
		Matrix4d m_matSphereWorldView;
		// Normal or Batch
		bool m_bIsNormal;
		//! \brief lod����
		int m_nLodNum;
		//! \brief �Ƿ��ǵ���
		bool m_isPnts;
		std::wstring m_strExt;
		//�л�ģʽ
		bool m_bIsDistanceChange;
		//�ڵ����
		unsigned int m_nTotalNum;
		//! \brief �Ѵ����BatchID�ĸ���
		unsigned int m_nBatchIDNum;
		//����ѹ��ö��
		TextureCompressType m_textureCompressType;

		unsigned int m_nBufferSize;

		I3DMIDInfo m_i3dmInfo;

		std::map<std::wstring, std::vector<GLTFAttributeIndexInfo> > m_mapAttributeIndexInfos;

#pragma region GLTF1.0
		std::map<std::wstring, Matrix4d> m_mapMeshTOLocalView_V1;
		std::map<std::wstring, std::vector<std::wstring> > m_mapMeshSet_V1;
		std::map<std::wstring, GLTFMesh> m_mapMeshs_V1;
		std::map<std::wstring, GLTFAccessor> m_mapAccessors_V1;
		std::map<std::wstring, GLTFBufferView> m_mapBufferViews_V1;
		std::map<std::wstring, GLTFBuffer> m_mapBuffers_V1;
		std::map<std::wstring, GLTFMaterial> m_mapMaterials_V1;
		std::map<std::wstring, GLTFTexture> m_mapTextures_V1;
		std::map<std::wstring, GLTFImage> m_mapImages_V1;
#pragma endregion

#pragma region GLTF2.0
		std::map<unsigned int, Matrix4d> m_mapMeshToLocalView;
		std::map<unsigned int, std::vector<unsigned int> > m_mapMeshSet;
		std::map<unsigned int, GLTFMesh> m_mapMeshs;
		std::map<unsigned int, GLTFAccessor> m_mapAccessors;
		std::map<unsigned int, GLTFBufferView> m_mapBufferViews;
		std::map<unsigned int, GLTFBuffer> m_mapBuffers;
		std::map<unsigned int, std::vector<GLTFMaterial> > m_mapMaterials;
		std::map<unsigned int, GLTFTexture> m_mapTextures;
		std::map<unsigned int, GLTFImage> m_mapImages;
#pragma endregion
	};
}

#endif