#if !defined(S3MBTOOLS_H__028B6316_FE68_40F4_8803_836609995FC3__INCLUDED_)
#define S3MBTOOLS_H__028B6316_FE68_40F4_8803_836609995FC3__INCLUDED_

#pragma once
#include "JsonValue.h"
#include "Material.h"
#include "MemoryStream.h"
#include "Shell.h"
#include "Skeleton.h"
#include "Texture.h"
#include <fstream>
#include <iostream>
#include "BoundingBox.h"
#include "DracoTool.h"

namespace S3MB
{
	// ѹ������
	class S3MB_API SkeletonCompressParam
	{
	public:
		SkeletonCompressParam()
		{
			m_svTag = SV_Standard;
			m_nCompressOption = 0;
		};
		SkeletonCompressParam(DracoCompressParam& dracoParam)
		{
			m_svTag = SV_DracoCompressed;
			m_dracoParam = dracoParam;
			m_nCompressOption = 0;
		};
		SkeletonCompressParam& operator=(const SkeletonCompressParam& cm)
		{
			m_svTag = cm.m_svTag;
			m_nCompressOption = cm.m_nCompressOption;
			m_dracoParam = cm.m_dracoParam;
			return *this;
		};
	public:
		// S3MBVertexTag
		S3MBVertexTag m_svTag;
		// ѹ������
		int m_nCompressOption;
		// SV_DracoCompressed ʱʹ��
		DracoCompressParam m_dracoParam;
	};


	class S3MB_API S3MBTools
	{
	public:
		// ����S3MB������
		static bool LoadStreamDataFromStream(MemoryStream& dataStream, MemoryStream& streamUnZipped, MemoryStream& streamShell, MemoryStream& streamSkeleton, 
			MemoryStream& streamTexture, MemoryStream& streamIDInfo, wstring& strJsonMaterials, wstring& strExtensions, float fVersion = S3MB_VERSIONV3_0_1);
		// ��ѹS3MB�ļ������ͷ�ѹ�����ڴ�
		static bool UnZipData(MemoryStream& streamUnZipped, unsigned char*& pZippedData, unsigned int nZippedSize);
		static bool UnZipData(MemoryStream& streamUnzipped, unsigned int& nUnZipSize, unsigned char*& pZippedData, unsigned int& nZippedSize);

		// ���عǼ���Ϣ
		static void LoadSkeleton(MemoryStream& streamSkeleton, std::map<wstring, Skeleton*>& mapSkeleton, float fVersion = S3MB_VERSIONV3_0_1);
		static bool LoadSkeletonData(MemoryStream& streamSkeleton, VertexDataPackage*& pVertexDataPackage, vector<IndexPackage*>& arrIndexPackage, float fVersion = S3MB_VERSIONV3_0_1);

		// ���ز���ѹDraco
		static bool  LoadDraco(MemoryStream &stream, \
			VertexDataPackage*& pVertexDataPack, std::vector<IndexPackage*>& arrIndexPackage, float fVersion = S3MB_VERSIONV3_0_1);

		// �ֽڶ���
		// isRead ָʾ�Ƿ�Ϊ��ȡ��
		static void StreamAlign(MemoryStream& stream, bool isRead);
		// ���ض�����Ϣ
		static bool LoadVertex(MemoryStream& streamSkeleton, VertexDataPackage*& pVertexDataPackage);
		// ���ط�����Ϣ
		static bool LoadNormal(MemoryStream& streamSkeleton, VertexDataPackage*& pVertexDataPackage);
		// ����������Ϣ
		static bool LoadTangent(MemoryStream& streamSkeleton, VertexDataPackage*& pVertexDataPackage);
		// ���ض�����ɫ
		static bool LoadVertexColor(MemoryStream& streamSkeleton, VertexDataPackage*& pVertexDataPackage);
		// ��������������Ϣ
		static bool LoadTextureCoords(MemoryStream& streamSkeleton, VertexDataPackage*& pVertexDataPackage);
		// ����ʵ������Ϣ
		static bool LoadInstanceInfo(MemoryStream& streamSkeleton, VertexDataPackage*& pVertexDataPackage, float fVersion = S3MB_VERSIONV3_0_1);
		// �ж��Ƿ���ʵ�������ζ���
		static bool IsInstanceBatch(VertexDataPackage* pVertexDataPackage);


