#pragma once
#include "StringHelper.h"
#include "Shell.h"
namespace S3MB
{
	class S3MB_API S3MBWriter
	{
	public:
		S3MBWriter()
		{
			m_bChangeTexture = true;
			m_CompressType = 14;//dxtѹ��
			m_bGenerateMipMap = true;
			m_fVersion = 1.0f;
		}
		~S3MBWriter() {}
	public:
		void ProcessSaveInfo(int vertexCompressOptions = 0);
		//! \brief ȡ��PagedLOD��ʵ��
		void FillEntityPack(RenderOperationPagedLOD* pROPagedLOD);
		//! \brief ȡ��Geode��ʵ��
		void FillEntityPack(RenderOperationGeode* pROGeode);
		//! \brief ȡ��Geometry�Ĳ��ʺ�����
		void FillEntityPack(Geometry* pGeometry);
		//! \brief ȡ��Material������
		void FillEntityPack(Material* pMaterial3D);
		void SetVersion(float fVersion);
		bool Save(int vertexCompressOptions = 0);
		//������Ҫд���ļ���RenderOperationGroup
		void SetROGroup(RenderOperationGroup* pGroup) { this->m_pROGroup = pGroup; }
		//���õ����ļ�·��
		void SetFilePath(wstring filePath) {
			if (filePath.find(L':') == wstring::npos)
				this->m_strFilePath = StringHelper::GetAbsolutePath(filePath);
			else
				this->m_strFilePath = filePath;
		}
		//�����Ƿ�ı�ͼƬ��ʽ,�Լ�Ŀ��ͼƬ��ʽ�Ƿ�mipmap
		void SetIsChangeTexture(bool bChange, bool bGenerateMipMap = true) {
			this->m_bChangeTexture = bChange; 
			this->m_bGenerateMipMap = bGenerateMipMap;
		}

		void Clear();
	private:
		// ����Դ�ļ�
		std::wstring m_strFilePath;

		RenderOperationGroup* m_pROGroup;

		//! \brief �Ƕ����õ��ڴ�������
		MemoryStream m_streamShell;

		//! \brief �Ǽܷ��õ��ڴ�������
		MemoryStream m_streamGeometry;

		//! \brief SelectionInfo���õ��ڴ�������
		MemoryStream m_streamSelectionInfo;

		//! \brief �Ƿ���SelectionInfo
		unsigned char m_bHasSelectionInfo;

		//! \brief �������õ��ڴ�������
		MemoryStream m_streamTexture;

		//! \brief ���в��ʷ��� Json
		wstring m_strJsonMaterials;

		//! \brief Ŀ��ѹ����ʽ��ԭ��ѹ����ʽ��һ��ʱ���Ƿ����ת��
		bool m_bChangeTexture;

		//! \brief ѹ������ʱ�Ƿ񴴽�mipmap
		bool m_bGenerateMipMap;

		// Ŀ��ѹ����������
		unsigned int m_CompressType;
		//�汾
		float m_fVersion;
		//! \brief ����Ϊ HashCode ��Ϊ��������
		std::map<wstring, Geometry*> m_mapGeometry;
		std::map<wstring, Material*> m_mapMaterial;
		std::map<wstring, TextureDataInfo*> m_mapTexture;
	};
}