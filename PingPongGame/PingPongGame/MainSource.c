
/*1. Ƣ�涧���� ���� �ٲٱ� -> 2 (����)
* 2. ���̵�(���ϸ�) -> 3
* 3. �ٻ� ���� -> 1 v
* 4. ��ֹ� �߰� -> 5
* 5. �𼭸� ���� ���� (�״�� ���ư���) -> 6
* 6. ���� ����Ÿ�� -> 4 v
* 7. �������� �Է� -> 7
*/

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13
#define YELLOW 14 
#define WHITE 15 

int p1x = 1, p2x = 80;
int p1y = 12, p2y = 12;
int bx = 40, by = 10, bintx = 0, binty = 0, bflx, bfly; //bx�� by�� ���� ������
int nowp1y = 7, nowp2y = 7;
int p1score = 0, p2score = 0;
int scox = 39, scoy = 2; //���ھ� ��ġ
int doublex = 37, doubley = 3, DoublePlayer = 0;
int sgame, GameCounter = 0;

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void endgame() {
	sgame = 0;
	system("cls");
	printf("game over");
}

void GiveScore(int team) {
	if (team == 1) {
		if (DoublePlayer == 2) {
			p2score += 2;
		}
		else {
			p2score++;
		}
	}
	else if (team == 2) {
		if (DoublePlayer == 1) {
			p1score += 2;
		}
		else {
			p1score++;
		}
	}
	bx = 40;
	by = 10;
	bintx = 0;
	binty = 0;
	sgame = 0;
	DoublePlayer = 0;
	main();
}

void PrintScore(int x, int y) {
	gotoxy(x, y);
	printf("%d : %d", p1score, p2score);
}

void pl1m(int x, int y) { //�÷��̾� 1�� �� ���
	for (int i = 0; i < 5; i++) {
		textcolor(RED, BLACK);
		gotoxy(x, y - i);
		printf("��");
		textcolor(WHITE, BLACK);
	}
}

void pl2m(int x, int y) { //�÷��̾� 2�� �� ���
	for (int i = 0; i < 5; i++) {
		textcolor(BLUE, BLACK);
		gotoxy(x, y - i);
		printf("��");
		textcolor(WHITE, BLACK);
	}
}

void PrintDouble(int x, int y, int team) {
	gotoxy(x, y);
	if (team == 1) {
		textcolor(RED, BLACK);
		DoublePlayer = 1;
	}
	else if (team == 2) {
		textcolor(BLUE, BLACK);
		DoublePlayer = 2;
	}
	printf("������ 2��");
	textcolor(WHITE, BLACK);
}

void bxy(int x, int y) { //�� ���
	gotoxy(x, y);
	printf("��");
}

void bmove(int x, int y) { //�� 
	system("cls");
	DubleScore();
	PrintScore(scox, scoy);
	bxy(x + bintx, y + binty); //�̵����
	pl1m(p1x, p1y); //�̵��Ҷ� �� ���
	pl2m(p2x, p2y);

	if (bintx > 39) { //������ ���� ��������
		GiveScore(2);
	}
	if (bintx < -38) { //���� ���� ��������
		GiveScore(1);
	}

	if (bintx >= 38) { //������ �ٿ� �����ٸ� ������ȯ
		if (binty + 9 >= nowp2y && binty + 9 <= nowp2y + 4) { //���� y��� ���� y�� ��
			bflx = 1;
			GameCounter++;
		}
	}
	if (bintx <= -37) { //���� �ٿ� �����ٸ� ������ȯ
		if (binty + 9 >= nowp1y && binty + 9 <= nowp1y + 4) {
			bflx = 0;
			GameCounter++;
		}
	}

	if (binty >= 10) { //�Ʒ��� ���� ������ �������� ��ȯ
		bfly = 1;
	}
	else if (binty <= -9) { //�Ʒ��� ���� ������ �������� ��ȯ
		bfly = 0;
	}


	if (bflx == 1) { //����
		bintx--;
	}
	else if (bflx == 0) { //������
		bintx++;
	}
	if (bfly == 1) { //�ö�
		binty--;
	}
	else if (bfly == 0) { //������
		binty++;
	}
}

void mainprint() {
	system("cls");
	PrintScore(scox, scoy);
	DubleScore();
	bxy(bx + bintx, by + binty); //�̵��Ҷ� �����
	pl1m(p1x, p1y);
	pl2m(p2x, p2y);
}

int DubleScore() {
	if (p1score > p2score) {
		if ((p1score - p2score) >= 3) {
			PrintDouble(doublex, doubley, 2);
		}
	}
	else {
		if ((p2score - p1score) >= 3) {
			PrintDouble(doublex, doubley, 1);
		}
	}
}

void mainmove() {
	//�÷��̾� 1
	bmove(bx, by);
	if (GetAsyncKeyState(0x57) & 0x8000) {
		if (nowp1y > 0) {
			p1y--;
			nowp1y--;
			mainprint();
		}
	}
	if (GetAsyncKeyState(0x53) & 0x8000) {
		if (nowp1y < 15) {
			p1y++;
			nowp1y++;
			mainprint();
		}
	}
	//�÷��̾� 2
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		if (nowp2y > 0) {
			p2y--;
			nowp2y--;
			mainprint();
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		if (nowp2y < 15) {
			p2y++;
			nowp2y++;
			mainprint();
		}
	}
	Sleep(20);
}

int main() {
	srand(time(NULL));
	system("mode con:cols=81 lines=20");
	system("title Ping Pong Game");
	bflx = rand() % 2;
	bfly = rand() % 2;
	PrintScore(scox, scoy);
	DubleScore();
	bxy(bx, by);
	pl1m(p1x, p1y);
	pl2m(p2x, p2y);
	sgame = 1;
	while (sgame) { // �ݺ�
		mainmove();
	}
}