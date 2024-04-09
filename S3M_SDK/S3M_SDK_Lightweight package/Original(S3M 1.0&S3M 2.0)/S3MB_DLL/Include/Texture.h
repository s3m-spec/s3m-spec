#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "MemoryStream.h"
#include <string>
#include <iostream>

using namespace std;

namespace S3MB
{
	//! ��������
	enum CodecType
	{
		//! ��ʹ�ñ��뷽ʽ
		encNONE = 0,
		//{{����ԭ����ѡ�����ʹ�ã����¸��汾ȥ��
		//! ʹ��unsigned char(1)���ʹ洢
		encBYTE = 1,
		//! ʹ��WORD(2)���ʹ洢
		encWORD = 2,
		//! ʹ��3�ֽ����ʹ洢
		enc3BYTE = 3,
		//! ʹ��4�ֽ����ʹ洢
		encDWORD = 4,
		//! ʹ��float���ʹ洢
		//encFLOAT	= 5,	
		//! ʹ��doubel���ʹ洢	
		//encDOUBLE	= 6,	
		//! Image��ѹ��
		encDCT = 8,
		//! SuperMap Grid LZW encoded.
		encSGL = 9,
		//! another Grid LZW encoded.
		encLGL = 10,
		//! ����������ɫӰ���ѹ����ʽ������
		encLZW = 11,
		//! PNGѹ���㷨
		encPNG = 12,
		//}}

		//! \brief ʸ������
		//! \brief ��ʹ�ñ��뷽ʽ
		envNONE = 0,
		//! \brief ʹ��doubel���ʹ洢	
		//envDOUBLE	= 6,
		//! \brief ʹ��unsigned char(1)���ʹ洢
		envBYTE = 1,
		//! \brief ʹ��WORD(2)���ʹ洢
		envWORD = 2,
		//! \brief ʹ��3�ֽ����ʹ洢
		env3BYTE = 3,
		//! \brief ʹ��4�ֽ����ʹ洢
		envDWORD = 4,
		//! \brief ZIP����ѹ����ʽ
		envLZW = 11,
		//! \brief ʹ�ù���������	 
		envHfm = 13,

		//! \brief դ�����
		//! \brief ��ʹ�ñ��뷽ʽ
		enrNONE = 0,
		//! \brief Image��ѹ��
		enrDCT = 8,
		//! \brief SuperMap Grid �γ̱���.
		enrSGL = 9,
		//! \brief another Grid �γ̱���. ����֧�ָ������Ĵ���
		enrLGL = 10,
		//! \brief ����������ɫӰ���ѹ����ʽ������,�õ���ZIPѹ������
		enrLZW = 11,
		//! \brief PNGѹ���㷨
		enrPNG = 12,
		//! \brief ʹ�ù���������
		enrHfm = 13,

		//! \brief s3t dxtn����ѹ��
		enrS3TCDXTN = 14,

		//! \brief lzma����ѹ��
		enrLZMA = 15,

		//! \brief Gif����
		enrGIF = 16,

		//! \brief ��ϱ���
		enrCompound = 17,

		//! \brief DDS+ZIP����
		enrDDSZIP = 18,

		//! \brief pvr PVRTC2  2 or 4 bpp,may be ipad4 will support... wxh
		enrPVRTPF_PVRTC2 = 19,

		//! \brief pvr PVRTC  2 or 4 bpp the ipad3 only support pvrtc1 default 2bpp
		enrPVRTPF_PVRTC = 20,

		//! \brief pvr PVRTC  2 or 4 bpp this is 4bpp
		enrPVRTPF_PVRTC_4bpp = 21,

		//! \brief Ericsson Texture compression version 1, standard format for openGL ES 2.0.  added by shansg
		enrPVRTPF_ETC1 = 22,

		//! \brief JPG
		enrJPG = 23,

		//! \brief pvr PVRTCFAST
		enrPVRTPF_PVRTC_FAST = 24,
	};

