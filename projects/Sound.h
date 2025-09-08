#pragma once
class Sound
{public:

	void Load();
	void PlaySe(int handle);
	void PlayBgm(int handle);
	void DeleteSound();
	int m_titleBgm;
	int m_playBgm;
	int m_clearBgm;
	int m_deadBgm;

	int m_jumpSe;
	int m_fallSe;
	int m_fireSe;
	int m_runSe;
	int m_ladderSe;
	int m_hitSe;
	int m_buttonSe;
		
};

