#pragma once
class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};

public:
	Scene* m_pParentScene = nullptr;		// 부모 Scene 컴포넌트	
	D2D1_VECTOR_2F		m_RelativeScale = {1,1};	// 상대 크기
	float				m_RelativeRotation = 0; // 상대 회전
	D2D1_VECTOR_2F 		m_RelativeLocation = {0,0}; // 상대 위치
	D2D1_MATRIX_3X2_F	m_RelativeTransform; // 상대 복합 변환
	D2D1_MATRIX_3X2_F	m_WorldTransform;    // 부모까지 반영된 최종 변환

	// RelativeTransform과 	m_WorldTransform을 계산한다.
	void UpdateTrasnform();
	void SetParent(Scene* pParentScene) { m_pParentScene = pParentScene; }
};

