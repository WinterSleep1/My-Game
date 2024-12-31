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

	mob_x = rand() % H + 1;					//	몬스터의 (x,y)를 무작위로 생성
	mob_y = rand() % V + 1;

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

		if(score_x[i] > H -2 || score_x[i] > H / 2) score_x[i] -= 2;		//	x가 너무 크면	x-2
		else score_x[i] += 1;
		
		if (score_y[i] > V - 2 || score_y[i] > V / 2) score_y[i] -= 2;		//	y가 너무 크면	y-2
		else score_y[i] += 1;
		
		map[score_y[i]][score_x[i]] = '.';
	}

	while (1) {
		if (map[mob_y][mob_x] == '.' || map[mob_y][mob_x] == 'C' || map[mob_y][mob_x] == '#') {	//	점수, 플레이어, 벽이랑 겹치면 재소환
			mob_x = rand() % H + 1;
			mob_y = rand() % V + 1;
		}
		else if (mob_x > H - 2 || mob_y > V - 2) {			//	x,y 중 하나라도 크면 재소환
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

	for (int i = 0; i < V; i++) {												//	맵 출력
		for (int j = 0; j < H; j++) {	
			printf("%c", map[i][j]);
		}
		printf("\n");
	}

	Gotoxy(x, y);														//	플레이어 노란색
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	printf("C");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	Gotoxy(mob_x, mob_y);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		//	몹 빨간색
	printf("%c", map[mob_y][mob_x]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	Gotoxy(0, 21);
	printf("Total Score : 5");			//	점수 개수
	Gotoxy(0, 22);
	printf("Get Score : %d", score);	//	현재 점수

	Gotoxy(0, 23);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		//	채력 빨간색
	if (hp == 3) printf(" ♥♥♥");
	else if (hp == 2) printf(" ♥♥♡");
	else if (hp == 1) printf(" ♥♡♡");
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

	if (score == 5) {							//	점수 모두 모으면 클리어
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("\n\n\tGame Clear !\n\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		return 0;
	}
	else if (hp == 0) {							//	채력 모두 소진시 강제종료
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