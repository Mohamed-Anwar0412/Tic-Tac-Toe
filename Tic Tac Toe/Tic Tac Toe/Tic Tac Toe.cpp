#include<stdio.h>
#include <windows.h>
#include"CC212SGL.h"
#include<time.h>
#include<string.h>
#pragma comment(lib,"CC212SGL.lib")

bool winrow(int arr[3][3],int x)
{
	int count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			if (arr[i][j] == x)
				count++;
		if (count == 3)
			return true;
		else
			count = 0;
	}
	return false;
}
bool wincolumn(int arr[3][3], int x)
{
	int count = 0;
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
			if (arr[i][j] == x)
				count++;
		if (count == 3)
			return true;
		else
			count = 0;
	}
	return false;
}
bool windiag(int arr[3][3], int x)
{
	int count = 0;
	for (int i = 0; i < 3; i++)
			if (arr[i][i] == x)
				count++;
	if (count == 3)
		return true;
	else
		count = 0;
	for (int i = 0, j = 2; i < 3; i++, j--)
		if (arr[i][j] == x)
			count++;
	if (count == 3)
		return true;
	return false;
}
int Doeswin(int arr[][3])
{
	if (winrow(arr, 1) || wincolumn(arr, 1) || windiag(arr, 1))
	{
		return 1;
	}
	else if (winrow(arr, 2) || wincolumn(arr, 2) || windiag(arr, 2))
	{
		return 2;
	}
	return 0;
}
void restart(int arr[3][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			arr[i][j] = 0;
}
bool nowin(int arr[][3])
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (arr[i][j] == 0)
				return false;
	return true;
}

#define cupdate 350

