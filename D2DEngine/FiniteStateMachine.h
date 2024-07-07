#pragma once
#include "Component.h"

class FSMState;
class FSMTransition;
class FSMSharedTransition;
class FiniteStateMachine : public Component
{
public:
	FiniteStateMachine() = default;
	virtual ~FiniteStateMachine() = default;

protected:
	FSMState* m_pCurrentState = nullptr;  // 현재 상태
	FSMState* m_pInitialState = nullptr;	// 초기 상태
	

	std::map<std::string, FSMState*> m_pStates;	// 생성된 FSMState들을 저장하는 컨테이너

	virtual void Update(float DeltaTime);
	void ChangeState(std::string stateName);
	void SetInitialState(std::string stateName);
	void AddState(FSMState* pState);	
};

