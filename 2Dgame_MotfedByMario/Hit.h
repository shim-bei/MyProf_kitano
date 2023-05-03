#pragma once
class {
public:

	int no = 0;
	
	void FlameOut() //画面外に出た時の動作
	{
		if (Act.Mar.Pos.y >= WIN_MAX_Y || Act.Mar.Pos.y <= 0)
		{
			//現在の時間を記憶してゲームオーバー画面に映る
			Tit.GameFinishTime = GetNowCount();
			Sce = Menu::Menu_02_TITLE;
		}
	}

	void GoodGoal() //ゴールした時の動作
	{
		//ゴールに当たったらゴール画面に移る
		for (int x = 0; x < STAGE_MAX_X; x++)
		{
			for (int y = 0; y < STAGE_MAX_Y; y++)
			{
				no = maze[x][y];
				if (no == 3 || no==4)
				{
					if (Act.CheckHit(Act.Mar.Pos.x, Act.Mar.Pos.x + CELL, 
						Act.Mar.Pos.y, Act.Mar.Pos.y + CELL, 
						x * CELL + 5, x * CELL + CELL - 5, y * CELL + 5, y * CELL + CELL))
					{
						Sce = Menu::Menu_03_TITLE;
					}
				}
			}
		}		
	}
private:
}Hit;
