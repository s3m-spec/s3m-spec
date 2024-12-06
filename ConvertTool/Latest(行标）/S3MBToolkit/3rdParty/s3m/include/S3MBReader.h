#if !defined(S3MBREADER_H__163B95BB_0AD1_4574_B93D_E66CC3D82755__INCLUDED_)
#define S3MBREADER_H__163B95BB_0AD1_4574_B93D_E66CC3D82755__INCLUDED_

#pragma once
#include "Shell.h"

namespace S3MB
{
	class S3MB_API S3MBReader
	{
	public:
		S3MBReader();
		~S3MBReader();

	public:
		// ����ȡ��s3mb�ļ�ת��ΪRenderOperationGroup
		void ReadFile(const wstring& strFilePath);
		// ���������ж�ȡs3mb
		bool LoadS3MBFromStream(void* buffer, unsigned int bufferSize);
		// ���ģ����Ϣ������̨
		void OutputSkeletonInfoToConsole();
		// ��ȡ��ȡ����RenderOperationGroup
		RenderOperationGroup* GetRenderOperationGroup();
		// ��ȡ��չ��Ϣ
		std::wstring GetExtensions() const;
		void Clear();

	private:
		// ����Դ�ļ�
		std::wstring m_strFilePath;

		RenderOperationGroup* m_pROGroup;
		// ��չ��Ϣ��JSON��ʽ��
		std::wstring m_strExtensions;
	};
}

#endif