#pragma once
#include "Scene.h"
class RenderScene :
    public Scene
{
public:
	RenderScene() = default;
	virtual ~RenderScene() = default;

	int m_ZOrder;		// �׸��� ����  
	bool m_Visible;		// �׸�������
	D2D1_MATRIX_3X2_F	m_RenderTransform;	// x������̳� ���Ʒ� ����
public:
	void SetZOrder(int zOrder) { m_ZOrder = zOrder; }
	int GetZOrder() const { return m_ZOrder; }
	void SetVisible(bool visible) { m_Visible = visible; }

	static bool CompareRenderOrder(RenderScene* a, RenderScene* b)
	{
		return a->m_ZOrder < b->m_ZOrder;
	}

};