	enum PixelFormat
	{
		//! \brief ��δ�趨, �ڲ�ʹ��
		IPF_UNKNOWN = 0,
		//! \brief 1λ,��ɫ
		IPF_MONO = 1,
		//! \brief 4λ,16ɫ
		IPF_FBIT = 4,
		//! \brief 8λ�޷���,256ɫ
		IPF_UBYTE = 8,
		//! \brief 8λ�з���,256ɫ,����
		IPF_BYTE = 80,
		//! \brief 16λ�з���,��ɫ
		IPF_TBYTE = 16,
		//! \brief 16λ�޷���,��ɫ������
		IPF_UTBYTE = 160,
		//! \brief 24λ,���ɫ
		IPF_RGB = 24,
		//! \brief 32λ,��ǿ���ɫ
		IPF_RGBA = 32,
		//! \brief 48λ,���ɫ
		IPF_TRGB = 48,
		//! \brief 64λ,������
		IPF_LONGLONG = 64,
		//! \brief LONG
		IPF_LONG = 320,
		//! \brief LONG
		IPF_ULONG = 321,
		//! \brief 32λ,������
		IPF_FLOAT = 3200,
		//! \brief 96λ��ʽ��Rͨ��32λ��float����Bͨ��32λ��float����Gͨ��32λ��float��
		IPF_FLOAT32_RGB = 4800,
		//! \brief 128λ��ʽ��Rͨ��32λ��float����Bͨ��32λ��float����Gͨ��32λ��float��, Aͨ��32λ��float��
		IPF_FLOAT32_RGBA = 4801,
		//! \brief 64λ,˫���ȸ�����
		IPF_DOUBLE = 6400
	};

	class S3MB_API TextureInfo
	{
	public:
		TextureInfo();
		~TextureInfo();
		const TextureInfo& operator=(const TextureInfo& Info);
		TextureInfo(const TextureInfo& Info);
		// �ӹ�����߸����ڴ�
		TextureInfo(PixelFormat enFormat, unsigned int Width, unsigned int Height, void* data, unsigned int nSize, const wstring& path = U(""));

		//! \brief �����ļ��м���
		//! \param fStream �ļ���[in]��
		void Load(MemoryStream& fStream);

		//! \brief �������ļ���
		//! \param fStream �ļ���[in]��
		void Save(MemoryStream& fStream);

		//! \brief ��ȡ���ݴ洢ʱ�Ĵ�С
		//! \return ���ش洢��С
		//! \remark ��δ���Ǳ����������Save()һ��ά��
		//! \attention �ַ����ĳ���Ҫ+4
		int GetDataSize();
	public:
		bool			m_bLoadImage;

		// ����ͼƬ�����ظ�ʽ
		PixelFormat		m_enFormat;

		// ����ͼƬ�Ŀ��
		unsigned int	m_nWidth;

		// ����ͼƬ�ĸ߶�
		unsigned int	m_nHeight;

		// ����ͼƬ������
		unsigned char* m_pBuffer;

		// ����ͼƬ�����ݵĳ���,��ѹ��ʱ����Ҫ
		unsigned int		m_nSize;

		// ����ͼƬ������·��
		wstring	m_strPath;

		wstring	m_strName;

		// ����ͼƬ������һ���м���mipmap
		unsigned int	m_nMipLev;

