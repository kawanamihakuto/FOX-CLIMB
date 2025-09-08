#pragma once
class Sound;
class GameClear
{
public:
	GameClear();
	~GameClear();

	void Init();
	void End();
	void Update();
	void Draw();

	void FadeOut();
	bool SceneChange();
private:
	int m_bgHandle;
	int m_clearFontHandle;
	int m_pressFontHandle;
	int m_frame;
	int m_count;
	int m_count2;
	bool m_isChange;
	bool m_isFade;
	int m_buttomNum;
	Sound* m_pSound;
};

