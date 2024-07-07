#include "pch.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "Helper.h"



FiniteStateMachine::~FiniteStateMachine()
{
	for (auto& state : m_pStates)
	{
		delete state.second;
	}
	m_pStates.clear();
}

void FiniteStateMachine::Update(float DeltaTime)
{
	if (m_pCurrState != m_pNextState)
	{
		if (m_pCurrState != nullptr)
		{
			m_pCurrState->Exit();
		}
		m_pCurrState = m_pNextState;
		m_pCurrState->Enter();
	}
	else
	{
		m_pCurrState->Update(DeltaTime);
	}

}

void FiniteStateMachine::SetNextState(std::string stateName)
{
	auto it = m_pStates.find(stateName);
	if (it != m_pStates.end())
	{
		m_pNextState = it->second;
	}
}