#pragma once
#ifndef S3MB_SKIN
#define S3MB_SKIN

#pragma once
#include "Matrix.h"
#include <string>
#include <vector>
#include "Quaternion.h"

namespace S3MB
{
	class S3MB_API Skin
	{
	public:
		// ���캯��
		Skin() {};

		// ��������
		~Skin(void);

		// ���صȺ�
		void operator=(const Skin& other);

		// ����/��ȡ��Ƥ������
		void SetName(const wstring& strName) { m_strName = strName; };
		const wstring& GetName() const { return m_strName; };

		// ����/��ȡ�ڵ����������
		void SetJointNodeIndexes(const std::vector<int>& vecIndex) { m_vecJointNodeIndex = vecIndex; };
		const std::vector<int>& GetJointNodeIndexes() const { return m_vecJointNodeIndex; };

		// ����/��ȡ����������
		void SetInverseBindMatrices(const std::vector<Matrix4d>& vecMatrix) { m_vecInverseBindMatrix = vecMatrix; };
		const std::vector<Matrix4d>& GetInverseBindMatrices() const { return m_vecInverseBindMatrix; };


	private:
		// ����
		wstring m_strName;

		// �ڵ����������
		vector<int> m_vecJointNodeIndex;

		// ����������
		vector<Matrix4d> m_vecInverseBindMatrix;
	};

	class S3MB_API Node
	{
	public:
		// ���캯����
		Node();

		// ���캯����
		~Node(void);

		// ���صȺš�
		void operator=(const Node& other);

		// ����/��ȡ�������ơ�
		void SetName(const wstring& strName) { m_strName = strName; };
		wstring& GetName(void) { return m_strName; };

		// ����/��ȡ����㡣
		void SetParent(Node* pParent) { m_pParent = pParent; };
		Node* GetParent() { return m_pParent; };

		// ��ȡ�ӽڵ������
		int GetNumChildren(void) { return m_nNumChildren; };
		// ��ȡ�ӽڵ㡣
		Node* GetChild(int nIndex) { return m_vecChildren.size() > nIndex ? m_vecChildren[nIndex] : nullptr; };

		// ����/��ȡ��Ƥ������
		void SetSkinIndex(int nIndex) { m_nSkinIndex = nIndex; };
		int GetSkinIndex() const { return m_nSkinIndex; };

		// ����/��ȡGeode������
		void SetPatchIndex(int nIndex) { m_nPatchIndex = nIndex; };
		int GetPatchIndex() const { return m_nPatchIndex; };

		// ����/��ȡ�ӽڵ���nodes�����е��������ɵ�����
		void SetChildNodeIndexes(const std::vector<int>& vecIndex) { m_vecChildNodeIndex = vecIndex; };
		const std::vector<int>& GetChildNodeIndexes() const { return m_vecChildNodeIndex; };

	protected:
		// �ͷ��ӽ��
		void ReleaseChild(Node* pNode);

		// ������ƣ���Ϊ����Ψһ��ʶ
		wstring m_strName;

		// �ӽ�����
		int  m_nNumChildren;

		// �ӽ������
		vector<Node*> m_vecChildren;

		// �����
		Node* m_pParent;

		// ��Ƥ������
		int m_nSkinIndex;

		// Geode������
		int m_nPatchIndex;

		// �ӽڵ���nodes�����е��������ɵ�����
		vector<int> m_vecChildNodeIndex;
	};

}

#endif