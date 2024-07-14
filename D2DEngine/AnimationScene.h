#pragma once
#include "BitmapScene.h"


class AnimationAsset;
struct ANIMATION_INFO;
class AnimationScene;

// 인터페이스 클래스
// 자식클래스에서 상속	받아 OnAnimationEnd 함수를 구현하여 애니메이션 종료시 처리할 내용을 작성한다.
class IAnimationProcesser
{
public:
	virtual void OnAnimationEnd(AnimationScene* pComponent, const std::string& AnimationName)=0;
};


// 애니메이션 인스턴스 정보
class AnimationScene :
    public BitmapScene
{
public:
	AnimationScene();
	virtual ~AnimationScene();
	
	// 공유하는 애니메이션 정보	
	AnimationAsset* m_pAnimationAsset = nullptr;  // 공유하는 애니메이션 정보
	
	// 인스턴스마다 다른 애니메이션 정보
	ANIMATION_INFO* m_pAnimationInfo = nullptr;	// 현재 애니메이션 프레임 정보
	IAnimationProcesser* m_pAnimationProcesser = nullptr;		// 애니메이션 종료시 호출할 콜백 함수
	std::wstring m_strAnimationAssetFilePath;    // 애니메이션 정보 파일 이름
	float m_FrameTime = 0.0f;	// 프레임 진행시간
	int m_FrameIndexCurr = -1;		// 현재 프레임 인덱스
	int m_FrameIndexPrev = -1;		// 이전 프레임 인덱스
	int m_AnimationIndex = -1;	// 현재 애니메이션 인덱스
	bool m_bAnimationEnd = false;	// 애니메이션 종료 여부
	D2D1_RECT_F m_SrcRect;		// D2D1Bitmap의 Source 영역
	D2D1_RECT_F m_DstRect;		// RenderTarget의 Destination 영역		

	bool m_bMirror;				// 좌우 반전 여부
	
	bool IsAnimationEnd();		// 애니메이션 종료 여부
	void LoadAnimationAsset(const std::wstring strFilePath);
	virtual void Update(float fTimeElapsed);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);	
	void SetAnimation(int index,bool mirror);
	void SetAnimationProcesser(IAnimationProcesser* pAnimationProcesser) { m_pAnimationProcesser = pAnimationProcesser; }
};

