#pragma once
#include "GameObject.h"

class AnimationScene;
class Character :
    public GameObject
{
public:
	Character();
	virtual ~Character();	
	
	AnimationScene* m_pAnimationScene = nullptr;
	//CollisionBox* m_pCollisionBox = nullptr;
};