		// ���ز�����Ϣ
		static void LoadMaterial(wstring strJsonMaterials, std::map<wstring, Material*>& mapMaterial,float fVersion);
		// ͨ��Json���ز�����Ϣ
		static void LoadMatFromJson(JsonValue& jsonMaterial, wstring& strMaterialName, Technique* pTechnique);
		static void LoadMatFromJsonV3(JsonValue& jsonMaterial, wstring& strMaterialName, Technique* pTechnique);
		// ͨ��Json����PBR������Ϣ
		static void LoadPBRFromJson(JsonValue& jsonPBR, PBRParams*& pPBR);
		static void LoadPBRFromJsonV3(JsonValue& jsonPBR, PBRParams*& pPBR);
		// ͨ��Json��������Ԫ
		static void LoadTUSFromJson(JsonValue& jsonTexture, TextureUnitState* pTextureUnitState);
		static void LoadTUSFromJsonV3(JsonValue& jsonTexture, TextureUnitState* pTextureUnitState);

		static MaterialType MaterialTypeFromString(wstring strType);

		static CullingMode CullModeFromString(wstring strType);
		static CullingMode CullModeFromStringV3(wstring strType);

		static AlphaMode AlphaModeFromString(wstring strType);
		static AlphaMode AlphaModeFromStringV3(wstring strType);

		static void AddressModeFromJson(JsonValue& jsonAddMode, TextureUnitState* pTextureUnitState);

		// ����������Ϣ
		static void LoadTexture(MemoryStream& streamTexture, std::map<wstring, TextureDataInfo*>& mapTexture, float fVersion);
		static void LoadTextureData(MemoryStream& streamTexture, TextureData* pTextureData, float fVersion);
		static void ProcessTextureData(TextureData* pTextureData, TextureCompressType nCompressType, bool bGenerateMipmap = true);
		static void ToStandardType(TextureCompressType& eCompressType, PixelFormat& eFormat, unsigned nCompressType, unsigned nFormat);

		// ����shell��Ϣ
		static void LoadShell(MemoryStream& streamShell, RenderOperationGroup* pROGroup, float fVersion = S3MB_VERSIONV3_0_1);
		// �ж��Ƿ��ǵ�����Geode��RO������PagedLODs�¿ɵ�������Geode����ʾ�������²�ڵ㣩
		static bool IsSingleGeode(MemoryStream& stream);
		static void LoadSingleGeode(RenderOperationGroup* pROGroup, RenderOperationGeode* pGeode, MemoryStream& stream, float fVersion = S3MB_VERSIONV3_0_1);
		
		static void LoadPagedLOD(RenderOperationGroup* pROGroup, RenderOperationPagedLOD* pROPagedLOD, MemoryStream& stream, float fVersion = S3MB_VERSIONV3_0_1);
		
		static void LoadGeode(RenderOperationGroup* pROGroup, RenderOperationGeode* pGeode, MemoryStream& stream);

		// ����IDInfo
		static void LoadIDInfo(std::map<wstring, Skeleton*>& mapSkeleton, MemoryStream& streamIDInfo,float fVersion);

		// ����shell��Ϣ
		static void SaveShell(RenderOperationGroup* pROGroup, MemoryStream& stream, float fVersion = S3MB_VERSIONV3_0_1);
		static void SavePagedLOD(RenderOperationPagedLOD* pROPagedLOD, MemoryStream& stream, float fVersion = S3MB_VERSIONV3_0_1);
		static void SaveGeode(RenderOperationGeode* pROGeode, MemoryStream& stream);

		// ����Ǽ���Ϣ
		static void SaveSkeleton(std::map<wstring, Skeleton*>& mapSkeleton, MemoryStream& streamSkeleton, SkeletonCompressParam& SkeletonCompParam, float fVersion = S3MB_VERSIONV3_0_1);
		// �Ǽ����ݱ��������
		static bool SaveSkeletonData(VertexDataPackage*& pVertexDataPackage, \
			vector<IndexPackage*>& arrIndexPackage, MemoryStream& streamSkeleton, SkeletonCompressParam& SkeletonCompParam, float fVersion = S3MB_VERSIONV3_0_1);
		
		static bool SaveDraco(VertexDataPackage* pVertexDataPack, std::vector<IndexPackage*>& arrIndexPackage, \
			const DracoCompressParam& dracoParam, MemoryStream &stream, float fVersion);
		
		// ���涥����Ϣ
		static bool SaveVertex(VertexDataPackage* pVertexDataPack, MemoryStream& stream);
		// ���淨����Ϣ
		static bool SaveNormal(VertexDataPackage* pVertexDataPack, MemoryStream& stream);
		// ����������Ϣ
		static bool SaveTangent(VertexDataPackage* pVertexDataPack, MemoryStream& stream);
		// ���涥����ɫ
		static bool SaveVertexColor(VertexDataPackage* pVertexDataPack, MemoryStream& stream);
		// ������������
		static bool SaveTextureCoords(VertexDataPackage* pVertexDataPack, MemoryStream& stream);
		// ����ʵ������Ϣ
		static bool SaveInstanceInfo(VertexDataPackage* pVertexDataPack, MemoryStream& stream);

