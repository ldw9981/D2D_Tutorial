#pragma once
class Scene
{
public:
	Scene();
	virtual ~Scene();

public:
	Scene* m_pParentScene = nullptr;		// �θ� Scene ������Ʈ	
	D2D_VECTOR_2F		m_RelativeScale = {1,1};	// ��� ũ��
	float				m_RelativeRotation = 0; // ��� ȸ��
	D2D_VECTOR_2F 		m_RelativeLocation = {0,0}; // ��� ��ġ
	D2D_MATRIX_3X2_F	m_RelativeTransform; // ��� ���� ��ȯ
	D2D_MATRIX_3X2_F	m_WorldTransform;    // �θ���� �ݿ��� ���� ��ȯ

	// RelativeTransform�� 	m_WorldTransform�� ����Ѵ�.
	void UpdateTrasnform();
	void SetParentScene(Scene* pParentScene) { m_pParentScene = pParentScene; }
	D2D1_VECTOR_2F GetWorldLocation()
	{
		D2D1_VECTOR_2F out;
		out.x = m_WorldTransform._31;
		out.y = m_WorldTransform._32;
		return out;
	}
};

