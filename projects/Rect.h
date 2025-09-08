#pragma once
#include"Vec2.h"
class Rect
{
public:
	Rect();
	~Rect();

	//�Z�`�̕`��
	void Draw(unsigned int Color,bool isFill);

	//������W�ƕ��A�������w��
	//left   : ��
	//top    : ��
	//width  : ��
	//height : ����
	void SetLT(float left, float top, float width, float height);

	//���S���W�ƕ��A�������w��
	void SetCenter(float x, float y, float width, float height);

	//�Z�`�̕����擾
	float GetWidth()const;

	//�Z�`�̍������擾
	float GetHeight()const;

	//�Z�`�̒��S���W���擾
	Vec2 GetCenter()const;

	//�Z�`�̍����X���W���擾
	float GetLeft()const { return m_left; }

	//�Z�`�̍����Y���W���擾
	float GetTop()const { return m_top; }

	//�Z�`�̉E����X���W���擾
	float GetRight()const { return m_right; }

	//�Z�`�̉E����Y���W���擾
	float GetBottom()const { return m_bottom; }

	//�Z�`�̓����蔻��
	//rect : �Z�`���
	//�������Ă��邩�ǂ���
	bool IsCollision(const Rect& rect);

public:
	float m_left;  //�����X���W
	float m_top;   //�����Y���W
	float m_right; //�E����X���W
	float m_bottom;//�E����Y���W
};

