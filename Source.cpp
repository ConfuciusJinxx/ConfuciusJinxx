#include <iostream>
#include <conio.h>
using namespace std;

bool GameOver;
const int wall_wdth = 30;
const int wall_hght = 20;
int headx = 0, heady = 0;
int fruitx = 0, fruity = 0, score = 0;
char wall = '#';
enum direction { stop = 0, Left, Right, Up, Down };
direction dir = stop;
int tailx[100], taily[100];
int prevx, prev2x, prevy, prev2y;
int ntail;
void setup()
{
	GameOver = false;
	headx = wall_wdth / 2;
	heady = wall_hght / 2;
	fruitx = rand() % (wall_wdth - 5);
	fruity = rand() % (wall_hght - 5);
}

void Map() 
{
	system("cls");
	for (int i = 0;i < wall_wdth + 3;++i)
	{
		cout << wall ;
	}

	for (int y = 0; y < wall_hght;++y)
	{
		for (int x = 0; x < wall_wdth + 3;x++)
		{
			if (x == 0 || x == wall_wdth + 2)
			{
				cout << wall;
			}
			if (headx == x && heady == y)
			{
				cout << "0";
			}
			else if (fruitx == x && fruity == y)
			{
				cout << "F";
			}
			else
			{
				bool print = false;
				for (int t = 0; t < ntail; ++t)
				{
					if (tailx[t] == x && taily[t] == y)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
				{
					cout << " ";
				}
			}
			
		}cout << endl;
	}cout << endl;
	cout << endl << "Score: " << score;

	for (int i = 0;i < wall_wdth + 3;++i)
	{
		cout << wall;
	}
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch()) 
		{
		case 'w':
			dir = Up;
			break;
		case 's':
			dir = Down;
			break;
		case 'a':
			dir = Left;
			break;
		case 'd':
			dir = Right;
			break;
		case 'k':
			GameOver = true;
			break;
		default:
			break;

		}
	}

}

void Logic()
{
	switch (dir)
	{
	case Up:
		heady--;
		break;
	case Down:
		heady++;
		break;
	case Left:
		headx--;
		break;
	case Right:
		headx++;
		break;
	}
	if (headx > wall_wdth || headx < 0 || heady > wall_hght || heady < 0)
	{
		GameOver = true;
	}
	for (int i = 0; i < ntail;++i)
	{
		if (headx == tailx[i] && heady == taily[i])
			GameOver = true;
	}
	
	if (headx == fruitx && heady == fruity)
	{
		score += 10;
		ntail++;
		fruitx = rand() % (wall_wdth - 5);
		fruity = rand() % (wall_hght - 5);

	}
	prevx = tailx[0];
	prevy = taily[0];
	tailx[0] = headx;
	taily[0] = heady;
	for (int i = 0; i < ntail; ++i)
	{
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
}

int main()
{
	setup();

	while (!GameOver)
	{
		Map();
		Input();
		Logic();
	}
}
