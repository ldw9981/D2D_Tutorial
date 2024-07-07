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
	FSMState* m_pCurrentState = nullptr;  // ���� ����
	FSMState* m_pInitialState = nullptr;	// �ʱ� ����
	

	std::map<std::string, FSMState*> m_pStates;	// ������ FSMState���� �����ϴ� �����̳�

	virtual void Update(float DeltaTime);
	void ChangeState(std::string stateName);
	void SetInitialState(std::string stateName);
	void AddState(FSMState* pState);	
};

