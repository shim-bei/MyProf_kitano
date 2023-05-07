#pragma once

class Stage
{
public:

	struct
	{
		//計算用と描画用で配列を使い分ける
		int Type[STAGE_MAX_X+1][STAGE_MAX_Y];
		int Type_Exp[POS_MAX_X+1][POS_MAX_Y]; //計算用
	}Blo;

	void Read()
	{
		//ポインタ型で背景の配列情報を格納する変数を定義
		FILE* fp_stage_1_1;
		//FILE* fp_block_exp;

		//CP内のテキストファイルからステージ情報を文字で読み込む。
		fp_stage_1_1 = fopen("C:/マリオメイク/UTF-O.txt", "r");
		//同様の手順で描画を行う

		//読み込んだ文字を最初に定義した配列に格納する
		for (int y = 0; y < STAGE_MAX_Y; y++)
		{
			for (int x = 0; x < STAGE_MAX_X + 1; x++)
			{
				(void)fscanf(fp_stage_1_1, "%d", &Blo.Type[x][y]);
			}
		}
		//ファイルを閉じる
		fclose(fp_stage_1_1);

		//ポインタ型では不便なので普通の配列（maze）に格納しなおす
	for (int x = 0; x < STAGE_MAX_X + 1; x++)
		{	
			for (int y = 0; y < STAGE_MAX_Y; y++)
			{
				maze[x][y] = Blo.Type[x][y];
			}
		}	
}

	//読み込んだテキストファイルの文字によってマップを１つずつ描画
	void Out(int *PosX)
	{
		int pic = 0;
		for (int x = 0; x < STAGE_MAX_X+1 ; x++)
		{
			for (int y = 0; y < STAGE_MAX_Y ; y++)
			{
				switch (maze[x][y])
				{
				case 0: pic = Pic.Sky;
					break;
				case 1: pic = Pic.Blo1;
					break;
				case 2: pic = Pic.Blo2;
					break;
				case 3: pic = Pic.Flag;
					break;
				case 4: pic = Pic.FlagPoal;
					break;
				case 5: pic = Pic.Coin;
					break;
				case 6: pic = Pic.Blo1;
					break;
				case 7: pic = Pic.Blo1;
					break;


				}
				DrawGraph(CELL * x + *PosX, CELL * y, pic, TRUE);
			}
		}
	}

private:
};

Stage Sta;