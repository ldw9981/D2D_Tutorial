#pragma once
#include "Character.h"
class Enemy :
    public TestCharacter
{
public:
	Enemy();
	~Enemy();

	// �θ��� Attack() �����Լ��� ������ �Ѵ�.
	// override Ű���带 ����ϸ� �θ��� �����Լ��� ������ ������ ��������� ǥ���� �� �ִ�.
	// �θ��� �Լ��� virtual �� ����Ǿ� ���� ������ �����Ϸ��� ������ �߻���Ų��.
	// �ڽ��� �Լ������� virtual Ű���带 ���� �����ϴ�.
	void Attack() override;
};

