#pragma once
#include "BitmapScene.h"


class AnimationAsset;
struct ANIMATION_INFO;


// �ִϸ��̼� �ν��Ͻ� ����
class AnimationScene :
    public BitmapScene
{
public:
	AnimationScene();
	virtual ~AnimationScene();
	
	// �����ϴ� �ִϸ��̼� ����	
	AnimationAsset* m_pAnimationAsset = nullptr;  // �����ϴ� �ִϸ��̼� ����
	
	// �ν��Ͻ����� �ٸ� �ִϸ��̼� ����
	ANIMATION_INFO* m_pAnimationInfo = nullptr;	// ���� �ִϸ��̼� ������ ����
	std::wstring m_strAnimationAssetFilePath;    // �ִϸ��̼� ���� ���� �̸�
	float m_FrameTime = 0.0f;	// ������ ����ð�
	int m_FrameIndexCurr = -1;		// ���� ������ �ε���
	int m_FrameIndexPrev = -1;		// ���� ������ �ε���
	int m_AnimationIndex = -1;	// ���� �ִϸ��̼� �ε���
	D2D1_RECT_F m_SrcRect;		// D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect;		// RenderTarget�� Destination ����		

	bool m_bMirror;				// �¿� ���� ����
	D2D1_MATRIX_3X2_F	m_ImageTransform;	// �ݴ� �������� ������ ���� ��� Scale.x = -1.0f 

	void LoadAnimationAsset(const std::wstring strFilePath);
	virtual void Update(float fTimeElapsed);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);	
	void SetAnimation(int index,bool mirror);
};

