#ifndef UGPALETTE_H
#define UGPALETTE_H

#include <new>
#include <vector>
#include "stdafx.h"
using namespace std;
namespace S3MB
{
	static union
	{
		int nTest;
		char cTest[sizeof(int)];
	}un_bigendina = { 1 };
#define  ISBIGENDIAN (un_bigendina.cTest[0] != 1)
	typedef unsigned int UGColor;
	class S3MB_API Palette
	{
	public:
		//! \brief
		struct PaletteEntry  //! \brief һ����ɫ����Ϣ
		{
			unsigned char peRed;      //! \brief ��ɫ�ı���
			unsigned char peGreen;    //! \brief ��ɫ�ı���
			unsigned char peBlue;     //! \brief ��ɫ�ı���
			unsigned char peFlags;    //! \brief ��ʶ��

			PaletteEntry()
			{
				peRed = 0;
				peGreen = 0;
				peBlue = 0;
				peFlags = 0;
			}
		};

	public:
		//!  \brief Toolkit
		Palette();
		//!  \brief Toolkit
		~Palette();

	public:
		static UGColor UGRGB(unsigned int r, unsigned int g, unsigned int b);
		static UGColor RGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
		static unsigned char REDVAL(UGColor clr);

		static unsigned char GREENVAL(UGColor clr);

		static unsigned char BLUEVAL(UGColor clr);

		static unsigned char ALPHAVAL(UGColor clr);
		//! \brief ���ҵ�ɫ���λ��
		//! \param paletteEntry Ҫ���ҵĵ�ɫ��
		//! \return �����ҵ��ĵ�ɫ���λ�ã��Ҳ������� -1
		int Find(PaletteEntry paletteEntry) const;
		//! \brief ������������һ����ɫ��
		//! \param paletteEntry Ҫ��ӵĵ�ɫ��
		//! \return ������Ӻ�,��ɫ���������е�λ��
		int Add(PaletteEntry paletteEntry);
		//! \brief ���������Ƴ���ɫ��
		//! \param nIndex Ҫ�Ƴ��ĵ�ɫ���������λ��
		//! \remarks ָ��λ�ñ��������鷶Χ��
		//! \param nCount �Ƴ��ĸ���,Ĭ��Ϊ1
		//! \return ����ʵ���Ƴ����ĸ���
		//! \remarks ��� nCount>UGArray.size-nIndex ����  nCount>UGArray.size-nIndex
		int RemoveAt(int nIndex, int nCount = 1);
		//! \brief ������ָ��λ�ò���һ����ɫ��
		//! \remarks ���ָ��λ�ò������鷶Χ��,���Զ�������[0,size]
		//! \param nIndex Ҫ�����λ��
		//! \param paletteEntry Ҫ����ĵ�ɫ��
		void InsertAt(int nIndex, PaletteEntry paletteEntry);
		//! \brief �������ָ��λ���滻��ɫ��
		//! \param nIndex ָ����λ��
		//! \remarks ָ��λ�ñ���������size��Χ֮��
		//! \param paletteEntry Ҫ�滻�ĵ�ɫ��
		void SetAt(int nIndex, PaletteEntry paletteEntry);
		//! \brief ��ȡָ��λ�õĵ�ɫ��
		//! \param nIndex ָ����λ��
		//! \remarks ָ��λ�ñ���������size��Χ֮��
		//! \return ���ػ�õĵ�ɫ��
		PaletteEntry GetAt(int nIndex)const;
		//! �Ƴ�����Ԫ��,ͬʱ������пռ�
		void RemoveAll();
		//! \brief �õ������ڲ�ָ��(��ַ����)
		//! \return ���������ڲ�ָ��(��ַ����) 
		PaletteEntry* GetData();
		//! \brief �������������һ������
		//! \brief palette Ҫ���ӵ�����
		//! \return ���ؼ����������ʼλ��
		int Append(const Palette& palette);
		//! \brief ���鿽��,ԭ�������ݱ�����
		//! \param palette ���������
		void Copy(const Palette& palette);
		//! \brief ����m_Palette���ڴ�ռ�Ϊ nSize, 
		//! \remarks ���ԭ�пռ䲻��, �ڴ�ռ������, 
		//! \param nSize ָ�����µĵ�ɫ�����
		void SetSize(int nSize);
		//! \brief �õ����õĵ�ɫ��ĸ���
		//! \return ���صĵ�ɫ��ĸ���
		int GetSize()const;
		//! \brief �ж������Ƿ�Ϊ��
		//! \return ����շ��� true,���򷵻� false.
		bool IsEmpty()const;

