#pragma once
#include<cmath>
class Vec2
{
public:
	float x;
	float y;

public:
	Vec2() :
		x(0.0f),
		y(0.0f)
	{
	}

	Vec2(float posX, float posY) :
		x(posX),
		y(posY)
	{
	}

	//’P€‰‰Zq+ Vec2 = +Vec2
	Vec2 operator+() const
	{
		return *this;
	}

	//’P€‰‰Zq- Vec2 = -Vec2
	Vec2 operator-() const
	{
		return Vec2{ -x, - y };
	}

	//‘«‚µZ c = a + b,c = (a += b)
	Vec2 operator+(Vec2 vec)const
	{
		return Vec2{ x + vec.x,y + vec.y };
	}

	//Vec2 += Vec2
	Vec2 operator+=(Vec2 vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	//ˆø‚«Z
	Vec2 operator-(Vec2 vec)const
	{
		return Vec2{ x - vec.x,y - vec.y };
	}

	//Vec2 -= Vec2
	Vec2 operator-=(Vec2 vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	//Š|‚¯Z
	Vec2 operator*(float scale)const
	{
		return Vec2{ x * scale,y * scale };
	}

	//Vec2 *= float
	Vec2 operator*=(float scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}

	//Š„‚èZ
	Vec2 operator/(float scale)const
	{
		return Vec2{ x / scale,y / scale };
	}

	//Vec2 /= float
	Vec2 operator/=(float scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}

	//ƒxƒNƒgƒ‹‚Ì’·‚³‚Ì2æ‚ğ‹‚ß‚é
	float sqLength()const
	{
		return x * x + y * y;
	}

	//ƒxƒNƒgƒ‹‚Ì’·‚³‚ğ‹‚ß‚é
	float Length()const
	{
		return sqrtf(sqLength());
	}

	//©g‚Ì³‹K‰»‚ğs‚¤
	void normalize()
	{
		float len = Length();
		if (len > 0.0f)
		{
			x /= len;
			y /= len;
		}
		//’·‚³‚O‚Ìê‡‚Í‰½‚à‚µ‚È‚¢
	}

	//©g‚ğ³‹K‰»‚µ‚½ƒxƒNƒgƒ‹‚ğæ“¾‚·‚é
	Vec2 getNormalize()const
	{
		float len = Length();
		if (len > 0.0f)
		{
			return Vec2{ x / len,y / len };
		}
		//’·‚³‚ª‚O‚Ìê‡
		return Vec2{ 0.0f,0.0f };
	}
};

