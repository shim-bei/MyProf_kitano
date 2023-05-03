#pragma once

class FUNCTION
{
public: 

	struct 
	{
		byte Turbo;

	}Flag;

	int FontHandle;
	int sec = 0;

	//制限時間の管理を行う
	void TimeKeep() {
		FontHandle = CreateFontToHandle(NULL, 30, 6);

		//制限時間を５０からカウントダウンしていく
		sec =50 - (GetNowCount() - GameStartTime) / 1000;
		DrawFormatString(10, 10, Col.Whi, "%d", sec);

		//50秒経ったらゲームオーバー画面に移る
		if (sec < 0) 
		{
			Sce = Menu::Menu_04_TITLE;
		}
	}

	//移動速度を変化させる　メカコスチュームの状態で「arduino」と打つと速度上昇
	void Turbo_Mec() 
	{
		if (CheckHitKey(KEY_INPUT_A) != 0)
		{
			Flag.Turbo = 1;
		}
		else if (CheckHitKey(KEY_INPUT_R) != 0 && Flag.Turbo == 1)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_D) != 0 && Flag.Turbo == 2)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_U) != 0 && Flag.Turbo == 3)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_I) != 0 && Flag.Turbo == 4)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_N) != 0 && Flag.Turbo == 5)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_O) != 0 && Flag.Turbo == 6)
		{
			Flag.Turbo = 0;
			Act.MoveX += 1;
		}
	}

	//移動速度を変化させる　科学コスチュームの状態で「H　E　L　B　O　C　N　F　N」（水平リーベ―僕の船）と打つと速度上昇
	void Turbo_Sci()
	{
		if (CheckHitKey(KEY_INPUT_H) != 0)
		{
			Flag.Turbo = 1;
		}
		else if (CheckHitKey(KEY_INPUT_E) != 0 && Flag.Turbo == 1)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_L) != 0 && Flag.Turbo == 2)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_B) != 0 && Flag.Turbo == 3)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_O) != 0 && Flag.Turbo == 4)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_C) != 0 && Flag.Turbo == 5)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_N) != 0 && Flag.Turbo == 6)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_F) != 0 && Flag.Turbo == 7)
		{
			Flag.Turbo++;
		}
		else if (CheckHitKey(KEY_INPUT_N) != 0 && Flag.Turbo == 8)
		{
			Flag.Turbo = 0;
			Act.MoveX += 2;
		}
	}


	void NewFunc()
	{
		Cal();
		Cha();
	}

private:

	void Cal();
	void Cha();
};


FUNCTION Func;

void FUNCTION::Cal() 
{
	//所定の順序で押されたら速度を変更
	if (Pic.PLAYER == Pic.Mec)
	{
		Turbo_Mec();
	}
	else if (Pic.PLAYER == Pic.Sci) 
	{
		Turbo_Sci();
	}
}

void FUNCTION::Cha()
{
}
