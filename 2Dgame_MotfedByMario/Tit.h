#pragma once

class TITLE
{
public:
	int FontHandle;
	int FontHandle2;

	int GameFinishTime;
	int sec ;
	int POKA;

	void Read() 
	{
		FontHandle = CreateFontToHandle(NULL, 80, 6);
	}

	//死んだときに少しDelayを設ける
	void Sleeper() 
	{
		while (sec < 2) 
		{
			POKA = 0;
			sec = (GetNowCount() - GameFinishTime) / 1000;
		}
	}

	void out() 
	{
		//描画する文字のフォント情報を入力
		FontHandle = CreateFontToHandle(NULL, 80, 6);
		FontHandle2 = CreateFontToHandle(NULL, 80, 10);

		//タイトル画面を描画、”Press　Enter Key！”を描画
		DrawGraph(0, 0, Pic.Title, TRUE);
		
		//Enterキーが押されたら画面出力を変更
		if(CheckHitKey(KEY_INPUT_NUMPADENTER)==1)
		{
			Sce = Menu::Menu_01_TITLE;
			GameStartTime = GetNowCount();
		}
	}

	//ゲームオーバーになったときの画面を設定、描画
	void GameOverEfect() 
	{
		DrawGraph(0, 0, Pic.Hit, TRUE);
	//	DrawGraph(270, 0, Pic.Title, TRUE);a
		sec = 50 - (GetNowCount() - GameFinishTime) / 1000;
		if (sec < 48) 
		{
			if (POKA == 0) 
			{
				PlaySoundA("C:/マリオメイク/poka.wav", SND_ASYNC);
				POKA = 1;
			}
			DrawGraph(0, 0,Pic.Retire, TRUE);
		}
	}

	//敵を踏んだ時の処理
	void EnemyKickEfect() 
	{
		DrawGraph(0, 0, Pic.Kicked, TRUE);
	//	DrawGraph(0, 0, Pic.Title, TRUE);
		sec = 50 - (GetNowCount() - GameFinishTime) / 1000;
		if (sec < 48) 
		{
			if (POKA == 0) 
			{
				PlaySoundA("C:/マリオメイク/poka.wav", SND_ASYNC);
				POKA = 1;
			}
			DrawGraph(0, 0, Pic.Retire, TRUE);
		}
	}
	//タイムオーバー時の処理
	void TimeOverEfect() 
	{
		Sleeper();

		DrawGraph(0, 0, Pic.Hit, TRUE);
		if (POKA == 0) 
		{
			//音を鳴らす処理
			POKA = 1;
			PlaySoundA("C:/マリオメイク/poka.wav", SND_ASYNC);
		}
		DrawFormatString(130, 300, Col.Bla, "You Overed!!");
	}

	//ゴールした時の画面の設定、描画
	void GoalEfect()
	{
		Sleeper();

		DrawGraph(0, 0, Pic.Goal, TRUE);
		DrawFormatString(30, 300, Col.Bla, "Yooouuu GOAAAAAAAALED!!");
	}
private:
};

TITLE Tit;