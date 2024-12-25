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
int score_x[10], score_y[10];
int x, y;
char map[V][H];
char c = 1;

void Gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void CreatMap() {
	srand(time(NULL));

	for (int i = 0; i < V; i++) {				//	맵 생성후
		for (int j = 0; j < H; j++) {
			if (i == 0 || i == V - 1) map[i][j] = WALL;			//	벽
			else if (j == 0 || j == H - 1) map[i][j] = WALL;	//	벽
			else map[i][j] = ' ';								//	공백
		}
	}

	for (int i = 0; i < 5; i++) {				//	 점수 5개 무작위 생성
		score_x[i] = rand() % H + 1;
		score_y[i] = rand() % V + 1;

		if(score_x[i] > H -2 || score_x[i] > H / 2) score_x[i] -= 2;		//	x가 너무 크면
		else score_x[i] += 1;
		
		if (score_y[i] > V - 2 || score_y[i] > V / 2) score_y[i] -= 2;		//	y가 너무 크면
		else score_y[i] += 1;
		
		map[score_y[i]][score_x[i]] = '.';
	}

}
void RenderMap() {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int i = 0; i < V; i++) {				//	맵 출력
		for (int j = 0; j < H; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}

	Gotoxy(0, 21);
	printf("Total Score : 5");
	Gotoxy(0, 22);
	printf("Get Score : %d", score);

}
void GetScore() {

	for (int i = 0; i < 6; i++) {
		Gotoxy(0, 23 + i);
		printf("x%d : %d\ty%d : %d\n", i+1, score_x[i], i+1, score_y[i]);

		if (x == score_x[i] && y == score_y[i]) {
			score++;
			map[y][x] = ' ';
		}
	}

}
void FinishGame() {

	if (score == 5) {
		system("cls");
		printf("Game Clear !");
		c = 0;
	}

}

int main() {
	int key;
	x = 1, y = 1;
	CreatMap();
	RenderMap();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	Gotoxy(x, y);
	printf("C");

	while (c) {
		if (_kbhit()) {

			key = _getch();
			system("cls");

			if (key == 224) {
				key = _getch();
			}

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
			FinishGame();
			RenderMap();
			GetScore();
			Gotoxy(x, y);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
			printf("C");
			Gotoxy(0, 29);
			printf("px : %d\tpy : %d", x ,y);
		}
	}

	return 0;
}