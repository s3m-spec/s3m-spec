#ifndef  _SHELL_H_
#define  _SHELL_H_
#include "Texture.h"
#include "Material.h"
#include "Skeleton.h"
#include <map>
using namespace std;
namespace S3MB
{

	//! \brief LOD�л�ģʽ
	enum RangeMode
	{
		DISTANCE_FROM_EYE_POINT, // ���ݵ�����ľ����л�
		PIXEL_SIZE_ON_SCREEN	 // ������Ļ���ش�С�л�
	};
	class S3MB_API BoundingSphere
	{
	public:
		BoundingSphere()
			:m_center(0.0, 0.0, 0.0), m_radius(-1) {}

		BoundingSphere(const Vector3d& center, double radius)
			:m_center(center), m_radius(radius) {}

		BoundingSphere(const BoundingSphere& bs)
			:m_center(bs.m_center), m_radius(bs.m_radius) {}

		BoundingSphere(const BoundingBox& box)
			:m_center(box.GetCenter()), m_radius((box.GetMax() - box.GetMin()).Length() / 2) {}

		~BoundingSphere(void) {}

		//! \brief �жϰ�Χ���Ƿ���Ч
		inline bool valid() const
		{
			return m_radius > 0.0;
		}

		//! \brief ��ȡ��Χ��
		inline BoundingBox GetBoundingBox() const
		{
			Vector3d vMinVec(m_center.x - m_radius, m_center.y - m_radius, m_center.z - m_radius);
			Vector3d vMaxVec(m_center.x + m_radius, m_center.y + m_radius, m_center.z + m_radius);
			return BoundingBox(vMinVec, vMaxVec);
		}

		inline void init()
		{
			m_center = Vector3d(0.0, 0.0, 0.0);
			m_radius = -1;
		}

		inline Vector3d GetCenter() const
		{
			return m_center;
		}

		inline double GetRadius() const
		{
			return m_radius;
		}

		//�� \brief ���ݸ����İ�Χ������չ�����ġ��뾶���ı�
		//!  \param ����չ����
		void ExpandBy(const BoundingSphere& bs);
	public:
		Vector3d m_center;
		double m_radius;
	};

	class RenderOperationGroup;
	class RenderOperationGeode;

	class S3MB_API RenderOperationNode
	{
	public:
		RenderOperationNode() {}
		virtual ~RenderOperationNode()
		{
			RemoveAllMaterial();
			RemoveAllTexData();
			RemoveAllGeometry();
		}

		//! \brief �����Group����ͷ���this������NULL
		virtual RenderOperationGroup* AsGroup() { return NULL; };

		//! \brief �����Geode����ͷ���this������NULL
		virtual RenderOperationGeode* AsGeode() { return NULL; };

		//! \brief ����
		virtual wstring ClassName() { return U("Node"); }

		//! \brief ����
		void SetName(wstring strName) { m_strName = strName; };

		//! \brief �������
		wstring GetName() { return m_strName; };

		//! \brief ��ð�Χ��
		BoundingSphere GetBoudingSphere() { return m_BoundingSphere; };

		//! \brief ���ð�Χ��
		void SetBoudingSphere(Vector3d vecCenter, double dRadius) {
			m_BoundingSphere.m_center = vecCenter;
			m_BoundingSphere.m_radius = dRadius;
		};

		//! \brief ����λ��
		void SetPosition(Matrix4d mat) { m_matLocalView = mat; };

		//! \brief ���λ��
		Matrix4d GetPosition() { return m_matLocalView; };

		//! \brief �����Ƿ����
		bool IsExistToMaterial(wstring strMaterialName);

		//! \brief �����Ƿ����
		bool IsExistToTexData(wstring strTextureName);

		//! \brief Node�Ƿ����
		bool IsExistToGeometry(wstring strName);

		//! \brief ���һ������
		//! \param strMaterialName �����������Ժ�Material3D������ֲ���Ӧ[in]
		//! \param pMaterial3D ������Ϣ[in]
		//! \return �ظ����ʷ���false[out]
		bool AddMaterial(wstring strMaterialName, Material* pMaterial);

		//! \brief ���һ��������Ϣ
		//! \param strTextureName ������[in]
		//! \param pTexData ������Ϣ[in]
		//! \return �ظ�������false[out]
		bool AddTextureData(wstring strTextureName, TextureDataInfo* pTexData);

		//! \brief ���һ��Geometry��Ϣ
		//! \param strName Geometry��[in]
		//! \param pGeometry Geometry��Ϣ[in]
		//! \return �ظ�����false[out]
		bool AddGeometry(wstring strName, Geometry* pGeometry);

		//! \brief ��ò���
		Material* GetMaterial(wstring strMaterialName);
		//! \brief ��ò���
		std::map<wstring, Material*>& GetMaterials();

		//! \brief �������
		TextureDataInfo* GetTextureData(wstring strTextureName);
		//! \brief �����������
		std::map<wstring, TextureDataInfo*>& GetTextureData();

		//! \brief ���Geometry
		Geometry* GetGeometry(wstring strName);

		//! \brief ���Geometry
		std::map<wstring, Geometry*>& GetGeometry();

		//! \brief �Ƴ����в���
		void RemoveAllMaterial();

		//! \brief �Ƴ���������
		void RemoveAllTexData();

		//! \brief �Ƴ�����Geometry
		void RemoveAllGeometry();

		//! \brief �Ƴ�ָ��Geometry
		virtual void RemoveGeometry(wstring strName);

		//! \brief ������в���
		void ClearMaterial3D() { m_mapMaterial.clear(); };

		//! \brief �����������
		void ClearTexData() { m_mapTextureData.clear(); };

		//! \brief �������Geometry
		void ClearGeometry() { m_mapGeometry.clear(); };
	protected:
		//! \brief ��Χ��
		BoundingSphere m_BoundingSphere;

