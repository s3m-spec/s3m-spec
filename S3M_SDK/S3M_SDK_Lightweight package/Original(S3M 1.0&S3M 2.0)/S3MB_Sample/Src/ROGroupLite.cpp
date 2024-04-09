#include "ROGroupLite.h"
#include "ImageOperator.h"
#include <processenv.h>
#include <S3MBTools.h>
#include "S3MBReader.h"
#include "S3MBWriter.h"
#include "S3MBSCP.h"
#include "S3MBAttributeReader.h"

void ROGroupLite::sampleV1(float fVersion)
{
	///************************************************************************/
	//*          1.����һ�����������ݲ�д��S3MB�ļ�
	///************************************************************************/
	RenderOperationGroup* pGroup;
	//����������������PBR���ʵĶ������

	pGroup = ROGroupLite::CreateROGroupLiteV1(1, U("./1.png"));

	S3MBWriter m_S3MBWriter;
	pGroup->ReComputeBoundingBox();//����Χ��/�򲻶Ի��ް�Χ��/��ʱ�ɵ���
	m_S3MBWriter.SetROGroup(pGroup);
	m_S3MBWriter.SetIsChangeTexture(true, true);//DXTѹ��
	wstring strS3mbFile = U("./cube1.s3mb");
	m_S3MBWriter.SetFilePath(strS3mbFile);
	m_S3MBWriter.SetVersion(fVersion);
	m_S3MBWriter.Save(0);
	m_S3MBWriter.Clear();
	delete pGroup;

	pGroup = ROGroupLite::CreateROGroupLiteV1(2, U("./3.jpg"));
	pGroup->ReComputeBoundingBox();
	m_S3MBWriter.SetROGroup(pGroup);
	m_S3MBWriter.SetIsChangeTexture(true, true);//DXTѹ��
	strS3mbFile = U("./cube2.s3mb");
	m_S3MBWriter.SetFilePath(strS3mbFile);
	m_S3MBWriter.Save(0);
	delete pGroup;
	m_S3MBWriter.Clear();

	pGroup = ROGroupLite::CreateROGroupLiteV1(3, U("./5.jpg"));
	pGroup->ReComputeBoundingBox();
	m_S3MBWriter.SetROGroup(pGroup);
	m_S3MBWriter.SetIsChangeTexture(true, true);//DXTѹ��
	strS3mbFile = U("./cube3.s3mb");
	m_S3MBWriter.SetFilePath(strS3mbFile);
	//m_S3MBWriter.Save(0);
	m_S3MBWriter.Save(0);
	m_S3MBWriter.Clear();
	///************************************************************************/
	//*        2:ͨ��ָ����s3mb�ļ�����ȡ����Ro��Ϣ�����������                                                                     */
	///************************************************************************/


	S3MBReader m_S3MBReaderRo;
	wstring strS3MBFileSrc = U("./cube1.s3mb");
	m_S3MBReaderRo.SetFilePath(strS3MBFileSrc);
	m_S3MBReaderRo.ReadS3MBAsROGroup();
	m_S3MBReaderRo.OutputGeometryInfoToConsole();
	pGroup = m_S3MBReaderRo.GetRenderOperationGroup();

	///************************************************************************/
	//*       3:ͨ��ָ����s3mb�����ļ�����json�ļ���������ȡs3md�����ļ�����������ֶμ����Ӧֵ                                                                */
	///************************************************************************/

	wstring strS3MBFolderSrc = U("../../../SampleData/attribute/attribute.json");
	S3MBAttributeReader::ReadAttribute(strS3MBFolderSrc);


	//////////////////////����SCP�ļ�//////////////////
	//�����
	Point3D m_Position(118, 39, 0);
	Rect2D geoBounds(0, 0, 0, 0);
	int epsgCode = 4326;
	bool isDegree = true;

	BoundingBox m_Box;
	m_Box.SetNULL();
	for (int i = 0; i < pGroup->GetNumChildren(); i++)
	{
		if (NULL != pGroup->GetChild(i)->AsGeode())
		{
			m_Box.Merge(((RenderOperationGeode*)(pGroup->GetChild(i)))->GetBoundingBox());
		}
	}
	///����SCP�ļ�//////////////////
	S3MBSCP* pS3MBSCP = new S3MBSCP();
	pS3MBSCP->m_fVersion = fVersion;
	pS3MBSCP->m_strAsset = U("SuperMap");

	pS3MBSCP->m_pntPosition = m_Position;
	pS3MBSCP->m_rcGeoBounds = geoBounds;
	pS3MBSCP->m_prjCoordEPSG = epsgCode;
	pS3MBSCP->m_bIsDegree = isDegree;
	pS3MBSCP->m_dbHeightMax = m_Box.GetMax().z + m_Position.z;
	pS3MBSCP->m_dbHeightMin = m_Box.GetMin().z + m_Position.z;
	//pS3MBSCP->m_enDataType = SDT_ObliquePhoto;

	pS3MBSCP->m_mapExtensions[U("s3m:FileType")] = U("OSGBCacheFile");
	pS3MBSCP->m_mapExtensions[U("s3m:RenderMode")] = U("Normal");
	pS3MBSCP->m_mapExtensions[U("s3m:TileSplitType")] = U("LOCAL");

	std::vector<wstring> vecRootFiles;//�����
	std::vector<BoundingBox> vecRootBoundboxs;//������ӦBoundingBox
	vecRootFiles.push_back(U("cube1.s3mb"));
	vecRootBoundboxs.push_back(m_Box);

	pS3MBSCP->SetTiles(vecRootFiles, vecRootBoundboxs);
	wstring strOutputFilePath = StringHelper::GetAbsolutePath(strS3MBFileSrc);
	wstring strFilePatch = StringHelper::GetAbsolutePath(strOutputFilePath, U("../sampleV1.scp"));
	pS3MBSCP->SaveToJsonFile(strFilePatch);
	delete pS3MBSCP;
	pS3MBSCP = NULL;
}

