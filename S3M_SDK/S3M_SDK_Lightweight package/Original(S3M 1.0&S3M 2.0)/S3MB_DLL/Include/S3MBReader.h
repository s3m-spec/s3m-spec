#include <vector>
#include <iostream>
#include <codecvt>
#include <locale>
#include <map>

#include "Skeleton.h"
#include "MemoryStream.h"
#include "Material.h"
#include "Texture.h"
#include "Shell.h"
#include "S3MBLayerInfos.h"


using namespace std;
namespace S3MB
{
	class S3MB_API S3MBReader
	{
	public:
		S3MBReader() { m_pROGroup = nullptr; } 
		~S3MBReader();

	public:
		//����ȡ��s3mb�ļ�ת��ΪRenderOperationGroup
		void ReadS3MBAsROGroup();
		//����s3mb·��
		void SetFilePath(const wstring& strFilePath);
		//���������ж�ȡs3mb
		bool LoadS3MBFromStream(void* buffer,unsigned int bufferSize);
		//���ģ����Ϣ������̨
		void OutputGeometryInfoToConsole();
		//��ȡ��ȡ����RenderOperationGroup
		RenderOperationGroup* GetRenderOperationGroup() { return m_pROGroup; };
		void Clear();

	private:
		// ����Դ�ļ�
		std::wstring m_strFilePath;

		RenderOperationGroup* m_pROGroup;
	};
}