#pragma once

class
{
public:
	//色の種類を定義
	int Whi;
	int Bla;
	int Gre;
	int Blu;
	int Red;
	
	//色の名前とRGBカラーを一致させる
	void Read()
	{
		Whi = GetColor(254, 254, 254);
		Bla = GetColor(0, 0, 0);
		Gre = GetColor(0, 255, 0);
		Blu = GetColor(0, 0, 255);
		Red = GetColor(255, 0, 0);
	}
private:
}Col;


class 
{
public:

	int FONT[50 + 1];

	void Read()
	{
		for (int I = 0; I < 51; I++)
		{
			FONT[I] = CreateFontToHandle("ＭＳ ゴシック",I,6,DX_FONTTYPE_NORMAL);
		}
	}

private:
}Fon;