void ROGroupLite::sampleV2(float fVersion)
{	
	///************************************************************************/
	//*          1.����һ�����������ݲ�д��S3MB�ļ�
	///************************************************************************/
	
	RenderOperationGroup* pGroup;
	pGroup = ROGroupLite::CreateROGroupLiteV2(1,true);
	S3MBWriter m_S3MBWriter;
	pGroup->ReComputeBoundingBox();//����Χ��/�򲻶Ի��ް�Χ��/��ʱ�ɵ���
	m_S3MBWriter.SetROGroup(pGroup);
	m_S3MBWriter.SetIsChangeTexture(true, true);//DXTѹ��
	wstring strS3mbFileWrite = U("./sampleV2.s3mb");
	m_S3MBWriter.SetFilePath(strS3mbFileWrite);
	m_S3MBWriter.SetVersion(fVersion);//���ð汾��Ϣ
	m_S3MBWriter.Save(0);
	m_S3MBWriter.Clear();


	
	///************************************************************************/
	//*        2:ͨ��ָ����s3mb�ļ�����ȡ����Ro��Ϣ�����������                                                                     */
	///************************************************************************/
	S3MBReader m_S3MBReaderRo;
	wstring strS3MBFileRead = U("./sampleV2.s3mb");
	m_S3MBReaderRo.SetFilePath(strS3MBFileRead);
	m_S3MBReaderRo.ReadS3MBAsROGroup();
	m_S3MBReaderRo.OutputGeometryInfoToConsole();
	pGroup = m_S3MBReaderRo.GetRenderOperationGroup();
	m_S3MBReaderRo.Clear();


	//////////////////////����SCP�ļ�//////////////////
	//�����
	Point3D m_Position(118, 39, 0);
	Rect2D geoBounds(0, 0, 0, 0);
	int epsgCode = 4326;
	bool isDegree = true;

	BoundingBox m_Box;
	m_Box.SetNULL();
	for (int i = 0; i < pGroup->GetNumChildren(); i++)
	{
		if (NULL != pGroup->GetChild(i)->AsGeode())
		{
			m_Box.Merge(((RenderOperationGeode*)(pGroup->GetChild(i)))->GetBoundingBox());
		}
	}
	///����SCP�ļ�//////////////////
	S3MBSCP* pS3MBSCP = new S3MBSCP();
	pS3MBSCP->m_fVersion = fVersion;
	pS3MBSCP->m_strAsset = U("SuperMap");

	pS3MBSCP->m_pntPosition = m_Position;
	pS3MBSCP->m_rcGeoBounds = geoBounds;
	pS3MBSCP->m_prjCoordEPSG = epsgCode;
	pS3MBSCP->m_bIsDegree = isDegree;
	pS3MBSCP->m_dbHeightMax = m_Box.GetMax().z + m_Position.z;
	pS3MBSCP->m_dbHeightMin = m_Box.GetMin().z + m_Position.z;
	//pS3MBSCP->m_enDataType = SDT_ObliquePhoto;

	pS3MBSCP->m_mapExtensions[U("s3m:FileType")] = U("OSGBCacheFile");
	pS3MBSCP->m_mapExtensions[U("s3m:RenderMode")] = U("Normal");
	pS3MBSCP->m_mapExtensions[U("s3m:TileSplitType")] = U("LOCAL");

	std::vector<wstring> vecRootFiles;//�����
	std::vector<BoundingBox> vecRootBoundboxs;//������ӦBoundingBox
	vecRootFiles.push_back(U("sampleV2.s3mb"));
	vecRootBoundboxs.push_back(m_Box);

	pS3MBSCP->SetTiles(vecRootFiles, vecRootBoundboxs);
	wstring strOutputFilePath = StringHelper::GetAbsolutePath(strS3mbFileWrite);
	wstring strFilePatch = StringHelper::GetAbsolutePath(strOutputFilePath, U("../sampleV2.scp"));
	pS3MBSCP->SaveToJsonFile(strFilePatch);
	delete pS3MBSCP;
	pS3MBSCP = NULL;
}

