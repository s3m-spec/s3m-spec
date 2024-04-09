#pragma once
//#include <stringapiset.h>
#include <stdarg.h>
#include <algorithm>
#include <sstream>
#include <vector>
//#include <winnls.h>
#include "stdafx.h"
#include <string>
using namespace std;

#define U(x)  L ## x

namespace S3MB
{
	class S3MB_API StringHelper
	{
	public:
		//���ַ�����Сд�ַ�ת��Ϊ��д�ַ�
		static wstring StrToUpper(wstring str);

		//�ж��ַ����Ƿ���ͬ
		static bool CompareNoCase(const wstring& strA, const wstring& strB);

		//�и��ַ���
		static void Split(const wstring& s, vector<wstring>&arrStr, const wchar_t flag = ' ');
		static void Split(const string& s, vector<string>& arrStr, const char flag = ' ');

		//ȥ�����ָ���ַ���
		static wstring TrimLeft(wstring& str, wchar_t* pStr = NULL);

		//ȥ���ұ�ָ���ַ���
		static wstring TrimRight(wstring& str, wchar_t* pStr = NULL);
		static wstring TrimRight(wstring& str, wchar_t ch);

		//unicode����ת��Ϊutf8����
		static std::string UNICODE_to_UTF8(const wstring& str);

		//utf8����ת��Ϊunicode����
		static std::wstring UTF8_to_UNICODE(const string& str);

		//ansi����ת��Ϊutf8����
		static std::string ANSI_to_UTF8(const string& str);

		//utf8����ת��Ϊansi����
		static std::string UTF8_to_ANSI(const string& str);

		//��ȡ�ַ�������
		static int GetStrLength(const wchar_t* pStr);
		// ��ʽ���ַ���
		static std::wstring Format(const wchar_t* pStr, ...);
		//! \brief ȡ���ַ����������ұߵ�ָ�����ȵ����ַ���
		//! \param nCount �ֽڸ���
		//! \return �����ұ�ָ�����ȵ����ַ���
		//! \include str_right.cpp
		static wstring Right(const wstring& str, int nCount);

		//! \brief ȡ���ַ�����������ߵ�ָ�����ȵ����ַ���
		//! \param nCount �ֽڸ���
		//! \return �������ָ�����ȵ����ַ���
		//! \include str_right.cpp
		static wstring Left(const wstring& str, int nCount);
		static wstring From(long lVal, unsigned int base = 10);
		static wstring From(unsigned long lVal, unsigned int base = 10);

		//��ȡ�ļ������ļ���
		static wstring GetDir(wstring filePath);

		//��ȡ�ļ�����·��
		static wstring GetAbsolutePath(wstring strSrcPath, wstring path);
		static wstring GetAbsolutePath(wstring relatPath);

		//�ı��ļ���׺
		static wstring ChangeExt(wstring path, wstring ext);
		//��ȡ�ļ���׺
		static wstring GetExt(wstring filePath);
		//�ж��ļ��Ƿ����
		static bool IsFileExist(wstring path);

	};

	class S3MB_API FileType
	{
	public:
		enum EmType
		{
			//! \brief δ֪���ݸ�ʽ��
			none = 0,
			//! \brief Tiff/BigTIFF/GeoTIFF�ļ���
			GTiff = 103,
			//! \brief bitmap�ļ���
			BMP = 121,
			//! \brief jpg�ļ���
			JPG = 122,
			//! \brief portal network graphic(PNG)��
			PNG = 123,
			//! \brief gif�ļ���
			GIF = 124,
			//! \brief tga�ļ���
			TGA = 125,
		};
		//! \brief ���ݺ�׺���õ��ļ����͡�
		//! \param strExtName [in] ��.�ĺ�׺����
		//! \return �ļ���ʽ���͡�
		static EmType ExtNameToFileType(const wstring& strExtName);

		//! \brief �����ļ����͵õ���׺����
		//! \param eFileType [in] �ļ���ʽ���͡�
		//! \return ��.�ĺ�׺����
		static wstring FileTypeToExtName(EmType eFileType);
	};
}
