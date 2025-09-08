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

	//�w�肵���Z�`�Ɠ������Ă��邩���肷��
	//rect     : �w�肵���Z�`
	//chipRect : �}�b�v�`�b�v�̒Z�a
	//�������Ă��邩��Ԃ�
	bool IsCollision(Rect rect, Rect& chipRect);

	bool IsLadderCollision(Rect rect, Rect& chipRect);

private:
	//�w�i�\��
	void DrawBg();

	//�}�b�v�`�b�v�\��
	void DrawMapChip();

	//��q�̕\��
	void DrawLadder();

	//�}�b�v�f�[�^��ǂݍ���
	void LoadMapData();

	int m_bgHandle;//�w�i�摜
	Vec2 m_pos;
	int m_mapHandle;//�}�b�v�`�b�v�摜

	//�摜�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_graphChipNumX;
	int m_graphChipNumY;

	int m_mapData[40][22];//�}�b�v�f�[�^

	
};

