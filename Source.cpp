#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
const int width = 30, height = 30;
enum direction { stop = 0, Up, Left, Right, Down };
int headX, headY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int ntail;
direction dir;
void setup()
{
	gameOver = false;
	dir = stop;
	headX = width / 2;
	headY = width / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;

}

void Draw()
{
	system("cls");
	for (int i = 0;i < width + 1;++i)
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height;++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (j == 0)
			{
				cout << "#";
			}
			if (i == headY && j == headX)
			{
				cout << "0";
			}
			else if (i == fruitY && j == fruitX)
			{
				cout << "F";
			}
			else
			{
				bool print = false;
				for (int k = 0; k < ntail; ++i)
				{
					if (tailX[k] == j && tailY[k] == i)
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
			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0;i < width + 1;++i)
	{
		cout << "#";
	}
	cout << endl;
	cout << endl << "score: " << score;
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = headX;
	tailY[0] = headY;
	for (int i = 1;i < ntail;++i)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}
	switch (dir)
	{
	case Left:
		headX--;
		break;
	case Right:
		headX++;
		break;
	case Up:
		headY--;
		break;
	case Down:
		headY++;
		break;
	default:
		break;
	}
	if (headX >= width || headX <= 0 || headY >= width || headY <= 0)
	{
		gameOver = true;
	}
	for (int i = 0;i < ntail;++i)
	{
		if (tailX[i] == headX && tailY[i] == headY)
			gameOver = true;
	}
	if (headX == fruitX && headY == fruitY)
	{

		fruitX = rand() % width;
		fruitY = rand() % height;
		score += 10;
		ntail++;
	}
}

void input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = Left;
			break;
		case 'd':
			dir = Right;
			break;
		case 'w':
			dir = Up;
			break;
		case 's':
			dir = Down;
			break;
		case 'k':
			gameOver = true;
			break;
		}
	}
}

int main() {
	setup();

	while (!gameOver)
	{
		Sleep(40 ^ 4);
		Draw();
		input();
		Logic();

	}
}