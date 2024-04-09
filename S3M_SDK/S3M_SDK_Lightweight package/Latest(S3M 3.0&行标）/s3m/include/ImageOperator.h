#if !defined(IMAGEOPERATOR_H__506D4D04_3FA2_4009_9B39_77F396F82FE8__INCLUDED_)
#define IMAGEOPERATOR_H__506D4D04_3FA2_4009_9B39_77F396F82FE8__INCLUDED_

#pragma once
#include "Palette.h"
#include "S3MBCommon.h"
#include "Texture.h"
#include <vector>

namespace S3MB
{
	class S3MB_API ImageOperator
	{
	public:
		// format ԭͼ������ظ�ʽ
		// width,height ԭͼ��Ŀ�Ⱥ͸߶�
		// in ԭͼ�������
		// comtype ͼ��ѹ������
		// out  ѹ��������,�ڲ�����ռ�
		// return ����ѹ����ͼ�����ݵĴ�С
		static unsigned int Encode(const unsigned int nPixSize, unsigned int& nWidth, unsigned int& nHeight, unsigned char* pBufferIn, unsigned char** ppBufferOut, unsigned int eCodecType = TC_DXT5, bool bGeneMipmaps = false);

		// ��ѹ��dxtn
		static unsigned int Decode(const unsigned int nPixSize, unsigned int nWidth, unsigned int nHeight, unsigned char** ppBufferOut, const unsigned char* pBufferIn, unsigned int eCodecType, bool bGeneMipmaps = false);

		// ����ָ���Ĵ�С����ͼƬ
		static void Scale(const unsigned int components, unsigned int widthin, unsigned int heightin, unsigned char* pBufferIn,
			unsigned int widthout, unsigned int heightout, unsigned char* pBufferOut);
		// ��ȡmipmap������
		static unsigned int GetMipMapData(unsigned int nWidth, unsigned int nHeight, const unsigned char* pBufferIn, unsigned char** ppBufferOut, vector<unsigned int>& arrByteOffset);

		// ��ȡָ��ѹ����ʽ������ѹ����Ĵ�С
		static unsigned int GetCompressedTextureSize(const unsigned int nPixSize, unsigned int nWidth, unsigned int nHeight, unsigned int eCodecType, bool bIsMipmaps = false);

		// ���ݿ�߻�ȡmipMap�㼶
		static unsigned int GetMipMapLevel(const unsigned int nWidth, const unsigned int nHeight);
	};

	class S3MB_API ImgToolkit
	{
	public:
		// ==============================================================
		// �������ظ�ʽ�����ؿ�ȼ���DWORD����İ���unsigned char�Ƶ�ʵ����Ҫ���.
		//
		static unsigned int AlignWidth(PixelFormat PixelFormat, unsigned int lPixelWidth);
		static unsigned int GetValue(const unsigned char* pByte, int nWidthBytes, PixelFormat pixelFormat, unsigned int x, unsigned int y);
		//
		static void SetValue(unsigned char* pByte, int nWidthBytes, PixelFormat pixelFormat, unsigned int x, unsigned int y, unsigned int nValue);
		static TextureData* GetTextureData(wstring filePath, bool bReverse = true);
		static bool JpgToBuffer(wstring filePath, TextureData*& pTextureData, unsigned int& bufferSize, unsigned char*& pBits, int& nBitCnt, bool bReverse = true);
		static bool PngToBuffer(wstring filePath, TextureData*& pTextureData, unsigned int& BufferSize, unsigned char*& pBits, int& nBitCnt, Palette& palette, bool bReverse = true);
		static bool BufferToTextureData(TextureData*& pTextureData, unsigned int bufferSize, unsigned char*& pBits, int nBitCnt, Palette palette);
		// ===================================================
	};

	class S3MB_API MemImage
	{
	public:
		// format ԭͼ������ظ�ʽ
		// width,height ԭͼ��Ŀ�Ⱥ͸߶�
		// in ԭͼ�������
		// comtype ͼ��ѹ������
		// out  ѹ��������,�ⲿ��������㹻�Ŀռ�
		// return ����ѹ����ͼ�����ݵĴ�С
		static unsigned int Encode(const unsigned int pixsize, unsigned int width, unsigned int height, const unsigned char* in, unsigned char *out);

		// ��ѹ��dxtn
		static void Decode(const unsigned int pixsize, unsigned int width, unsigned int height, unsigned char* out, const unsigned char *in);

		// ����ָ���Ĵ�С����ͼƬ
		static void Scale(const unsigned int components, unsigned int widthin, unsigned int heightin, unsigned char *in,
			unsigned int widthout, unsigned int heightout, unsigned char *out);

	};
}

#endif