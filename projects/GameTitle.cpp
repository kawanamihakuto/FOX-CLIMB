#include "GameTitle.h"
#include"DxLib.h"
#include"Game.h"
#include"Pad.h"
#include"Sound.h"
GameTitle::GameTitle() :
	m_titleFontHandle(-1),
	m_pressFontHandle(-1),
	m_bgHandle(-1),
	m_frame(0),
	m_isFade(false),
	m_isChange(false),
	m_count(0)
{
}
GameTitle::~GameTitle()
{
}

void GameTitle::Init()
{
	m_titleFontHandle = CreateFontToHandle("HGP‘n‰pÌßÚ¾ÞÝ½EB",128,3);
	m_pressFontHandle = CreateFontToHandle("HGP‘n‰pÌßÚ¾ÞÝ½EB", 64, 3);
	m_bgHandle= LoadGraph("data/back.png");
	//printfDx("titleInit");
	m_isChange = false;
	m_frame = 0;
	m_isFade = false;
	m_count = 0;
}

void GameTitle::End()
{
	DeleteFontToHandle(m_titleFontHandle);
	DeleteFontToHandle(m_pressFontHandle);
	DeleteGraph(m_bgHandle);
}

void GameTitle::Update()
{
	m_frame++;
	SceneChange();
}

void GameTitle::Draw()
{
	DrawExtendGraph(0, 0, kScreenWidth, kScreenHeight, m_bgHandle, true);

	int width = GetDrawFormatStringWidthToHandle(m_titleFontHandle, "FOX CLIMB");
	DrawStringToHandle((kScreenWidth / 2) - (width / 2), kScreenHeight / 2-128,
		"FOX CLIMB", GetColor(255, 0, 255), m_titleFontHandle);
	int width2 = GetDrawFormatStringWidthToHandle(m_pressFontHandle, "PRESS START( B )");
	if ((m_frame / 30) % 2 == 0)
	{
		DrawStringToHandle((kScreenWidth / 2) - (width2 / 2), kScreenHeight / 2 + 128,
			"PRESS START( B )", GetColor(255, 255, 0), m_pressFontHandle);
	}
	
	/*if (Pad::IsTrigger(PAD_INPUT_2))
	{
		m_isFade = true;
	}
	if (m_isFade)
	{
		FadeOut();
	}*/
}

void GameTitle::FadeOut()
{
	/*m_count++;
	int alpha = m_count * 255 / 30;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0,kScreenWidth, kScreenHeight, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (m_count >= 100)
	{
		m_isChange = true;
	}*/
}

bool GameTitle::SceneChange()
{
	/*if (m_isChange)
	{
		return true;
	}
	*/
		return false;
	
	
}
