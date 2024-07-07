#pragma once
#include "Component.h"

class FSMState;
class FSMTransition;
class FSMSharedTransition;
class FiniteStateMachine : public Component
{
public:
	FiniteStateMachine() = default;
	virtual ~FiniteStateMachine();

protected:
	FSMState* m_pCurrState = nullptr;  // ���� ����	
	FSMState* m_pNextState = nullptr;	// ���� ����

	std::map<std::string, FSMState*> m_pStates;	// ������ FSMState���� �����ϴ� �����̳�

	virtual void Update(float DeltaTime);
	void SetNextState(std::string stateName);

	template<typename T>
	void CreateState(const std::string StateName)
	{
		T* pState = new T(this,StateName);
		m_pStates.insert(std::make_pair(pState->GetName(), pState));
	}
};

