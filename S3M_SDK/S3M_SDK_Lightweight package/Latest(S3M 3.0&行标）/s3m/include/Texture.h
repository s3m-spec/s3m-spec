#if !defined(TEXTURE_H__7B66F789_1A72_4B27_8D89_5557F1D5CC57__INCLUDED_)
#define TEXTURE_H__7B66F789_1A72_4B27_8D89_5557F1D5CC57__INCLUDED_

#pragma once
#include "S3MBEnums.h"
#include "MemoryStream.h"
#include <string>
#include <iostream>

using namespace std;

namespace S3MB
{	
	// �������ݵķ�װ�ࡣ
	class S3MB_API TextureData
	{
	public:
		// ���캯��
		TextureData();
		// �������캯��
		TextureData(const TextureData& other);
		// ��ֵ����
		TextureData& operator=(const TextureData& other);

		// ��¡�Լ�������
		virtual TextureData* Clone();
		// ��������
		virtual ~TextureData();
		// �ͷ���������
		void Release();

	private:
#if defined OPENGL_ES_VERSION2
		// ѹ��������DXTת����ΪNONE
		void CompressTypeDXTToNONE();
#endif
	public:
		// ���������ڴ�
		unsigned char* m_pBuffer;
		// ����ĸ�
		unsigned int m_nHeight;
		// ����Ŀ�
		unsigned int m_nWidth;
		// ��������
		unsigned int m_nDepth;
		// ��������ظ�ʽ
		PixelFormat m_enFormat;

		// ѹ����������
		TextureCompressType m_eCompressType;

		// ���ݵ��ڴ��С
		unsigned int m_nSize;
	};

	struct S3MB_API TextureDataInfo
	{
		TextureData* m_pTextureData;

		bool m_bMipmap;

		int m_nLevel;

		std::wstring m_strName;

		TextureDataInfo();

		TextureDataInfo(const TextureDataInfo& other);

		TextureDataInfo& operator = (const TextureDataInfo& other);

		~TextureDataInfo();
	};
}
#endif