#pragma once
#include "Rect.h"
#include"Vec2.h"
class Ball;
class Sound;
class BallCont
{
public:
	BallCont();
	~BallCont();

	void Init();
	void End();
	void Update();
	void Draw();

	Rect GetColRect()const { return m_colRect; }

	Ball* CreateBall();

	Sound* m_pSound;
private:
	int m_timer;
	int m_timer2;

	int m_handle;
	int m_animCount;
	int m_animIndex;

	Vec2 m_pos;

	Rect m_colRect;
};