		// ����ͼƬ��ѹ������
		CodecType	m_nCompress;
	};
	//! \brief
	enum _3DPixelFormat
	{
		//! \brief δ֪���ظ�ʽ.
		PF_UNKNOWN = 0,
		//! \brief 8λ���أ���������.
		PF_L8 = 1,
		PF_BYTE_L = PF_L8,
		//! \brief 16λ���أ���������.
		PF_L16 = 2,
		PF_SHORT_L = PF_L16,
		//! \brief 8λ���أ�����alphaֵ.
		PF_A8 = 3,
		PF_BYTE_A = PF_A8,
		//! \brief 8λ����, 4λalphaֵ, 4λ����.
		PF_A4L4 = 4,
		//! \brief ���ֽ�����, һ������alphaֵ��һ����������
		//! \brief 8λ����, 4λ����, 4λalpha.
		PF_L4A4 = 35,
		//! \brief 16λ����, ÿ4λ����BGRA.
		PF_B4G4R4A4 = 36,
		//! \brief 24λ����, ÿ8λ����BRG.
		PF_B8R8G8 = 37,
		//! \brief 32λ����, ÿ10λ����BGR, 2λ����alpha.
		PF_B10G10R10A2 = 38,
		PF_BYTE_LA = 5,
		//! \brief 16λ���ظ�ʽ, R,G,BΪ5��6��5.
		PF_R5G6B5 = 6,
		//! \brief 16λ���ظ�ʽ, B,G,RΪ5��6��5.
		PF_B5G6R5 = 7,
		//! \brief 8λ����, B,G,RΪ2��3��3.
		PF_R3G3B2 = 31,
		//! \brief 16λ����, alpha��R,G,BΪ4,4,4,4.
		PF_A4R4G4B4 = 8,
		//! \brief 16λ����, alpha��R,G,BΪ1,5,5,5.
		PF_A1R5G5B5 = 9,
		//! \brief 24λ����, R,G,BΪ8,8,8.
		PF_R8G8B8 = 10,
		//! \brief 24λ����, B,G,RΪ8,8,8.
		PF_B8G8R8 = 11,
		//! \brief 32λ����, alpha,R,G,BΪ8,8,8,8.
		PF_A8R8G8B8 = 12,
		//! \brief 32λ����, B, G, R,alphaΪ8,8,8,8.
		PF_A8B8G8R8 = 13,
		//! \brief 32λ����, B, G, R,alphaΪ8,8,8,8.
		PF_B8G8R8A8 = 14,
		//! \brief 32λ����, R, G, B,alphaΪ8,8,8,8.
		PF_R8G8B8A8 = 28,
		// 128λ����, ÿ��Ԫ��ռ32λ
		PF_FLOAT32_RGBA = 25,
		//! \brief 32λ����, R, G, BΪ8��8,8��alpha��Ч
		PF_X8R8G8B8 = 26,
		//! \brief 32λ����, B G, RΪ8��8,8��alpha��Ч
		PF_X8B8G8R8 = 27,
		//! \brief 3�ֽ�����, ÿ����ɫռһ���ֽ�
		PF_BYTE_RGB = PF_B8G8R8,
		//! \brief 3�ֽ�����, ÿ����ɫռһ���ֽ�
		PF_BYTE_BGR = PF_R8G8B8,
		//! \brief 4�ֽ�����, ÿ����ɫ��alpha��ռһ���ֽ�
		PF_BYTE_BGRA = PF_A8R8G8B8,
		//! \brief 4�ֽ�����, ÿ����ɫ��alpha��ռһ���ֽ�
		PF_BYTE_RGBA = PF_A8B8G8R8,
		//! \brief 32λ���� ��λ����alpha��ÿ����ɫռ10λ
		PF_A2R10G10B10 = 15,
		//! \brief 32λ����, ��λ����alpha��ÿ����ɫռ10λ
		PF_A2B10G10R10 = 16,
		//! \brief DirectDraw Surface (DDS) DXT1 format
		PF_DXT1 = 17,
		//! \brief DirectDraw Surface (DDS) DXT2 format
		PF_DXT2 = 18,
		//! \brief DirectDraw Surface (DDS) DXT3 format
		PF_DXT3 = 19,
		//! \brief DirectDraw Surface (DDS) DXT4 format
		PF_DXT4 = 20,
		//! \brief DirectDraw Surface (DDS)) DXT5 format
		PF_DXT5 = 21,
		// 16λ����, ����R
		PF_FLOAT16_R = 32,
		// 48λ����, ÿ16λfloat����RGB
		PF_FLOAT16_RGB = 22,
		// 64λ����,ÿ16λfloat����RGBA
		PF_FLOAT16_RGBA = 23,
		// 16λ���أ�float����R
		PF_FLOAT32_R = 33,
		// 96λ����, ÿ32λfloat����RGB
		PF_FLOAT32_RGB = 24,
		// 128λ����, ÿ32λfloat����RGBA
		// �����������
		PF_DEPTH = 29,
		// 64λ����, ÿ16λfloat����RGBA
		PF_SHORT_RGBA = 30,
		// ��ǰ�������ظ�ʽ����Ŀ
		PF_COUNT = 34
	};
	//! \brief �������ݵķ�װ�ࡣ
	class S3MB_API TextureData
	{
	public:
		//! \brief ���캯��
		TextureData();
		//! \brief �������캯��
		TextureData(const TextureData& other);
		//! \brief �������캯��
		TextureData(const TextureInfo& textureInfo);
		//! \brief ��ֵ����
		TextureData& operator=(const TextureData& other);

