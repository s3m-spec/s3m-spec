#if !defined(MATERIAL_H__746A408B_9321_4536_BA2C_49197406FB4D__INCLUDED_)
#define MATERIAL_H__746A408B_9321_4536_BA2C_49197406FB4D__INCLUDED_

#pragma once
#include "S3MBCommon.h"
#include "JsonValue.h"

namespace S3MB
{
	// PBR�����˶�����
	struct S3MB_API TextureMotionParameter
	{
	public:
		// ����ƽ���˶��Ĳ���
		UVMotionParameter m_OffsetMotion;
		// �������ŵĲ���
		UVMotionParameter m_TilingMotion;

		TextureMotionParameter();

		TextureMotionParameter(const TextureMotionParameter& other);

		TextureMotionParameter& operator=(const TextureMotionParameter& other);

		~TextureMotionParameter();

		bool ToJson(JsonValue & json);

		bool FromJson(JsonValue & json);
	};

	class S3MB_API PBRParams
	{
	public:
		PBRParams();

		virtual MaterialParamType GetType() = 0;

	public:
		// �����Է���ǿ�ȵ�����
		Vector3d m_vec3EmissiveFactor;
		// �Է������������������е���� RGB����
		int m_nEmissiveTextureIndex;
		// �Է�������������������������������е����
		int m_nEmissiveTextureCoordIndex;
		// �Է��������˶��Ĳ�������
		TextureMotionParameter m_EmissiveTextureMotion;

		// �������������������е���ţ��������İ�͹ϸ�� float��ʽRGB����
		int m_nNormalTextureIndex;
		// ��������������������������������е����
		int m_nNormalTextureCoordIndex;
		// �����������������
		float m_fNormalTextureScale;
		

		// �ڵ�ͼ�����������е���ţ�����������氼͹�ԶԹ��յ�Ӱ�죬�����϶���Ͱ� float�Ҷ�����
		int m_nOcclusionTextureIndex;
		// �ڵ�ͼ�������������������������е����
		int m_nOcclusionTextureCoordIndex;
		// �ڵ�ͼ����������
		float m_fOcclusionTextureStrength;

		// ��Ĥ���������������е���� RGB����
		int m_nMaskTextureIndex;
		// ��Ĥ����������������������������е����
		int m_nMaskTextureCoordIndex;

		// �������������������е���� RGB����
		int m_nSemanticTextureIndex;
		// ��������������������������������е����
		int m_nSemanticTextureCoordIndex;
	};

	// �����ֲڶ�ģ��
	class S3MB_API PBRMetallicRough : public PBRParams
	{
	public:
		PBRMetallicRough();

		virtual MaterialParamType GetType();

	public:
		// ����Ļ�����ɫ
		Vector4d m_vec4BaseColor;
		// ���������ɫ�����������������е����
		int m_nBaseColorTextureIndex;
		// ���������ɫ�������������������������е����
		int m_nBaseColorTextureCoordIndex;
		// ��ɫ�����˶��Ĳ�������
		TextureMotionParameter m_BaseColorTextureMotion;
		// �����Ⱥʹֲ������������������е����(Rͨ���洢�����ȣ�Gͨ���洢�ֲڶ�)
		int m_nMetallicRoughnessTextureIndex;
		// �����Ⱥʹֲ�����������������������е����
		int m_nMetallicRoughnessTextureCoordIndex;
		// ���ƽ�����ǿ��������
		float m_fMetallicFactor;
		// ���ƴֲ���ǿ��������
		float m_fRoughnessFactor;
	};

	class S3MB_API TextureUnitState
	{
	public:
		TextureUnitState();

	public:
		// ����
		wstring m_strName;

		// ����Ԫʹ�õ���������
		wstring m_strTextureName;

		// �������õ��ļ�
		wstring m_strTexureURL;

		// ���������������ģʽ
		UVWAddressingMode m_AddressMode;

		// �����˲���ͳһ��ʽ
		FilterOptions m_TextureFilteringOption;

		// ��Сʱ���˲�����
		FilterOptions m_MinFilter;

		// �Ŵ�ʱ���˲�����
		FilterOptions m_MaxFilter;

		// �������
		mutable Matrix4d m_TexModMatrix;
	};

	class S3MB_API Pass
	{
	public:
		Pass();
		~Pass();
	public:
		// ͨ����
		wstring m_strName;
		// ������
		ColorValue m_Ambient;
		// ɢ���
		ColorValue m_Diffuse;
		// �����
		ColorValue m_Specular;
		// ���⣬Ӱ�췢����Ĵ�С
		float m_Shininess;
		// �ü�ģʽ
		CullingMode m_CullMode;
		// PBR����
		PBRParams* m_pPRBMaterial;
		// texture unit states ������
		typedef std::vector<TextureUnitState*> TextureUnitStates;
		TextureUnitStates m_pTextureUnitStates;

		// ������滷��ģʽ
		// return ����ģʽ
		int GetPFFMode();

		// �������滷��ģʽ
		// mode ����ģʽ
		void SetPFFMode(PolygonFrontFace mode);

		TextureUnitState* CreateTextureUnitState();
		// ��ȡTextureUnitState������
		unsigned short GetTextureUnitStatesSize(void) const;

		// ��ȡTextureUnitState
		TextureUnitState* GetTextureUnitState(unsigned short index);
		// ��ȡTextureUnitState
		TextureUnitState* GetTextureUnitState(const std::wstring& name);
		// ��alphaModeΪMaskʱ����ɫ���������ֵ��baseColor��Alphaֵ���бȽϾ����Ƿ���
		float m_fAlphaCutoff;
		// ʹ�õĶ�����ɫ��������
		wstring strVertexProgram;
		// ʹ�õ�ƬԪ��ɫ��������
		wstring strFragmentProgram;
		// AlphaMode
		AlphaMode m_AlphaMode;

		// ��չ��Ϣ�������Զ�������µĲ��ʲ�������ë�����۾��Ȳ��ʵ����в���
		wstring m_strExtensions;
	};

	class S3MB_API Technique
	{
	public:
		Technique();
		~Technique();
		Pass* CreatePass();
		typedef vector<Pass*> Passes;
		// pass�б�
		Passes mPasses;
		// ��ȡpass����
		unsigned short getNumPasses(void) const;
		// ����������ȡָ��pass
		Pass* getPass(unsigned short index);
		// �������ƻ�ȡָ������
		Pass* getPass(const wstring& name);
		// ɾ������pass
		void removeAllPasses(void);
	};

	typedef vector<Technique*> Techniques;
	class S3MB_API Material
	{
	public:
		Material();
		~Material();
		Technique* CreateTechnique();

		// ��ȡTechnique����
		int getNumTechniques(void) const;
		// ����������ȡָ��Technique
		Technique* getTechnique(unsigned short index);
		// �Ƴ�����Technique
		void removeAllTechniques(void);

	public:
		wstring m_strName;
		Techniques mTechniques;
	};
}

#endif