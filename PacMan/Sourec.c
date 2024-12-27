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
int hp;
int mob_x, mob_y;
int score_x[10], score_y[10];
int x, y;
char map[V][H];
char c = 1;
	//	더블 버퍼 변수
int screenIndex;
HANDLE screen[2];

void Gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void CreatMap() {
	srand(time(NULL));
	mob_x = rand() % H + 1;
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
												//	몬스터 1마리 소환
	if (map[mob_y][mob_x] != '.' || map[mob_y][mob_x] != ' ' || map[mob_y][mob_x] != '#') map[mob_y][mob_x] = 'X';
	else {
		int mob_x = rand() % H + 1;				//	플레이어, 점수, 벽 과 겹치면 재소환
		int mob_y = rand() % V + 1;				//	만약 또 같으면 어쩔수 없음
	}
}
void RenderMap() {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int i = 0; i < V; i++) {												//	맵 출력
		for (int j = 0; j < H; j++) {	
			if (map[i][j] == 'X') {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);		//	몹은 빨간색으로 표현
				printf("%c", map[i][j]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else printf("%c", map[i][j]);
		}
		printf("\n");
	}

	Gotoxy(0, 21);
	printf("Total Score : 5");
	Gotoxy(0, 22);
	printf("Get Score : %d", score);
	Gotoxy(0, 23);
	if (hp == 3) printf("HP : ♥♥♥");				//	변수 만들기 귀찮았음
	else if (hp == 2) printf("HP : ♥♥♡");
	else if (hp == 1) printf("HP : ♥♡♡");
	else printf("HP : ♡♡♡");

}
void GetScore() {

	for (int i = 0; i < 6; i++) {

		if (x == score_x[i] && y == score_y[i]) {
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
void FinishGame() {

	if (score == 5) {							//	점수 모두 모으면 클리어
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("\n\n\tGame Clear !\n\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		c = 0;
	}
	else if (hp == 0) {							//	채력 모두 소진시 강제종료
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("\n\n\tGame Over !\n\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		c = 0;
	}


}
void Player(int x, int y) {
				//	플레이어는 노란색으로 표현
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	Gotoxy(x, y);
	printf("C");

}

int main() {

	int key;
	x = 1, y = 1, hp = 3;

	CreatMap();
	RenderMap();
	Player(x, y);

	while (c) {

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
			RenderMap();
			Player(x, y);
			GetScore();
			FinishGame();
		}
	}

	return 0;
}