		//! \brief ��¡�Լ�������
		virtual TextureData* Clone();
		//! \brief ��������
		virtual ~TextureData();
		//! \brief �ͷ���������
		void Release();

		//! \brief �����ļ��м���
		bool Load(MemoryStream& fStream, unsigned int eCodecType = 0);

		//! \brief �������ļ���
		void Save(MemoryStream& fStream, unsigned int eCodecType = 0);


	private:
		//! \brief �������ļ���
		//! \remarks ʵ�������DDS���뼰zipѹ��
		bool BuildTextureTier(MemoryStream& fStream);
#if defined OPENGL_ES_VERSION2
		//! \brief ѹ��������DXTת����ΪNONE
		void CompressTypeDXTToNONE();
#endif
	public:
		//! \brief ���������ڴ�
		unsigned char* m_pBuffer;
		//! \brief ����ĸ�
		unsigned int m_nHeight;
		//! \brief ����Ŀ�
		unsigned int m_nWidth;
		//! \brief ��������
		unsigned int m_nDepth;
		//! \brief ��������ظ�ʽ��Ŀǰֻ֧��RGBA
		_3DPixelFormat m_enFormat;

		// ѹ����������
		CodecType m_CompressType;

		// ���ݵ��ڴ��С
		unsigned int m_nSize;
	};

	struct TextureDataInfo
	{
		TextureData* m_pTextureData;

		bool m_bMipmap;

		int m_nLevel;

		TextureDataInfo()
		{
			m_pTextureData = NULL;
			m_bMipmap = false;
			m_nLevel = 0;
		}

		TextureDataInfo(const TextureDataInfo& other)
		{
			m_pTextureData = NULL;
			*this = other;
		}

		TextureDataInfo& operator = (const TextureDataInfo& other)
		{
			if (m_pTextureData != NULL)
			{
				delete m_pTextureData;
				m_pTextureData = NULL;
			}

			if (other.m_pTextureData != NULL)
			{
				m_pTextureData = new TextureData(*other.m_pTextureData);
			}

			m_bMipmap = other.m_bMipmap;
			m_nLevel = other.m_nLevel;
			return *this;
		}

		~TextureDataInfo()
		{
			if (m_pTextureData != NULL)
			{
				delete m_pTextureData;
				m_pTextureData = NULL;
			}
		}
	};

	class S3MB_API ToolsEngine
	{
	public:
		//! \brief  ���ر�a��ģ���������ӽ�a��2�Ĵη�������
		static unsigned int NextP2(unsigned int a);

		static bool Zip(unsigned char* pvDestBuffer, unsigned int& dwDestLen,
			const unsigned char* pvSrcBuffer, unsigned int dwSrcLen, int nLevel = 8);
	};
}
#endif