RenderOperationGroup* ROGroupLite::CreateROGroupLiteV1(int lodId, wstring texturePath)
{
	MeshParamInfo info = CreateMeshData(lodId);
	Geometry* pGeometry = CreateGeometry(info);

	//��������
	TextureData* pTextureData = CreateTextureData(texturePath);
	TextureDataInfo* pTextureDataInfo = new TextureDataInfo;
	pTextureDataInfo->m_pTextureData = pTextureData;
	//��������
	Material* pMaterial = CreateMaterial(texturePath);

	RenderOperationGroup* pGroup = new RenderOperationGroup;
	RenderOperationPagedLOD* pPagedLOD = new RenderOperationPagedLOD;
	RenderOperationGeode* pGeode = new RenderOperationGeode;

	//�����������ʣ��Ǽܣ�RenderOperationGeoemtry, UGRenderOperationGeode,UGRenderOperationGroup֮��Ĺ�ϵ
	pGroup->AddTextureData(texturePath, pTextureDataInfo);
	pGroup->AddMaterial(pMaterial->m_strName, pMaterial);
	pGeometry->m_strMaterialName = pMaterial->m_strName;
	pGeometry->m_arrIndexPackage[0]->m_strPassName.push_back(pMaterial->m_strName);
	pGroup->AddGeometry(pGeometry->m_strGeoName, pGeometry);
	pGeode->AddGeometry(pGeometry);
	pGroup->AddChild(pPagedLOD);
	pPagedLOD->AddChild(pGeode);

	pGeode->ComputerBoundingBox();
	BoundingBox bboxObj = pGeode->GetBoundingBox();
	BoundingSphere bSphere(bboxObj);
	pGeode->SetBoudingSphere(bSphere.GetCenter(), bSphere.GetRadius());

	//��Ӧ���л��ļ�,Ŀǰ֧��һ��pagedLodֻ��һ��ģ�ͣ�����¹Ҷ���ļ����򴴽����pagedLod,ÿ����һ���ļ��������л����롣
	if (lodId < 3)
	{
		wstring strLod = to_wstring(lodId + 1);
		wstring strLodFile = U("cube") + strLod + U(".s3mb");
		pPagedLOD->GetFileNames().push_back(strLodFile);
	}
	//Lod�л�ģʽ���л���������Լ����ơ�
	pPagedLOD->SetRangeMode(RangeMode::DISTANCE_FROM_EYE_POINT);
	// ����LOD�任�ľ���
	double nLodDis = MIN(1024, bSphere.m_radius * pow(2.0, 3 - lodId));
	pPagedLOD->GetRanges().push_back(std::vector<std::pair<float, float> >::value_type(0, nLodDis));
	pPagedLOD->SetBoudingSphere(bSphere.m_center, bSphere.m_radius);

	return pGroup;
}
void ROGroupLite::createTextureDataInfo(const wstring&  mtldataPath, RenderOperationGroup* pGroup)
{
	wstring texturePath = U("");
	// ��������
	TextureData* pTextureData;
	TextureDataInfo* pTextureDataInfo = new TextureDataInfo;
	texturePath = mtldataPath;
	pTextureData = CreateTextureData(texturePath);
	pTextureDataInfo->m_pTextureData = pTextureData;
	pGroup->AddTextureData(texturePath, pTextureDataInfo);
}
RenderOperationGroup* ROGroupLite::CreateROGroupLiteV2(int lodId, bool isV2)
{
	// �����Ǽ�
	MeshParamInfo info = CreateMeshData(lodId);
	Geometry* pGeometry = CreateGeometry(info,isV2);

	// ��������
	MtlData* mtldata = CreateMtlData();
	Material* pMaterial = CreateMaterial(mtldata);

	RenderOperationGroup* pGroup = new RenderOperationGroup;
	RenderOperationPagedLOD* pPagedLOD = new RenderOperationPagedLOD;
	RenderOperationGeode* pGeode = new RenderOperationGeode;

	
	wstring texturePath = U("");
	if (mtldata->baseTexMap.texPath != nullptr)
	{	
		// ��������
		createTextureDataInfo(mtldata->baseTexMap.texPath, pGroup);
	}
	if (mtldata->EmissionMap.texPath != nullptr)
	{	
		// ��������
		createTextureDataInfo(mtldata->EmissionMap.texPath, pGroup);
	}
	if (mtldata->MetallicRoughMap.texPath != nullptr)
	{	
		// ��������
		createTextureDataInfo(mtldata->MetallicRoughMap.texPath, pGroup);
	}
	if (mtldata->NormalMap.texPath != nullptr)
	{	
		// ��������
		createTextureDataInfo(mtldata->NormalMap.texPath, pGroup);
	}
	if (mtldata->OcclusionMap.texPath != nullptr)
	{	
		// ��������
		createTextureDataInfo(mtldata->OcclusionMap.texPath, pGroup);
	}
	// �����������ʣ��Ǽܣ�RenderOperationGeoemtry, UGRenderOperationGeode,UGRenderOperationGroup֮��Ĺ�ϵ
	
	//pGroup->AddTextureData(texturePath, pTextureDataInfo);
	pGroup->AddMaterial(pMaterial->m_strName, pMaterial);
	pGeometry->m_strMaterialName = pMaterial->m_strName;
	pGeometry->m_arrIndexPackage[0]->m_strPassName.push_back(pMaterial->m_strName);
	pGroup->AddGeometry(pGeometry->m_strGeoName, pGeometry);
	pGeode->AddGeometry(pGeometry);
	pGroup->AddChild(pPagedLOD);
	pPagedLOD->AddChild(pGeode);

	pGeode->ComputerBoundingBox();
	BoundingBox bboxObj = pGeode->GetBoundingBox();
	BoundingSphere bSphere(bboxObj);
	pGeode->SetBoudingSphere(bSphere.GetCenter(), bSphere.GetRadius());

	//// ��Ӧ���л��ļ�,Ŀǰ֧��һ��pagedLodֻ��һ��ģ�ͣ�����¹Ҷ���ļ����򴴽����pagedLod,ÿ����һ���ļ��������л����롣
	//if (lodId < 3)
	//{
	//	wstring strLod = to_wstring(lodId + 1);
	//	wstring strLodFile = U("������" + strLod + U(".s3mb";
	//	pPagedLOD->GetFileNames().push_back(strLodFile);
	//}
	// Lod�л�ģʽ���л���������Լ����ơ�
	pPagedLOD->SetRangeMode(RangeMode::DISTANCE_FROM_EYE_POINT);
	// ����LOD�任�ľ���
	//double nLodDis = MIN(1024, bSphere.m_radius * pow(2.0, 3 - lodId));
	//pPagedLOD->GetRanges().push_back(std::vector<std::pair<float, float> >::value_type(0, nLodDis));
	pPagedLOD->SetBoudingSphere(bSphere.m_center, bSphere.m_radius);

	return pGroup;
}

