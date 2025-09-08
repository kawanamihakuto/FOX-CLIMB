#pragma once
#include"Vec2.h"
class Rect
{
public:
	Rect();
	~Rect();

	//短形の描画
	void Draw(unsigned int Color,bool isFill);

	//左上座標と幅、高さを指定
	//left   : 左
	//top    : 上
	//width  : 幅
	//height : 高さ
	void SetLT(float left, float top, float width, float height);

	//中心座標と幅、高さを指定
	void SetCenter(float x, float y, float width, float height);

	//短形の幅を取得
	float GetWidth()const;

	//短形の高さを取得
	float GetHeight()const;

	//短形の中心座標を取得
	Vec2 GetCenter()const;

	//短形の左上のX座標を取得
	float GetLeft()const { return m_left; }

	//短形の左上のY座標を取得
	float GetTop()const { return m_top; }

	//短形の右下のX座標を取得
	float GetRight()const { return m_right; }

	//短形の右下のY座標を取得
	float GetBottom()const { return m_bottom; }

	//短形の当たり判定
	//rect : 短形情報
	//当たっているかどうか
	bool IsCollision(const Rect& rect);

public:
	float m_left;  //左上のX座標
	float m_top;   //左上のY座標
	float m_right; //右下のX座標
	float m_bottom;//右下のY座標
};

