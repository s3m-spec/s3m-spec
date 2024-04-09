#ifndef  _MATERIAL_H_
#define  _MATERIAL_H_

#include "JsonParser.h"
#include "Skeleton.h"
#define S3MB_MATERIAL	 "material"
using namespace std;

namespace S3MB
{	
#define TEXTUREMOTION_OFFSETSPEEDU			U("OffsetSpeedU")
#define TEXTUREMOTION_OFFSETSPEEDV			U("OffsetSpeedV")
#define TEXTUREMOTION_OFFSETPERIOD			U("OffsetPeriod")
#define TEXTUREMOTION_TILINGSPEEDU			U("TilingSpeedU")
#define TEXTUREMOTION_TILINGSPEEDV			U("TilingSpeedV")
#define TEXTUREMOTION_TILINGPERIOD			U("TilingPeriod")
	// ��Ⱦ�����õĵĲü�ģʽ
	enum CullingMode
	{
		// Hardware never culls triangles and renders everything it receives.
		CULL_NONE = 1,
		// Hardware culls triangles whose vertices are listed clockwise in the view (default).
		CULL_CLOCKWISE = 2,
		// Hardware culls triangles whose vertices are listed anticlockwise in the view.
		CULL_ANTICLOCKWISE = 3
	};
	//! \brief ������ɫ���ٵĲ�������
	enum TrackVertexColourType
	{
		TVC_NONE = 0x0,
		TVC_AMBIENT = 0x1,
		TVC_DIFFUSE = 0x2,
		TVC_SPECULAR = 0x4,
		TVC_EMISSIVE = 0x8
	};
	//! \brief ��Ⱦ�����õĵ�������滷�Ʒ���
	enum PolygonFrontFace
	{
		//! \brief ���涼��
		PFF_NONE = 1,
		//! \brief ˳ʱ��
		PFF_CW = 2,
		//! \brief ��ʱ��.
		PFF_CCW = 3,
		//! \brief ��ʾʹ������Ĭ�ϵĻ��Ʒ�ʽ
		PFF_DEFAULT = 4,
	};

	enum MaterialParamType
	{
		MAT_Unknown = 0,
		// �����ֲڶ�ģ��
		MAT_PBRMetallicRough = 1,
		// �����߹�ģ��
		MAT_PBRSpecularGlossy = 2,
	};

	// Filtering options for textures / mipmaps. 
	enum FilterOptions
	{
		// No filtering, used for FILT_MIP to turn off mipmapping
		FO_NONE,
		// Use the closest pixel
		FO_POINT,
		// Average of a 2x2 pixel area, denotes bilinear for MIN and MAG, trilinear for MIP
		FO_LINEAR,
		/// Equal to: min=FO_LINEAR, mag=FO_LINEAR, mip=FO_LINEAR
		FO_TRILINEAR,
		// Similar to FO_LINEAR, but compensates for the angle of the texture plane
		FO_ANISOTROPIC
	};
	//! \brief UV���������˶��Ĳ���
	struct UVMotionParameter
	{
		//! \brief U������ٶ�
		float m_fSpeedU;
		//! \brief V������ٶ�
		float m_fSpeedV;
		//! \brief ����
		float m_fPeriod;

		UVMotionParameter()
		{
			m_fSpeedU = 0.0;
			m_fSpeedV = 0.0;
			m_fPeriod = 0.0;
		}

		UVMotionParameter(float fSpeedU, float fSpeedV, float fPeriod)
		{
			m_fSpeedU = fSpeedU;
			m_fSpeedV = fSpeedV;
			m_fPeriod = fPeriod;
		}

		UVMotionParameter(const UVMotionParameter& other)
			:m_fSpeedU(other.m_fSpeedU),
			m_fSpeedV(other.m_fSpeedV),
			m_fPeriod(other.m_fPeriod)
		{
		}

		UVMotionParameter & operator=(const UVMotionParameter& other)
		{
			m_fSpeedU = other.m_fSpeedU;
			m_fSpeedV = other.m_fSpeedV;
			m_fPeriod = other.m_fPeriod;
			return *this;
		}

		~UVMotionParameter()
		{
		}
	};
	//! \brief PBR�����˶�����
	struct TextureMotionParameter
	{
	public:
		//! \brief ����ƽ���˶��Ĳ���
		UVMotionParameter m_OffsetMotion;
		//! \brief �������ŵĲ���
		UVMotionParameter m_TilingMotion;

		TextureMotionParameter()
			:m_OffsetMotion(0.0, 0.0, 0.0),
			m_TilingMotion(1.0, 1.0, 0.0)
		{
		}