ROGroupLite::MtlData* ROGroupLite::CreateMtlData()
{
	MtlData* mtlData = new MtlData;
	mtlData->baseTexMap.coordIndex = 0;
	mtlData->baseTexMap.texPath = (wchar_t*)U("./0.jpg");
	mtlData->NormalMap.texPath = (wchar_t*)U("./NormalMap.jpg");
	mtlData->NormalMap.coordIndex = 0;
	return mtlData;
}

void ROGroupLite::CreateTextureUnitState(int& iPathFlag, const int& nCoordIdx, int& TextureIndex, int& TextureCoordIndex, Pass* pPass, const wstring& textureDataName, const Matrix4d& texMatrix )
{
	TextureIndex = iPathFlag++;
	TextureCoordIndex = nCoordIdx;
	TextureUnitState* pTexUnit = pPass->CreateTextureUnitState();
	// ���ʶ���ͨ����ͼ��������ƹ�����ͼ����
	pTexUnit->m_strTextureName = textureDataName;
	pTexUnit->m_TexModMatrix = texMatrix;
}

Material* ROGroupLite::CreateMaterial(MtlData* mtldata)
{
	Material* pMaterial3D = new Material;
	wstring strMtlName = U("����");
	Technique* pTech = pMaterial3D->CreateTechnique();
	Pass* pPass = pTech->CreatePass();

	pPass->SetPFFMode((PolygonFrontFace)PFF_NONE);

	pPass->m_pPRBMaterial = new PBRMetallicRough;
	PBRMetallicRough* pPbr = (PBRMetallicRough*)pPass->m_pPRBMaterial;
	wstring textureDataName = U("");

	int nPathFlag = 0;
	if (mtldata->baseTexMap.texPath != nullptr)
	{	
		textureDataName = mtldata->baseTexMap.texPath;
		CreateTextureUnitState(nPathFlag, mtldata->baseTexMap.coordIndex, pPbr->m_nBaseColorTextureIndex, pPbr->m_nBaseColorTextureCoordIndex, 
			pPass, textureDataName, mtldata->baseTexMap.texMatrix);
	}
	if (mtldata->EmissionMap.texPath != nullptr)
	{	
		textureDataName = mtldata->EmissionMap.texPath;
		CreateTextureUnitState(nPathFlag, mtldata->EmissionMap.coordIndex, pPbr->m_nEmissiveTextureIndex, pPbr->m_nEmissiveTextureCoordIndex,
			pPass,textureDataName, mtldata->EmissionMap.texMatrix);
	}
	if (mtldata->MetallicRoughMap.texPath != nullptr)
	{	
		textureDataName = mtldata->MetallicRoughMap.texPath;
		CreateTextureUnitState(nPathFlag, mtldata->MetallicRoughMap.coordIndex, pPbr->m_nMetallicRoughnessTextureIndex, pPbr->m_nMetallicRoughnessTextureCoordIndex,
			pPass,textureDataName, mtldata->MetallicRoughMap.texMatrix);
	}
	if (mtldata->NormalMap.texPath != nullptr)
	{	
		textureDataName = mtldata->NormalMap.texPath;
		CreateTextureUnitState(nPathFlag, mtldata->NormalMap.coordIndex, pPbr->m_nNormalTextureIndex, pPbr->m_nNormalTextureCoordIndex,
			pPass, textureDataName, mtldata->NormalMap.texMatrix);
	}
	if (mtldata->OcclusionMap.texPath != nullptr)
	{	
		textureDataName = mtldata->OcclusionMap.texPath;
		CreateTextureUnitState(nPathFlag, mtldata->OcclusionMap.coordIndex, pPbr->m_nOcclusionTextureIndex, pPbr->m_nOcclusionTextureCoordIndex,
			pPass, textureDataName, mtldata->OcclusionMap.texMatrix);
	}
	strMtlName += textureDataName;
	// ���ʶ�������
	pMaterial3D->m_strName = strMtlName;
	// ����ͨ������
	pPass->m_strName = strMtlName;

	pPass->m_fAlphaCutoff = mtldata->alphaCutOff;
	pPass->m_AlphaMode = mtldata->alphaMode;
	pPbr->m_vec4BaseColor =  mtldata->baseColorFactor;
	pPbr->m_vec3EmissiveFactor = mtldata->EmissionFactor;
	pPbr->m_fMetallicFactor =  mtldata->metallicFactor;
	pPbr->m_fRoughnessFactor = mtldata->RoughnessFactor;
	// ������ɫ
	//{
	//	UGfloat fParency;
	//	Color diffuseColor;
	//	pPass->m_Diffuse.SetValue(diffuseColor.r, diffuseColor.g, diffuseColor.b, 1.0 - fParency);

	return pMaterial3D;
}

