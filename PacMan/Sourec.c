#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define H 40
#define V 20
#define WALL '#'

int score = 0;
int hp = 3;
int mob_x, mob_y;
int score_x[10], score_y[10];
int x = 1, y = 1;
char map[V][H];

void Gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void CreatMap() {

	srand(time(NULL));

	mob_x = rand() % H + 1;					//	������ (x,y)�� �������� ����
	mob_y = rand() % V + 1;

	for (int i = 0; i < V; i++) {				//	�� ������
		for (int j = 0; j < H; j++) {
			if (i == 0 || i == V - 1) map[i][j] = WALL;			//	��
			else if (j == 0 || j == H - 1) map[i][j] = WALL;	//	��
			else map[i][j] = ' ';								//	����
		}
	}

	for (int i = 0; i < 5; i++) {				//	 ���� 5�� ������ ����
		score_x[i] = rand() % H + 1;
		score_y[i] = rand() % V + 1;

		if(score_x[i] > H -2 || score_x[i] > H / 2) score_x[i] -= 2;		//	x�� �ʹ� ũ��	x-2
		else score_x[i] += 1;
		
		if (score_y[i] > V - 2 || score_y[i] > V / 2) score_y[i] -= 2;		//	y�� �ʹ� ũ��	y-2
		else score_y[i] += 1;
		
		map[score_y[i]][score_x[i]] = '.';
	}

	while (1) {
		if (map[mob_y][mob_x] == '.' || map[mob_y][mob_x] == 'C' || map[mob_y][mob_x] == '#') {	//	����, �÷��̾�, ���̶� ��ġ�� ���ȯ
			mob_x = rand() % H + 1;
			mob_y = rand() % V + 1;
		}
		else if (mob_x > H - 2 || mob_y > V - 2) {			//	x,y �� �ϳ��� ũ�� ���ȯ
			mob_x = rand() % H + 1;
			mob_y = rand() % V + 1;
		}
		else {
			map[mob_y][mob_x] = 'X';
			return 0;
		}
	}

}
void RenderMap() {

	for (int i = 0; i < V; i++) {												//	�� ���
		for (int j = 0; j < H; j++) {	
			printf("%c", map[i][j]);
		}
		printf("\n");
	}

	Gotoxy(x, y);														//	�÷��̾� �����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("C");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	Gotoxy(mob_x, mob_y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		//	�� ������
	printf("%c", map[mob_y][mob_x]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	Gotoxy(0, 21);
	printf("Total Score : 5");			//	���� ����
	Gotoxy(0, 22);
	printf("Get Score : %d", score);	//	���� ����

	Gotoxy(0, 23);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		//	ä�� ������
	if (hp == 3) printf(" ������");
	else if (hp == 2) printf(" ������");
	else if (hp == 1) printf(" ������");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
void GetScore() {

	for (int i = 0; i < 6; i++) {

		if (x == score_x[i] && y == score_y[i] && map[score_y[i]][score_x[i]] == '.') {
			score++;
			map[y][x] = ' ';
		}
		else if (x == mob_x && y == mob_y) {
			hp--;
			x = 1;
			y = 1;
		}
	}

}
void CursorView() {
	CONSOLE_CURSOR_INFO cursor = { 0 };
	cursor.dwSize = 1;
	cursor.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);

}
int FinishGame() {

	if (score == 5) {							//	���� ��� ������ Ŭ����
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("\n\n\tGame Clear !\n\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		return 0;
	}
	else if (hp == 0) {							//	ä�� ��� ������ ��������
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("\n\n\tGame Over !\n\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		return 0;
	}
	else return 1;


}

int main() {

	int key;

	CursorView();
	CreatMap();
	RenderMap();

	while (1) {

		if (_kbhit()) {

			key = _getch();
			system("cls");

			if (key == 224) key = _getch();

			switch (key) {
			case UP:
				if (y > 1) y--;
				break;
			case DOWN:
				if (y < V-2) y++;
				break;
			case LEFT:
				if (x > 1) x--;
				break;
			case RIGHT:
				if (x < H-2) x++;
				break;
			}

			if (FinishGame() == 0) return 0;
			RenderMap();
			GetScore();
		}
	}

	return 0;
}