		TextureMotionParameter(const TextureMotionParameter& other)
			:m_OffsetMotion(other.m_OffsetMotion),
			m_TilingMotion(other.m_TilingMotion)
		{
		}

		TextureMotionParameter & operator=(const TextureMotionParameter& other)
		{
			m_TilingMotion = other.m_TilingMotion;
			m_OffsetMotion = other.m_OffsetMotion;
			return *this;
		}

		~TextureMotionParameter()
		{
		}
		bool ToJson(JsonValue & json)
		{
			json.Add(TEXTUREMOTION_OFFSETSPEEDU, m_OffsetMotion.m_fSpeedU);
			json.Add(TEXTUREMOTION_OFFSETSPEEDV, m_OffsetMotion.m_fSpeedV);
			json.Add(TEXTUREMOTION_OFFSETPERIOD, m_OffsetMotion.m_fPeriod);
			json.Add(TEXTUREMOTION_TILINGSPEEDU, m_TilingMotion.m_fSpeedU);
			json.Add(TEXTUREMOTION_TILINGSPEEDV, m_TilingMotion.m_fSpeedV);
			json.Add(TEXTUREMOTION_TILINGPERIOD, m_TilingMotion.m_fPeriod);
			return true;
		}

		bool FromJson(JsonValue & json)
		{
			json.GetValue(TEXTUREMOTION_OFFSETSPEEDU, m_OffsetMotion.m_fSpeedU);
			json.GetValue(TEXTUREMOTION_OFFSETSPEEDV, m_OffsetMotion.m_fSpeedV);
			json.GetValue(TEXTUREMOTION_OFFSETPERIOD, m_OffsetMotion.m_fPeriod);
			json.GetValue(TEXTUREMOTION_TILINGSPEEDU, m_TilingMotion.m_fSpeedU);
			json.GetValue(TEXTUREMOTION_TILINGSPEEDV, m_TilingMotion.m_fSpeedV);
			json.GetValue(TEXTUREMOTION_TILINGPERIOD, m_TilingMotion.m_fPeriod);
			return true;
		}
	};
	class S3MB_API PBRParams
	{
	public:
		enum AlphaMode
		{
			PBRAM_UnKnown = 0,
			// ƬԪ��alphaֵ���Ϊ1.0,
			PBRAM_OPAQUE = 1,
			// ƬԪ����alpha����
			PBRAM_MASK = 2,
			// ƬԪ��alphaֵ���baseColor��alphaֵ
			PBRAM_BLEND = 3,
		};
	public:
		PBRParams();

		virtual MaterialParamType GetType() = 0;

	public:
		// �����Է���ǿ�ȵ�����
		Vector3d m_vec3EmissiveFactor;
		//! \brief �Է������������������е���� RGB����
		int m_nEmissiveTextureIndex;
		//! \brief �Է�������������������������������е����
		int m_nEmissiveTextureCoordIndex;
		//! \brief �Է��������˶��Ĳ�������
		TextureMotionParameter m_EmissiveTextureMotion;

		//! \brief �������������������е���ţ��������İ�͹ϸ�� float��ʽRGB����
		int m_nNormalTextureIndex;
		//! \brief ��������������������������������е����
		int m_nNormalTextureCoordIndex;
		//! \brief �����������������
		float m_fNormalTextureScale;
		

		//! \brief �ڵ�ͼ�����������е���ţ�����������氼͹�ԶԹ��յ�Ӱ�죬�����϶���Ͱ� float�Ҷ�����
		int m_nOcclusionTextureIndex;
		//! \brief �ڵ�ͼ�������������������������е����
		int m_nOcclusionTextureCoordIndex;
		//! \brief �ڵ�ͼ����������
		float m_fOcclusionTextureStrength;
		

		

	};

	// �����ֲڶ�ģ��
	class S3MB_API PBRMetallicRough : public PBRParams
	{
	public:
		PBRMetallicRough();

		virtual MaterialParamType GetType() { return MAT_PBRMetallicRough; }
	public:
		// ����Ļ�����ɫ
		Vector4d m_vec4BaseColor;
		//! \brief ���������ɫ�����������������е����
		int m_nBaseColorTextureIndex;
		//! \brief ���������ɫ�������������������������е����
		int m_nBaseColorTextureCoordIndex;
		//! \brief ��ɫ�����˶��Ĳ�������
		TextureMotionParameter m_BaseColorTextureMotion;
		//! \brief �����Ⱥʹֲ������������������е����(Rͨ���洢�����ȣ�Gͨ���洢�ֲڶ�)
		int m_nMetallicRoughnessTextureIndex;
		//! \brief �����Ⱥʹֲ�����������������������е����
		int m_nMetallicRoughnessTextureCoordIndex;
		// ���ƽ�����ǿ��������
		float m_fMetallicFactor;
		// ���ƴֲ���ǿ��������
		float m_fRoughnessFactor;
	};

