//初期設定

#define _CRT_SECURE_NO_WARNINGS
#include "DxLib.h"
#include "math.h"

#define WIN_MAX_X 640
#define WIN_MAX_Y 480
#define WIN_POS_X 0
#define WIN_POS_Y 0
#define POS_MAX_X 6400
#define POS_MAX_Y 480
#define CELL 32
#define STAGE_MAX_X 6400/32
#define STAGE_MAX_Y 480/32

char maze[STAGE_MAX_X + 1][STAGE_MAX_Y];

enum Menu
{
Menu_00_TITLE,
Menu_01_TITLE,
Menu_02_TITLE,
Menu_03_TITLE,
Menu_04_TITLE,
Menu_05_TITLE,
Menu_06_TITLE,
};

int Sce = Menu::Menu_00_TITLE;

int GameStartTime;

#include "Sub.h"
#include "Pic.h"
#include "Tit.h"
#include "Sta.h"
#include "Act.h"
#include "Hit.h"
#include "Func.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE); // ウィンドウモードに設定
	DxLib_Init();   // DXライブラリ初期化処理
	SetWindowInitPosition(WIN_POS_X, WIN_POS_Y);
	SetGraphMode(1540,750, 32);
	SetDrawScreen(DX_SCREEN_BACK);

	Col.Read();
	Fon.Read();
	Pic.Read();
	Sta.Read();
	Tit.Read();
	Act.NumberReset();
	SetFontSize(60);

	Pic.PLAYER = Pic.Mec;
	Pic.MarioOpp = Pic.MecOpp;
	Pic.MarioRev = Pic.MecRev;
	Pic.MarioRevOpp = Pic.MecRevOpp;
	Act.Flag.Mec = 1;
	Act.Flag.Sci = 0;
	Pic.Mario = Pic.PLAYER;


	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0 && ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//1フレームごとに行う作業を while文にまとめた
		switch (Sce) 
		{
		case Menu::Menu_00_TITLE:
			Tit.out();
			Act.NumberReset();
			break;

		case Menu::Menu_01_TITLE:
			Act.Out();
			Func.TimeKeep();
			Func.NewFunc();
			Hit.FlameOut();
			Hit.GoodGoal();
			break;

		case Menu::Menu_02_TITLE:
			Tit.GameOverEfect();
			break;

		case Menu::Menu_03_TITLE:
			Tit.GoalEfect();
			break;
		
		case Menu::Menu_04_TITLE:
			Tit.TimeOverEfect();
			break;

		case Menu::Menu_05_TITLE:
			Tit.EnemyKickEfect();
			break;
		}
		if (Sce != Menu::Menu_00_TITLE && Sce != Menu::Menu_01_TITLE) 
		{
			if (CheckHitKey(KEY_INPUT_NUMPADENTER) == 1) 
			{
				Sce = Menu_00_TITLE;
			}
		}
	}
	//WaitKey();      // キー入力待ち
	DxLib_End();    // DXライブラリ終了処理
	return 0;
}
