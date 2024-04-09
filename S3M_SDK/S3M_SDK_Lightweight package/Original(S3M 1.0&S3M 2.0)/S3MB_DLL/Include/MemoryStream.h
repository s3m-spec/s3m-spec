#ifndef  _MEM_STREAM_H_
#define   _MEM_STREAM_H_
#include "stdafx.h"
#include <string>
#include "StringHelper.h"
using namespace std;
namespace S3MB
{
	class MemoryStream
	{
		enum stringType { UTF8, Ansi, Unicode };
	public:
		//���캯��
		MemoryStream()
		{
			m_WtPos = 0;
			m_RdPos = 0;
			m_bManaged = false;
			m_type = UTF8;
			m_SizeAdd = 4096;
		}
		explicit MemoryStream(std::size_t size, std::size_t sizeAdd = 4096, stringType typeName = UTF8)
		{
			m_pBuffer = new unsigned char[size];
			memset(m_pBuffer, 0, size);
			m_nSize = size;
			m_RdPos = 0;
			rdPtr = m_pBuffer;
			m_WtPos = 0;
			wtPtr = m_pBuffer;
			m_bManaged = true;
			m_type = typeName;
			m_SizeAdd = sizeAdd;
		}
		MemoryStream(void* buffer, std::size_t size, std::size_t sizeAdd = 4096, stringType typeName = UTF8)
		{
			m_pBuffer = (unsigned char*)buffer;
			m_nSize = size;
			m_WtPos = size;
			wtPtr = m_pBuffer + size;
			rdPtr = m_pBuffer;
			m_RdPos = 0;
			m_bManaged = false;
			m_type = typeName;
			m_SizeAdd = sizeAdd;
		}
		~MemoryStream()
		{
			if (m_bManaged)
			{
				delete[] m_pBuffer;
			}
			m_pBuffer = NULL;
			m_WtPos = 0;
		}
		//�ͷ��ڴ�
		void Clear()
		{
			this->~MemoryStream();
		}
	public://���ز�����
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

		MemoryStream& operator <<(const char* pBuffer)
		{
			std::size_t size = strlen(pBuffer);
			if (m_pBuffer && m_WtPos + size <= m_nSize)
			{
				memcpy(m_pBuffer + m_WtPos, pBuffer, size);
				m_WtPos += size;
			}
			else if (m_bManaged)
			{
				do
				{
					ResizeSpace();
				} while (m_WtPos + size > m_nSize);
				memcpy(m_pBuffer + m_WtPos, pBuffer, size);
				m_WtPos += size;
			}
			return *this;
		}
		MemoryStream& operator <<(const std::string str)
		{
			string temp;
			if (m_type == UTF8)
			{
				temp = StringHelper::ANSI_to_UTF8(str);
			}
			else
			{
				temp = str;
			}
			*this << (unsigned int)temp.size();
			return operator <<(temp.c_str());
		}
		//MemoryStream& operator >>(const char*& pBuffer)
		//{
		//	if (m_pBuffer && m_RdPos < m_nSize)
		//	{
		//		const char* p = (const char*)(m_pBuffer + m_RdPos);
		//		std::size_t size = strlen(p);
		//		if (size + m_RdPos <= m_nSize)
		//		{
		//			pBuffer = p;
		//			m_RdPos += size;
		//		}
		//	}
		//	return *this;
		//}
		MemoryStream& operator >>(std::string& str)
		{
			unsigned int size = 0;
			*this >> size;
			if (size == 0)
			{
				str = "";
			}
			else if (m_pBuffer && m_RdPos < m_nSize)
			{
				const char* p = (const char*)(m_pBuffer + m_RdPos);
				if (size + m_RdPos <= m_nSize)
				{
					if (m_type == UTF8)
					{
						string temp;
						temp.assign(p, p + size);
						str = StringHelper::UTF8_to_ANSI(temp);
					}
					else
					{
						str.assign(p, p + size);
					}
					m_RdPos += size;
				}
			}
			return *this;
		}