ROGroupLite::MeshParamInfo ROGroupLite::CreateMeshData(int lodId)
{
	//������Ϣ
	float verts[24] =
	{
		0.1234f, 0.1234f, 0.1234f,   //��0������
		20.1234f, 0.1234f, 0.1234f,  //��1������
		20.1234f, 0.1234f, 20.1234f, //��2������
		0.1234f, 0.1234f, 20.1234f,  //��3������
		0.1234f, 20.1234f, 0.1234f,  //��4������
		20.1234f, 20.1234f, 0.1234f, //��5������
		20.1234f, 20.1234f, 20.1234f,//��6������
		0.1234f, 20.1234f, 20.1234f  //��7������
	};
	std::vector<float> m_Vers(verts, verts + sizeof(verts) / sizeof(verts[0]));
	//����������Ϣ
	unsigned int VertsIndex[36] =
	{
		0, 1, 2,//ǰ��
		0, 2, 3,
		4, 7, 6,//��
		4, 6, 5,
		4, 0, 3,//���
		4, 3, 7,
		1, 5, 6,//�Ҳ�
		1, 6, 2,
		3, 2, 6,//����
		3, 6, 7,
		0, 4, 1,//�ײ�
		1, 4, 5
	};
	std::vector<unsigned int> m_Indexes(VertsIndex, VertsIndex + sizeof(VertsIndex) / sizeof(VertsIndex[0]));
	//������Ϣ
	float normals[108] =
	{
		0, -1, 0, 0, -1, 0, 0, -1, 0,
			0, -1, 0, 0, -1, 0, 0, -1, 0,//ǰ��
			0, 1, 0, 0, 1, 0, 0, 1, 0,
			0, 1, 0, 0, 1, 0, 0, 1, 0,//��
			-1, 0, 0, -1, 0, 0, -1, 0, 0,
			-1, 0, 0, -1, 0, 0, -1, 0, 0,//���
			1, 0, 0, 1, 0, 0, 1, 0, 0,
			1, 0, 0, 1, 0, 0, 1, 0, 0,//�Ҳ�
			0, 0, 1, 0, 0, 1, 0, 0, 1,
			0, 0, 1, 0, 0, 1, 0, 0, 1,//����
			0, 0, -1, 0, 0, -1, 0, 0, -1,
			0, 0, -1, 0, 0, -1, 0, 0, -1//�ײ�
	};
	std::vector<float> m_Normals(normals, normals + sizeof(normals) / sizeof(normals[0]));
	//UV��Ϣ
	float uvs[72] =
	{
		0, 0, 2, 0, 2, 2,
		0, 0, 2, 2, 0, 2,
		0, 0, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 1,
		0, 0, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 1,
		0, 0, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 1,
		0, 0, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 1,
		0, 0, 1, 0, 1, 1,
		0, 0, 1, 1, 0, 1
	};
	std::vector<float> m_UVs(uvs, uvs + sizeof(uvs) / sizeof(uvs[0]));
	wstring strID = U("�Ǽ�1");
	//��ʼ���Ǽ���Ϣ
	struct MeshParamInfo info = { strID,lodId,m_Vers,m_Indexes,m_Normals,m_UVs };
	return info;
}

