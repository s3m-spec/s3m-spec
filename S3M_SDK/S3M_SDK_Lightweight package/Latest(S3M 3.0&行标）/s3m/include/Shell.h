#if !defined(SHELL_H__01180357_13FC_4EA5_965C_09325C4EA952__INCLUDED_)
#define SHELL_H__01180357_13FC_4EA5_965C_09325C4EA952__INCLUDED_

#pragma once
#include "Texture.h"
#include "Material.h"
#include "Skeleton.h"
#include "S3MBCommon.h"
#include "BoundingSphere.h"
#include <map>
#include "Skin.h"
#include "Animation.h"

using namespace std;
namespace S3MB
{
	class RenderOperationGroup;
	class RenderOperationGeode;

	class S3MB_API RenderOperationNode
	{
	public:
		RenderOperationNode();
		virtual ~RenderOperationNode();

		// �����Group����ͷ���this������NULL
		virtual RenderOperationGroup* AsGroup();

		// �����Geode����ͷ���this������NULL
		virtual RenderOperationGeode* AsGeode();

		// ����
		virtual wstring ClassName();

		// ����
		void SetName(wstring strName);

		// �������
		wstring GetName();

		// ��ð�Χ��
		BoundingSphere GetBoundingSphere();

		// ���ð�Χ��
		void SetBoundingSphere(Vector3d vecCenter, double dRadius);

		// ��÷����Χ��
		OrientedBoundingBox GetOrientedBoundingBox();

		// ���÷����Χ��
		void SetOrientedBoundingBox(OrientedBoundingBox orientedBoundingBox);

		BoundingBox GetBoundingBox();

		void SetBoundingBox(BoundingBox boundingBox);

		// ����λ��
		void SetPosition(Matrix4d mat);

		// ���λ��
		Matrix4d GetPosition();

		// �����Ƿ����
		bool IsMaterialExist(wstring strMaterialName);

		// �����Ƿ����
		bool IsTexDataExist(wstring strTextureName);

		// Node�Ƿ����
		bool IsSkeletonExist(wstring strName);
		  
		// ���һ������
		// strMaterialName �����������Ժ�Material3D������ֲ���Ӧ[in]
		// pMaterial3D ������Ϣ[in]
		// return �ظ����ʷ���false[out]
		bool AddMaterial(wstring strMaterialName, Material* pMaterial);

		// ���һ��������Ϣ
		// strTextureName ������[in]
		// pTexData ������Ϣ[in]
		// return �ظ�������false[out]
		bool AddTextureData(wstring strTextureName, TextureDataInfo* pTexData);

		// ���һ��Skeleton��Ϣ
		// strName Skeleton��[in]
		// pSkeleton Skeleton��Ϣ[in]
		// return �ظ�����false[out]
		bool AddSkeleton(wstring strName, Skeleton* pSkeleton);

		// ��ò���
		Material* GetMaterial(wstring strMaterialName);
		// ��ò���
		std::map<wstring, Material*>& GetMaterials();

		// �������
		TextureDataInfo* GetTextureData(wstring strTextureName);
		// �����������
		std::map<wstring, TextureDataInfo*>& GetTextureData();

		// ���Skeleton
		Skeleton* GetSkeleton(wstring strName);

		// ���Skeleton
		std::map<wstring, Skeleton*>& GetSkeleton();

		// �Ƴ����в���
		void RemoveAllMaterial();

		// �Ƴ���������
		void RemoveAllTexData();

		// �Ƴ�����Skeleton
		void RemoveAllSkeleton();

		// �Ƴ�ָ��Skeleton
		virtual void RemoveSkeleton(wstring strName);

		// ������в���
		void ClearMaterial3D();

		// �����������
		void ClearTexData();

		// �������Skeleton
		void ClearSkeleton();

	protected:
		// ��Χ��
		BoundingSphere m_BoundingSphere;

		// �����Χ��
		OrientedBoundingBox m_OBB;

		// ��Χ��
		BoundingBox m_BoundingBox;

		// ����
		wstring m_strName;

		// λ��
		Matrix4d m_matLocalView;

		// ������Ϣ
		std::map<wstring, Material*> m_mapMaterial;

		// ������Ϣ
		std::map<wstring, TextureDataInfo*> m_mapTextureData;

		// Node��Ϣ
		std::map<wstring, Skeleton*> m_mapSkeleton;
	};

	class S3MB_API RenderOperationGroup : public RenderOperationNode
	{
	public:
		RenderOperationGroup();

		virtual ~RenderOperationGroup();

		// �����Group����ͷ���this������NULL
		virtual RenderOperationGroup* AsGroup();

		// ����
		virtual wstring ClassName();

		// ���ø��ڵ�
		void SetParentNode(RenderOperationNode* pNode);

		// ��ø��ڵ�
		RenderOperationNode* GetParentNode();

		// ����ӽڵ�
		void AddChild(RenderOperationNode* pNode);

		// ����ӽڵ�����
		int GetNumChildren();

		// ����������ӽڵ�
		// nIndex ����[in]
		// return Node[out]
		RenderOperationNode* GetChild(int nIndex);

		// �Ƴ����нڵ�
		void RemoveAllChildren();

		// ���¼�������child��Χ��
		// bReCalSkeletonBBOX �Ƿ����¼���Skeleton�İ�Χ��
		virtual void ReComputeBoundingBox(bool bReCalSkeletonBBOX = true);

	private:
		// ���ڵ�
		RenderOperationNode* m_pParentNode;

		// �ӽڵ�
		std::vector<RenderOperationNode*> m_vecChildNode;
	};

	class S3MB_API RenderOperationPagedLOD : public RenderOperationGroup
	{
	public:
		RenderOperationPagedLOD();

		virtual ~RenderOperationPagedLOD();

		// �����Group����ͷ���this������NULL
		virtual RenderOperationGroup* AsGroup();

		// ����
		virtual wstring ClassName();

		// ��÷�Χ
		std::vector<std::pair<float, float> >& GetRanges();

		// �������Ƭ
		std::vector<wstring>& GetFileNames();

		// �л���Χģʽ
		void SetRangeMode(RangeMode nMode);

		// ����л���Χģʽ
		RangeMode GetRangeMode();

		// ���¼�������child��Χ�У������������Χ��
		// bReCalSkeletonBBOX �Ƿ����¼���Skeleton�İ�Χ��
		void ReComputeBoundingBox(bool bReCalSkeletonBBOX = true) override;

		// ����/��ȡ�ڵ���������
		void SetNodes(const std::vector<Node*>& vecNode, bool bOwn = true);
		const std::vector<Node*>& GetNodes() const { return m_vecNode; }

		// ����/��ȡ��Ƥ���������
		void SetSkins(const std::vector<Skin*>& vecSkin, bool bOwn = true);
		const std::vector<Skin*>& GetSkins() const { return m_vecSkin; };

		// ����/��ȡ���ж�����������Ϣ
		void SetAnimationStates(const std::vector<Animation*>& vecAnimation, bool bOwn = true);
		const std::vector<Animation*>& GetAnimationStates() const { return m_vecAnimationState; };

		// ����/��ȡ���ж�����Ϣ
		void SetAnimationCurves(const std::vector<std::map<wstring, AnimationCurve*> >& vecAnimationCurve, bool bOwn = true);
		const std::vector<std::map<wstring, AnimationCurve*> >& GetAnimationCurves() const { return m_vecAnimationCurve; };

	private:
		// �л���Χ
		std::vector<std::pair<float, float> > m_vecRangeList;

		// LOD��Ƭ��
		std::vector<wstring> m_vecFileName;

		// LOD��Ƭ��Χ��
		std::map<wstring, BoundingSphere> m_mapBoundingSphere;

		// �л���Χģʽ
		RangeMode m_nRangeMode;

		// �ڵ���������
		std::vector<Node*> m_vecNode;
		bool m_bOwnNode;

		// ��Ƥ���������
		std::vector<Skin*> m_vecSkin;
		bool m_bOwnSkin;

		// ����״̬
		std::vector<Animation*> m_vecAnimationState;
		bool m_bOwnAnimationState;

		// ������Ϣ��vector�Ͷ���״̬��vector��Ӧ��map��keyֵ�Ƕ�����Ӧ��Geode������
		std::vector<std::map<wstring, AnimationCurve*> > m_vecAnimationCurve;
		bool m_bOwnAnimationCurve;
	};

	class S3MB_API RenderOperationGeode : public RenderOperationNode
	{
	public:
		RenderOperationGeode();
		virtual ~RenderOperationGeode();

		// �����Group����ͷ���this������NULL
		virtual RenderOperationGeode* AsGeode();

		// ����
		virtual wstring ClassName();

		// ���Skeleton
		// pROGeoemtry Skeleton[in]
		void AddSkeleton(Skeleton* pROGeoemtry);

		// ���Geoemtry����
		int GetNumSkeleton();

		// ���Skeleton
		// nIndex ����[in]
		// return Skeleton[out]
		Skeleton* GetSkeleton(int nIndex);

		// �滻Skeleton
		// �滻��������[in]
		// �滻��Skeleton[in]
		// �Ƿ�ɾ��ԭ����
		void ReplaceSkeleton(int nIndex, Skeleton* pSkeleton, bool bRelease = false);

		// �Ƴ�ָ��Skeleton
		virtual void RemoveSkeleton(wstring strName);

		// ����Skeleton
		void Release();

		// �����Χ��
		void ComputerBoundingBox();

	private:
		// Skeleton����
		std::vector<Skeleton*> m_vecSkeleton;

	public:
		// ���Ա�
		GeodeInfo m_GeodeInfo;

		// ID
		wstring m_strUniqueID;
	};
}

#endif