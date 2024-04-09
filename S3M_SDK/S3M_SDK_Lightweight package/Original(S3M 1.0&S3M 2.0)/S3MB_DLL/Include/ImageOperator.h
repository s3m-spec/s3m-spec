#pragma once
#include <vector>
#include "Palette.h"
#include "Texture.h"
#include "stdafx.h"

using namespace std;
namespace S3MB
{
#define DXT1_ENCODE_SIZE(w,h) (((w-1)/4 + 1)*((h-1)/4 + 1)*8)
#define DXT3_ENCODE_SIZE(w,h) (((w-1)/4 + 1)*((h-1)/4 + 1)*16)
#define DXT5_ENCODE_SIZE DXT3_ENCODE_SIZE
	//! \brief �������ظ�ʽ��λ��Ϊ1λ.
#define IPF_MONO_BITS 1
//! \brief �������ظ�ʽ��λ��Ϊ4λ.
#define IPF_FBIT_BITS 4
//! \brief �������ظ�ʽ��λ��Ϊ8λ.
#define IPF_BYTE_BITS 8
//! \brief �������ظ�ʽ��λ��Ϊ16λ.
#define IPF_TBYTE_BITS 16
//! \brief �������ظ�ʽ��λ��Ϊ24λ.
#define IPF_RGB_BITS  24
//! \brief �������ظ�ʽ��λ��Ϊ32λ.
#define IPF_RGBA_BITS 32
//! \brief �õ���unsigned charΪ��λ��DWORD����Ŀ��.
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4) 

	class S3MB_API ImageOperator
	{
	public:
		// format ԭͼ������ظ�ʽ
		// width,height ԭͼ��Ŀ�Ⱥ͸߶�
		// in ԭͼ�������
		// comtype ͼ��ѹ������
		// out  ѹ��������,�ڲ�����ռ�
		// return ����ѹ����ͼ�����ݵĴ�С
		static unsigned int Encode(const unsigned int nPixSize, unsigned int& nWidth, unsigned int& nHeight, unsigned char* pBufferIn, unsigned char** ppBufferOut, unsigned int eCodecType = enrS3TCDXTN, bool bGeneMipmaps = false);

		// ��ѹ��dxtn
		static unsigned int Decode(const unsigned int nPixSize, unsigned int nWidth, unsigned int nHeight, unsigned char** ppBufferOut, const unsigned char* pBufferIn, unsigned int eCodecType, bool bGeneMipmaps = false);

		// ����ָ���Ĵ�С����ͼƬ
		static void Scale(const unsigned int components, unsigned int widthin, unsigned int heightin, unsigned char* pBufferIn,
			unsigned int widthout, unsigned int heightout, unsigned char* pBufferOut);

		//��Ӱ���������ų�������
		static unsigned char* MakeSquareForPVR(unsigned int& nWidth, unsigned int& nHeight, unsigned char* pBufferIn);

		// ��ȡmipmap������
		static unsigned int GetMipMapData(unsigned int nWidth, unsigned int nHeight, const unsigned char* pBufferIn, unsigned char** ppBufferOut, vector<unsigned int>& arrByteOffset);

		//! \brief  ���ر�a��ģ���������ӽ�a��2�Ĵη�������
		static unsigned int NextP2(unsigned int a);

		//! \brief ��ȡָ��ѹ����ʽ������ѹ����Ĵ�С
		//! \brief
		static unsigned int GetCompressedTextureSize(const unsigned int nPixSize, unsigned int nWidth, unsigned int nHeight, unsigned int eCodecType, bool bIsMipmaps = false);

		//! \brief ���ݿ�߻�ȡmipMap�㼶
		static unsigned int GetMipMapLevel(const unsigned int nWidth, const unsigned int nHeight);
		//
		//
		//	/** ת��Ϊ�����ͼ��
		//		@remarks
		//		��textInfo�Ŀ�߾�����һ��
		//		@note
		//		�µ���������1/4�洢ԭ�������RGB,���½�1/4�洢alpha,�������Ұ벿��Ϊ��
		//	*/
		//	static void TextureToAtlas(TextureInfo& textInfo);
		//
		//	/** �����ͼ��ת��Ϊ����
		//		@remarks
		//			��textInfo�Ŀ�߾���СΪԭ����һ��
		//		@note
		//			�µ������RGB����ԭ��������1/4����,alpha����ԭ��������1/4����
		//	*/
		//	static void AltasToTexture(TextureInfo& textInfo);
		//
		//	//! \�Ƿ���ѹ������
		//	static bool IsCompressedTextureType(CodecType eType);
		//
		//#if defined OPENGL_ES_VERSION2
		//	//! \brief get the pvr file contenie
		//	static void GetPvrTextureData(const string &strFilePath, UGTextureInfo& textData);
		//	//! \brief get the pvr file contenie
		//	static void GetKtxTextureData(const string &strFilePath, UGTextureInfo& textData);
		//#endif
		//
		//private:
		//
		//
#if _MSC_VER > 1200
	//! \brief ����UGC�����ȡpvr���ظ�ʽ
	//static unsigned int GetPVRPixelFormat(unsigned int eCodecType, unsigned int nComponent);
#endif
	};
	class S3MB_API ImgToolkit
	{
	public:
		//==============================================================
		//�������ظ�ʽ�����ؿ�ȼ���DWORD����İ���unsigned char�Ƶ�ʵ����Ҫ���.
		//! \brief
		  //!  \brief Toolkit
		static unsigned int AlignWidth(PixelFormat PixelFormat, unsigned int lPixelWidth);
		static unsigned int GetValue(const unsigned char* pByte, int nWidthBytes, PixelFormat pixelFormat, unsigned int x, unsigned int y);
		//! \brief
		  //!  \brief Toolkit
		static void SetValue(unsigned char* pByte, int nWidthBytes, PixelFormat pixelFormat, unsigned int x, unsigned int y, unsigned int nValue);
		static TextureData* GetTextureData(wstring filePath, bool bReverse = true);
		static bool JpgToBuffer(wstring filePath, TextureData*& pTextureData, unsigned int& bufferSize, unsigned char*& pBits, int& format, bool bReverse = true);
		static bool PngToBuffer(wstring filePath, TextureData*& pTextureData, unsigned int& BufferSize, unsigned char*& pBits, int& format, Palette& palette, bool bReverse = true);
		static bool GDALToBuffer(wstring filePath, TextureData*& pTextureData, unsigned int& BufferSize, unsigned char*& pBits, int& format, Palette& palette, bool bReverse = true);
		static bool BufferToTextureData(TextureData*& pTextureData, unsigned int bufferSize, unsigned char*& pBits, int format, Palette palette);
		//===================================================
	};
}