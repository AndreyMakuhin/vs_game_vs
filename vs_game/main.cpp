#include <stdlib.h>
#include <iostream>
#include <string>


class Player
{
public:
	int x, y;
	int score;
	bool trapped;
	std::string name;
	Player()
	{
		x = 0, y = 0, score = 0; trapped = false;
		name = "";
	}
};

class Lab
{
protected:
	const int X = 10, Y = 20;

	//# - wall, v - trap, * - chest of gold
	
	char lab[10 + 1][20 + 1] =
	{
	"####################",
	"#                  #",
	"#      vvvvv       #",
	"#      v   v       #",
	"#      v * v       #",
	"#      v * v       #",
	"#      v   v       #",
	"#      vvvvv       #",
	"#                  #",
	"####################"
	};
	/*
	char lab[10 + 1][20 + 1] = 
	{
	"####################",
	"#                  #",
	"#     #vvvvv#      #",
	"#     #v   v#      #",
	"#     #v * v#      #",
	"#     #v * v#      #",
	"#     #v   v#      #",
	"#     #vvvvv#      #",
	"#                  #",
	"####################"
	};
	*/
	Player p[2];
	int cur_p = 0;
	int move_num = 0;
	Lab()
	{
		p[0].x = 8; p[0].y = 1;
		p[1].x = 8; p[1].y = 18;
	}
	int Next(int i)
	{
		return (i + 1) % 2;
	}
public:
	void SetName(std::string name)//set name of bot
	{
		p[cur_p].name = name;
	}
	int GetSizeX()//vertical size of lab
	{
		return X;
	}
	int GetSizeY()//horizontal size of lab
	{
		return Y;
	}
	char GetLab(int x, int y)//return element of lab at x,y
	{
		return lab[x][y];
	}
	void GetMe(int &x, int &y)//return (in parameters) x,y of my bot
	{
		x = p[cur_p].x;
		y = p[cur_p].y;
	}
	void GetEnemy(int &x, int &y)//return x,y of enemy bot
	{
		x = p[Next(cur_p)].x;
		y = p[Next(cur_p)].y;
	}
};

#include "players.h"
//#include "players_me.h"

class Battle : public Lab
{
	void PlaceChest()
	{
	metka:;
		int x = rand() % X;
		int y = rand() % Y;
		if (lab[x][y] == ' ' && !(x == p[0].x && y == p[0].y) && !(x == p[1].x && y == p[1].y))
			lab[x][y] = '*';
		else
			goto metka;
	}
	void PlaceTrap()
	{
	metka:;
		int x = rand() % X;
		int y = rand() % Y;
		if (lab[x][y] == ' ' && !(x == p[0].x && y == p[0].y) && !(x == p[1].x && y == p[1].y))
			lab[x][y] = 'v';
		else
			goto metka;
	}
public:
	int GetScore(int i)
	{
		return p[i].score;
	}
	std::string GetName(int i)
	{
		return p[i].name;
	}

	void SetNames()
	{
		cur_p = 0; PLAYER1(this);
		cur_p = 1; PLAYER2(this);
		cur_p = 0;
	}
	char Move()
	{
		move_num++;
		if (cur_p == 0)
			return PLAYER1(this);
		else
			return PLAYER2(this);
	}
	int Step()
	{
		if (p[cur_p].trapped == true)
		{
			p[cur_p].trapped = false;
			cur_p = Next(cur_p);
			return 0;
		}
		
		char m=Move();

		int dx = 0, dy = 0;
		if (m == 'U')dx = -1;
		if (m == 'D')dx = 1;
		if (m == 'L')dy = -1;
		if (m == 'R')dy = 1;

		if(lab[p[cur_p].x +dx][p[cur_p].y+dy] == '#'||((p[cur_p].x + dx == p[Next(cur_p)].x)&&(p[cur_p].y + dy==p[Next(cur_p)].y)))
		{
			cur_p = Next(cur_p);
			return 0;
		}
		p[cur_p].x += dx;
		p[cur_p].y += dy;

		if (lab[p[cur_p].x][p[cur_p].y] == 'v')
		{
			lab[p[cur_p].x][p[cur_p].y] = ' ';
			p[cur_p].trapped = true;
			PlaceTrap();
		}
		if (lab[p[cur_p].x][p[cur_p].y] == '*')
		{
			lab[p[cur_p].x][p[cur_p].y] = ' ';
			p[cur_p].score++;
			PlaceChest();
		}
		cur_p = Next(cur_p);
		return 0;
	}
	void PrintLab()
	{
		for(int x=0;x<GetSizeX();x++)
		{
			for (int y = 0; y < GetSizeY(); y++)
			{
				if(x==p[0].x&&y==p[0].y)
					std::cout << "1";
				else
					if(x == p[1].x && y == p[1].y)
						std::cout << "2";
						else
							std::cout << GetLab(x, y);
			}
			std::cout << std::endl;
		}
		std::cout << "Player[" << p[0].name << "] score is: " << p[0].score << std::endl;
		std::cout << "Player[" << p[1].name << "] score is: " << p[1].score << std::endl;
		std::cout << "Move: " << move_num << std::endl;
	}
};


int main()
{
	Battle LTTB;

	LTTB.SetNames();
	
	//for debug purpose
	/*
	LTTB.PrintLab();
	while (getchar() != ' ')
	{
		LTTB.Step();
		LTTB.PrintLab();
	}
	*/
	
	//judge
	
	for (int i = 0; i < 2000; i++)
		LTTB.Step();

	std::cout << "Player[" << LTTB.GetName(0) << "] score is: " << LTTB.GetScore(0) << std::endl;
	std::cout << "Player[" << LTTB.GetName(1) << "] score is: " << LTTB.GetScore(1) << std::endl;

	if (LTTB.GetScore(0)*.9 > LTTB.GetScore(1))
		std::cout << "Win player: " << LTTB.GetName(0);
	else
	if (LTTB.GetScore(1)*.9 > LTTB.GetScore(0))
		std::cout << "Win player: " << LTTB.GetName(1);
	else
		std::cout << "Draw!";
	
	std::cin.get();

	return 0;
}