int main()
{
	CC212SGL g;
	g.setup();
	g.setFullScreenMode();
	g.hideCursor();
	float xd = g.getWindowWidth() / 2, yd = g.getWindowHeight() / 2;
	float cx = 0, cy = 0;
	int time_start = 0;
	int dragon[3][4];
	int default_q = 0;
	int piece[2];
	piece[0] = g.loadImage("material\\X.png");
	piece[1] = g.loadImage("material\\Y.png");
	bool exist[9] = { 0 };
	int position[9][2] = { {-450, -450}, { -100,-450 }, { 250,-450 }, { -450,-100 }, { -100,-100 }, { 250,-100 }, { -450,250 }, { -100,250 }, { 250,250 } };
	int map[3][3] = { 0 };
	int dragonAnimationIndex = 0;
	int dragonAnimationDiretion = 1;
	int An = 0;
	bool pchange = true, pick = true, p1win = false, p2win = false, updatescore = false, done = false, first = false, done2 = true, finish = false, cpu = false, choice;
	int p = 0;
	int v = 0;
	char strwin[50];
	char score1[50] = "Player 1 : 0";
	char score2[50] = "Player 2 : 0";
	char scorecpu[50] = "CPU : 0";
	int p1 = 0, p2 = 0;
	int cr = 20;
	int xselectindex = 1;
	int yselectindex = 1;
	int xcpu, ycpu;
	while (!finish)
	{
		g.beginDraw();
		g.setDrawingThickness(10);
		g.setFontSizeAndBoldness(32, 100);
		g.setDrawingColor(WHITE);

		g.drawText(xd-100, 200, "1- Player vs CPU\n2- Player vs Player");
		g.moveCursor(xd - 50, 250);
		g.endDraw();
		if (kbhit())
		{
			if (GetAsyncKeyState('1'))
			{
				choice = true;
				finish = true;
			}
			if (GetAsyncKeyState('2'))
			{
				choice = false;
				finish = true;
			}
		}

	}
	while (1)
	{
		time_start = clock();


		//game rendering===============================================

		g.beginDraw();
		g.setDrawingThickness(10);
		g.setFontSizeAndBoldness(32, 100);
		g.setDrawingColor(WHITE);

		//Horizontal lines

		g.drawLine(xd - 600, yd - 200, xd + 600, yd - 200);
		g.drawLine(xd - 600, yd + 200, xd + 600, yd + 200);

		//vertical lines

		g.drawLine(xd - 200, yd - 600, xd - 200, yd + 600);
		g.drawLine(xd + 200, yd - 600, xd + 200, yd + 600);

		//score display

		g.drawText(50, 200, "SCORE");
		
		g.drawText(50, 250, score1);
			if (choice)
			{
				g.drawText(50, 300, scorecpu);
			}
			else
				g.drawText(50, 300, score2);
		
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (map[i][j] == 1)
					{
						g.drawImage(piece[0], xd + position[i * 3 + j][0], yd + position[i * 3 + j][1], RGB(255, 255, 255));
					}
					else if (map[i][j] == 2)
					{
						g.drawImage(piece[1], xd + position[i * 3 + j][0], yd + position[i * 3 + j][1], RGB(255, 255, 255));
					}
				}
			}
			if (Doeswin(map)==1)
			{
				if(updatescore&&!done)
				{
					score1[strlen(score1) - 1]++;
					updatescore = false;
					done = true;
				}
				g.setFontSizeAndBoldness(42, 300);
				g.setDrawingColor(RED);
				g.drawText(xd - 250, yd, "Player 1 win!! continue?? (Y/N)");
			}
			else if(Doeswin(map) == 2)
			{
				if (updatescore&&!done)
				{
					if (choice)
						scorecpu[strlen(scorecpu) - 1]++;
					else
						score2[strlen(score2) - 1]++;
					updatescore = false;
					done = true;
				}
				g.setFontSizeAndBoldness(42, 300);
				g.setDrawingColor(RED);
				if (choice)
					g.drawText(xd - 220, yd, "CPU win!! continue?? (Y/N)");
				else
					g.drawText(xd - 250, yd, "Player 2 win!! continue?? (Y/N)");
			}
			if (nowin(map)&&!Doeswin(map))
			{
				g.setFontSizeAndBoldness(42, 300);
				g.setDrawingColor(RED);
				g.drawText(xd - 200, yd, "TIE!! continue?? (Y/N)");
			}
			else
				done2 == true;

			//selecting tool
			g.setDrawingColor(WHITE);
			g.drawSolidCircle(xd - cr/2 + cx, yd - cr/2 + cy, cr);
	
		g.endDraw();

		//end game rendering======================================================

		//game logic==========================================================

		if (pchange&&pick)
		{
			v = 1;
			pchange = false;
			pick = false;
			cy = 0;
			cx = 0;
			yselectindex = 1;
			xselectindex = 1;
		}
		else if(pick)
		{
			v = 2;
			pchange = true;
			pick = false;
			cy = 0;
			cx = 0;
			yselectindex = 1;
			xselectindex = 1;
		}
			if (kbhit())	//Non-Blocking
			{
				if (!cpu&&!Doeswin(map))
				{
					if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP))
					{
						if (cy > -cupdate)
						{
							cy -= cupdate;
							yselectindex -= 1;
						}
					}
					else if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))
					{
						if (cy < cupdate)
						{
							cy += cupdate;
							yselectindex += 1;
						}
					}
					else if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT))
					{
						if (cx < cupdate)
						{
							cx += cupdate;
							xselectindex += 1;
						}
					}
					else if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT))
					{
						if (cx > -cupdate)
						{
							cx -= cupdate;
							xselectindex -= 1;
						}
					}
					else if (GetAsyncKeyState(VK_RETURN) || GetAsyncKeyState(VK_SPACE))
					{
						if (map[yselectindex][xselectindex] == 0)
						{
							map[yselectindex][xselectindex] = v;
							pick = true;
							if (choice)
								cpu = true;
						}
					}
				}
				else if (cpu && !Doeswin(map))
				{
					xcpu = rand() % 3;
					ycpu = rand() % 3;
					if (map[xcpu][ycpu] == 0)
					{
						map[xcpu][ycpu] = v;
						pick = true;
						cpu = false;
					}
					else
					{
						xcpu = rand() % 3;
						ycpu = rand() % 3;
					}
				}
				if (GetAsyncKeyState('R'))
				{
					restart(map);
					score1[strlen(score1) - 1] = '0';
					score2[strlen(score2) - 1] = '0';
					scorecpu[strlen(scorecpu) - 1] = '0';
				}

			}
			if (Doeswin(map))
			{
				if (!done)
					updatescore = true;
				else
					updatescore = false;
				if (kbhit())
				{
					if (GetAsyncKeyState('Y') || GetAsyncKeyState('y'))
					{
						restart(map);
						done = false;
					}
					else if (GetAsyncKeyState('N') || GetAsyncKeyState('n'))
						break;
				}
			}
			if (nowin(map) && !Doeswin(map))
			{
				if (kbhit())
				{
					if (GetAsyncKeyState('Y') || GetAsyncKeyState('y'))
						restart(map);
					else if (GetAsyncKeyState('N') || GetAsyncKeyState('n'))
						break;
				}
			}
		
		//timing===============

		while ((clock() / (float)CLOCKS_PER_SEC * 1000.0f) - (time_start / (float)CLOCKS_PER_SEC * 1000.0f) < 80);	//ms
	}
	
	return 0;
}