		//! \brief ����
		wstring m_strName;

		//! \brief λ��
		Matrix4d m_matLocalView;

		//! \brief ������Ϣ
		std::map<wstring, Material*> m_mapMaterial;

		//! \brief ������Ϣ
		std::map<wstring, TextureDataInfo*> m_mapTextureData;

		//! \brief Node��Ϣ
		std::map<wstring, Geometry*> m_mapGeometry;
	};

	class S3MB_API RenderOperationGroup : public RenderOperationNode
	{
	public:
		RenderOperationGroup()
			:m_pParentNode(NULL) {}
		virtual ~RenderOperationGroup()
		{
			RemoveAllChildren();
			m_pParentNode = NULL;
		}

		//! \brief �����Group����ͷ���this������NULL
		virtual RenderOperationGroup* AsGroup() { return this; };

		//! \brief ����
		virtual wstring ClassName() { return U("Group"); }

		//! \brief ���ø��ڵ�
		void SetParentNode(RenderOperationNode* pNode) { m_pParentNode = pNode; }

		//! \brief ��ø��ڵ�
		RenderOperationNode* GetParentNode() { return m_pParentNode; }

		//! \brief ����ӽڵ�
		void AddChild(RenderOperationNode* pNode);

		//! \brief ����ӽڵ�����
		int GetNumChildren() { return m_vecChildNode.size(); }

		//! \brief ����������ӽڵ�
		//! \param nIndex ����[in]
		//! \return Node[out]
		RenderOperationNode* GetChild(int nIndex);

		//! \brief �Ƴ����нڵ�
		void RemoveAllChildren();

		//! \brief ���¼�������child��Χ��
		//! \param bReCalGeometryBBOX �Ƿ����¼���geometry�İ�Χ��
		virtual void ReComputeBoundingBox(bool bReCalGeometryBBOX = true);
	private:
		//! \brief ���ڵ�
		RenderOperationNode* m_pParentNode;

		//! \brief �ӽڵ�
		std::vector<RenderOperationNode*> m_vecChildNode;
	};

	class S3MB_API RenderOperationPagedLOD : public RenderOperationGroup
	{
	public:
		RenderOperationPagedLOD()
			:m_nRangeMode(PIXEL_SIZE_ON_SCREEN) {}

		virtual ~RenderOperationPagedLOD();

		//! \brief �����Group����ͷ���this������NULL
		virtual RenderOperationGroup* AsGroup() { return this; };

		//! \brief ����
		virtual wstring ClassName() { return U("PagedLOD"); }

		//! \brief ��÷�Χ
		std::vector<std::pair<float, float> >& GetRanges() { return m_vecRangeList; }

		//! \brief �������Ƭ
		std::vector<wstring>& GetFileNames() { return m_vecFileName; }

		//! \brief ��ȡ����Ƭ�İ�Χ��
		std::map<wstring, BoundingSphere>& GetLODSphere() {
			return m_mapBoundingSphere;
		}

		//! \brief �л���Χģʽ
		void SetRangeMode(RangeMode nMode) { m_nRangeMode = nMode; };

		//! \brief ����л���Χģʽ
		RangeMode GetRangeMode() { return m_nRangeMode; };

		//! \brief ���¼�������child��Χ�У������������Χ��
		//! \param bReCalGeometryBBOX �Ƿ����¼���geometry�İ�Χ��
		void ReComputeBoundingBox(bool bReCalGeometryBBOX = true) override;

	private:
		//! \brief �л���Χ
		std::vector<std::pair<float, float> > m_vecRangeList;

		//! \brief LOD��Ƭ��
		std::vector<wstring> m_vecFileName;

		//! \brief LOD��Ƭ��Χ��
		std::map<wstring, BoundingSphere> m_mapBoundingSphere;

		//! \brief �л���Χģʽ
		RangeMode m_nRangeMode;
	};

	//���Ա�
	struct GeodeInfo
	{
		wstring m_strTableName;
		unsigned int m_nID;
	};

	class S3MB_API RenderOperationGeode : public RenderOperationNode
	{
	public:
		RenderOperationGeode() {}
		virtual ~RenderOperationGeode() { Release(); }

		//! \brief �����Group����ͷ���this������NULL
		virtual RenderOperationGeode* AsGeode() { return this; };

		//! \brief ����
		virtual wstring ClassName() { return U("Geode"); }

		//! \brief ���Geometry
		//! \param pROGeoemtry Geometry[in]
		void AddGeometry(Geometry* pROGeoemtry);

		//! \brief ���Geoemtry����
		int GetNumGeometry() { return m_vecROGeometry.size(); }

		//! \brief ���Geometry
		//! \param nIndex ����[in]
		//! \return Geometry[out]
		Geometry* GetGeometry(int nIndex);

		//! \brief �滻Geometry
		//! \param �滻��������[in]
		//! \param �滻��Geometry[in]
		//! \param �Ƿ�ɾ��ԭ����
		void ReplaceGeometry(int nIndex, Geometry* pGeometry, bool bRelease = false);

		//! \brief �Ƴ�ָ��Geometry
		virtual void RemoveGeometry(wstring strName);

		//! \brief ����Geometry
		void Release();

		//! \brief �����Χ��
		void ComputerBoundingBox();

		//! \brief ��ð�Χ��
		BoundingBox GetBoundingBox() { return m_BoundingBox; }

	private:
		//! \brief ��Χ��
		BoundingBox m_BoundingBox;

		//! \brief Geoemtry����
		std::vector<Geometry*> m_vecROGeometry;

	public:
		//! \brief ���Ա�
		GeodeInfo m_GeodeInfo;

		//! \brief ID
		wstring m_strUniqueID;
	};
}

#endif