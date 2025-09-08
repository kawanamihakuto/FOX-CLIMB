#pragma once
#include"Vec2.h"
#include"Rect.h"
class Bg
{
public:
	Bg();
	~Bg();

	void Init();
	void Update();
	void Draw();

	//指定した短形と当たっているか判定する
	//rect     : 指定した短形
	//chipRect : マップチップの短径
	//当たっているかを返す
	bool IsCollision(Rect rect, Rect& chipRect);

	bool IsLadderCollision(Rect rect, Rect& chipRect);

private:
	//背景表示
	void DrawBg();

	//マップチップ表示
	void DrawMapChip();

	//梯子の表示
	void DrawLadder();

	//マップデータを読み込む
	void LoadMapData();

	int m_bgHandle;//背景画像
	Vec2 m_pos;
	int m_mapHandle;//マップチップ画像

	//画像に含まれるマップチップの数
	int m_graphChipNumX;
	int m_graphChipNumY;

	int m_mapData[40][22];//マップデータ

	
};

