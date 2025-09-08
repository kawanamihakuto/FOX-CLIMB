#include "SceneMain.h"
#include"Player.h"
#include"Bg.h"
#include"barrel.h"
#include"Ball.h"
#include"BallCont.h"
#include"DxLib.h"
#include"Game.h"
#include"GameTitle.h"
#include"GameClear.h"

namespace
{
	constexpr int kBallMax = 15;
}

SceneMain::SceneMain() :
	m_count(0),
	m_count2(0),
	m_isClear(false),
	m_ResetTimer(0),
	m_isReset(false)
{
	m_pBg = new Bg;
	m_pPlayer = new Player;
	//m_pBarrel = new barrel;
	m_pBallCont = new BallCont;
	m_pGameTitle = new GameTitle;
	m_pGameClear = new GameClear;
	for (int i = 0; i < kBallMax; i++)
	{
		m_pBall[i] = nullptr;
	}
}

SceneMain::~SceneMain()
{

}

void SceneMain::Init()
{
	m_pPlayer->Init();
	//m_pBarrel->Init();
	m_pBallCont->Init();
	//printfDx("sceneInit");
	m_count = 0;
	m_count2 = 0;
	m_isClear = false;
	for (int i = 0; i < kBallMax; i++)
	{
		DeleteBall(i);
	}
	m_isReset = false;
}

void SceneMain::End()
{
	m_pPlayer->End();
	m_pBallCont->End();
}

void SceneMain::Update()
{
	m_pBg->Update();
	m_pPlayer->Update();
	//m_pBarrel->Update();
	m_pBallCont->Update();
	UpdateBall();
	CheckClear();

	m_count++;
	if (m_count >= 255)
	{
		m_count = 255;
	}
	if (m_pPlayer->m_pos.x <= -32 || m_pPlayer->m_pos.x >= kScreenWidth + 32 ||
		m_pPlayer->m_pos.y >= kScreenHeight + 32)
	{
		m_isReset = true;
		m_pPlayer->Dead();
	}
}

void SceneMain::Draw()
{
	m_pBg->Draw();
	m_pPlayer->Draw();	
	m_pBallCont->Draw();
	//m_pBarrel->Draw();
	if (!m_pBall)return;
	for (int i = 0; i < kBallMax; i++)
	{
		if (!m_pBall[i])continue;
		m_pBall[i]->Draw();
	}
	if (m_isReset)
	{
		m_ResetTimer++;
		int alpha = m_ResetTimer * 255 / 120;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (!m_isReset)
	{
		int alpha = 255 - (m_count * 255 / 30);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void SceneMain::UpdateBall()
{
	if (m_isReset)
	{
		if (m_ResetTimer >= 130)
		{
			m_ResetTimer = 0;
			End();
			Init();
		}
		return;
	}
	Ball* newBall = m_pBallCont->CreateBall();
	if (newBall != nullptr)
	{
		for (int i = 0; i < kBallMax; i++)
		{
			if (m_pBall[i] == nullptr)
			{
				m_pBall[i] = newBall;
				break;
			}
		}
	}

	for (int i = 0; i < kBallMax; i++)
	{
		if (!m_pBall[i])continue;

		m_pBall[i]->Update();

		bool isColPlayer = m_pBall[i]->GetColRect().IsCollision(m_pPlayer->GetColRect());
		bool isOffScreen = false;
		isOffScreen = m_pBall[i]->GetPos().y > kScreenHeight;
		if (isColPlayer||isOffScreen)
		{
			DeleteBall(i);
		}
		if (isColPlayer)
		{
			m_isReset = true;
			m_pPlayer->Dead();
		}
	}
	
	bool isColEnemy = m_pBallCont->GetColRect().IsCollision(m_pPlayer->GetColRect());
	if (isColEnemy)
	{
		m_isReset = true;
		m_pPlayer->Dead();
	}
}

void SceneMain::DeleteBall(int index)
{
	if (!m_pBall[index])return;

	delete m_pBall[index];
	m_pBall[index] = nullptr;
	//printfDx("íœ");
}

bool SceneMain::CheckClear()
{
	if (m_pPlayer->m_pos.x<=(32*7)&& m_pPlayer->m_pos.y<=0)
	{
		m_isClear = true;
	}
	if (m_isClear)
	{
		return true;	
	}
	else
	{
		return false;
	}
}


