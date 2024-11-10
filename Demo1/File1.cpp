#include<graphics.h>
#include<iostream>
#include<string>
#include "Player.h"
#include"Enemy.h"
#include "FloatPOINT.h"

//固定60FPS
const float FIXED_TIME_STEP = 0.016f;

const int  WINDOW_WIDTH = 1280;
const int  WINDOW_HEIGHT = 720;

FloatPOINT player_pos = { 500.0f, 500.0f };
FloatPOINT enemy_pos = { 200.0f, 500.0f };
FloatPOINT enemy_pos1 = { 240.0f, 500.0f };
//玩家
Player anim_player(_T("img/player_left_%d.png"), _T("img/player_right_%d.png"), 6, 45, player_pos, 100.0f, WINDOW_WIDTH, WINDOW_HEIGHT);

/// <summary>
/// 生成敌人对象
/// </summary>
/// <param name="enemy_list">传入地址,没有使用const进行修饰,可以进行修改</param>
void TryGenerateEnemy(std::vector<Enemy*>& enemy_list)
{
	//计数器
	const int INTERVAL = 1000;
	static int counter = 0;
	//当累加到100的倍数时就新生成一个Enemy对象
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
	//初始化图形窗口,分辨率为1280X720
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	//控制程序是否继续运行
	bool running = true;
	//定义一个IMAGE对象,用于存储背景图像
	IMAGE img_background;
	std::vector<Enemy*> enemy_list;
	//从指定路径加载图像到对象中
	loadimage(&img_background, _T("img/background.png"));
	//开启批量绘制,减少闪烁和刷新次数
	BeginBatchDraw();
	//记录上帧时间
	DWORD last_time = GetTickCount();
	while (running)
	{
		//记录时间当前时间,GetTickCount记录系统启动后的毫秒数
		DWORD current_time = GetTickCount();
		DWORD delta_time = current_time - last_time;
		last_time = current_time;
		//用于接受并处理窗口消息(如键盘和鼠标事件),防止阻塞窗口运行
		ExMessage msg;
		while (peekmessage(&msg))//检查是否有消息未处理,如果有则提取消息
		{
			anim_player.ProcessLinstenKey(msg);
		}

		TryGenerateEnemy(enemy_list);
		cleardevice();//清除窗口内容,为重新绘制做准备
		putimage(0, 0, &img_background);//将背景图绘制在窗口的0,0位置
		for (Enemy* enemy : enemy_list)
		{
			enemy->Move(anim_player, delta_time);
		}
		anim_player.PlayAnimation(delta_time);
		FlushBatchDraw();//执行批量绘制,将内容一次性刷新到窗口上
	}
	//关闭批量绘制,结束绘制操作
	EndBatchDraw();
	return 0;
}