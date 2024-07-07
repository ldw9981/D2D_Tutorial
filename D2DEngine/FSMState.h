#pragma once

/*
	FSMState �߻�Ŭ���� 
	���̴� Transition Class�� ����ص��ǰ�
	CheckTransition �Լ��� ������(override) �ؼ� ����ص���
*/
class FSMTransition;
class FiniteStateMachine;
class FSMState
{
public:
	FSMState(FiniteStateMachine* pOwner, std::string Name)
		:m_pOwner(pOwner)
		, m_Name(Name)
	{

	}
	virtual ~FSMState()
	{

	}
	std::string m_Name;
	FiniteStateMachine* m_pOwner;

	
public:
	void SetOwner(FiniteStateMachine* pOwner) { m_pOwner = pOwner; }
	
	const std::string& GetName() { return m_Name; }

	virtual void Enter() = 0;	// ���� ������ ������ ����
	virtual void Update(float DeltaTime)=0; // ���� �϶� ��� ������ ����, ���� ���� �˻� (Check Transition Condition) �� ���� �Ѵ�.
	virtual void Exit() = 0;	// ���� Ż�⶧ ������ ����
};


