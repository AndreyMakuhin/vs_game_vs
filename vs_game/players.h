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
	int** mask = new int*[X];
	for (int i = 0; i < X; i++)
	{
		mask[i] = new int[Y];
		for (int j = 0; j < Y; j++)
		{
			mask[i][j] = -1;
		}
	}
	cell treasures[10];
	int trCount = 0;

	int x_me, y_me;
	L->GetMe(x_me, y_me);

	myQ.push({ x_me, y_me, 0 });

	while (!myQ.empty())
	{
		cell recent = myQ.front();
		mask[recent.x][recent.y] = recent.steps;
		recent.steps++;
		if (L->GetLab(recent.x, recent.y) == '*')
		{
			treasures[trCount] = recent;
			trCount++;
		}

		if (recent.x > 1 && L->GetLab(recent.x -1 , recent.y) != '#')//(recent.x > 1 && mask[recent.y * X + recent.x - 1] != '#')
		{
			if(mask[recent.x - 1][recent.y] < 0)
				myQ.push({ recent.x - 1, recent.y, recent.steps });
		}

		if (recent.x < X - 1 && L->GetLab(recent.x + 1, recent.y) != '#')
		{
			if (mask[recent.x + 1][recent.y] < 0)
				myQ.push({ recent.x + 1, recent.y, recent.steps });
		}

		if (recent.y > 1 && L->GetLab(recent.x, recent.y - 1 ) != '#')
		{
			if (mask[recent.x][recent.y - 1 ] < 0)
				myQ.push({ recent.x, recent.y - 1, recent.steps });
		}

		if (recent.y < Y - 1 && L->GetLab(recent.x, recent.y + 1) != '#')
		{
			if (mask[recent.x][recent.y + 1] < 0)
				myQ.push({ recent.x, recent.y + 1, recent.steps });
		}

		myQ.pop();

		for (int i = 0; i < X; i++)
		{			
			for (int j = 0; j < Y; j++)
			{
				std::cout << mask[i][j];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	int minDist = 1000000;
	cell target;

	for (cell c : treasures)
	{
		if (c.steps < minDist && c.steps > 0)
			target = c;
	}

	myQ.push(target);

	while (!myQ.empty())
	{
		cell recent = myQ.front();

		int rX = recent.x;
		int rY = recent.y;

		if (mask[rX + 1][rY] < recent.steps)
		{
			if (rX + 1 == x_me && rY == y_me)
			{
				return 'U';
			}
			myQ.push({ rX + 1, rY, mask[rX + 1][rY] - 1 });
			myQ.pop();
			break;
		}
		if (mask[rX - 1][rY] < recent.steps)
		{
			if (rX - 1 == x_me && rY == y_me)
			{
				return 'D';
			}
			myQ.push({ rX - 1, rY, mask[rX - 1][rY] - 1});
			myQ.pop();
			break;
		}
		if (mask[rX][rY - 1] < recent.steps)
		{
			if (rX == x_me && rY + 1 == y_me)
			{
				return 'L';
			}
			myQ.push({ rX, rY - 1, mask[rX][rY - 1] - 1 });
			myQ.pop();
			break;
		}
		if (mask[rX][rY + 1] < recent.steps)
		{
			if (rX == x_me && rY + 1 == y_me)
			{
				return 'R';
			}
			myQ.push({ rX, rY + 1, mask[rX][rY + 1] - 1});
			myQ.pop();
			break;
		}
	}

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

