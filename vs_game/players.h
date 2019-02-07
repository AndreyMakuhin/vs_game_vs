#define PLAYER1 Makuhin
#define PLAYER2 Test2

#include <algorithm>
#include <queue>
#include <vector>

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
			mask[i][j] = 999999;
		}
	}
	std::vector<cell> treasures;	

	int x_me, y_me;
	L->GetMe(x_me, y_me);

	myQ.push({ x_me, y_me, 0 });
	mask[x_me][y_me] = 0;

	while (!myQ.empty())
	{
		cell recent = myQ.front();		
		int deltaSteps = 1;
		if (L->GetLab(recent.x, recent.y) == '*')
		{
			treasures.push_back(recent);			
		}

		if (recent.x > 1 && L->GetLab(recent.x - 1 , recent.y) != '#')
		{
			if (L->GetLab(recent.x - 1, recent.y) == 'v')
				deltaSteps = 2;
			else
				deltaSteps = 1;
			
			if (mask[recent.x - 1][recent.y] > recent.steps)
			{
				
				myQ.push({ recent.x - 1, recent.y, recent.steps + deltaSteps});
				mask[recent.x - 1][recent.y] = recent.steps + deltaSteps;
			}				
		}

		if (recent.x < X - 1 && L->GetLab(recent.x + 1, recent.y) != '#')
		{
			if (L->GetLab(recent.x + 1, recent.y) == 'v')
				deltaSteps = 2;
			else
				deltaSteps = 1;
			
			if (mask[recent.x + 1][recent.y] > recent.steps)
			{
				
				myQ.push({ recent.x + 1, recent.y, recent.steps + deltaSteps });
				mask[recent.x + 1][recent.y] = recent.steps + deltaSteps;
			}				
		}

		if (recent.y > 1 && L->GetLab(recent.x, recent.y - 1 ) != '#')
		{
			if (L->GetLab(recent.x, recent.y - 1) == 'v')
				deltaSteps = 2;
			else
				deltaSteps = 1;
			
			if (mask[recent.x][recent.y - 1] > recent.steps)
			{
				
				myQ.push({ recent.x, recent.y - 1, recent.steps + deltaSteps });
				mask[recent.x][recent.y - 1] = recent.steps;
			}				
		}

		if (recent.y < Y - 1 && L->GetLab(recent.x, recent.y + 1) != '#')
		{
			if (L->GetLab(recent.x, recent.y + 1) == 'v')
				deltaSteps = 2;
			else
				deltaSteps = 1;
			

			if (mask[recent.x][recent.y + 1] > recent.steps)
			{
				
				myQ.push({ recent.x, recent.y + 1, recent.steps + deltaSteps });
				mask[recent.x][recent.y + 1] = recent.steps + deltaSteps;
			}				
		}

		myQ.pop();

		
	}

	int minDist = 1000000;
	cell target;

	for (cell c : treasures)
	{
		if (c.steps < minDist)
		{
			target = c;
			minDist = target.steps;
		}
			
	}

	//std::cout << "target is " << target.x << " " << target.y << " for " << target.steps << " steps\n";

	myQ.push(target);	

	while (!myQ.empty())
	{
		cell recent = myQ.front();

		if (mask[recent.x + 1][recent.y] < recent.steps)
		{
			if (mask[recent.x + 1][recent.y] == 0)
			{
				//std::cout << "returning U\n";
				return 'U';
			}
			else
			{
				myQ.push({ recent.x + 1, recent.y, mask[recent.x + 1][recent.y]});
				myQ.pop();				
			}			
		}
		else if (mask[recent.x - 1][recent.y] < recent.steps)
		{
			if (mask[recent.x - 1][recent.y] == 0)
			{	
				//std::cout << "returning D\n";
				return 'D';
			}
			else
			{
				myQ.push({ recent.x - 1, recent.y, mask[recent.x - 1][recent.y]});
				myQ.pop();	
				continue;
			}			
		}
		else if (mask[recent.x][recent.y - 1] < recent.steps)
		{
			if (mask[recent.x][recent.y - 1] == 0)
			{
				//std::cout << "returning R\n";
				return 'R';
			}
			else
			{
				myQ.push({ recent.x, recent.y - 1, mask[recent.x][recent.y - 1]});
				myQ.pop();	
				continue;
			}			
		}
		else if (mask[recent.x][recent.y + 1] < recent.steps)
		{
			if (mask[recent.x][recent.y + 1] == 0)
			{
				//std::cout << "returning L\n";
				return 'L';
			}
			else
			{
				myQ.push({ recent.x, recent.y + 1, mask[recent.x][recent.y + 1]});
				myQ.pop();	
				continue;
			}			
		}
		else
		{
			/*std::cout << "returning STOP\n";
			std::cout << "target params " << target.x << " "<< target.y << " " << target.steps << "\n" ;
			std::cout << "bot coordinates " << x_me << " " << y_me << "\n";
			for (int i = 0; i < X; i++)
			{
				for (int j = 0; j < Y; j++)
				{
					std::cout << mask[i][j] << '\t';
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;*/

			return ' ';
		}
	}	
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

