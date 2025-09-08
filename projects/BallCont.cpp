#include "BallCont.h"
#include"Ball.h"
#include"DxLib.h"
#include"Sound.h"
namespace
{
	constexpr float kCharaSize = 64.0f;//キャラクターサイズ
}

BallCont::BallCont():
	m_timer(0),
	m_timer2(0),
	m_handle(-1),
	m_animCount(0),
	m_animIndex(0),
	m_pos(80*5,144)
{
	m_pSound = new Sound;
}


BallCont::~BallCont()
{
}

void BallCont::Init()
{
	m_handle = LoadGraph("data/transparent-particles.png");
	m_pSound->Load();
}

void BallCont::End()
{
	DeleteGraph(m_handle);
	m_pSound->DeleteSound();
}

void BallCont::Update()
{
	m_timer++;
	m_timer2++;
	m_colRect.SetCenter(m_pos.x, m_pos.y, kCharaSize - 30, kCharaSize - 30);
	m_animCount++;
	if (m_animCount % 8 == 0)
	{
		m_animIndex = (m_animIndex + 1) % 6;
	}
}

void BallCont::Draw()
{
	float drawX = m_pos.x - kCharaSize * 0.5f;
	float drawY = m_pos.y - kCharaSize * 0.5f;
	int srcX = m_animIndex * 64;
	DrawRectGraph(drawX, drawY-10,
		srcX,0,kCharaSize-10,kCharaSize-10, m_handle, true);
#ifdef _DEBUG
	//当たり判定を表示
	m_colRect.Draw(0x0000ff, false);
#endif
}

Ball* BallCont::CreateBall()
{
	if (m_timer >= 200)
	{
		ChangeVolumeSoundMem(200, m_pSound->m_fireSe);
		m_pSound->PlaySe(m_pSound->m_fireSe);
		m_timer = 0;
		Ball* pBall = new Ball();

		return pBall;
	}
	if (m_timer2 >= 250)
	{
		ChangeVolumeSoundMem(200, m_pSound->m_fireSe);
		m_pSound->PlaySe(m_pSound->m_fireSe);
		m_timer2 = 0;
		Ball* pBall = new Ball();

		return pBall;
	}
	return nullptr;
}
