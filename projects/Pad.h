#pragma once
namespace Pad
{
	void Update();

	//������Ă��邩
	bool IsPress(int key);

	//�����ꂽ�u�Ԃ��擾
	bool IsTrigger(int key);

	//�b�����u�Ԃ��擾
	bool IsRelease(int key);
}

