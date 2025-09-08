#include "Sound.h"
#include"DxLib.h"
void Sound::Load()
{
	m_titleBgm = LoadSoundMem("data/titleBgm.mp3");
	m_playBgm  = LoadSoundMem("data/playBgm.mp3");
	m_clearBgm = LoadSoundMem("data/clearBgm.mp3");
	m_deadBgm  = LoadSoundMem("data/deadBgm.mp3");

	m_jumpSe = LoadSoundMem("data/jumpSe.mp3");
	m_fallSe = LoadSoundMem("data/fallSe.mp3");
	m_fireSe = LoadSoundMem("data/fireSe.mp3");
	m_runSe  = LoadSoundMem("data/runSe.mp3");
	m_ladderSe = LoadSoundMem("data/ladderSe.mp3");
	m_hitSe = LoadSoundMem("data/hitSe.mp3");
	m_buttonSe = LoadSoundMem("data/buttonSe.mp3");
} 

void Sound::PlaySe(int handle)
{
	PlaySoundMem(handle,DX_PLAYTYPE_BACK);
}

void Sound::PlayBgm(int handle)
{
	PlaySoundMem(handle, DX_PLAYTYPE_LOOP);
}

void Sound::DeleteSound()
{
	DeleteSoundMem(m_titleBgm);
	DeleteSoundMem(m_playBgm);
	DeleteSoundMem(m_clearBgm);
	DeleteSoundMem(m_deadBgm);
	DeleteSoundMem(m_jumpSe );
	DeleteSoundMem(m_fallSe );
	DeleteSoundMem(m_fireSe );
	DeleteSoundMem(m_runSe  );
	DeleteSoundMem(m_ladderSe);
	DeleteSoundMem(m_hitSe );
	DeleteSoundMem(m_buttonSe);
}
