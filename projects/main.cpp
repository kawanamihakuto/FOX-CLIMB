#include "DxLib.h"
#include"Game.h"
#include"SceneMain.h"
#include"Pad.h"
#include"GameTitle.h"
#include"GameClear.h"
#include"Player.h"
#include"Sound.h"
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E���[�h�ݒ�
	ChangeWindowMode(true);
	//�E�B���h�E�̃^�C�g���ݒ�
	SetMainWindowText("FOX CLIMB");
	//��ʂ̃T�C�Y�ύX
	SetGraphMode(kScreenWidth, kScreenHeight, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	SceneMain* m_pScene = new SceneMain;
	GameTitle* m_pTitle = new GameTitle;
	GameClear* m_pClear = new GameClear;
	Player* m_pPlayer = new Player;
	Sound* m_pSound = new Sound;
	m_pTitle->Init();
	m_pSound->Load();
	enum GameState {
		GAME_TITLE,   // �X�^�[�g���
		GAME_PLAY,    // �v���C��
		GAME_CLEAR,   // �N���A
		GAME_OVER     // �Q�[���I�[�o�[
	};

	GameState state = GAME_TITLE;
	
	int count = 0;
	int count2=0;
	int buttonNum=0;
	bool isChange=false;
	bool isChange2=false;
	while (ProcessMessage() != -1)
	{
		//���̃t���[���̊J�n���Ԃ��擾
		LONGLONG start = GetNowHiPerformanceCount();

		//�O�̃t���[���ɕ`�悵�����e���N���A����
		ClearDrawScreen();

		//�����ɃQ�[���̏���������
		switch (state)
		{
		case GAME_TITLE:
			//printfDx("GAME_TITLE\n");
			m_pTitle->Update();
			m_pTitle->Draw();
			Pad::Update();
			if (CheckSoundMem(m_pSound->m_titleBgm)==0)
			{
				m_pSound->PlayBgm(m_pSound->m_titleBgm);
				ChangeVolumeSoundMem(128,m_pSound->m_titleBgm);
			}
			if (Pad::IsTrigger(PAD_INPUT_B))
			{
				isChange = true;
				if (buttonNum == 0)
				{
					buttonNum++;
					m_pSound->PlaySe(m_pSound->m_buttonSe);
				}
				
			}
			if (isChange)
			{
				count++;
				int alpha = count * 255 / 30;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
				DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(0, 0, 0), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				if (count >= 100)
				{
					count = 0;
					buttonNum = 0;
					isChange = false;
					state = GAME_PLAY;
					m_pScene->Init();
					m_pPlayer->Init();
					m_pPlayer->m_pos = { 320,640 };
					m_pTitle->End();
					StopSoundMem(m_pSound->m_titleBgm);
				}
			}

			break;

		case GAME_PLAY:
			//printfDx("GAME_PLAY\n");
			m_pScene->Update();
			m_pScene->Draw();
			Pad::Update();
			if (CheckSoundMem(m_pSound->m_playBgm) == 0)
			{
				m_pSound->PlayBgm(m_pSound->m_playBgm);
				ChangeVolumeSoundMem(128, m_pSound->m_playBgm);
			}
			if (m_pScene->CheckClear())
			{
				count2++;
				int alpha = count2 * 255 / 30;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
				DrawBox(0, 0, kScreenWidth, kScreenHeight, GetColor(0, 0, 0), TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				
				if (count2 >= 40)
				{
					count2 = 0;
					state = GAME_CLEAR;
					m_pClear->Init();
					m_pScene->End();
					StopSoundMem(m_pSound->m_playBgm);
				}
				
			}
			break;
		case GAME_CLEAR:
			//printfDx("GAME_CLEAR\n");
			m_pClear->Update();
			m_pClear->Draw();
			Pad::Update();
			if (CheckSoundMem(m_pSound->m_clearBgm) == 0)
			{
				m_pSound->PlayBgm(m_pSound->m_clearBgm);
				ChangeVolumeSoundMem(128, m_pSound->m_clearBgm);
			}
			if (m_pClear->SceneChange())
			{
				
				state = GAME_TITLE;
				m_pClear->End();
				m_pTitle->Init();
				StopSoundMem(m_pSound->m_clearBgm);
				
			}
			break;
		}

		
		

		//esc�L�[�ŋ����I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		//�`�悵�����e����ʂɔ��f����
		ScreenFlip();

		//�t���[�����[�g60�ɌŒ�
		while (GetNowHiPerformanceCount() - start < 16667)
		{

		}


	}
	m_pTitle->End();
	m_pScene->End();
	m_pClear->End();
	m_pSound->DeleteSound();
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}