#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

// Чистка
#define clear system("cls");

	//Новае строки
#define enter "\n"				//Новая строка x 1
#define enterX2 "\n\n"			//Новая строка x 2
#define enterX3 "\n\n\n"		//Новая строка x 3
#define enterX4 "\n\n\n\n"		//Новая строка x 4

	//Табуляции
#define tab "\t"							//Табуляция x 1
#define tabX2 "\t\t"						//Табуляция x 2
#define tabX3 "\t\t\t"						//Табуляция x 3
#define tabX4 "\t\t\t\t"					//Табуляция x 4
#define tabX6 "\t\t\t\t\t\t"				//Табуляция x 6
#define tabX12 "\t\t\t\t\t\t\t\t\t\t\t\t"	//Табуляция x 12

	//Цвета
#define light_red "\x1b[31m"		//Ярко_красный
#define light_green "\x1b[32m"		//Ярко_зелёный
#define light_yellow "\x1b[33m"		//Ярко_жёлтый
#define light_blue "\x1b[34m"		//Ярко_голубой
#define light_purple "\x1b[35m"		//Ярко_фиолетовый
#define light_turquoise "\x1b[36m"	//Ярко_бирюзовый

#define red "\x1b[91m"			// Красный
#define green "\x1b[92m"		// Зелёный
#define yellow "\x1b[93m"		// Жёлтый
#define blue "\x1b[94m"			// Синий
#define purple "\x1b[95m"		// Пурпл
#define turquoise "\x1b[96m"	// Бирюзовый
#define grey "\x1b[90m"			// серый
#define reset "\x1b[0m"			// - Цвет

void CursoreVisable(bool a)
{
	CONSOLE_CURSOR_INFO curs = { 0 };
	curs.dwSize = sizeof(curs);
	curs.bVisible = a;
	::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);
}

void cls(int x, int y) {			//установка курсора на позицию  x y
	COORD coord;    coord.X = x;
	coord.Y = y;    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

const int width = 30;
const int hight = 30;
int foodx, foody;
int x;
int y;
int score = 0;
int tailx[200] = { 0 };
int taily[200] = { 0 };
int tail = 0;
enum direction { LEFT, RIGHT, UP, DOWN };
direction go;
bool gameover;
bool esc;


void start()
{
	esc = false;
	gameover = false;
	x = width / 2;
	y = hight / 2;
	foodx = rand() % width;
	foody = rand() % hight;
}


void map()
{
	cls(0, 0);

	cout << enterX2 << tabX12;
	cout << yellow << "Рекорд: " << light_yellow << score << reset << enter;

	cout << enterX3 << tabX6;
	for (int i = 0; i < width; i++)
		cout << light_yellow << " #" << reset;//Потолок
	cout << enter;

	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << tabX6 << light_yellow << "#" << reset; // Левая стена
			}

			if (i == y && j == x)
				cout << light_turquoise << " " << char(34) << reset; //Голова

			else if (i == foody && j == foodx)
				cout << purple << " " << char(127) << reset;//Еда

			else
			{
				bool print = false;

				for (int k = 0; k < tail; k++)
				{
					if (tailx[k] == j && taily[k] == i)
					{
						cout << purple << " " << char(15) << reset; // Хвост
						print = true;
					}
				}

				if (!print)
				{
					cout << "  ";
				}
			}

			if (j == width - 1)
			{
				cout << light_yellow << "#" << reset;//Правая стена
			}
		}

		cout << enter;
	}
	cout << tabX6;

	for (int i = 0; i < width; i++) {
		cout << light_yellow << " #" << reset;//Пол

	}
}

void move()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case'a':
		case 'A':
			go = LEFT;
			break;
		case's':
		case 'S':
			go = DOWN;
			break;
		case'w':
		case'W':
			go = UP;
			break;
		case'd':
		case'D':
			go = RIGHT;
			break;
		case 27:
			esc = true;
			break;
		}
	}
}

void logic()
{
	int prevX = tailx[0];
	int prevY = taily[0];
	int prev2X, prev2Y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < tail; i++)
	{
		prev2X = tailx[i];
		prev2Y = taily[i];
		tailx[i] = prevX;
		taily[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (go)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x > width - 1 || x < 0 || y > hight - 1 || y < 0)
		gameover = true;

	for (int i = 0; i < tail; i++)
	{
		if (tailx[i] == x && taily[i] == y)
			gameover = true;
	}

	if (x == foodx && y == foody)
	{
		foodx = rand() % width;
		foody = rand() % hight;
		tail++;
		score += 10;
	}

}

int main() {
	setlocale(0, "");

	cout << enterX3 << tabX4 << green "Змейка " << char(134) << reset << enterX2;
	cout << light_turquoise << "Управление:" << enterX2 <<
		light_turquoise << "w/W = Вверх" << enter <<
		light_turquoise << "s/S = Вниз" << enter <<
		light_turquoise << "a/A = Вправо" << enter <<
		light_turquoise << "d/D = Влево" << reset << enterX3;
	cout << light_yellow << "Ваше имя: " << reset;

	string name;
	cin >> name;

	start();
	clear;

	while (!gameover && !esc)//Процесс игры
	{
		CursoreVisable(FALSE);
		map();
		logic();
		move();
		Sleep(10);
	}

	clear;
	if (gameover) {
		cout << enterX3 << tabX2 << red << "Вы ударились бошкой об стену!" << enter;
		cout << tabX2 << light_yellow << "Рекорд пурпле домиков у " << red << name << ": " << light_green << score << reset << enter;
		Sleep(1000);

		return 0;
	}
	else if (esc = true) {
		clear;
		cout << enterX3 << tabX2 << light_green << "Вы вышли из игры!" << reset << enter;
		cout << tabX2 << light_yellow << "Рекорд пурпле домиков у " << red << name << ": " << light_green << score << reset << enter;
	}

	return 0;

}