#define PLAYER1 Makuhin
#define PLAYER2 Test2

#include <algorithm>
#include <queue>

/*char Test1(Lab *L)
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
}*/

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

		if (recent.x < X - 1 && mask[recent.y * X + recent.x + 1] != '#')
		{
			myQ.push({ recent.x + 1, recent.y, recent.steps });
		} 

		if (recent.y > 1 && mask[(recent.y - 1)* X + recent.x] != '#')
		{
			myQ.push({ recent.x, recent.y - 1, recent.steps });
		}

		if (recent.y < Y - 1 && mask[(recent.y + 1)* X + recent.x] != '#')
		{
			myQ.push({ recent.x, recent.y + 1, recent.steps });
		}

		myQ.pop();
	}

	int minDist = 1000000;
	cell target;

	for (cell c : treasures)
	{
		if (c.steps < minDist)
			target = c;
	}

	myQ.push(target);

	while (!myQ.empty())
	{
		cell recent = myQ.front();

		int rX = recent.x;
		int rY = recent.y;

		if (mask[rY * X + rX + 1] < recent.steps)
		{
			if(rX + 1 == x_me && rY == y_me)
			{
				return 'U';
			}
			myQ.push({ rX + 1, rY, mask[rY * X + rX + 1] });
			myQ.pop();
			break;
		}
		if (mask[rY * X + rX - 1] < recent.steps)
		{
			if (rX - 1 == x_me && rY == y_me)
			{
				return 'D';
			}
			myQ.push({ rX - 1, rY, mask[rY * X + rX - 1] });
			myQ.pop();
			break;
		}
		if (mask[(rY - 1) * X + rX ] < recent.steps)
		{
			if (rX  == x_me && rY + 1 == y_me)
			{
				return 'L';
			}
			myQ.push({ rX, rY - 1, mask[(rY -1 )* X + rX ] });
			myQ.pop();
			break;
		}
		if (mask[(rY + 1) * X + rX] < recent.steps)
		{
			if (rX == x_me && rY + 1== y_me)
			{
				return 'R';
			}
			myQ.push({ rX, rY + 1, mask[(rY + 1)* X + rX] });
			myQ.pop();
			break;
		}
	}
	
	return ' ';
}