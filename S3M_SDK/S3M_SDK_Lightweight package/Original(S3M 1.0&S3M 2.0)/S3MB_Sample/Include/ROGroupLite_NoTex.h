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
		int mtlID;
		std::vector<float> verts;
		std::vector<unsigned int> indexs;
		std::vector<float> normals;
		std::vector<float> texCoords;
		std::vector<float> colors;
	};
	static RenderOperationGroup* CreateROGroupLite();

	//! \brief ����һ��ģ�͹Ǽ�����
	static MeshParamInfo CreateMeshData();

	//! \brief ���ݶ�ȡ�Ķ�����Ϣ����geometry����
	static Geometry* CreateGeometry(MeshParamInfo& meshInfo);

	//! \brief ��������
	static TextureData* CreateTextureData();

	//! \brief ��������
	static Material* CreateMaterial(wstring textureDataName);
};
