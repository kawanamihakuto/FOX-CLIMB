#include "barrel.h"
#include<algorithm>
#include"Game.h"
#include"Player.h"

namespace
{
	const Vec2 kInitPos = { 100.0f,144.0f };
	constexpr float kGravity = 0.5f;
	constexpr float kSize = 32;
}
barrel::barrel() :
	m_handle(-1),
	m_isTurn(false),
	m_spawnTimer(0),
	m_alive(false),
	m_x(0),
	m_y(0),
	m_image(0)
{
	m_pBg = new Bg;
	m_pos = kInitPos;
	m_pPlayer = new Player;
}

barrel::~barrel()
{
}

void barrel::Init()
{
	m_handle = LoadGraph("data/fireball-1.png");
	m_barrels.clear();

}

void barrel::Update()
{
	m_spawnTimer++;
	if (m_spawnTimer > 180)
	{
		SpawnBarrel();
		m_spawnTimer = 0;
	}
	UpdataBarrel();
	RemoveDeadBarrel();

	Rect chipRect;
	CheckHitMap(chipRect);

}

void barrel::Draw()
{
	for (auto& b : m_barrels)
	{
		if (!b.m_alive)continue;
		DrawRectGraph((int)b.m_pos.x-kSize*0.5f, (int)b.m_pos.y - kSize * 0.5f,
			0,0,kSize,kSize, b.m_image, true,b.m_isTurn);
#ifdef _DEBUG
		/*DrawBox(b.m_pos.x - kSize * 0.5f, b.m_pos.y - kSize * 0.5f,
			b.m_pos.x + kSize - kSize * 0.5f, b.m_pos.y + kSize - kSize * 0.5f,
			GetColor(255, 0, 255), false 
		);*/
		b.m_colRect.Draw(0x0000ff, false);
#endif // _DEBUG
	}

	

}

//¶¬
void barrel::SpawnBarrel()
{
	barrel b;
	b.m_x = kInitPos.x;
	b.m_y = kInitPos.y;
	b.m_move.x = 5.0f;
	b.m_move.y = 0.0f;
	b.m_image = m_handle;
	b.m_alive = true;
	m_barrels.push_back(b);
}

//XV
void barrel::UpdataBarrel()
{
	for (auto& b : m_barrels)
	{
		if (!b.m_alive)continue;

		//b.m_move.y += kGravity;
		b.m_pos.x += b.m_move.x;
		b.m_pos.y += b.m_move.y;

		if (b.m_pos.x >= kScreenWidth)
		{
			b.m_pos.y += kSize * 5;
			b.m_move.x = -b.m_move.x;
			b.m_isTurn = !b.m_isTurn;
		}
		else if (b.m_pos.x <= 0)
		{
			b.m_pos.y += kSize * 5;
			b.m_move.x = -b.m_move.x;
			b.m_isTurn = !b.m_isTurn;
		}

		b.m_colRect.SetCenter(b.m_pos.x, b.m_pos.y, kSize - 1, kSize - 1);
		
		//íœ
		if (b.m_pos.y >= kScreenHeight)
		{
			printfDx("íœ\n");
			b.m_alive = false;
		}
		
		bool isColPlayer = b.GetColRect().IsCollision(m_pPlayer->GetColRect());

		if (isColPlayer)
		{
			printfDx("“–‚½‚Á‚Ä‚é");
		}

		if (m_pPlayer->IsCollision(b.m_colRect))
		{
			printfDx("“–‚½‚Á‚Ä‚é");
		}
		
	}
}

void barrel::RemoveDeadBarrel()
{
	m_barrels.erase(
		std::remove_if(m_barrels.begin(), m_barrels.end(),
			[](const barrel& b) {return !b.m_alive; }),
		m_barrels.end()
	);
}

void barrel::CheckHitMap(Rect chipRect)
{
	for (auto& b : m_barrels)
	{
		if (!b.m_alive)continue;

		//m_colRect.SetCenter(b.m_pos.x, b.m_pos.y, kSize-1, kSize-1);

		if (m_pBg->IsCollision(m_colRect, chipRect))
		{
			if (b.m_move.y > 0.0f)
			{
				b.m_pos.y = chipRect.GetTop() - kSize * 0.5f;
				b.m_move.y = 0.0f;
			}
		}
	}
}
