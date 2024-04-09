#if !defined(MEMORYSTREAM_H__E8796474_8DB7_4AAE_BAD5_171A8EDFC823__INCLUDED_)
#define MEMORYSTREAM_H__E8796474_8DB7_4AAE_BAD5_171A8EDFC823__INCLUDED_

#pragma once
#include "stdafx.h"
#include <string>
#include "S3MBCommon.h"
#include "S3MBUtils.h"

namespace S3MB
{
	class S3MB_API MemoryStream
	{
	public:
		// ���캯��
		MemoryStream();
		~MemoryStream();

		void Close();

	public:
		// ���ز�����
		template<typename T>
		MemoryStream& operator <<(const T& value)
		{
			if (m_pBuffer && m_WtPos + sizeof(T) <= m_nSize)
			{
				*(T*)(m_pBuffer + m_WtPos) = value;
				m_WtPos += sizeof(T);
			}
			else if (m_bManaged)
			{
				ResizeSpace();
				*(T*)(m_pBuffer + m_WtPos) = value;
				m_WtPos += sizeof(T);
			}
			return *this;
		}
		template<typename T>
		MemoryStream& operator >>(T& value)
		{
			if (m_pBuffer && m_RdPos < m_nSize)
			{
				value = *((T*)(m_pBuffer + m_RdPos));
				m_RdPos += sizeof(T);
			}
			return *this;
		}

		MemoryStream& operator <<(const char* pBuffer);
		MemoryStream& operator <<(const std::string str);
		MemoryStream& operator <<(const wchar_t* pBuffer);
		MemoryStream& operator <<(const std::wstring str);

		MemoryStream& operator >>(std::string& str);
		MemoryStream& operator >>(std::wstring& str);

	public:
		// ���ڶ�ȡ��
		void Init(void* buffer, std::size_t size, bool bManaged = false, StringEncodeType typeName = UTF8);
		// ����д����
		void Init(std::size_t size = 4096, std::size_t sizeAdd = 4096, StringEncodeType typeName = UTF8);
		// ������Ӵ����й̶���С���ڴ����ݵ�Ŀ���ڴ���
		template<typename T>
		void Load(T* buffer, std::size_t size)
		{
			if (m_pBuffer && m_RdPos + size * sizeof(T) <= m_nSize)
			{
				for (int i = 0; i < size; i++)
				{
					*buffer = *(T*)(m_pBuffer + m_RdPos);
					buffer++;
					m_RdPos += sizeof(T);
				}
			}
		}
		// ������Ӹ����ڴ���п����̶���С�����ݵ�������
		template<typename T>
		void Save(T* buffer, std::size_t size)
		{
			if (size == 0)
			{
				return;
			}
			if (m_pBuffer && m_WtPos + size * sizeof(T) < m_nSize)
			{
				for (int i = 0; i < size; i++)
				{
					*(T*)(m_pBuffer + m_WtPos) = *buffer;
					buffer++;
					m_WtPos += sizeof(T);
				}
			}
			else
			{
				do
				{
					ResizeSpace(size * sizeof(T));
				} while (m_WtPos + size * sizeof(T) > m_nSize);

				for (int i = 0; i < size; i++)
				{
					*(T*)(m_pBuffer + m_WtPos) = *buffer;
					buffer++;
					m_WtPos += sizeof(T);
				}
			}
		}
		// ǳ���������ƶ�ָ��λ��
		unsigned char* TakeStream(std::size_t size);
		// ��ȡ�ڴ���ָ��
		unsigned char* GetDataPtr();
		// ��ȡ��ʼ/��λ��
		std::size_t GetReadPosition();
		// ��ȡ����/дλ��
		std::size_t GetWritePosition();
		// ��ȡ���ݳ���
		std::size_t GetLength();
		// �������ݶ�ȡλ��
		void SetReadPosition(std::size_t lPos);	
		// ���·����ڴ��С
		bool ResizeSpace(std::size_t sizeAdd = 4096);

	private:
		unsigned char* m_pBuffer;
		std::size_t m_nSize;// �����ڴ��ܴ�С
		std::size_t m_SizeAdd;// �ڴ��Զ�������С
		std::size_t m_WtPos;
		std::size_t m_RdPos;
		bool m_bManaged;// �Ƿ��й��ڴ�
		StringEncodeType m_type;// �ַ����������
	};
}
#endif