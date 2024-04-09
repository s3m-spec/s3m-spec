#pragma once
#include <string>
#include <time.h>
#include "stdafx.h"
using namespace std;
namespace S3MB
{
#define ROUND(x) (((x)>0)?int((x)+0.5):(int((x)-0.5)))
	class S3MB_API S3mbTime
	{
	public:
		//! \brief �������캯��
		S3mbTime(double dValue);
		//! \brief ��ȡʱ��
		double GetTime() const;
		//! \brief ����һ����ʽ���ַ���,��S3mbTime����Ϣ����һ�������Ķ����ַ���
	//! \remarks 
	//! %d Day of month as decimal number (01 �C 31);
	//! %H Hour in 24-hour format (00 �C 23);
	//! %m Month as decimal number (01 �C 12)
	//! %M Minute as decimal number (00 �C 59)
	//! %S Second as decimal number (00 �C 59)
	//! %y Year without century, as decimal number (00 �C 99)
	//! %Y Year with century, as decimal number
		string Format(const char* pFormat) const;

		//! \brief ��double��ֵת��Ϊtm�ṹ
		void GetDateTime(struct tm& tmDest) const;
	private:
		//! \brief ��ȡ��׼��tm�ṹ
		void GetStandardTm(struct tm& tmDest) const;
		double m_time;
	};
	class S3MB_API S3mbVariant
	{
	public:
		//! \brief ֧�ֵ�����
		enum VarType
		{
			//! \brief δ���������
			Null = 0,
			//! \brief ���ֽ�����
			Byte = 1,
			//! \brief ˫�ֽ���������
			Short = 2,
			//! \brief ���ֽ���������
			Integer = 3,
			//! \brief ���ֽ���������
			Long = 4,
			//! \brief ���ֽڸ�������
			Float = 5,
			//! \brief ���ֽڸ�������
			Double = 6,
			//! \brief ʱ������
			Time = 7,
			//! \brief ����������
			Binary = 8,
			//! \brief �ַ���
			String = 9,
			//! \brief ��������
			Date = 10,
			//! \brief ʱ������� 
			TimeStamp = 11,
			//! \brief ��������
			Boolean = 12
		};//Ϊ����UGFieldInfo�е���������ʱ���������ֿ�����ԭ����time������չΪtime date timestamp������ο�UGFieldInfo�ж�Ӧ������

		struct binaryVal {
			//! \brief �洢 Binary ָ����� Stringָ��
			void* pVal;
			//! \brief �洢Binary �������Ĵ�С ���ֽ�Ϊ��λ��
			unsigned int nSize;
		};

		//! \brief ��������
		union VarValue
		{
			unsigned char bVal;
			short sVal;
			int	iVal;
			long  lVal;
			float fVal;
			double dVal;
			double   tmVal; // S3mbTime���ڲ�ʵ��
			struct binaryVal binVal;
		};

	public:
		//! \brief Ĭ�Ϲ��캯��
		S3mbVariant();

		//! \brief ��������
		~S3mbVariant();

		//! \brief �������캯��
		S3mbVariant(const S3mbVariant& varSrc);

		//! \brief unsigned char���͹��캯��
		S3mbVariant(unsigned char bVal);
		//! \brief short���͹��캯��
		S3mbVariant(short sVal);
		//! \brief int���͹��캯��
		S3mbVariant(int iVal);
		//! \brief long���͹��캯��
		S3mbVariant(long lVal);
		//! \brief float���͹��캯��
		S3mbVariant(float fVal);
		//! \brief double���͹��캯��
		S3mbVariant(double dVal);
		//! \brief S3mbTime���͹��캯��
		S3mbVariant(const S3mbTime& tmVal);
		//! \brief unsigned char* ���͹��캯��
		//! \remarks �ڲ�Ϊ�ڴ濽�������ע���ͷ�pData;
		S3mbVariant(const unsigned char* pData, int nSize);
		//! \brief string ���͹��캯��
		S3mbVariant(const string& str);

		//! \brief �� varSrc ��ֵ���塣
		const S3mbVariant& operator=(const S3mbVariant& varSrc);
		//! \brief �� bVal ��ֵ����
		const S3mbVariant& operator=(unsigned char bVal);
		//! \brief �� sVal ��ֵ����
		const S3mbVariant& operator=(short sVal);
		//! \brief �� iVal ��ֵ����
		const S3mbVariant& operator=(int iVal);
		//! \brief �� lVal ��ֵ����
		const S3mbVariant& operator=(long lVal);
		//! \brief �� fVal ��ֵ����
		const S3mbVariant& operator=(float fVal);
		//! \brief �� dVal ��ֵ����
		const S3mbVariant& operator=(double dVal);
		//! \brief �� tmVal ��ֵ����
		const S3mbVariant& operator=(const S3mbTime& tmVal);
		//! \brief �� str ��ֵ����
		const S3mbVariant& operator=(const string& str);

		//! \brief ���ñ���ֵΪbVal 
		void Set(unsigned char bVal);
		//! \brief ���ñ���ֵΪsVal 
		void Set(short sVal);
		//! \brief ���ñ���ֵΪnVal 
		void Set(int nVal);
		//! \brief ���ñ���ֵΪnVal 
		void Set(long lVal);
		//! \brief ���ñ���ֵΪdVal 
		void Set(float dVal);
		//! \brief ���ñ���ֵΪdVal 
		void Set(double dVal);
		//! \brief ���ñ���ֵΪtmVal 
		void Set(const S3mbTime& tmVal);
		//! \brief ���ñ���ֵΪpDataָ����ַ���
		void Set(const unsigned char* pData, unsigned int nSize);
		//! \brief ���ñ���ֵΪstr 
		void Set(const string& str);
		//! \brief ����Ϊ��
		void SetNull();

		//! \brief �ж��Ƿ����
		//! \remarks ���Ͳ����, ����Ϊ�����(COleVariant�Ĵ���ʽ)
		bool operator==(const S3mbVariant& varSrc) const;

		//! \brief �ж��Ƿ����
		//! \remarks ���Ͳ����, ����Ϊ�����(COleVariant�Ĵ���ʽ)
		bool operator!=(const S3mbVariant& varSrc) const;

		//! \brief �жϴ�С
		//! \remarks ���Ͳ����, ����Ϊ�����(COleVariant�Ĵ���ʽ)
		bool operator<(const S3mbVariant& varSrc) const;

		//! \brief ���
		void Clear();

		//! \brief ��ȡ��������
		VarType GetType() const
		{
			return m_nType;
		}

		//! \brief ��ȡ����ֵ
		VarValue& GetValue()
		{
			return m_value;
		}

		//! \brief ��ȡ����ֵ
		const VarValue& GetValue() const
		{
			return m_value;
		}

		//! \brief ת��Ϊdouble����
		double ToDouble() const;
		//! \brief ת��Ϊint32 ����
		int ToInt() const;
		//! \brief ת��Ϊint64 ����
		long ToLong() const;
		//! \brief ת��ΪString����
		//! \remarks ����UGTime���ͣ�ת�������ݿ�ʶ��ĸ�ʽҲ���� %Y-%m-%d %H:%M:%S ��
		wstring ToString() const;
		//! \brief ת��ΪString����
		//! \remarks ����UGTime���ͣ�ת���ɱ��ص�ǰ��ʱ����,�����������ͺ�ToString()����һ����
		string ToStringLocal() const;

	public:
		//! \brief ��������
		VarType m_nType;

		//! \brief ����ֵ
		VarValue m_value;

	};
}