		MemoryStream& operator <<(const wchar_t* pBuffer)
		{
			std::size_t size = wcslen(pBuffer) * sizeof(wchar_t);
			if (m_pBuffer && m_WtPos + size <= m_nSize)
			{
				memcpy(m_pBuffer + m_WtPos, pBuffer, size);
				m_RdPos += size;
			}
			else if (m_bManaged)
			{
				do
				{
					ResizeSpace();
				} while (m_WtPos + size > m_nSize);
				memcpy(m_pBuffer + m_WtPos, pBuffer, size);
				m_RdPos += size;
			}
			return *this;
		}
		MemoryStream& operator <<(const std::wstring str)
		{
			if (m_type == UTF8)
			{
				std::string utf8String = StringHelper::UNICODE_to_UTF8(str);
				*this << (unsigned int)utf8String.size();
				return operator <<(utf8String.c_str());
			}
			else
			{
				return operator <<(str.c_str());
			}
		}
		//MemoryStream& operator >>(const wchar_t*& pBuffer)
		//{
		//	if (m_pBuffer && m_RdPos < m_nSize)
		//	{
		//		const wchar_t* p = (const wchar_t*)(m_pBuffer + m_RdPos);
		//		std::size_t size = wcslen(p) * sizeof(wchar_t);
		//		if (size + m_RdPos < m_nSize)
		//		{
		//			pBuffer = p;
		//			m_RdPos += size + sizeof(wchar_t);
		//		}
		//	}
		//	return *this;
		//}
		MemoryStream& operator >>(std::wstring& str)
		{
			unsigned int size = 0;
			*this >> size;
			if (size == 0)
			{
				str = U("");
			}
			else if (m_pBuffer && m_RdPos < m_nSize)
			{
				if (m_type == UTF8)
				{
					const char* p = (const char*)(m_pBuffer + m_RdPos);
					if (size + m_RdPos <= m_nSize)
					{

						string temp;
						temp.assign(p, p + size);
						str = StringHelper::UTF8_to_UNICODE(temp);
					}
					m_RdPos += size;
				}
				//else
				//{
				//	str.assign(p, p + size - 1);
				//}
			}
			return *this;
		}
	public:
		//���ڶ�ȡ��
		void Init(void* buffer, std::size_t size, bool bManaged = false, stringType typeName = UTF8)
		{
			m_pBuffer = (unsigned char*)buffer;
			m_nSize = size;
			m_WtPos = size;
			m_RdPos = 0;
			m_bManaged = bManaged;
			m_type = typeName;
		}
		//����д����
		void Init(std::size_t size = 4096, std::size_t sizeAdd = 4096, stringType typeName = UTF8)
		{
			m_pBuffer = new unsigned char[size];
			memset(m_pBuffer, 0, size);
			m_nSize = size;
			m_WtPos = 0;
			wtPtr = m_pBuffer;
			rdPtr = m_pBuffer;
			m_RdPos = 0;
			m_bManaged = true;
			m_type = typeName;
			m_SizeAdd = sizeAdd;
		}
		//������Ӵ����й̶���С���ڴ����ݵ�Ŀ���ڴ���
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
		//������Ӹ����ڴ���п����̶���С�����ݵ�������
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
		//ǳ���������ƶ�ָ��λ��
		unsigned char* TakeStream(std::size_t size)
		{
			if (m_pBuffer && m_RdPos + size <= m_nSize)
			{
				unsigned char* p = m_pBuffer + m_RdPos;
				m_RdPos += size;
				return p;
			}
			return nullptr;
		}
		unsigned char* GetDataPtr()
		{
			return m_pBuffer;
		}
		std::size_t GetReadPosition()
		{
			return m_RdPos;
		}
		std::size_t GetWritePosition()
		{
			return m_WtPos;
		}
		std::size_t GetLength()
		{
			return m_WtPos;
		}
		void SetReadPosition(std::size_t lPos)
		{
			m_RdPos = lPos;
			return;
		}
		//���·����ڴ��С
		bool ResizeSpace(std::size_t sizeAdd = 4096)
		{
			if (sizeAdd < m_SizeAdd)
			{
				void* p = realloc(m_pBuffer, m_nSize + m_SizeAdd);
				if (p == NULL)return false;
				m_pBuffer = (unsigned char*)p;
				m_nSize += m_SizeAdd;
			}
			else
			{
				void* p = realloc(m_pBuffer, m_nSize + sizeAdd + m_SizeAdd);
				if (p == NULL)return false;
				m_pBuffer = (unsigned char*)p;
				m_nSize += m_SizeAdd + sizeAdd;
			}
			return true;
		}
	private:
		//MemoryStream(const MemoryStream& memStream);
		//const MemoryStream& operator =(const MemoryStream&);
	private:
		unsigned char* m_pBuffer;
		//��ʱû��
		unsigned char* rdPtr;
		//��ʱû��
		unsigned char* wtPtr;
		std::size_t m_nSize;
		std::size_t m_SizeAdd;
		std::size_t m_WtPos;
		std::size_t m_RdPos;
		bool m_bManaged;
		stringType m_type;
	};
}
#endif