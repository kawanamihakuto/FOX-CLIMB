#include "GameClear.h"
#include"DxLib.h"
#include"Game.h"
#include"Pad.h"
#include"Sound.h"
GameClear::GameClear():
	m_bgHandle(-1),
	m_clearFontHandle(-1),
	m_pressFontHandle(-1),
	m_frame(0),
	m_count(0),
	m_count2(0),
	m_isChange(false),
	m_isFade(false),
	m_buttomNum(0)
{
	m_pSound = new Sound;
}

GameClear::~GameClear()
{
}

void GameClear::Init()
{
	m_bgHandle = LoadGraph("data/back.png");
	m_clearFontHandle = CreateFontToHandle("HGP‘n‰pÌßÚ¾Şİ½EB", 128, 3);
	m_pressFontHandle = CreateFontToHandle("HGP‘n‰pÌßÚ¾Şİ½EB", 64, 3);
	//printfDx("clearInit");
	m_count = 0;
	m_count2 = 0;
	m_isFade = false;
	m_isChange = false;
	m_buttomNum = 0;
	m_pSound->Load();
}

void GameClear::End()
{
	DeleteFontToHandle(m_clearFontHandle);
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_pressFontHandle);
	m_pSound->DeleteSound();
}

void GameClear::Update()
{
	m_frame++;
	m_count++;
	if (m_count >= 255)
	{
		m_count = 255;
	}
	
		SceneChange();
	
}

void GameClear::Draw()
{
	DrawExtendGraph(0, 0, kScreenWidth, kScreenHeight, m_bgHandle, true);

	int width = GetDrawFormatStringWidthToHandle(m_clearFontHandle, "GAME CLEAR!");
	DrawStringToHandle((kScreenWidth / 2) - (width / 2), kScreenHeight / 2-128,
		"GAME CLEAR!", GetColor(255, 0, 255), m_clearFontHandle);

	int width2 = GetDrawFormatStringWidthToHandle(m_pressFontHandle, "PRESS RETRY( B ) ");
	if ((m_frame / 30) % 2 == 0)
	{
		DrawStringToHandle((kScreenWidth / 2) - (width2 / 2), kScreenHeight / 2 + 128,
			"PRESS RETRY( B )", GetColor(255, 255, 0), m_pressFontHandle);
	}

	int alpha = 255 - (m_count * 255 / 30);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameClear::FadeOut()
{
	
}

bool GameClear::SceneChange()
{
	if (Pad::IsTrigger(PAD_INPUT_B)&&m_count>=100)
	{
		if (m_buttomNum == 0)
		{
			m_buttomNum++;
			m_pSound->PlaySe(m_pSound->m_buttonSe);
		}
		m_isFade = true;
	}
	if (m_isFade)
	{
		m_count2++;

		int alpha = m_count2 * 255 / 30;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(0, 0, 0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		if (m_count2 >= 100)
		{
			return true;
		}
	}
	
	if (!m_isChange)
	{
		return false;
	}
	
}