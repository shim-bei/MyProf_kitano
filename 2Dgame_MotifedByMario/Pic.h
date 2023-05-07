#pragma once

class {
public:
	//画像を格納する定数を定義
	int Blo1;
	int Blo2;
	int Sky;
	int Kuri;
	int Kuri1;
	int FlagPoal;
	int Flag;
	int Coin;

	int Mario;
	int MarioOpp;
	int MarioRev;
	int MarioRevOpp;
	int Mec;
	int MecOpp;
	int MecRev;
	int MecRevOpp;
	int Sci;
	int SciOpp;
	int SciRev;
	int SciRevOpp;

	int Title;
	int Hit;
	int Kicked;
	int Retire;
	int Goal;
	int test1;
	int test2;
	int test3;
	int PLAYER;
	

	void Read()
	{
		//定義した定数にCP内から画像を読み込み、格納する
		 Blo1 = LoadGraph("C:/マリオメイク/block1.png");
		 Blo2 = LoadGraph("C:/マリオメイク/block2.png");
		 Sky = LoadGraph("C:/マリオメイク/sky-32.png");
		 FlagPoal= LoadGraph("C:/マリオメイク/frag-stick.png");
		 Flag = LoadGraph("C:/マリオメイク/frag-stick.png");
		 Coin= LoadGraph("C:/マリオメイク/coin.png");
		 Kuri = LoadGraph("C:/マリオメイク/enemy.png");

		 Kuri1 = LoadGraph("C:/マリオメイク/enemy.png");
		 Mario = LoadGraph("C:/マリオメイク/mario-32.png");
		 MarioOpp = LoadGraph("C:/マリオメイク/マリオ逆足.png");
		 MarioRev = LoadGraph("C:/マリオメイク/マリオ逆進.png");
		 MarioRevOpp = LoadGraph("C:/マリオメイク/mario-32Reverse.png");
		 Mec = LoadGraph("C:/マリオメイク/メカトロ野郎.png");
		 MecOpp = LoadGraph("C:/マリオメイク/メカトロ野郎逆足.png");
		 MecRev = LoadGraph("C:/マリオメイク/メカトロ野郎逆進.png");
		 MecRevOpp = LoadGraph("C:/マリオメイク/メカトロ野郎reverse.png");
		 Sci = LoadGraph("C:/マリオメイク/化学系君順進.png");
		 SciOpp = LoadGraph("C:/マリオメイク/化学系君逆足.png");
		 SciRev = LoadGraph("C:/マリオメイク/化学系君逆進.png");
		 SciRevOpp = LoadGraph("C:/マリオメイク/化学系君逆進逆足.png");

		 Title = LoadGraph("C:/マリオメイク/title-new.png");
		 Goal = LoadGraph("C:/マリオメイク/title-new.png");
		 Hit = LoadGraph("C:/マリオメイク/エネミーヒット.png");
		 Kicked = LoadGraph("C:/マリオメイク/エネミーキック.png");
		 Retire = LoadGraph("C:/マリオメイク/あなたは留年しました.png");

		 test1 = LoadGraph("C:/マリオメイク/test1.png");
		 test2 = LoadGraph("C:/マリオメイク/test2.png");
		 test3 = LoadGraph("C:/マリオメイク/test3.png");

		 PLAYER = Mario;
	}
private:
}Pic;
