#pragma once

/*
	FSM���� ���̸� �ٷ�� Ŭ����
	�� Ŭ������ ����ص� ������ State�� CheckTransition�� ���� ������ ���� �ۼ��ص��ȴ�.
	�������� �ۼ��� ���� ������ ���� ���ٸ� �ڽ� Transition Ŭ���� �ۼ��� ����غ���.
*/
class FiniteStateMachine;
class GameObject;
class FSMTransition
{
public:
	FSMTransition(FiniteStateMachine* pOwner)
		:m_pOwner(pOwner)
	{

	}

	virtual ~FSMTransition()
	{

	}

public:
	std::string m_NextState;			// ��ȭ�� �����̸�
	virtual bool CheckCondition() = 0;	// ���� ����
	FiniteStateMachine* m_pOwner;
public:
	void SetOwner(FiniteStateMachine* pOwner) { m_pOwner = pOwner; }
};

