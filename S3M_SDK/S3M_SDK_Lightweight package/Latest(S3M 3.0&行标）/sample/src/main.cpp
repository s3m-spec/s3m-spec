#include "ROGroupLite.h"

int main(int argc, char* argv[])
{	
	bool bHasPBR = false;
	if (bHasPBR)
	{
		// PBR���ʷ���
		ROGroupLite::sampleV2();
	}
	else 
	{
		// ��ͨ���ʷ���
		ROGroupLite::sampleV1();
	}
	system("pause");
	return 0;
}