Geometry* ROGroupLite::CreateGeometry(MeshParamInfo& meshInfo, bool isV2)
{
	Geometry* pGeometry = new Geometry;
	wstring strName = to_wstring((size_t)meshInfo.LodID);
	//�Ǽ����֣�Ψһ
	pGeometry->m_strGeoName = meshInfo.strID + strName;
	pGeometry->m_pVertexDataPackage = new VertexDataPackage;
	pGeometry->m_pVertexDataPackage->m_nVertexDimension = 3;
#pragma region �պ�
	//pGeometry->m_pVertexDataPackage->SetVertexNum(meshInfo.verts.size() / 3);
	//float* pVertices = pGeometry->m_pVertexDataPackage->m_pVertices;
	//int vertPoint = 0;
	//for (; vertPoint < meshInfo.verts.size(); vertPoint++, pVertices++)
	//{
	//	*pVertices = meshInfo.verts[vertPoint];
	//}
#pragma endregion

#pragma region ���պ�
	pGeometry->m_pVertexDataPackage->SetVertexNum(meshInfo.indexs.size());
	float* pVertices = pGeometry->m_pVertexDataPackage->m_pVertices;
	int i = 0;
	for (; i < meshInfo.indexs.size(); i++)
	{
		pVertices[3 * i] = meshInfo.verts[meshInfo.indexs[i] * 3];
		pVertices[3 * i + 1] = meshInfo.verts[meshInfo.indexs[i] * 3 + 1];
		pVertices[3 * i + 2] = meshInfo.verts[meshInfo.indexs[i] * 3 + 2];
	}
#pragma endregion


	//uv
	{
		pGeometry->m_pVertexDataPackage->m_TexCoordCount[0] = meshInfo.texCoords.size() / 2;
		pGeometry->m_pVertexDataPackage->m_pTexCoords[0] = new float[meshInfo.texCoords.size()];
		pGeometry->m_pVertexDataPackage->m_nTexDimensions[0] = 2;
		float* pTexCoords = pGeometry->m_pVertexDataPackage->m_pTexCoords[0];
		//��ֵUV
		//pTexCoords = NULL;
		for (int i = 0; i < meshInfo.texCoords.size() / 2; i++)
		{
			pTexCoords[2 * i] = meshInfo.texCoords[2 * i];
			pTexCoords[2 * i + 1] = meshInfo.texCoords[2 * i + 1];
		}
	}

	IndexPackage* pIndexPackage = new IndexPackage;

	if (meshInfo.verts.size()/3 < 65536)
	{

		pIndexPackage->m_enIndexType = IT_16BIT;
		pIndexPackage->SetIndexNum(meshInfo.indexs.size());

		unsigned short* pIndexes = pIndexPackage->m_pIndexes;
		int indexPoint = 0;
		for (; indexPoint < meshInfo.indexs.size(); indexPoint++, pIndexes++)
		{
			//*pIndexes = meshInfo.indexs[indexPoint];
			*pIndexes = indexPoint;
		}
		pGeometry->m_arrIndexPackage.push_back(pIndexPackage);
	}
	else
	{
		
		pIndexPackage->m_enIndexType = IT_32BIT;
		pIndexPackage->SetIndexNum(meshInfo.indexs.size());
		
		unsigned int* pIndexes = (unsigned int*)pIndexPackage->m_pIndexes;
		int indexPoint = 0;
		for (; indexPoint < meshInfo.indexs.size(); indexPoint++, pIndexes++)
		{
			//*pIndexes = meshInfo.indexs[indexPoint];
			*pIndexes = indexPoint;
		}
		pGeometry->m_arrIndexPackage.push_back(pIndexPackage);
	}

	if (meshInfo.colors.size() > 0)
	{
		//������ɫ
		/*pGeometry->m_pVertexDataPackage->SetColorNum(meshInfo.colors.size());
		UGint colorPoint = 0;
		UGuint* pColor = pGeometry->m_pVertexDataPackage->m_pVertexColor;
		for (; colorPoint < meshInfo.colors.size(); colorPoint++, pColor++)
		{
			*pColor = meshInfo.colors[colorPoint];
		}*/
	}

	if (pGeometry->m_pVertexDataPackage->m_nVerticesCount > 0 && pGeometry->m_pVertexDataPackage->m_pVertices != NULL && meshInfo.normals.size() > 0)
	{
		////��ֵ����
		//pGeometry->m_pVertexDataPackage->m_pNormals = NULL;
		pGeometry->m_pVertexDataPackage->m_nNormalCount = pGeometry->m_pVertexDataPackage->m_nVerticesCount;//����������ڷ���������
		float* pNormals = new float[pGeometry->m_pVertexDataPackage->m_nNormalCount * 3];
		pGeometry->m_pVertexDataPackage->m_pNormals = pNormals;
		for (int i = 0; i < pGeometry->m_pVertexDataPackage->m_nNormalCount; i++)
		{
			pNormals[3 * i] = meshInfo.normals[3 * i];
			pNormals[3 * i + 1] = meshInfo.normals[3 * i + 1];
			pNormals[3 * i + 2] = meshInfo.normals[3 * i + 2];
		}
	}

#pragma region ����instanceInfoʾ��
	if (!isV2)//s3m2.0 pbr�����ݲ�֧��ʵ������Ϣ
	{
		std::vector<Matrix4d> vecMats;
		std::vector<unsigned int> vecIds;
		for (int i = 0; i < 5; i++)
		{
			Matrix4d mat = Matrix4d::IDENTITY;
			mat.m[3][0] = 20 * i;
			mat.m[3][1] = 20 * i;
			vecMats.push_back(mat);
			vecIds.push_back(i + 1);
		}
		pGeometry->CreateInstanceInfo(vecMats, vecIds);
	}
#pragma endregion

	pGeometry->ComputerBoundingBox();
	return pGeometry;
}

