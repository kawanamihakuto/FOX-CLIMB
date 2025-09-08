#include "Player.h"
#include"DxLib.h"
#include"SceneMain.h"
#include"Vec2.h"
#include"Rect.h"
#include"Ball.h"
#include"Sound.h"
#include"Game.h"
namespace
{
	constexpr float kSpeed = 2.5f;//移動速度
	constexpr float kGravity = 0.5f;//重力
	constexpr float kJumpPower = 8.0f;//ジャンプ力
	constexpr float kCharaSize = 28.0f;//キャラクターサイズ
	const Vec2 kInitPos = { 320.0f,640.0f };//初期位置
}
Player::Player() :
	m_handle(-1),
	m_isRight(true),
	m_isGround(false),
	m_isLadder(false),
	m_isGravity(true),
	m_isClear(false),
	m_isDead(false),
	m_animCount(0),
	m_animIndex(0),
	m_animRow(0),
	m_deadTimer(0),
	m_fallNum(0),
	m_hitHandle(-1),
	m_hitAnimCount(0),
	m_hitAnimIndex(0)
{
	m_pBg = new Bg;
	m_pSound = new Sound;
	m_pos = kInitPos;

	
}

Player::~Player()
{
}

void Player::Init()
{
	m_handle = LoadGraph("data/FoxSpritesheet.png");
	m_hitHandle = LoadGraph("data/fireBallHit.png");
	m_pos = { 320,600 };
	m_move = { 0,0 };
	m_isDead = false;
	m_pSound->Load();
	m_fallNum = 0;
}

void Player::End()
{
	DeleteGraph(m_handle);
	DeleteGraph(m_hitHandle);
	m_pSound->DeleteSound();
}

void Player::Update()
{
	m_animCount++;
	if (m_isDead)
	{
		m_hitAnimCount++;
		StopSoundMem(m_pSound->m_runSe);
		StopSoundMem(m_pSound->m_ladderSe);
		StopSoundMem(m_pSound->m_jumpSe);
		if (m_pos.y >= kScreenHeight)
		{
			if (CheckSoundMem(m_pSound->m_fallSe) == 0)
			{
				if (m_fallNum == 0)
				{
					m_fallNum++;
					ChangeVolumeSoundMem(160, m_pSound->m_fallSe);
					m_pSound->PlaySe(m_pSound->m_fallSe);
				}
			}
			
		}
		if (CheckSoundMem(m_pSound->m_hitSe) == 0)
		{
			if (CheckSoundMem(m_pSound->m_fallSe)==0)
			{
				ChangeVolumeSoundMem(160, m_pSound->m_hitSe);
				m_pSound->PlaySe(m_pSound->m_hitSe);
			}
		}
		
	
		m_animRow = 8;
		if (m_animCount % 8 == 0)
		{
			m_animIndex = (m_animIndex + 1) % 6;
		}

		if (m_hitAnimCount % 8 == 0)
		{
			m_hitAnimIndex = (m_hitAnimIndex + 1) % 6;
		}


		return;
	}
	Move();
	Jump();
	Gravity();

	CheckClear();
	Rect chipRect;//当たったマップチップの短形
	CheckHitMap(chipRect);
	CheckHitLadder(chipRect);
	m_colRect.SetCenter(m_pos.x, m_pos.y, kCharaSize - 10, kCharaSize - 10);
	
	
	
	
}

void Player::Draw()
{
	float drawX = m_pos.x - 32 * 0.5f;
	float drawY = m_pos.y - 32 * 0.5f;
	int srcX = m_animIndex * 32;
	int srcY = m_animRow * 32;
	if (m_isRight)
	{
		DrawRectGraph(drawX, drawY, srcX+3, srcY+1 ,
			32, 32, m_handle, true);
	}
	else
	{
		DrawRectGraph(drawX, drawY, srcX+3, srcY +1,
			32, 32, m_handle, true,true);
	}

	int hitSrcX = m_hitAnimIndex * 29;
	if (m_isDead)
	{
		DrawRectGraph(drawX, drawY, hitSrcX ,0 ,
			29, 27, m_hitHandle, true);
	}
	
	
	
#ifdef _DEBUG
	//当たり判定を表示
	m_colRect.Draw(0x0000ff, false);
#endif
}

void Player::Gravity()
{
	if (m_isGravity)
	{
		m_move.y += kGravity;
	}
}

bool Player::CheckClear()
{
	if (m_pos.y <= 0&&m_pos.x<=32*7)
	{
		m_isClear = true;
		
	}
	if (m_isClear)
	{
		return true;
	}
	return false;
}

void Player::Dead()
{
	m_isDead = true;
}

