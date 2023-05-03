//ヘッダーファイルの読み込み
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

//定数を定義
#define F_WIDE (80)
#define F_HIGHT (21)
#define LIMIT (50)
#define FPS (3)
#define INTER (1000/FPS)
#define INTER2 (100/FPS)
#define Grav (3)

//定数を名前で定義…列挙定数
enum
{
	CHARACTER_PLAYER,
	CHARACTER_KURIBO,
	CHARACTER_KURIBO2,
	CHARACTER_MAX
};

//マリオ、クリボーの座標をまとめて定義
typedef struct
{
	int x, y;
}VEC2;

//マリオ、クリボーの現在、過去、初期座標を定義
typedef struct
{
	const VEC2 defaultPosition;
	VEC2 position;
	VEC2 lastPosition;
}CHARACTER;

//背景を格納する変数を定義
char maze[F_HIGHT][F_WIDE + 1];

//背景を文字で定義
char defaultMaze[F_HIGHT][F_WIDE + 1] =
{
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$oo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",

"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$oooo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ooo$$$$$$$$$$$$$$$oooo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$oo$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ooo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ooo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",

"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$oooo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$oooo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$f$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ooooo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ff$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o$$$$$$$$$$$$$$$$$$$$$$$$$$#$$$$$$$$fff$$$",

"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o$$$$$$$$$$$$$$$$$$$$$$$$$##$$$$$$$$$ff$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o$$$$$$$$$$$$$$$$$$$$$$$$###$$$$$$$$$$f$$$",
"$$$$$$$c$c$$$$$$$$$$$$$$$$$$$$$$$$$$$$o$$$$$$$$$$$$$$$$$$$$$$$####$$$$$$$$$$f$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$#####$$$$$$$$$$f$$$",
"$$$$$$bbbbb$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$######$$$$$$$$$$f$$$",

"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$#######$$$$$$$$$$f$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$########$$$$$$$$$$f$$$",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$#####$$$$$$$$$$$$$$$$$$$$$$$#########$$$$$$$$$$f$$$",
"#####################$$###############$#########################################",
"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
};

//マリオ、クリボーの初期座標のみをあらかじめ代入
CHARACTER characters[CHARACTER_MAX] =
{
	{
		{3,18},
		{},
		{},

	},
	{
		{15,18},
		{},
		{},
	},
		{
		{40,18},
		{},
		{},
	},

};


//背景の初期データをコピー（mazeを直接変更すると元に戻らなくなるため）
char screen[F_HIGHT][F_WIDE + 1];


//一番最初に行うプログラムを設定
void Init()
{
	//配列mazeに背景の初期配列DefaultMazeをコピーした後、
	memcpy(maze, defaultMaze, sizeof(maze));

	//マリオ、クリボーの現在、過去座標に初期座標を代入
	for (int i = 0; i < CHARACTER_MAX; i++)
	{
		characters[i].position = characters[i].lastPosition = characters[i].defaultPosition;
	}
}

//マップとキャラクターを描画する
void D_MAP()
{
	//文字を数字に変換
	memcpy(screen, maze, sizeof maze);
	for (int i = 0; i < CHARACTER_MAX; i++)
	{
		screen[characters[i].position.y][characters[i].position.x] = i;
	}
	system("cls");  //画面をクリア

	for (int y = 0; y < F_HIGHT; y++)
	{
		for (int x = 0; x < F_WIDE; x++)
		{
			//マップの文字の種類に応じて描画するアスキーアートを描画する
			switch (screen[y][x]) {
			case CHARACTER_PLAYER:printf("a"); break;
			case CHARACTER_KURIBO:printf("b"); break;
			case CHARACTER_KURIBO2:printf("b"); break;
			case 'c':printf("h"); break;
			case 'o':printf(" "); break;
			case '$':printf(" "); break;
			case '#':printf("f"); break;
			case 'f':printf("g"); break;
			case 'b':printf("h"); break;
			}
		}printf("\n");
	}
}


//座標の当たり判定を行う
bool Equal(VEC2 _v0, VEC2 _v1)
{
	return
		(_v0.x == _v1.x) && (_v0.y == _v1.y);
}

bool EqualKick(VEC2 _v0, VEC2 _v1)
{
	return
		(_v0.x == _v1.x || _v0.x + 1 == _v1.x || _v0.x - 1 == _v1.x) && (_v0.y + 1 == _v1.y);
}

bool FlagKick;
int STRAGE;
int Count = 0;

//マリオがクリボーを踏んだかチェックする関数
void KickCheck()
{
	for (int i = CHARACTER_PLAYER + 1; i < CHARACTER_MAX; i++)
	{
		if (EqualKick(characters[CHARACTER_PLAYER].position, characters[i].position) == 1)
		{
			FlagKick = 1;
			STRAGE = i;
			break;
		}
	}
}

