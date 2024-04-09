#if !defined(S3MBWRITER_H__DEC17B34_A38E_4EF0_8CB2_419D83CB01BD__INCLUDED_)
#define S3MBWRITER_H__DEC17B34_A38E_4EF0_8CB2_419D83CB01BD__INCLUDED_

#pragma once
#include "Shell.h"
#include "S3MBTools.h"

namespace S3MB
{
	class S3MB_API S3MBWriter
	{
	public:
		S3MBWriter();
		~S3MBWriter();

	public:
		// ����ʵ����Ϣ�����������
		void ProcessEntities();
		// ȡ��PagedLOD��ʵ��
		void FillEntityPack(RenderOperationPagedLOD* pROPagedLOD);
		// ȡ��Geode��ʵ��
		void FillEntityPack(RenderOperationGeode* pROGeode);
		// ȡ��Skeleton�Ĳ��ʺ�����
		void FillEntityPack(Skeleton* pSkeleton);
		// ȡ��Material������
		void FillEntityPack(Material* pMaterial3D);
		// �����ļ�������
		bool WriteFile(const wstring& filePath);
		// ������Ҫд���ļ���RenderOperationGroup
		void SetROGroup(RenderOperationGroup* pGroup);
		// �����Ƿ�ı�ͼƬ��ʽ,�Լ�Ŀ��ͼƬ��ʽ�Ƿ�mipmap
		void SetIsChangeTexture(bool bChange, bool bGenerateMipMap = true);
		// ������չ��Ϣ
		void SetExtensions(const std::wstring& strExtensions);
		// ����Skeletonѹ������
		void SetSkeletonCompressParam(SkeletonCompressParam pParam);
		void Clear();

	private:
		// ����Դ�ļ�
		std::wstring m_strFilePath;

		RenderOperationGroup* m_pROGroup;
		SkeletonCompressParam m_SkeletonCompressParam;

		// �Ƕ����õ��ڴ�������
		MemoryStream m_streamShell;

		// �Ǽܷ��õ��ڴ�������
		MemoryStream m_streamSkeleton;

		// IDInfo���õ��ڴ�������
		MemoryStream m_streamIDInfo;

		// �Ƿ���IDInfo
		unsigned char m_bHasIDInfo;

		// ������õ��ڴ�������
		MemoryStream m_streamTexture;

		// ���в��ʷ��� Json
		wstring m_strJsonMaterials;

		// Ŀ��ѹ����ʽ��ԭ��ѹ����ʽ��һ��ʱ���Ƿ����ת��
		bool m_bChangeTexture;

		// ѹ������ʱ�Ƿ񴴽�mipmap
		bool m_bGenerateMipMap;

		// Ŀ��ѹ����������
		unsigned int m_CompressType;
		// �汾
		float m_fVersion;

		std::map<wstring, Skeleton*> m_mapSkeleton;
		std::map<wstring, Material*> m_mapMaterial;
		std::map<wstring, TextureDataInfo*> m_mapTexture;

		// ��չ��Ϣ��JSON��ʽ��
		std::wstring m_strExtensions;
	};
}

#endif