void Player::Move()
{
	
	if (m_isGround)
	{
		if (Pad::IsPress(PAD_INPUT_LEFT))
		{
			m_animRow = 1;
			if (m_animCount % 8 == 0)
			{
				m_animIndex = (m_animIndex + 1) % 6;
			}
			if (CheckSoundMem(m_pSound->m_runSe) == 0)
			{
				m_pSound->PlaySe(m_pSound->m_runSe);
			}
			
			m_move.x = -kSpeed;
			m_isRight = false;

			if (!m_isGravity)
			{
				StopSoundMem(m_pSound->m_runSe);
			}
		}
		else if (Pad::IsPress(PAD_INPUT_RIGHT))
		{
			m_animRow = 1;
			if (m_animCount % 8 == 0)
			{
				m_animIndex = (m_animIndex + 1) % 6;
			}
			if (CheckSoundMem(m_pSound->m_runSe) == 0)
			{
				m_pSound->PlaySe(m_pSound->m_runSe);
			}
			
			m_move.x = kSpeed;
			m_isRight = true;
			if (!m_isGravity)
			{
				StopSoundMem(m_pSound->m_runSe);
			}
		}
		else
		{
			m_animRow = 0;
			if (m_animCount % 8 == 0)
			{
				m_animIndex = (m_animIndex + 1) % 4;
			}
			m_move.x = 0.0f;
			StopSoundMem(m_pSound->m_runSe);
		}
	}
	if (m_isLadder)
	{
		
		if (Pad::IsPress(PAD_INPUT_UP))
		{
			m_animRow = 2;
			if (m_animCount % 8 == 0)
			{
				m_animIndex = (m_animIndex + 1) % 4;
			}
			m_isGround = true;
			m_isGravity = false;
			m_move.x = 0.0f;
			m_move.y = -2.0f;

			if (CheckSoundMem(m_pSound->m_ladderSe)==0)
			{
				m_pSound->PlaySe(m_pSound->m_ladderSe);
			}
		}
		else if (Pad::IsPress(PAD_INPUT_DOWN))
		{
			m_animRow = 2;
			if (m_animCount % 8 == 0)
			{
				m_animIndex = (m_animIndex + 1) % 4;
			}
			m_isGround = true;
			m_isGravity = false;
			m_move.x = 0.0f;
			m_move.y = 2.0f;
			
		}
		else if (Pad::IsPress(PAD_INPUT_LEFT))
		{
			
			if (!m_isGravity)
			{
				m_animRow = 2;
				if (m_animCount % 8 == 0)
				{
					m_animIndex = (m_animIndex + 1) % 4;
				}
				if (!m_isGravity)
				{
					if (CheckSoundMem(m_pSound->m_ladderSe) == 0)
					{
						m_pSound->PlaySe(m_pSound->m_ladderSe);
					}
				}
			}
			
		}
		else if (Pad::IsPress(PAD_INPUT_RIGHT))
		{
			
			if (!m_isGravity)
			{
				m_animRow = 2;
				if (m_animCount % 8 == 0)
				{
					m_animIndex = (m_animIndex + 1) % 4;
				}
				if (CheckSoundMem(m_pSound->m_ladderSe) == 0)
				{
					if (CheckSoundMem(m_pSound->m_ladderSe) == 0)
					{
						m_pSound->PlaySe(m_pSound->m_ladderSe);
					}
				}
			}
			
		}
		else
		{
			StopSoundMem(m_pSound->m_ladderSe);
			if (!m_isGravity)
			{
				m_animRow = 2;
				m_animIndex = 0;
				m_move.y = 0.0f;
			}
		}
	}
	if (!m_isLadder)
	{
		StopSoundMem(m_pSound->m_ladderSe);
	}

}

void Player::Jump()
{
	//ジャンプ中は飛ばす
	if (!m_isGround)
	{
		StopSoundMem(m_pSound->m_runSe);
		if (m_move.y >= 0)
		{
			m_animRow = 5;
			m_animIndex = 1;
		}
		if (m_move.y < 0)
		{
			m_animRow = 5;
			m_animIndex = 0;
		}
		return;
	}
	if (m_isGravity)
	{
		if (Pad::IsTrigger(PAD_INPUT_B))
		{
			m_pSound->PlaySe(m_pSound->m_jumpSe);
			m_move.y = -kJumpPower;
			m_isGround = false;
		}
	}
	
}

void Player::CheckHitMap(Rect chipRect)
{
	//横から当たったかチェックする
	m_pos.x += m_move.x;
	m_colRect.SetCenter(m_pos.x, m_pos.y, kCharaSize-1, kCharaSize-1);
	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_move.x > 0.0f)
		{
			m_pos.x = chipRect.GetLeft() - kCharaSize * 0.5f;
		}
		else if (m_move.x < 0.0f)
		{
			m_pos.x = chipRect.GetRight() + kCharaSize * 0.5f;
		}
		m_move.x = 0.0f;
	}

	//縦から当たったかチェックする
	m_pos.y += m_move.y;
	m_colRect.SetCenter(m_pos.x, m_pos.y, kCharaSize-1, kCharaSize-1);

	if (m_pBg->IsCollision(m_colRect, chipRect))
	{
		if (m_move.y > 0.0f)
		{
			m_pos.y = chipRect.GetTop() - kCharaSize * 0.5f;
			m_move.y = 0.0f;
			m_isGround = true;
			m_isGravity = true;
		}
		else if (m_move.y < 0.0f)
		{
			m_pos.y = chipRect.GetBottom() + kCharaSize * 0.5f;
			m_move.y *= -1.0f;
		}
	}	
}

void Player::CheckHitLadder(Rect chipRect)
{
	if (m_pBg->IsLadderCollision(m_colRect, chipRect))
	{
		m_isLadder = true;
	}
	else
	{
		m_isGravity = true;
		m_isLadder = false;
	}
}

bool Player::IsCollision(Rect rect)
{
	//絶対に当たらないパターンをはじいていく
	if (m_colRect.m_left > rect.m_right)return false;
	if (m_colRect.m_top > rect.m_bottom)return false;
	if (m_colRect.m_right < rect.m_left)return false;
	if (m_colRect.m_bottom < rect.m_top)return false;

	//当たらないパターン以外は当たっている
	 return true;
}
