#pragma once
#if !defined(S3MB_ANIMATION)
#define S3MB_ANIMATION
#include "Quaternion.h"
#include <string>
#include <vector>
using namespace std;
namespace S3MB 
{
	class S3MB_API AnimationKey
	{
	public:
		AnimationKey();

		virtual ~AnimationKey() {}

		// ���صȺš�
		void operator=(const AnimationKey& other);

		// ����/��ȡ��ǰ֡��ʱ��
		void SetTime(float fTimePos) { m_fTimePos = fTimePos; }
		double GetTime(void) const { return m_fTimePos; }

		// ����/��ȡ��ǰ֡�����ű�
		// vecScale ��ǰ֡�����ű�[in]��
		void SetScale(const Vector3d& vecScale) { m_vecScale = vecScale; };
		const Vector3d& GetScale(void) const { return m_vecScale; };

		// ����/��ȡ��ǰ֡����ת�Ƕ�
		// rot ��ǰ֡����ת�Ƕ�[in]��
		void SetRotation(const Quaternion& rot) { m_Rotation = rot; };
		const Quaternion& GetRotation(void) const { return m_Rotation; };

		// ����/��ȡ��ǰ֡��ƽ��
		// vecTrans ��ǰ������λ��[in]��
		void SetTranslate(const Vector3d& vecTrans) { m_vecTranslate = vecTrans; };
		const Vector3d& GetTranslate(void) const { return m_vecTranslate; };

		// ����/��ȡ��ǰ֡��Ȩ��
		void SetWeights(const double& dWeights) { m_dWeights = dWeights; };
		const double& GetWeights() const { return m_dWeights; };

	private:
		// ��ǰ֡����ת�Ƕ�
		Quaternion m_Rotation;

		// ��ǰ֡��ƽ��
		Vector3d m_vecTranslate;

		// ��ǰ֡�����ű�
		Vector3d m_vecScale;

		// ��ǰ֡��Ȩ��
		double m_dWeights;

		// ��ǰ֡��ʱ��
		float m_fTimePos;
	};

	class S3MB_API AnimationCurve
	{
	public:
		AnimationCurve() {};
		~AnimationCurve();

		// ����/��ȡ�����任������
		// scale��ʾ���š�rotation��ʾ��ת��translation��ʾƽ�ơ�weights��ʾȨ��
		void SetPath(const wstring& strPath) { m_strPath = strPath; };
		const wstring& GetPath() const { return m_strPath; };

		// ���ùؼ�֡����
		std::vector<AnimationKey*>& GetKeys() { return m_vecKeys; };

		// ���ӹؼ�֡����
		AnimationKey* AddKey();

	private:
		// �����任������
		wstring m_strPath;

		// ������Ϣ
		std::vector<AnimationKey*> m_vecKeys;
	};

	class S3MB_API Animation
	{
	public:
		Animation();
		Animation(const wstring& strAnimName, double dTimePos, double dLength, bool bEnabled = false);
		// �������캯��
		Animation(const Animation &rhs);

		// ����/��ȡ��������
		void SetAnimationName(wstring& strName) { m_strAnimationName = strName; };
		const wstring& GetAnimationName() const { return m_strAnimationName; };

		// ����/��ȡ����λ��
		void SetTimePosition(double dTimePos) { m_dTimePos = dTimePos; };
		double GetTimePosition(void) const { return m_dTimePos; };

		// ����/��ȡ��������
		void SetLength(double dLen) { m_dLength = dLen; };
		double GetLength() const { return m_dLength; };

		// ����/��ȡ��ʼʱ��
		void SetStartTime(double dStartTime) { m_dStartTime = dStartTime; };
		double GetStartTime(void) const { return m_dStartTime; };

		// ����/��ȡ��ֹʱ��
		void SetEndTime(double dEndTime) { m_dEndTime = dEndTime; };
		double GetEndTime(void) const { return m_dEndTime; };

		// ����/��õ�ǰ�����Ƿ���õı�ʶ
		void Enabled(bool bEnabled) { m_bEnabled = bEnabled; };
		bool GetEnabled(void) const { return m_bEnabled; };

	private:
		// ��������
		wstring m_strAnimationName;

		// ����λ��
		double m_dTimePos;

		// ��������
		double m_dLength;

		// ��ʼʱ��
		double m_dStartTime;

		// ����ʱ��
		double m_dEndTime;

		// �Ƿ����
		bool m_bEnabled;
	};

}

#endif