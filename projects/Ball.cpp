#include "Ball.h"
#include"DxLib.h"

namespace
{
	constexpr float kSpeed = 5.0f;
	constexpr float kBallSize = 32.0f;
}
Ball::Ball():
	m_isTurn(false),
	m_pos({416,144}),
	m_move({kSpeed,0}),
	m_animCount(0),
	m_animIndex(0)
	
{
	m_handle = LoadGraph("data/firespritesheet.png");
}

Ball::~Ball()
{
	DeleteGraph(m_handle);
}

void Ball::Init()
{

}

void Ball::Update()
{
	if (m_pos.x >= 1280)
	{
		if (m_move.x > 0)
		{
			m_pos.y += 160;
		}
		m_isTurn = true;
	}
	if (m_pos.x <= 0)
	{
		if (m_move.x < 0)
		{
			m_pos.y += 160;
		}
		m_isTurn = false;
	}
	if (!m_isTurn)
	{
		m_move = { kSpeed,0 };

		if (m_animCount % 8 == 0)
		{
			m_animIndex = (m_animIndex + 1) % 5;
		}
	}
	if (m_isTurn)
	{
		m_move = { -kSpeed,0 };

		if (m_animCount % 8 == 0)
		{
			m_animIndex = (m_animIndex + 1) % 5;
		}
	}
	m_pos += m_move;
	m_colRect.SetCenter(m_pos.x, m_pos.y, kBallSize-10, kBallSize-10);

	m_animCount++;
}

void Ball::Draw()
{
	float DrawX = m_pos.x - kBallSize * 0.5;
	float DrawY = m_pos.y - kBallSize * 0.5;
	int srcX = m_animIndex * 29;
	DrawRectGraph(DrawX, DrawY,srcX,0,29,27, m_handle,true,m_isTurn);
#ifdef _DEBUG
	m_colRect.Draw(0xff0000, false);
#endif
}



