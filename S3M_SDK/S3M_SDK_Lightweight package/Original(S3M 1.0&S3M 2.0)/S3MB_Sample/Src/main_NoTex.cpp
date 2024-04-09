#include <iostream>
#include <codecvt>
#include <fstream>
#include <string>

#include "S3MBReader.h"
#include "S3MBWriter.h"
#include "ROGroupLite_NoTex.h"
#include <iosfwd>

using namespace std;
using namespace S3MB;
int main(int argc, char* argv[])
{

	///************************************************************************/
	//*          1.����һ�����������ݲ�д��S3MB�ļ�
    ///************************************************************************/	

	RenderOperationGroup* pGroup = ROGroupLite::CreateROGroupLite();

	S3MBWriter m_S3MBWriter;
	m_S3MBWriter.SetROGroup(pGroup);
	m_S3MBWriter.SetIsChangeTexture(true);
	wstring strS3mbFile = L"./������.s3mb";
	m_S3MBWriter.SetFilePath(strS3mbFile);
	m_S3MBWriter.Save(0);

	///************************************************************************/
    //*        2:ͨ��ָ����s3mb�ļ�����ȡ����Ro��Ϣ�����������                                                                     */
   ///************************************************************************/


	S3MBReader m_S3MBReaderRo;

	wstring strS3MBFileSrc = L"./������.s3mb";
	//cout << "��������Ҫ��ʾ��S3mb·����" << endl;
	//string strS3MBFileSrc;
	//cin >> strS3MBFileSrc;
	m_S3MBReaderRo.SetFilePath(strS3MBFileSrc);
	m_S3MBReaderRo.ReadS3MBAsROGroup();
	system("pause");
	///************************************************************************/
    //*       3:ͨ��ָ����s3mb�����ļ��У�������ȡs3md�����                                                                */
   ///************************************************************************/


	//S3MBReader m_S3MBReaderAtt;

	//string strS3MBFolderSrc = "..\\SampleData\\CBD_part";
	//m_S3MBReaderAtt.SetFilePath(strS3MBFolderSrc);
	//m_S3MBReaderAtt.ReadS3MBAttribute();
}