		//! \brief ����ɫ����ɫת��ɫ��Colorset lugw
		//UGColorset ConvertToColorset();

	protected:
		//! \brief ����ɫ��������ʵ��
		vector<PaletteEntry> m_Palette;

	};

	struct S3MB_API ImageData
	{
		//!  \brief Toolkit
		int nWidth;		//! \brief Image�Ŀ�
		  //!  \brief Toolkit
		int nHeight;		//! \brief Image�ĸ�
		  //!  \brief Toolkit
		int nWidthBytes;	//! \brief Image���ֽ���������nWidth*ÿ�������ֽ���������32λ�ֽ�������4
		  //!  \brief Toolkit
		unsigned char btPlanes;	//! \brief ��ɫ����ɫ��Ŀ
		  //!  \brief Toolkit
		unsigned char btBitsPixel; //! \brief ÿ�����ص�bit��������32��24
		  //!  \brief Toolkit
		unsigned char btTextureCodecType;	//! \brief ����ѹ����ʽ
		  //!  \brief Toolkit
		bool bBkTransparent;
		//!  \brief Toolkit
		UGColor clrBack;
		//!  \brief Toolkit
		Palette palette;	//! \brief ��ɫ��
		  //!  \brief Toolkit
		void* pBits;		//! \brief �ڴ����飬ͨ�������洢��ɫֵ

		  //!  \brief Toolkit
		  //!  \brief Toolkit
		ImageData()
		{
			//!  \brief Toolkit
			nWidth = 0;
			//!  \brief Toolkit
			nHeight = 0;
			//!  \brief Toolkit
			nWidthBytes = 0;
			//!  \brief Toolkit
			btPlanes = 1;
			//!  \brief Toolkit
			btBitsPixel = 0;
			//!  \brief Toolkit
			btTextureCodecType = 0;
			//!  \brief Toolkit
			bBkTransparent = false;
			//!  \brief Toolkit
			clrBack = Palette::UGRGB(255, 255, 255);
			//!  \brief Toolkit
			pBits = NULL;
			//!  \brief Toolkit
		}

		void ConvertData()
		{
			if (pBits != NULL)
			{
				void* pByteDest = GetConvertedBits();
				delete[](unsigned char*)pBits;
				pBits = pByteDest;
			}
		}

		// ���÷������ͷ��ڴ�
		void* GetConvertedBits()
		{
			unsigned char* pByteDest = NULL;
			if (pBits != NULL)
			{
				int nCount = nWidthBytes * nHeight;
				pByteDest = new unsigned char[nCount];
				unsigned char* pByteSrc = (unsigned char*)pBits;
				unsigned char* pByteTem = NULL;
				for (int i = 0; i < nHeight; i++)
				{
					pByteTem = pByteDest + (nHeight - 1 - i) * nWidthBytes;
					::memcpy(pByteTem, pByteSrc, nWidthBytes);
					pByteSrc += nWidthBytes;
				}
			}
			return pByteDest;
		}

