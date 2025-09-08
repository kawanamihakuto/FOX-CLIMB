#pragma once
#include"Vec2.h"
#include"Rect.h"
class Ball
{
public:
	Ball();
	~Ball();

	void Init();
	void Update();
	void Draw();

	Vec2 GetPos()const { return m_pos; }
	Rect GetColRect()const { return m_colRect; }
private:
	int m_handle;
	bool m_isTurn;
	Vec2 m_pos;
	Vec2 m_move;
	Rect m_colRect;

	int m_animCount;
	int m_animIndex;
};

