#include "Bg.h"
#include"DxLib.h"
#include"Game.h"
#include<fstream>
#include<sstream>

namespace
{
	constexpr int kChipSize = 32;//マップチップ1つのサイズ
	constexpr float kChipScale = 1.0f;//マップチップ拡大率

	//チップを置く数
	constexpr int kChipNumX = kScreenWidth/kChipSize;
	constexpr int kChipNumY = kScreenHeight/kChipSize;

	
}

Bg::Bg():
	m_pos{0,0},
	m_graphChipNumX(0),
	m_graphChipNumY(0),
	m_mapData()
{
	//マップデータを読み込む
	LoadMapData();

	m_bgHandle = LoadGraph("data/back.png");
	m_mapHandle = LoadGraph("data/tileset2.png");
	
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_mapHandle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipSize;
	m_graphChipNumY = graphH / kChipSize;

}

Bg::~Bg()
{
	DeleteGraph(m_bgHandle);
	DeleteGraph(m_mapHandle);
}

void Bg::Init()
{
	
}

void Bg::Update()
{

}

void Bg::Draw()
{
	DrawBg();
	DrawMapChip();
	DrawLadder();
}

bool Bg::IsCollision(Rect rect, Rect& chipRect)
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			if (m_mapData[x][y] == 0)continue;       
			if (m_mapData[x][y] == 257)continue;
			int chipLeft = static_cast<int>(x * kChipSize * kChipScale);
			int chipRight = static_cast<int>(chipLeft+kChipSize * kChipScale);
			int chipTop = static_cast<int>(y * kChipSize * kChipScale);
			int chipBottom = static_cast<int>(chipTop + kChipSize * kChipScale);

			//絶対に当たらない場合
			if (chipLeft > rect.GetRight())continue;
			if (chipTop > rect.GetBottom())continue;
			if (chipRight < rect.GetLeft())continue;
			if (chipBottom < rect.GetTop())continue;

			//ぶつかったマップチップの短形を設定する
			chipRect.m_left = static_cast<float>(chipLeft);
			chipRect.m_right = static_cast<float>(chipRight);
			chipRect.m_top = static_cast<float>(chipTop);
			chipRect.m_bottom = static_cast<float>(chipBottom);

			//いずれかのチップに当たっていたら終了する
			return true;
		}
	}
	return false;
}

bool Bg::IsLadderCollision(Rect rect, Rect& chipRect)
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			if (m_mapData[x][y] == 0)continue;
			if (m_mapData[x][y] == 26)continue;
			int chipLeft = static_cast<int>(x * kChipSize * kChipScale);
			int chipRight = static_cast<int>(chipLeft + kChipSize * kChipScale);
			int chipTop = static_cast<int>(y * kChipSize * kChipScale);
			int chipBottom = static_cast<int>(chipTop + kChipSize * kChipScale);

			//絶対に当たらない場合
			if (chipLeft > rect.GetRight())continue;
			if (chipTop > rect.GetBottom())continue;
			if (chipRight < rect.GetLeft())continue;
			if (chipBottom < rect.GetTop())continue;

			//ぶつかったマップチップの短形を設定する
			chipRect.m_left = static_cast<float>(chipLeft);
			chipRect.m_right = static_cast<float>(chipRight);
			chipRect.m_top = static_cast<float>(chipTop);
			chipRect.m_bottom = static_cast<float>(chipBottom);

			//いずれかのチップに当たっていたら終了する
			return true;
		}
	}
	return false;
}

void Bg::DrawBg()
{
	DrawExtendGraph(m_pos.x, m_pos.y, kScreenWidth, kScreenHeight, m_bgHandle, true);
}

void Bg::DrawMapChip()
{
	//マップチップの描画
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			int posX = x * kChipSize;
			int posY = y * kChipSize;
			//設置するチップ
			int chipNo = m_mapData[x][y];          

			//マップチップのグラフィック切り出し座標
			int srcX = kChipSize * (chipNo % m_graphChipNumX);
			int srcY = kChipSize * (chipNo / m_graphChipNumY);

			//描画
			DrawRectRotaGraph(
				static_cast<int>(posX+kChipSize*kChipScale*0.5f),
				static_cast<int>(posY+kChipSize*kChipScale*0.5f),
				srcX, srcY,
				kChipSize, kChipSize, kChipScale, 0.0f, m_mapHandle, true);
#ifdef _DEBUG
			//当たり判定
			DrawBoxAA(posX, posY, 
				posX + kChipSize * kChipScale, posY + kChipSize * kChipScale,
				0x00ff00, false);
#endif 


		}
	}
}

void Bg::DrawLadder()
{
	for (int i = 0; i < 9; i++)
	{
		DrawRectGraph(32*34, 32*11 + i*32, 32 * 7, 32 * 10, 32, 32, m_mapHandle,true);
		DrawRectGraph(32* 5, 32*6 + i*32, 32 * 7, 32 * 10, 32, 32, m_mapHandle,true);
		
		
	}

	for (int i = 0; i < 8; i++)
	{
		DrawRectGraph(32 * 34, 32*2 + i * 32, 32 * 7, 32 * 10, 32, 32, m_mapHandle, true);
	}

	for (int i = 0; i < 4; i++)
	{
		DrawRectGraph(32 * 23, 32*16 + i * 32, 32 * 7, 32 * 10, 32, 32, m_mapHandle, true);
		DrawRectGraph(32 * 27, 32*11 + i * 32, 32 * 7, 32 * 10, 32, 32, m_mapHandle, true);
		DrawRectGraph(32 * 17, 32*6 + i * 32, 32 * 7, 32 * 10, 32, 32, m_mapHandle, true);		
	}

	for (int i = 0; i < 5; i++)
	{
		DrawRectGraph(32 * 5, 0 + i * 32, 32 * 7, 32 * 10, 32, 32, m_mapHandle, true);
		DrawRectGraph(32 * 15, 0 + i * 32, 32 * 7, 32 * 10, 32, 32, m_mapHandle, true);
	}
}

void Bg::LoadMapData()
{
	
	std::ifstream file("data/maptip.csv");
	std::string line;

	//getline関数で1行ずつ読み込む
	int y = 0;
	while (std::getline(file, line) && y < kChipNumY)
	{
		std::istringstream stream(line);
		std::string field;

		//「,」区切りごとにデータを読み込む
		int x = 0;
		while (getline(stream, field, ',') && x < kChipNumX)
		{
			//文字列をintがたに変換してm_chipDataに追加する
			m_mapData[x][y] = std::stoi(field);          
			x++;
		}
		y++;
	}
}
