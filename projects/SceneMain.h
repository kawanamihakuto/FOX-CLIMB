#pragma once
class Player;
class Bg;
class barrel;
class Ball;
class BallCont;
class GameTitle;
class GameClear;
class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();
	void Update();
	void Draw();

	bool CheckClear();
private:
	Player* m_pPlayer;

	Bg* m_pBg;

	//barrel* m_pBarrel;

	Ball* m_pBall[15];

	BallCont* m_pBallCont;

	GameTitle* m_pGameTitle;

	GameClear* m_pGameClear;

	void UpdateBall();

	void DeleteBall(int index);

	int m_count;
	int m_count2;
	bool m_isClear;

	bool m_isReset;
	int m_ResetTimer;
};

