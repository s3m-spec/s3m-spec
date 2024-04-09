#pragma once
#include "Shell.h"
using namespace std;
using namespace S3MB;
class ROGroupLite
{
public:
	struct MeshParamInfo
	{
		wstring strID;
		int LodID;
		// ������Ϣ
		std::vector<float> verts;
		// ����������Ϣ
		std::vector<unsigned int> indexs;
		// ������Ϣ
		std::vector<float> normals;
		// uv
		std::vector<float> texCoords;
		// 
		std::vector<float> colors;
	};

	struct TexInfo
	{
		wchar_t* texPath;
		int coordIndex;
		void* otherData;
		Matrix4d texMatrix;
		TexInfo():texPath(nullptr),coordIndex(0),otherData(nullptr), texMatrix(Matrix4d::IDENTITY) {}
	};

	typedef struct MtlPbrData
	{
		wchar_t * name;
		PBRParams::AlphaMode alphaMode;
		float alphaCutOff;
		TexInfo baseTexMap;
		Vector4d baseColorFactor;
		TexInfo MetallicRoughMap;
		float metallicFactor;
		float RoughnessFactor;
		TexInfo OcclusionMap;
		TexInfo EmissionMap;
		Vector3d EmissionFactor;
		TexInfo NormalMap;
		MtlPbrData():name((wchar_t*)U("default")),alphaMode(PBRParams::AlphaMode::PBRAM_OPAQUE),alphaCutOff(0.0f),baseColorFactor(1,1,1,1),
			metallicFactor(0),RoughnessFactor(0),EmissionFactor(0,0,0){}
	} MtlData;
	static void sampleV1(float fVersion);

	static void sampleV2(float fVersion);

	static RenderOperationGroup* CreateROGroupLiteV1(int lodId, wstring texturePath);

	static RenderOperationGroup* CreateROGroupLiteV2(int lodId, bool isV2 = false);

	static void createTextureDataInfo(const wstring&  mtldataPath, RenderOperationGroup* pGroup);
	//! \brief ͨ��MtlData��������
	static Material* CreateMaterial(MtlData* mtldatae);

	static void CreateTextureUnitState(int& iPathFlag, const int& nCoordIdx, int& TextureIndex, int& TextureCoordIndex, Pass* pPass, const wstring& textureDataName, const Matrix4d& texMatrix);
	//! \brief ����һ��ģ�͹Ǽ�����
	static MeshParamInfo CreateMeshData(int lodId);

	static MtlData* CreateMtlData();

	//! \brief ���ݶ�ȡ�Ķ�����Ϣ����geometry����
	static Geometry* CreateGeometry(MeshParamInfo& meshInfo, bool isV2 = false);

	//! \brief ��������
	static TextureData* CreateTextureData(wstring texturePath);

	//! \brief ��������
	static Material* CreateMaterial(wstring textureDataName);
};