	// �����߹�ģ��
	class S3MB_API PBRSpecularGlossy : public PBRParams
	{
	public:
		PBRSpecularGlossy();

		virtual MaterialParamType GetType() { return MAT_PBRSpecularGlossy; }
	public:
		// ɢ����ɫ
		Vector4d m_vec4DiffuseFactor;
		// �������ɫ
		Vector3d m_vec3SpecularFactor;
		// �߹�ǿ��
		float m_fGlossinessFactor;
		// ɢ����ɫ����
		wstring m_strDiffuseTexture;
		// �����߹�ǿ������RGBͨ���澵�����ɫ��Aͨ����߹�ǿ��
		wstring m_strSpecularGlossinessTexture;
	};

	class S3MB_API TextureUnitState
	{
	public:
		enum TextureAddressingMode
		{

			TAM_WRAP,

			TAM_MIRROR,

			TAM_CLAMP,

			TAM_BORDER,
		};

		struct UVWAddressingMode
		{
			TextureAddressingMode u, v, w;
		};

		TextureUnitState();

	public:
		// optional name for the TUS
		wstring m_strName;

		// ����Ԫʹ�õ���������
		wstring m_strTextureName;

		// �������õ��ļ�
		wstring m_strTexureURL;

		// ���������������ģʽ
		UVWAddressingMode m_AddressMode;

		//�����˲���ͳһ��ʽ
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
		// ��Ⱦ�����õĵĲü�ģʽ
		CullingMode m_CullMode;
		// ͸�������������
		bool m_TransparentSorting;
		// PBR����
		PBRParams* m_pPRBMaterial;
		//! \brief ������ɫ����
		unsigned int m_Tracking;
		//�Ƿ����Alpha���
		bool m_bBlendAlpha;
		//��ߴ�
		float m_dPointSize;
		float m_dPointMinSize;
		float m_dPointMaxSize;
		//! \brief�����ƫ������������
		float m_fConstantPolygonOffset;
		//! \brief�����ƫ��������¶����Ӳ���
	//! \brief����ƫ���� = maxSlope * m_fSlopeScalePolygonOffset + m_fConstantPolygonOffset
		float m_fSlopeScalePolygonOffset;

		//! \brief  �Ƿ��������
		bool m_bMutiTexture;
		/// Storage of texture unit states
		typedef std::vector<TextureUnitState*> TextureUnitStates;
		TextureUnitStates m_pTextureUnitStates;

		//! \brief ������滷��ģʽ
		//! \return ����ģʽ
		int GetPFFMode();

		//! \brief �������滷��ģʽ
		//! \param mode ����ģʽ
		void SetPFFMode(PolygonFrontFace mode);

		TextureUnitState* CreateTextureUnitState();
		//��ȡTextureUnitState������
		unsigned short GetTextureUnitStatesSize(void) const;

		//��ȡTextureUnitState
		TextureUnitState* GetTextureUnitState(unsigned short index);
		// ��alphaModeΪMaskʱ����ɫ���������ֵ��baseColor��Alphaֵ���бȽϾ����Ƿ���
		float m_fAlphaCutoff;
		//ʹ�õĶ�����ɫ��������
		wstring strVertexProgram;
		//ʹ�õ�ƬԪ��ɫ��������
		wstring strFragmentProgram;
		// AlphaMode
		PBRParams::AlphaMode m_AlphaMode;
		
	};

	class S3MB_API Technique
	{
	public:
		Technique();
		~Technique();
		Pass* CreatePass();
		typedef vector<Pass*> Passes;
		/// List of primary passes
		Passes mPasses;
		/** Retrieves the number of passes. */
		unsigned short getNumPasses(void) const;
		/** Retrieves the Pass with the given index. */
		Pass* getPass(unsigned short index);
		/** Retrieves the Pass matching name.*/
		Pass* getPass(const wstring& name);
		/** Removes all Passes from this Technique. */
		void removeAllPasses(void);
	};

	class S3MB_API Material
	{
	public:
		Material();
		~Material();
		Technique* CreateTechnique();
		wstring m_strName;
		typedef vector<Technique*> Techniques;
		Techniques mTechniques;
		/** Retrieves the number of techniques. */
		int getNumTechniques(void) const;
		/** Gets the indexed technique. */
		Technique* getTechnique(unsigned short index);
		/** Removes all the techniques in this Material. */
		void removeAllTechniques(void);
	};
}

#endif