TextureData* ROGroupLite::CreateTextureData(wstring texturePath)
{	
	if (texturePath.find(U(':')) == wstring::npos)
	{
		wchar_t buffer[200];
		GetCurrentDirectoryW(200, buffer);
		wstring strPath(buffer);
		texturePath = StringHelper::GetAbsolutePath(texturePath);
	}
	TextureData* m_pTextureData = ImgToolkit::GetTextureData(texturePath);
	return m_pTextureData;
}

Material* ROGroupLite::CreateMaterial(wstring textureDataName)
{
	Material* pMaterial3D = new Material;
	wstring strMtlName = U("����");
	Technique* pTech = pMaterial3D->CreateTechnique();
	Pass* pPass = pTech->CreatePass();

	pPass->SetPFFMode((PolygonFrontFace)PFF_NONE);
	strMtlName += textureDataName;

	TextureUnitState* pTexUnit = pPass->CreateTextureUnitState();
	//���ʶ���ͨ����ͼ��������ƹ�����ͼ����
	pTexUnit->m_strTextureName = textureDataName;

	// ���ʶ�������
	pMaterial3D->m_strName = strMtlName;
	// ����ͨ������
	pPass->m_strName = strMtlName;
	pPass->m_pPRBMaterial = new PBRMetallicRough;
	PBRMetallicRough* pPbr = (PBRMetallicRough*)pPass->m_pPRBMaterial;
	pPbr->m_nBaseColorTextureIndex = 0;
	// ������ɫ
	//{
	//	UGfloat fParency;
	//	Color diffuseColor;
	//	pPass->m_Diffuse.SetValue(diffuseColor.r, diffuseColor.g, diffuseColor.b, 1.0 - fParency);

	//	Color ambientColor;

	//	pPass->m_Ambient.SetValue(ambientColor.r, ambientColor.g, ambientColor.b, 1.0 - fParency);

	//	Color specularColor;
	//	pPass->m_Specular.SetValue(specularColor.r, specularColor.g, specularColor.b, 1.0 - fParency);

	//	Color emmissiveColor;
	//	pPass->m_SelfIllumination.SetValue(emmissiveColor.r, emmissiveColor.g, emmissiveColor.b, 1.0 - fParency);

	//	pPass->m_Shininess;
	//}
	return pMaterial3D;
}



