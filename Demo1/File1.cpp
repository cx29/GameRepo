#include<graphics.h>
#include<iostream>
#include<string>
#include "Player.h"
#include"Enemy.h"
#include "FloatPOINT.h"

//�̶�60FPS
const float FIXED_TIME_STEP = 0.016f;

const int  WINDOW_WIDTH = 1280;
const int  WINDOW_HEIGHT = 720;

FloatPOINT player_pos = { 500.0f, 500.0f };
FloatPOINT enemy_pos = { 200.0f, 500.0f };
FloatPOINT enemy_pos1 = { 240.0f, 500.0f };
//���
Player anim_player(_T("img/player_left_%d.png"), _T("img/player_right_%d.png"), 6, 45, player_pos, 100.0f, WINDOW_WIDTH, WINDOW_HEIGHT);

/// <summary>
/// ���ɵ��˶���
/// </summary>
/// <param name="enemy_list">�����ַ,û��ʹ��const��������,���Խ����޸�</param>
void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
	//������
	const int INTERVAL = 1000;
	static int counter = 0;
	//���ۼӵ�100�ı���ʱ��������һ��Enemy����
	if ((++counter) % INTERVAL == 0)
	{
		Enemy* enemy = new Enemy(
			_T("img/enemy_left_%d.png"),
			_T("img/enemy_right_%d.png"),
			6, 45,
			WINDOW_WIDTH, WINDOW_HEIGHT
		);
		enemy_list.push_back(enemy);
	}
}

int main()
{
	//��ʼ��ͼ�δ���,�ֱ���Ϊ1280X720
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	//���Ƴ����Ƿ��������
	bool running = true;
	//����һ��IMAGE����,���ڴ洢����ͼ��
	IMAGE img_background;
	std::vector<Enemy*> enemy_list;
	//��ָ��·������ͼ�񵽶�����
	loadimage(&img_background, _T("img/background.png"));
	//������������,������˸��ˢ�´���
	BeginBatchDraw();
	//��¼��֡ʱ��
	DWORD last_time = GetTickCount();
	while (running)
	{
		//��¼ʱ�䵱ǰʱ��,GetTickCount��¼ϵͳ������ĺ�����
		DWORD current_time = GetTickCount();
		DWORD delta_time = current_time - last_time;
		last_time = current_time;
		//���ڽ��ܲ���������Ϣ(����̺�����¼�),��ֹ������������
		ExMessage msg;
		while (peekmessage(&msg))//����Ƿ�����Ϣδ����,���������ȡ��Ϣ
		{
			anim_player.ProcessLinstenKey(msg);
		}

		TryGenerateEnemy(enemy_list);
		cleardevice();//�����������,Ϊ���»�����׼��
		putimage(0, 0, &img_background);//������ͼ�����ڴ��ڵ�0,0λ��
		for (Enemy* enemy : enemy_list)
		{
			enemy->Move(anim_player, delta_time);
		}
		anim_player.PlayAnimation(delta_time);
		FlushBatchDraw();//ִ����������,������һ����ˢ�µ�������
	}
	//�ر���������,�������Ʋ���
	EndBatchDraw();
	return 0;
}