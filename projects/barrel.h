#pragma once
#include"DxLib.h"
#include"Vec2.h"
#include"Rect.h"
#include"Bg.h"
#include<vector>
class Rect;
class Player;
class barrel
{
public:
	barrel();
	~barrel();

	void Init();
	void Update();
	void Draw();

	Rect GetColRect()const { return m_colRect; }

	Rect m_colRect;
	
private:
	void SpawnBarrel();
	void UpdataBarrel();
	void RemoveDeadBarrel();
	void Gravity();
	void Move();

	int m_handle;

	bool m_isTurn;

	int m_spawnTimer;

	Bg* m_pBg;

	std::vector<barrel> m_barrels;

	bool m_alive;

	float m_x;
	float m_y;

	int m_image;
protected:
	Vec2 m_pos;
	Vec2 m_move;

	

	Player* m_pPlayer;

	//マップチップとの当たり判定
	//chipRect : マップチップの当たり判定
	void CheckHitMap(Rect chipRect);
};

