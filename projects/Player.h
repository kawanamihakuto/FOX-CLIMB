#pragma once
#include"Vec2.h"
#include"Pad.h"
#include"Rect.h"
#include"Bg.h"
class Rect;
class Sound;
class Player
{
public:
	Player();
	~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	void Gravity();

	//�����蔻����擾
	Rect GetColRect()const { return m_colRect; }

	bool IsCollision(Rect rect);

	Rect m_colRect;//�����蔻��̒Z�`

	bool CheckClear();

	Vec2 m_pos;//���W

	void Dead();
private:

	void Move();

	void Jump();

	int m_handle;

	bool m_isRight;

	bool m_isGround;

	bool m_isLadder;

	bool m_isGravity;

	bool m_isClear;

	bool m_isDead;

	int m_deadTimer;

	Bg* m_pBg;

	Sound* m_pSound;
	
	int m_animCount;
	int m_animIndex; 
	int m_animRow;

	int m_fallNum;

	int m_hitHandle;

	int m_hitAnimCount;

	int m_hitAnimIndex;
	
protected:
	
	Vec2 m_move;//�ړ���
	
	//�}�b�v�`�b�v�Ƃ̓����蔻��
	//chipRect : �}�b�v�`�b�v�̓����蔻��
	void CheckHitMap(Rect chipRect);

	//��q�̓����蔻��
	void CheckHitLadder(Rect chipRect);
};