		ImageData* Clone()
		{
			ImageData* pImageDataDes = NULL;
			try {
				pImageDataDes = new ImageData;
				pImageDataDes->pBits = new unsigned char[this->nHeight * this->nWidthBytes];
			}
			catch (std::bad_alloc) {
				delete pImageDataDes;
				return NULL;
			}
			pImageDataDes->btBitsPixel = this->btBitsPixel;
			pImageDataDes->btPlanes = this->btPlanes;
			pImageDataDes->nHeight = this->nHeight;
			pImageDataDes->nWidth = this->nWidth;
			pImageDataDes->nWidthBytes = this->nWidthBytes;
			pImageDataDes->bBkTransparent = this->bBkTransparent;
			pImageDataDes->clrBack = this->clrBack;
			pImageDataDes->palette.Copy(this->palette);
			::memcpy(pImageDataDes->pBits, this->pBits, pImageDataDes->nHeight * pImageDataDes->nWidthBytes);
			return pImageDataDes;
		}

		void DealWithTransparentColors()
		{
			if (this->pBits != NULL)
			{
				switch (this->btBitsPixel)
				{
				case 32:
				{
					int count = this->nHeight * this->nWidthBytes / 4;
					UGColor* pRGBAs = (UGColor*)this->pBits;
					UGColor ugColor;
					int transparent = 0;
					for (int i = 0; i < count; i++)
					{
						ugColor = pRGBAs[i];
						transparent = 255 - Palette::ALPHAVAL(ugColor);
						if (transparent >= 255)
						{
							pRGBAs[i] = Palette::RGBA(255, 255, 255, 0);
						}
						else if (transparent < 255 && transparent > 0)
						{
							pRGBAs[i] = Palette::RGBA(Palette::REDVAL(ugColor) * (255 - transparent) / 255 + transparent,
								Palette::GREENVAL(ugColor) * (255 - transparent) / 255 + transparent,
								Palette::BLUEVAL(ugColor) * (255 - transparent) / 255 + transparent,
								255);
						}
					}
				}
				break;
				}
			}
		}

		void ReverseData()
		{
			if (pBits != NULL)
			{
				unsigned char* pByteSrc = NULL;
				unsigned char* pByteDest = NULL;
				unsigned char* pByteTem = new unsigned char[nWidthBytes];
				int nCount = nHeight / 2;
				for (int i = 0; i < nCount; ++i)
				{
					pByteDest = (unsigned char*)pBits + (nHeight - 1 - i) * nWidthBytes;
					pByteSrc = (unsigned char*)pBits + i * nWidthBytes;
					::memcpy(pByteTem, pByteDest, nWidthBytes);
					::memcpy(pByteDest, pByteSrc, nWidthBytes);
					::memcpy(pByteSrc, pByteTem, nWidthBytes);
				}

				if (pByteTem != NULL)
				{
					delete[] pByteTem;
				}
			}
		}
	};

	class S3MB_API ColorValue
	{
	public:
		ColorValue() :
			r(0), g(0), b(0), a(0) {}
		ColorValue(double red, double green, double blue, double alpha) :
			r(red), g(green), b(blue), a(alpha) {}
		double r;
		double g;
		double b;
		double a;
		//! \brief ����R��G��B��A����������ά��ɫ ��
		//! \param nRed ��ɫ��������Χ0-255[in]��
		//! \param nGreen ��ɫ��������Χ0-255[in]��
		//! \param nBlue ��ɫ��������Χ0-255[in]��
		//! \param nAlpha ��͸���ȷ�������Χ0-255[in]��
		void SetValue(int nRed, int nGreen, int nBlue, int nAlpha);
		//! \brief ����R��G��B��A����������ά��ɫ��
		//! \param dRed ��ɫ��������Χ0-1.0[in]��
		//! \param dGreen ��ɫ��������Χ0-1[in]��
		//! \param dBlue ��ɫ��������Χ0-1[in]��
		//! \param dAlpha ��͸���ȷ�������Χ0-1[in]��
		void SetValue(double nRed, double nGreen, double nBlue, double nAlpha);
		//! \brief  ��ColorValueת��ΪUGColor
		UGColor GetValue() const;
	};

}

#endif