		// ���������Ϣ
		static void SaveMaterial(std::map<wstring, Material*>& mapMaterial, JsonValue& jsonMaterials, float fVersion);
		static void MaterialToJson(Material* pMaterial, JsonValue& jsonMaterial, float fVersion);
		// pMaterialתjson��Ϣ
		static void TechniqueToJson(const wstring strMaterialName, Technique* pTechnique, JsonValue& jsonContent,float fVersion);
		static wstring MaterialTypeToString(MaterialType emType);
		static wstring CullModeToString(CullingMode emType);
		// PRBתjson��Ϣ
		static void PBRToJson(PBRParams* pPBR, JsonValue& jsonPBR);
		static wstring AlphaModeToString(AlphaMode emType);
		// pTextureUnitStateתjson��Ϣ
		static void TUSToJson(TextureUnitState* pTextureUnitState, JsonValue& jsonMaterial);
		static void AddressModeToJson(TextureUnitState* pTextureUnitState, JsonValue& jsonAddMode);

		static void SaveTextures(std::map<wstring, TextureDataInfo*>& mapTexture,MemoryStream& streamTexture,
			unsigned int nCompressType, bool bTextureChange = true, bool bGenerateMipmap = true);
		// �������ݱ���
		static void SaveTextureData(TextureData* pTextureData, \
			MemoryStream& streamTexture, unsigned int nCompressType, bool bIsChangeTexture = true, bool bGenerateMipmap = true);
		// ����ѹ������
		static void ProcessTextureData(TextureData* pTextureData, unsigned int nCompressType, bool bGenerateMipmap = true);

		// ����IDInfo
		static bool SaveIDInfo(std::map<wstring, Skeleton*>& mapSkeleton, MemoryStream& m_streamIDInfo);

		// ��Χ�еı��������
		static void LoadBoundingBox(MemoryStream& stream, BoundingBox& bbox);
		static void SaveBoundingBox(const BoundingBox& bbox, MemoryStream& stream);

		// �����Χ�еı��������
		static void SaveOBB(const OrientedBoundingBox& bBox, MemoryStream& streamBBox);
		static void LoadOBB(MemoryStream& streamBBox, OrientedBoundingBox& bBox);
		// ���������ļ�
		static bool SaveStreamData2File(const wstring strDestFilePath, \
			MemoryStream& streamShell, MemoryStream& streamSkeleton, \
			wstring& strJsonMaterials, MemoryStream& streamTexture, \
			bool bHasIDInfo, MemoryStream& streamIDInfo, wstring& strExtensions, float fVersion);

		private:
			static bool CanUseDraco(VertexDataPackage* pVertexPack, std::vector<IndexPackage*> vecIndexPack);

			static void LoadStream(MemoryStream& streamSrc, MemoryStream& streamDst);
			static void SaveStream(MemoryStream& streamDst, MemoryStream& streamSrc);

			// ���������ı��������
			static void AnimationsToJson(RenderOperationPagedLOD* pROPagedLOD, JsonValue& jsonAnimations);
			static void AnimationsFromJson(JsonValue& jsonAnimations, RenderOperationPagedLOD*& pROPagedLOD);

			// nodeתjson��Ϣ
			static void NodeToJson(const std::vector<Node*>& vecNode, JsonValue& jsonNodes);
			static void NodeFromJson(JsonValue& jsonNodes, std::vector<Node*>& vecNode);

			// skinתjson��Ϣ
			static void SkinToJson(const std::vector<Skin*>& vecSkin, JsonValue& jsonSkins);
			static void SkinFromJson(JsonValue& jsonSkins, std::vector<Skin*>& vecSkin);

			// ����תjson��Ϣ
			static void AnimationToJson(const std::vector<Animation*>& vecAnimationState, \
				const std::vector<std::map<wstring, AnimationCurve*> >& vecAnimationCurve, JsonValue& jsonAnimationContents);
			static void AnimationFromJson(JsonValue& jsonAnimationContents, \
				std::vector<Animation*>& vecAnimationState, std::vector<std::map<wstring, AnimationCurve*> >& vecAnimationCurve);

			// �������Ե���չ
			static bool LoadVertexAttributeExtension(MemoryStream& stream, VertexDataPackage* pVertexDataPack);
			static bool SaveVertexAttributeExtension(VertexDataPackage* pVertexDataPack, MemoryStream& stream);

			// ��������
			static bool LoadIndexPackages(MemoryStream& stream, vector<IndexPackage*>& vecIndexPackage, float fVersion = S3MB_VERSIONV3_0_1);
			static bool SaveIndexPackages(vector<IndexPackage*>& vecIndexPackage, MemoryStream& stream, float fVersion = S3MB_VERSIONV3_0_1);
	};
}

#endif
