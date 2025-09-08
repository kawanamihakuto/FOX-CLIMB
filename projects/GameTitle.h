#pragma once

class GameTitle
{
public:
	GameTitle();
	~GameTitle();

	void Init();
	void End();
	void Update();
	void Draw();

	void FadeOut();
	bool SceneChange();
	bool m_isChange;
private:
	int m_titleFontHandle;
	int m_pressFontHandle;
	int m_bgHandle;
	int m_frame;
	bool m_isFade;
	int m_count;
};