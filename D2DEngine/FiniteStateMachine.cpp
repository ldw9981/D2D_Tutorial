#include "pch.h"
#include "FiniteStateMachine.h"
#include "FSMState.h"
#include "Helper.h"



void FiniteStateMachine::Update(float DeltaTime)
{
	if (m_pCurrentState == nullptr)
	{
		// �ʱ� ���·� �ٲ۴�.
		assert(m_pInitialState != nullptr);
		ChangeState(m_pInitialState->GetName());
		return;
	}

	// Update Action
	// ���� �������� State�� Update�� ������� �������� ������ ������ ó���ϰ� �Ѵ�.
	m_pCurrentState->Update(DeltaTime);

	// Transition Check�����Ͽ� ���ǿ� �����Ұ�� �Ѱܹ��� nextState�� �����Ѵ�.
	std::string nextStateName;
	if (m_pCurrentState->CheckTransition(nextStateName))
	{
		ChangeState(nextStateName);
		return;
	}
	/*
	// ���� Transition Check
	for (auto pStateAlias : m_pStateAlias)
	{
		// ���� State�� Alias�� ���ԵǾ� �ִ��� Ȯ���Ѵ�.
		if (!pStateAlias->CheckAlias(m_pCurrentState))
			continue;

		// Alias�� ���ԵǾ� ���� ��� Transition�� Ȯ���Ѵ�.
		if (pStateAlias->CheckTransition(nextStateName))
		{
			ChangeState(nextStateName);
			break;
		}
	}
	*/
}

void FiniteStateMachine::ChangeState(std::string stateName)
{
	if (m_pCurrentState)
	{
		// Exit Action 
		// State�� ����ɶ� ���� State�� ���� ó���� ������ �����Ѵ�.
		m_pCurrentState->Exit();
	}

	auto it = m_pStates.find(stateName);
	if (it != m_pStates.end())
	{
		m_pCurrentState = it->second;

		// Enter Action
		// State�� ����ɶ� ���ο� State�� ���� ó���� ������ �����Ѵ�.
		m_pCurrentState->Enter();
	}
	else
	{
		std::wstring wstrStateName = D2DHelper::StringToWString(stateName);
		LOG_WARNING(L"No state with name: %s ", wstrStateName.c_str());
	}
}

void FiniteStateMachine::SetInitialState(std::string stateName)
{
	auto it = m_pStates.find(stateName);
	if (it != m_pStates.end())
	{
		m_pInitialState = it->second;
	}
	else
	{
		std::wstring wstrStateName = D2DHelper::StringToWString(stateName);
		LOG_WARNING(L"No state with name: %s ", wstrStateName.c_str());
	}
}

void FiniteStateMachine::AddState(FSMState* pState)
{
	m_pStates.insert(make_pair(pState->GetName(), pState));
}