//マリオがクリボーにあたったかチェック
void E_CHECK()
{
	for (int i = CHARACTER_PLAYER + 1; i < CHARACTER_MAX; i++)
	{
		if (Equal(characters[CHARACTER_PLAYER].position, characters[i].position) == 1)
		{
			printf("%d\n", FlagKick);
			if (FlagKick == 0)
			{
				system("cls");
				printf("You Dead");
				exit(0);
			}
			else
			{
				characters[STRAGE + 1].position.x = -1;
				STRAGE = 0;
				if (Count > 2)
				{
					FlagKick = 0;
					Count = 0;
				}
				break;
			}
		}
	}
}

//マリオ、クリボーの下のマップが床か否かチェック
void F_CHECK()
{
	for (int i = 0; i < CHARACTER_MAX; i++)
	{
		if (maze[characters[i].position.y + 1][characters[i].position.x] == '$' ||
			maze[characters[i].position.y + 1][characters[i].position.x] == 'o')
		{
			characters[i].position.y++;
		}
	}
}

//マリオがゴールフラッグにあたったかチェック
void G_CHECK()
{s
	if (maze[characters[CHARACTER_PLAYER].position.y][characters[CHARACTER_PLAYER].position.x] == 'f')
	{
		system("cls");
		printf("You Got Goal!!!!!!");
		exit(0);
	}
}

//マリオが画面外に出たかチェック
void OUT_CHECK()
{
	if (0 > characters[CHARACTER_PLAYER].position.y ||
		F_HIGHT - 2 < characters[CHARACTER_PLAYER].position.y ||
		0 > characters[CHARACTER_PLAYER].position.x ||
		F_WIDE + 1 < characters[CHARACTER_PLAYER].position.x)
	{
		system("cls");
		printf("You Dead!");
		exit(0);
	}
}

//main関数
int main()
{
	Init();
	D_MAP();

	//時間を取得する変数を定義
	time_t lastClock = clock();
	int Keyget;

	Keyget = _getch();
	if (Keyget == 's') {

		//”E"が押される、マリオが死ぬもしくはゴールするまで繰り返す
		while (1)
		{
			time_t newClock = clock();

			//一定時間が経過したら
			if (newClock > lastClock + INTER)
			{
				lastClock = newClock;

				//クリボーを移動させる
				for (int i = CHARACTER_PLAYER + 1; i < CHARACTER_MAX; i++)
				{
					VEC2 newPosition = characters[i].position;
					switch (i)
					{
					case CHARACTER_KURIBO:if (newPosition.x >= 0) { newPosition.x--; }; break;
					case CHARACTER_KURIBO2:if (newPosition.x >= 0) { newPosition.x--; }; break;
					}
					characters[i].lastPosition = characters[i].position;
					characters[i].position = newPosition;
				}

				//各関数の実行
				F_CHECK();
				G_CHECK();
				OUT_CHECK();
				D_MAP();
			}

			//キーボードが押された時の処理
			if (_kbhit())
			{
				//必要な変数を定義
				int i = 0;
				VEC2 lastPosition;
				VEC2 lastPosition2;
				VEC2 newPosition = lastPosition = lastPosition2 = characters[CHARACTER_PLAYER].position;

				lastPosition2.y -= 3;

				//押されたキーによってマリオの座標を変化させる
				switch (_getch())
				{
				case 'd':newPosition.x++; break;

				case 'a':newPosition.x--; break;

				case 'w':if (maze[newPosition.y + 1][newPosition.x] != '$' &&
					maze[newPosition.y + 1][newPosition.x] != 'o')
				{
					while (newPosition.y == lastPosition.y && i < 5)
					{
						newPosition.y--;
						i++;
						if (maze[newPosition.y - 1][newPosition.x] == '$')
						{
							if (maze[newPosition.y][newPosition.x] == 'b')
							{
								maze[newPosition.y][newPosition.x] = '$';
								newPosition.y++;
								break;
							}

						}lastPosition.y--;
					}
				}	break;
				case 's':newPosition.y++; break;

					//バグ防止のため、”E”が押されたら強制終了
				case 'e':exit(0); break;
				}

				//マリオの移動先が壁でもブロックでも無ければ移動、そうでなければ移動しない
				if (maze[newPosition.y][newPosition.x] != '#' &&
					maze[newPosition.y][newPosition.x] != 'b')
				{
					characters[CHARACTER_PLAYER].position = newPosition;
				}
				else
				{
					newPosition = lastPosition;
				}
				D_MAP();


			};
			E_CHECK();
			KickCheck();
		}
	}
}