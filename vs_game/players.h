#define PLAYER1 Makuhin
#define PLAYER2 Test2

#include <algorithm>
#include <queue>


char Test1(Lab *L)
{
	L->SetName(__FUNCTION__);
	
	int X = L->GetSizeX(); int Y = L->GetSizeY();

	int xp, yp;
	L->GetMe(xp, yp);

	int xb = 1000, yb = 1000, max_d = 1000;
	for (int x = 0; x < X; x++)
		for (int y = 0; y < Y; y++)
			if (L->GetLab(x, y) == '*')
			{
				if (max_d > abs(xp - x) + abs(yp - y))
				{
					xb = x; yb = y; max_d = abs(xp - x) + abs(yp - y);
				}
			}
	if (xb < xp && L->GetLab(xp-1,yp)!='#')
		return 'U';
	if (xb > xp && L->GetLab(xp + 1, yp) != '#')
		return 'D';
	if (yb < yp && L->GetLab(xp , yp-1) != '#')
		return 'L';
	if (yb > yp && L->GetLab(xp , yp+1) != '#')
		return 'R';

	return ' ';
}

char Test2(Lab *L)
{
	L->SetName(__FUNCTION__);

	int X = L->GetSizeX(); int Y = L->GetSizeY();

	int xp, yp;
	L->GetMe(xp, yp);

	int xb = 1000, yb = 1000, max_d = 1000;
	
	for (int x = 0; x < X; x++)
		for (int y = 0; y < Y; y++)
			if (L->GetLab(x, y) == '*')
			{
				if (max_d > abs(xp - x) + abs(yp - y))
				{
					xb = x; yb = y; max_d = abs(xp - x) + abs(yp - y);
				}
			}
	if (yb < yp)
		return 'L';
	if (yb > yp)
		return 'R';
	if (xb < xp)
		return 'U';
	if (xb > xp)
		return 'D';
	
	return ' ';
}

char Makuhin(Lab *L)
{


	L->SetName(__FUNCTION__);

	struct cell {
		int x;
		int y;
		int steps;
	};

	std::queue<cell> myQ;

	int X = L->GetSizeX(); int Y = L->GetSizeY();
	int* mask = new int[X*Y];
	cell treasures[10];
	int trCount = 0;

	int x_me, y_me;
	L->GetMe(x_me, y_me);

	myQ.push({x_me, y_me});

	while (!myQ.empty())
	{		
		cell recent = myQ.front();
		mask[recent.y * X + recent.x] = recent.steps++;
		if (L->GetLab(recent.x, recent.y) == '*')
		{
			treasures[trCount++] = recent ;
		}

		if (recent.x > 1 && mask[recent.y * X + recent.x - 1] != '#')
		{
			myQ.push({recent.x - 1, recent.y, recent.steps});
		}


	}

	int dist_x = 1000, dist_y = 1000, delta_x = 0, delta_y = 0, min_dist = 1000;
	cell target = { -1, -1 };
	for (int x = 0; x < X; x++)
	{
		for (int y = 0; y < Y; y++)
		{
			if (L->GetLab(x, y) == '*')
			{
				dist_x = std::min(abs(x - x_me), dist_x);
				dist_y = std::min(abs(y - y_me), dist_y);
				if (dist_x + dist_y < min_dist)
				{
					min_dist = dist_x + dist_y;
					target = { x,y };
				}
			}
		}
	}

	int direct_x = target.x - x_me;
	int direct_y = target.y - y_me;

	if (abs(direct_x) > abs(direct_y))
	{
		if (direct_x > 0)
		{
			return 'D';
		}
		else if (direct_x < 0)
		{
			return 'U';
		}
	}
	else
	{
		if (direct_y > 0)
		{
			return 'R';
		}
		else if (direct_y < 0)
		{
			return 'L';
		}
	}
	return ' ';
}