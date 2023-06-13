#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

// ������
#define clear system("cls");

	//����� ������
#define enter "\n"				//����� ������ x 1
#define enterX2 "\n\n"			//����� ������ x 2
#define enterX3 "\n\n\n"		//����� ������ x 3
#define enterX4 "\n\n\n\n"		//����� ������ x 4

	//���������
#define tab "\t"							//��������� x 1
#define tabX2 "\t\t"						//��������� x 2
#define tabX3 "\t\t\t"						//��������� x 3
#define tabX4 "\t\t\t\t"					//��������� x 4
#define tabX6 "\t\t\t\t\t\t"				//��������� x 6
#define tabX12 "\t\t\t\t\t\t\t\t\t\t\t\t"	//��������� x 12

	//�����
#define light_red "\x1b[31m"		//����_�������
#define light_green "\x1b[32m"		//����_������
#define light_yellow "\x1b[33m"		//����_�����
#define light_blue "\x1b[34m"		//����_�������
#define light_purple "\x1b[35m"		//����_����������
#define light_turquoise "\x1b[36m"	//����_���������

#define red "\x1b[91m"			// �������
#define green "\x1b[92m"		// ������
#define yellow "\x1b[93m"		// Ƹ����
#define blue "\x1b[94m"			// �����
#define purple "\x1b[95m"		// �����
#define turquoise "\x1b[96m"	// ���������
#define grey "\x1b[90m"			// �����
#define reset "\x1b[0m"			// - ����

void CursoreVisable(bool a)
{
	CONSOLE_CURSOR_INFO curs = { 0 };
	curs.dwSize = sizeof(curs);
	curs.bVisible = a;
	::SetConsoleCursorInfo(::GetStdHandle(STD_OUTPUT_HANDLE), &curs);
}

void cls(int x, int y) {			//��������� ������� �� �������  x y
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
	cout << yellow << "������: " << light_yellow << score << reset << enter;

	cout << enterX3 << tabX6;
	for (int i = 0; i < width; i++)
		cout << light_yellow << " #" << reset;//�������
	cout << enter;

	for (int i = 0; i < hight; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << tabX6 << light_yellow << "#" << reset; // ����� �����
			}

			if (i == y && j == x)
				cout << light_turquoise << " " << char(34) << reset; //������

			else if (i == foody && j == foodx)
				cout << purple << " " << char(127) << reset;//���

			else
			{
				bool print = false;

				for (int k = 0; k < tail; k++)
				{
					if (tailx[k] == j && taily[k] == i)
					{
						cout << purple << " " << char(15) << reset; // �����
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
				cout << light_yellow << "#" << reset;//������ �����
			}
		}

		cout << enter;
	}
	cout << tabX6;

	for (int i = 0; i < width; i++) {
		cout << light_yellow << " #" << reset;//���

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

	cout << enterX3 << tabX4 << green "������ " << char(134) << reset << enterX2;
	cout << light_turquoise << "����������:" << enterX2 <<
		light_turquoise << "w/W = �����" << enter <<
		light_turquoise << "s/S = ����" << enter <<
		light_turquoise << "a/A = ������" << enter <<
		light_turquoise << "d/D = �����" << reset << enterX3;
	cout << light_yellow << "���� ���: " << reset;

	string name;
	cin >> name;

	start();
	clear;

	while (!gameover && !esc)//������� ����
	{
		CursoreVisable(FALSE);
		map();
		logic();
		move();
		Sleep(10);
	}

	clear;
	if (gameover) {
		cout << enterX3 << tabX2 << red << "�� ��������� ������ �� �����!" << enter;
		cout << tabX2 << light_yellow << "������ ������ ������� � " << red << name << ": " << light_green << score << reset << enter;
		Sleep(1000);

		return 0;
	}
	else if (esc = true) {
		clear;
		cout << enterX3 << tabX2 << light_green << "�� ����� �� ����!" << reset << enter;
		cout << tabX2 << light_yellow << "������ ������ ������� � " << red << name << ": " << light_green << score << reset << enter;
	}

	return 0;

}