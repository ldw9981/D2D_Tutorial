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
	FSMState* m_pCurrState = nullptr;  // 현재 상태	
	FSMState* m_pNextState = nullptr;	// 다음 상태

	std::map<std::string, FSMState*> m_pStates;	// 생성된 FSMState들을 저장하는 컨테이너

	virtual void Update(float DeltaTime);
	void SetNextState(std::string stateName);

	template<typename T>
	void CreateState(const std::string StateName)
	{
		T* pState = new T(this,StateName);
		m_pStates.insert(std::make_pair(pState->GetName(), pState));
	}
};

