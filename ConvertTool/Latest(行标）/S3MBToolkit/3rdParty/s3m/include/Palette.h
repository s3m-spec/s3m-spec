#if !defined(PALETTE_H__1CABBE54_3EAD_4A5E_97D7_E0D9F49E0D8B__INCLUDED_)
#define PALETTE_H__1CABBE54_3EAD_4A5E_97D7_E0D9F49E0D8B__INCLUDED_

#pragma once
#include "stdafx.h"
#include "S3MBCommon.h"
#include <vector>

namespace S3MB
{
	class S3MB_API Palette
	{
	public:
		Palette();
		~Palette();

	public:
		static unsigned int RGB(unsigned int r, unsigned int g, unsigned int b);
		static unsigned int RGBA(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
		static unsigned char REDVAL(unsigned int clr);

		static unsigned char GREENVAL(unsigned int clr);

		static unsigned char BLUEVAL(unsigned int clr);

		static unsigned char ALPHAVAL(unsigned int clr);
		// ���ҵ�ɫ���λ��
		// paletteEntry Ҫ���ҵĵ�ɫ��
		// return �����ҵ��ĵ�ɫ���λ�ã��Ҳ������� -1
		int Find(PaletteEntry paletteEntry) const;
		// ������������һ����ɫ��
		// paletteEntry Ҫ��ӵĵ�ɫ��
		// return ������Ӻ�,��ɫ���������е�λ��
		int Add(PaletteEntry paletteEntry);
		// ���������Ƴ���ɫ��
		// nIndex Ҫ�Ƴ��ĵ�ɫ���������λ��
		// ˵���� ָ��λ�ñ��������鷶Χ��
		// nCount �Ƴ��ĸ���,Ĭ��Ϊ1
		// return ����ʵ���Ƴ����ĸ���
		// ˵���� ��� nCount>UGArray.size-nIndex ����  nCount>UGArray.size-nIndex
		int RemoveAt(int nIndex, int nCount = 1);
		// ������ָ��λ�ò���һ����ɫ��
		// ˵���� ���ָ��λ�ò������鷶Χ��,���Զ�������[0,size]
		// nIndex Ҫ�����λ��
		// paletteEntry Ҫ����ĵ�ɫ��
		void InsertAt(int nIndex, PaletteEntry paletteEntry);
		// �������ָ��λ���滻��ɫ��
		// nIndex ָ����λ��
		// ˵���� ָ��λ�ñ���������size��Χ֮��
		// paletteEntry Ҫ�滻�ĵ�ɫ��
		void SetAt(int nIndex, PaletteEntry paletteEntry);
		// ��ȡָ��λ�õĵ�ɫ��
		// nIndex ָ����λ��
		// ˵���� ָ��λ�ñ���������size��Χ֮��
		// return ���ػ�õĵ�ɫ��
		PaletteEntry GetAt(int nIndex)const;
		//! �Ƴ�����Ԫ��,ͬʱ������пռ�
		void RemoveAll();
		// �õ������ڲ�ָ��(��ַ����)
		// return ���������ڲ�ָ��(��ַ����) 
		PaletteEntry* GetData();
		// �������������һ������
		// palette Ҫ���ӵ�����
		// return ���ؼ����������ʼλ��
		int Append(const Palette& palette);
		// ���鿽��,ԭ�������ݱ�����
		// palette ���������
		void Copy(const Palette& palette);
		// ����m_Palette���ڴ�ռ�Ϊ nSize, 
		// ˵���� ���ԭ�пռ䲻��, �ڴ�ռ������, 
		// nSize ָ�����µĵ�ɫ�����
		void SetSize(int nSize);
		// �õ����õĵ�ɫ��ĸ���
		// return ���صĵ�ɫ��ĸ���
		int GetSize()const;
		// �ж������Ƿ�Ϊ��
		// return ����շ��� true,���򷵻� false.
		bool IsEmpty()const;

	protected:
		// ����ɫ��������ʵ��
		vector<PaletteEntry> m_Palette;
	};

	class S3MB_API ColorValue
	{
	public:
		ColorValue();
		ColorValue(double red, double green, double blue, double alpha);

		// ���ص�ֵ�ж��������
		// rhs [in]��
		// return �Ƿ���ȡ�
		bool operator==(const ColorValue& rhs) const;

		// ���ز���ֵ�ж��������
		// rhs [in]��
		// return �Ƿ񲻵ȡ�
		bool operator!=(const ColorValue& rhs) const;
		
		// ����R��G��B��A����������ά��ɫ ��
		// nRed ��ɫ��������Χ0-255[in]��
		// nGreen ��ɫ��������Χ0-255[in]��
		// nBlue ��ɫ��������Χ0-255[in]��
		// nAlpha ��͸���ȷ�������Χ0-255[in]��
		void SetValue(int nRed, int nGreen, int nBlue, int nAlpha);
		// ����R��G��B��A����������ά��ɫ��
		// dRed ��ɫ��������Χ0-1.0[in]��
		// dGreen ��ɫ��������Χ0-1[in]��
		// dBlue ��ɫ��������Χ0-1[in]��
		// dAlpha ��͸���ȷ�������Χ0-1[in]��
		void SetValue(double nRed, double nGreen, double nBlue, double nAlpha);
		//  ��ColorValueת������ֵ
		unsigned int GetValue() const;

	public:
		double r;
		double g;
		double b;
		double a;
	};
}

#endif



