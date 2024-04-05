// 1991147, 박정제
// BABA IS YOU
#include <stdio.h>
#include <conio.h>
#include <Windows.h>


// 색상 정의
#define BLACK	0
#define BLUE1	1
#define GREEN1	2
#define CYAN1	3
#define RED1	4
#define MAGENTA1 5
#define YELLOW1	6
#define GRAY1	7
#define GRAY2	8
#define BLUE2	9
#define GREEN2	10
#define CYAN2	11
#define RED2	12
#define MAGENTA2 13
#define YELLOW2	14
#define WHITE	15


#define ESC 0x1b

#define SPECIAL1 0xe0 // 특수키는 0xe0 + key 값으로 구성된다.
#define SPECIAL2 0x00 // keypad 경우 0x00 + key 로 구성된다.

#define UP  0x48 // Up key는 0xe0 + 0x48 두개의 값이 들어온다.
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
#define ENTER 13

#define UP2		'w'
#define DOWN2	's'
#define LEFT2	'a'
#define RIGHT2	'd'

#define WIDTH 48
#define HEIGHT 16

#define col 10
#define span 10


/*
0 empty
1~15 동사
16~127 개체
	소문자 객체
	대문자 텍스트
128-255 상태
*/

#define empty 0

#define IS 1

#define baba 16
#define BABA 17
#define flag 18
#define FLAG 19
#define rock 20
#define ROCK 21
#define wall 22
#define WALL 23
#define xxxx 24
#define XXXX 25
#define star 26
#define STAR 27

#define YOU 128
#define WIN 129
#define STOP 130
#define PUSH 131
#define LOSE 132

#define select 255

/*
아무것도 아닌상태 0
PUSH STOP  1
TEXT 2
YOU 3
FLOAT 4
*/
#define LAYER 4
#define LAYER_nothing 0
#define LAYER_PUSH_STOP 1
#define LAYER_TEXT 2
#define LAYER_YOU 3

void loading();
void draw(int x, int y, int i);
void removeCursor(void);
void gotoxy(int x, int y);
void textcolor(int fg_color, int bg_color);
void cls(int bg_color, int text_color);
void remove_pix(int x, int y);
void change_condition(int object, int state, int num);
void print_state();
int ismoveable(int x, int y, unsigned char ch);
int moveable(int x, int y, unsigned char ch);
int change_layer(int data);
int iswin();
void reset_level();
void reset_plevel();
void set_level_0();
void set_level_1();
void set_level_2();
void set_level_3();
void set_level_4();
void set_level_5();
void set_level_6();
void set_level_7();
void set_level_error();
void set_level(int level);
void print_main(int level);
void print_win();
void print_howtoplay();

struct point {
	int x;
	int y;
};

int redraw = 0;
int Delay = 100; // 100 msec delay, 이 값을 줄이면 속도가 빨라진다.
int screen[LAYER][WIDTH][HEIGHT] = {0};
int screen_p[LAYER][WIDTH][HEIGHT] = {0};
unsigned char *prt[256] = { 0 }; //1,0값만 들어가는데 c언어에는 bool이 없어 가장작은 자료형인 char로 선언

void loading() {
	cls(BLACK, WHITE);
	system("mode con cols=480 lines=160");
	cls(BLACK, BLACK);

	removeCursor();

	textcolor(WHITE, BLACK);

	/*
	ㅁㅁㅁㅁ0[12][10]
		ㅁㅁㅁㅁ0[0-9] : 그림
		ㅁㅁㅁㅁ0[10][0-1] : 글씨색과 배경색
		ㅁㅁㅁㅁ0[10][2] : 채우기 존재여부
		ㅁㅁㅁㅁ0[10][3-4] : 글씨색과 배경색
		ㅁㅁㅁㅁ0[11][5] : LAYER
		ㅁㅁㅁㅁ0[11][0-] : 속성
	*/
	 
	//0
	static unsigned char empty0[12][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1},
	{BLACK,BLACK}
	};
	prt[empty] = empty0;

	//1
	static unsigned char IS0[12][10] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,1,1,0,0,1,1,1,0},
	{0,0,1,0,0,1,0,0,0,0},
	{0,0,1,0,0,1,0,0,0,0},
	{0,0,1,0,0,1,0,0,0,0},
	{0,0,1,0,0,0,1,1,0,0},
	{0,0,1,0,0,0,0,0,1,0},
	{0,0,1,0,0,0,0,0,1,0},
	{0,1,1,1,0,1,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{WHITE,WHITE}
	};
	prt[IS] = IS0;

	//16
	static unsigned char baba0[12][10] = {
	{0,0,1,0,0,0,1,0,0,0},
	{0,0,1,1,0,0,1,0,0,0},
	{0,1,1,1,1,1,1,1,1,0},
	{1,1,1,1,1,1,1,0,1,1},
	{1,1,1,1,1,0,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{0,1,1,1,1,1,1,1,1,0},
	{1,0,0,1,0,0,1,0,1,0},
	{1,0,0,1,0,0,1,0,0,1},
	{WHITE,WHITE}
	};
	prt[baba] = baba0;


	//17
	static unsigned char BABA0[12][10] = {
	{1,1,1,0,0,0,0,1,0,0},
	{1,0,0,1,0,0,1,0,1,0},
	{1,1,1,0,0,1,1,1,1,1},
	{1,0,0,1,0,1,0,0,0,1},
	{1,1,1,0,0,1,0,0,0,1},
	{1,1,1,0,0,0,0,1,0,0},
	{1,0,0,1,0,0,1,0,1,0},
	{1,1,1,0,0,1,1,1,1,1},
	{1,0,0,1,0,1,0,0,0,1},
	{1,1,1,0,0,1,0,0,0,1},
	{RED2,RED2}
	};
	prt[BABA] = BABA0;

	//18
	static unsigned char flag0[12][10] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,1,1,1,0},
	{0,0,1,1,1,1,1,1,1,1},
	{0,0,1,1,1,1,1,1,1,1},
	{0,0,1,1,1,1,1,1,1,1},
	{0,0,1,1,1,1,0,0,0,1},
	{0,0,1,0,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0,0,0},
	{1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{YELLOW2,YELLOW2}
	};
	prt[flag] = flag0;

	//19
	static unsigned char FLAG0[12][10] = {
	{0,1,1,1,1,0,1,0,0,0},
	{0,1,0,0,0,0,1,0,0,0},
	{0,1,1,1,0,0,1,0,0,0},
	{0,1,0,0,0,0,1,0,0,0},
	{0,1,0,0,0,0,1,1,1,1},
	{0,0,1,0,0,0,0,1,1,0},
	{0,1,0,1,0,0,1,0,0,0},
	{1,1,1,1,1,0,1,0,1,1},
	{1,0,0,0,1,0,1,0,0,1},
	{1,0,0,0,1,0,0,1,1,0},
	{YELLOW2,YELLOW2}
	};
	prt[FLAG] = FLAG0;

	//20
	static unsigned char rock0[12][10] = {
	{0,0,1,1,1,1,1,1,0,0},
	{0,1,1,1,1,1,1,1,1,0},
	{1,2,1,1,1,1,1,1,1,1},
	{1,1,2,2,2,1,1,1,1,2},
	{1,1,1,1,1,1,2,2,2,1},
	{1,2,1,1,1,1,1,1,1,1},
	{1,1,2,2,2,2,2,1,1,1},
	{1,1,1,1,1,1,1,1,2,1},
	{0,1,1,1,1,2,2,2,1,0},
	{0,0,1,1,1,1,1,1,0,0},
	{YELLOW1,YELLOW1,1,GRAY2,GRAY2}
	};
	prt[rock] = rock0;

	//21
	static unsigned char ROCK0[12][10] = {
	{1,1,1,0,0,0,1,1,0,0},
	{1,0,0,1,0,1,0,0,1,0},
	{1,1,1,0,0,1,0,0,1,0},
	{1,0,1,0,0,1,0,0,1,0},
	{1,0,0,1,0,0,1,1,0,0},
	{0,1,1,0,0,1,0,0,1,0},
	{1,0,0,1,0,1,0,1,0,0},
	{1,0,0,0,0,1,1,0,0,0},
	{1,0,0,1,0,1,0,1,0,0},
	{0,1,1,0,0,1,0,0,1,0},
	{YELLOW1,YELLOW1}
	};
	prt[ROCK] = ROCK0;

	//23
	static unsigned char wall0[12][10] = {
	{0,1,2,2,2,2,2,2,1,0},
	{1,2,1,1,1,1,1,1,2,1},
	{1,1,2,2,2,2,2,2,1,1},
	{1,1,1,1,1,1,1,1,1,1},
	{1,1,2,1,1,1,2,1,1,1},
	{1,1,2,1,1,1,2,1,1,1},
	{2,1,1,1,2,1,1,1,2,1},
	{2,1,1,1,2,1,1,1,2,1},
	{1,1,2,1,1,1,2,1,1,1},
	{1,1,2,1,1,1,2,1,1,1},
	{GRAY1,GRAY1,1,GRAY2,GRAY2}
	};
	prt[wall] = wall0;

	//23
	static unsigned char WALL0[12][10] = {
	{1,0,0,0,1,0,0,1,0,0},
	{1,0,0,0,1,0,1,0,1,0},
	{1,0,1,0,1,1,1,1,1,1},
	{1,0,1,0,1,1,0,0,0,1},
	{0,1,0,1,0,1,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0},
	{1,0,0,0,0,1,0,0,0,0},
	{1,0,0,0,0,1,0,0,0,0},
	{1,0,0,0,0,1,0,0,0,0},
	{1,1,1,1,0,1,1,1,1,0},
	{GRAY2,GRAY2}
	};
	prt[WALL] = WALL0;

	//24
	static unsigned char xxxx0[12][10] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,0,1,0,1,0},
	{0,0,1,0,0,0,0,1,0,0},
	{0,1,0,1,0,0,1,0,1,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,0,1,0,0,1,0,1,0},
	{0,0,1,0,0,0,0,1,0,0},
	{0,1,0,1,0,0,1,0,1,0},
	{0,0,0,0,0,0,0,0,0,0},
	{RED2,RED2}
	};
	prt[xxxx] = xxxx0;

	//25
	static unsigned char XXXX0[12][10] = {
	{0,0,0,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0,1,0},
	{0,0,1,0,0,0,0,1,0,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,1,0,0,0,0,1,0,0},
	{0,1,0,0,0,0,0,0,1,0},
	{0,0,0,0,0,0,0,0,0,0},
	{RED2,RED2}
	};
	prt[XXXX] = XXXX0;

	//26
	static unsigned char star0[12][10] = {
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{1,1,1,1,1,1,1,1,1,1},
	{0,1,1,1,1,1,1,1,1,0},
	{0,0,1,1,1,1,1,1,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,0,0},
	{0,1,1,1,0,0,1,1,1,0},
	{0,1,0,0,0,0,0,0,1,0},
	{YELLOW1,YELLOW1}
	};
	prt[star] = star0;

	//27
	static unsigned char STAR0[12][10] = {
	{0,1,1,1,0,1,1,1,1,1},
	{1,0,0,0,0,0,0,1,0,0},
	{0,1,1,0,0,0,0,1,0,0},
	{0,0,0,1,0,0,0,1,0,0},
	{1,1,1,0,0,0,0,1,0,0},
	{0,0,1,0,0,0,1,1,1,0},
	{0,1,0,1,0,0,1,0,0,1},
	{1,1,1,1,1,0,1,1,1,0},
	{1,0,0,0,1,0,1,0,1,0},
	{1,0,0,0,1,0,1,0,0,1},
	{YELLOW1,YELLOW1}
	};
	prt[STAR] = STAR0;

	//128
	static unsigned char YOU0[12][10] = {
	{0,1,1,1,1,1,1,1,1,0},
	{2,1,2,1,1,1,2,1,1,2},
	{2,1,2,1,1,1,2,1,1,2},
	{2,1,2,1,1,1,2,1,1,2},
	{1,2,2,1,1,1,2,1,1,2},
	{1,2,1,1,2,2,1,2,2,1},
	{1,2,1,2,1,1,2,1,1,1},
	{1,2,1,2,1,1,2,1,1,1},
	{1,1,1,1,2,2,1,1,1,1},
	{0,1,1,1,1,1,1,1,1,0},
	{RED2,RED2,1,BLACK,RED2}
	};
	prt[YOU] = YOU0;

	//129
	static unsigned char WIN0[12][10] = {
	{0,1,1,1,1,1,1,1,1,0},
	{1,1,1,1,2,2,2,1,1,1},
	{1,1,1,1,1,2,1,1,1,1},
	{2,1,1,1,2,2,2,1,1,2},
	{2,1,1,1,2,2,2,2,1,2},
	{2,1,2,1,2,2,2,1,2,2},
	{2,1,2,1,2,2,2,1,1,2},
	{1,2,1,2,1,2,1,1,1,1},
	{1,1,1,1,2,2,2,1,1,1},
	{0,1,1,1,1,1,1,1,1,0},
	{YELLOW2,YELLOW2,1,BLACK,YELLOW2}
	};
	prt[WIN] = WIN0;


	//130
	static unsigned char STOP0[12][10] = {
	{0,2,2,2,1,2,2,2,2,0},
	{2,1,1,1,1,1,1,2,1,1},
	{1,2,2,1,1,1,1,2,1,1},
	{1,1,1,2,1,1,1,2,1,1},
	{2,2,2,1,1,1,1,2,1,1},
	{1,1,2,2,1,1,2,2,2,1},
	{1,2,1,1,2,1,2,1,1,2},
	{1,2,1,1,2,1,2,2,2,1},
	{1,2,1,1,2,1,2,1,1,1},
	{0,1,2,2,1,1,2,1,1,0},
	{GREEN1,GREEN1,1,BLACK,GREEN1}
	};
	prt[STOP] = STOP0;


	//131
	static unsigned char PUSH0[12][10] = {
	{0,2,2,2,1,2,1,1,2,0},
	{1,2,1,1,2,2,1,1,2,1},
	{1,2,2,2,1,2,1,1,2,1},
	{1,2,1,1,1,2,1,1,2,1},
	{1,2,1,1,1,1,2,2,1,1},
	{1,1,2,2,2,1,2,1,1,2},
	{1,2,1,1,1,1,2,1,1,2},
	{1,1,2,2,1,1,2,2,2,2},
	{1,1,1,1,2,1,2,1,1,2},
	{0,2,2,2,1,1,2,1,1,0},
	{YELLOW1,YELLOW1,1,BLACK,YELLOW1}
	};
	prt[PUSH] = PUSH0;

	static unsigned char LOSE0[12][10] = {
	{0,2,1,1,1,1,2,2,1,0},
	{1,2,1,1,1,2,1,1,2,1},
	{1,2,1,1,1,2,1,1,2,1},
	{1,2,1,1,1,2,1,1,2,1},
	{1,2,2,2,2,1,2,2,1,1},
	{1,1,2,2,2,1,2,2,2,1},
	{1,2,1,1,1,1,2,1,1,1},
	{1,1,2,2,1,1,2,2,2,1},
	{1,1,1,1,2,1,2,1,1,1},
	{0,2,2,2,1,1,2,2,2,0},
	{BLUE1,BLUE1,1,BLACK,BLUE1}
	};
	prt[LOSE] = LOSE0;

	//255
	static unsigned char select0[12][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1},
	{WHITE,WHITE}
	};
	prt[select] = select0;

}

void draw(int x, int y, int i) {
	textcolor(*((prt[i] + 10 * col) + 0), *((prt[i] + 10 * col) + 1));
	int realx = 0, realy = 0;
	x *= col;
	y *= span;
	for (realx = 0;realx < 10;realx++) {
		for (realy = 0;realy < 10;realy++) {
			if ((*((prt[i] + realy * col) + realx)) == 1) {
				gotoxy(x + realx, y + realy);
				printf("@");
			}
		}
	}
	if (*((prt[i] + 10 * col) + 2)) {
		textcolor(*((prt[i] + 10 * col) + 3), *((prt[i] + 10 * col) + 4));
		for (realx = 0;realx < 10;realx++) {
			for (realy = 0;realy < 10;realy++) {
				if ((*((prt[i] + realy * col) + realx)) == 2) {
					gotoxy(x + realx, y + realy);
					printf("@");
				}
			}
		}
	}
	textcolor(WHITE, BLACK);
}

void removeCursor(void) { // 커서를 안보이게 한다

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}
// 화면 지우기고 원하는 배경색으로 설정한다.
void cls(int bg_color, int text_color)
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);

}

void remove_pix(int x, int y) {
	textcolor(15, 0);
	int realx = x * col;
	int realy = y * span;
	
	gotoxy(realx, realy++);printf("          ");
	gotoxy(realx, realy++);printf("          ");
	gotoxy(realx, realy++);printf("          ");
	gotoxy(realx, realy++);printf("          ");
	gotoxy(realx, realy++);printf("          ");
	gotoxy(realx, realy++);printf("          ");
	gotoxy(realx, realy++);printf("          ");
	gotoxy(realx, realy++);printf("          ");
	gotoxy(realx, realy++);printf("          ");
	gotoxy(realx, realy++);printf("          ");

}

void move(int x_1, int y_1, int i, char ch) {
	struct point del[768];
	int count = 0;
	int widthi, heighti;
	switch (ch) {
	case UP:
		for (widthi = 0;widthi < WIDTH;widthi++) {
			for (heighti = 0;heighti < HEIGHT;heighti++) {
				if (screen[3][widthi][heighti]) {
					draw(widthi, heighti - 1, screen[3][widthi][heighti]);
					screen[3][widthi][heighti - 1] = screen[3][widthi][heighti];
					screen[3][widthi][heighti] = 0;
					del[count].x = widthi;
					del[count++].y = heighti;
				}
			}
		}
		break;
	case DOWN:
		for (widthi = 0;widthi < WIDTH;widthi++) {
			for (heighti = HEIGHT - 1;heighti >= 0;heighti--) {
				if (screen[3][widthi][heighti]) {
					draw(widthi, heighti + 1, screen[3][widthi][heighti]);
					screen[3][widthi][heighti + 1] = screen[3][widthi][heighti];
					screen[3][widthi][heighti] = 0;
					del[count].x = widthi;
					del[count++].y = heighti;
				}
			}
		}
		break;
	case LEFT:
		for (widthi = 0;widthi < WIDTH;widthi++) {
			for (heighti = 0;heighti < HEIGHT;heighti++) {
				if (screen[3][widthi][heighti]) {
					draw(widthi - 1, heighti, screen[3][widthi][heighti]);
					screen[3][widthi - 1][heighti] = screen[3][widthi][heighti];
					screen[3][widthi][heighti] = 0;
					del[count].x = widthi;
					del[count++].y = heighti;
				}
			}
		}
		break;
	case RIGHT:
		for (widthi = WIDTH - 1;widthi >= 0;widthi--) {
			for (heighti = 0;heighti < HEIGHT;heighti++) {
				if (screen[3][widthi][heighti]) {
					draw(widthi + 1, heighti, screen[3][widthi][heighti]);
					screen[3][widthi + 1][heighti] = screen[3][widthi][heighti];
					screen[3][widthi][heighti] = 0;
					del[count].x = widthi;
					del[count++].y = heighti;
				}
			}
		}
		break;
	}
}

void change_condition(int object, int state,int num) {
	*((prt[object] + ((state - 128) / 10 + 11) * col) + (state - 128) % 10) = num;
}

void print_state() {
	FILE *outfile;
	outfile = fopen("state.txt", "w");
	fprintf(outfile, "\nIS \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ",*((prt[IS] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nbaba \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[baba] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nBABA \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[BABA] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nflag \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[flag] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nFLAG \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[FLAG] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nrock \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[rock] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nROCK \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[ROCK] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nwall \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[wall] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nWALL \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[WALL] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nxxxx \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[xxxx] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nXXXX \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[XXXX] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nstar \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[star] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nSTAR \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[STAR] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nYOU \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[YOU] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nWIN \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[WIN] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	fprintf(outfile, "\nSTOP \n");
	for (int i = 0;i < 12;i++) {
		for (int k = 0;k < 10;k++) {
			fprintf(outfile, "%d ", *((prt[STOP] + i * col) + k));
		}
		fprintf(outfile, "\n");
	}
	for (int layeri = 0;layeri < LAYER;layeri++){
		fprintf(outfile, "\n%d\n",layeri);
		for (int heighti = 0;heighti < HEIGHT;heighti++) {
			for (int widthi = 0;widthi < WIDTH;widthi++) {
				fprintf(outfile, "%3d",screen[layeri][widthi][heighti]);
			}
			fprintf(outfile, "\n");
		}
	}
	

	//fprintf(outfile, "");
	fclose(outfile);

}

void check_state() {
	int widthi, heighti;
	static struct point condition[128]; // x : data number, y: 조건번호
	static int count_condition=1;


	// 조건 읽고쓰기

	// 이전조건 지우기
	while (--count_condition) {
		change_condition(condition[count_condition].x, condition[count_condition].y, 0);
		//*((prt[condition[count_condition].x] + ((condition[count_condition].y - 128) / 10) * col) + ((condition[count_condition].y - 128) % 10)) = 0;
	}
	count_condition = 1;
	// 객체 데이터를 수정하기
	for (widthi = 0;widthi < WIDTH;widthi++) {
		for (heighti = 0;heighti < HEIGHT;heighti++) {
			if (screen[LAYER_TEXT][widthi][heighti] == IS) {
				if (widthi > 0 && (widthi < (WIDTH - 1) ) ) {
					if ( screen[LAYER_TEXT][widthi - 1][heighti] < 128 && screen[LAYER_TEXT][widthi - 1][heighti] >= 16 && screen[LAYER_TEXT][widthi - 1][heighti] % 2) { //IS 왼쪽에 16이상 128미만 홀수인 데이터 (TEXT) 가 있을경우
						if (screen[LAYER_TEXT][widthi + 1][heighti] >= 128) { // IS 오른쪽에 상태가 있을경우
							change_condition(screen[LAYER_TEXT][widthi - 1][heighti] - 1, screen[LAYER_TEXT][widthi + 1][heighti],1);
							//change_layer(screen[LAYER_TEXT][widthi - 1][heighti] - 1, screen[LAYER_TEXT][widthi + 1][heighti]);
							//*((prt[screen[LAYER_TEXT][widthi - 1][heighti]-1] + (((screen[LAYER_TEXT][widthi + 1][heighti] - 128) / 10) + 11) * col) + (screen[LAYER_TEXT][widthi + 1][heighti] - 128) % 10) = 1;
							condition[count_condition].x = screen[LAYER_TEXT][widthi - 1][heighti] - 1;
							condition[count_condition].y = screen[LAYER_TEXT][widthi + 1][heighti];
							count_condition += 1;
						}
						else if (screen[LAYER_TEXT][widthi + 1][heighti] < 128 && screen[LAYER_TEXT][widthi + 1][heighti] >= 16 && screen[LAYER_TEXT][widthi + 1][heighti] % 2) {
							for (int l = 0;l < LAYER;l++) {
								for (int w = 0;w < WIDTH;w++) {
									for (int h=0;h < HEIGHT;h++) {
										if (screen[l][w][h] == screen[LAYER_TEXT][widthi - 1][heighti] - 1) {
											screen[l][w][h] = screen[LAYER_TEXT][widthi + 1][heighti] - 1;
											redraw = 1;
										}
									}
								}
							}
						}
						/*else if (screen[LAYER_TEXT][widthi + 1][heighti] < 128 && screen[LAYER_TEXT][widthi + 1][heighti] >= 16) {
							for (int layeri = 0;layeri < LAYER;layeri++) {
								for (int widthi = 0;widthi < WIDTH;widthi++) {
									for (int heighti = 0;heighti < HEIGHT;heighti++) {
										if (screen[layeri][widthi][heighti] == screen[LAYER_TEXT][widthi - 1][heighti] - 1) {
											screen[layeri][widthi][heighti] = 0;
											screen[layeri][widthi][heighti] = screen[LAYER_TEXT][widthi + 1][heighti] - 1;
											screen[*((prt[screen[LAYER_TEXT][widthi - 1][heighti] - 1] + 11 * col) + 0)][widthi][heighti] = 0;
											screen[*((prt[screen[LAYER_TEXT][widthi + 1][heighti] - 1] + 11 * col) + 0)][widthi][heighti] = screen[LAYER_TEXT][widthi + 1][heighti] - 1;
										}
									}
								}
							}*/
						
						//}
					}
				}

				if (heighti > 0 && (heighti < (HEIGHT - 2) ) ) {
					if (screen[LAYER_TEXT][widthi][heighti-1] < 128 && screen[LAYER_TEXT][widthi][heighti - 1] >= 16 && screen[LAYER_TEXT][widthi][heighti - 1] % 2) { //IS 위에 16이상 128미만 홀수인 데이터 (TEXT) 가 있을경우
						if (screen[LAYER_TEXT][widthi][heighti + 1] >= 128) { // IS 아래에 상태가 있을경우
							change_condition(screen[LAYER_TEXT][widthi][heighti - 1] - 1, screen[LAYER_TEXT][widthi][heighti + 1], 1);
							//change_layer(screen[LAYER_TEXT][widthi][heighti - 1] - 1, screen[LAYER_TEXT][widthi][heighti + 1]);
							//*((prt[screen[LAYER_TEXT][widthi][heighti + 1] - 1] + (((screen[LAYER_TEXT][widthi][heighti - 1] - 127) / 10) + 11) * col) + (screen[LAYER_TEXT][widthi][heighti - 1] - 127) % 10) = 1;
							condition[count_condition].x = screen[LAYER_TEXT][widthi][heighti - 1] - 1;
							condition[count_condition].y = screen[LAYER_TEXT][widthi][heighti + 1];
							count_condition += 1;
						}
						else if (screen[LAYER_TEXT][widthi][heighti + 1] < 128 && screen[LAYER_TEXT][widthi][heighti + 1] >= 16 && screen[LAYER_TEXT][widthi][heighti + 1] % 2) {
							for (int l = 0;l < LAYER;l++) {
								for (int w = 0;w < WIDTH;w++) {
									for (int h = 0;h < HEIGHT;h++) {
										if (screen[l][w][h] == screen[LAYER_TEXT][widthi][heighti - 1] - 1) {
											screen[l][w][h] = screen[LAYER_TEXT][widthi][heighti + 1] - 1;
											redraw = 1;
										}
									}
								}
							}
						}
						/*else if (screen[LAYER_TEXT][widthi][heighti - 1] < 128 && screen[LAYER_TEXT][widthi][heighti - 1] >= 16) {

							for (widthi = 0;widthi < WIDTH;widthi++) {
								for (heighti = 0;heighti < HEIGHT;heighti++) {
									if (screen[*((prt[screen[LAYER_TEXT][widthi][heighti + 1] - 1] + 11 * col) + 0)][widthi][heighti] == screen[LAYER_TEXT][widthi][heighti + 1] - 1) {
										screen[*((prt[screen[LAYER_TEXT][widthi][heighti + 1] - 1] + 11 * col) + 0)][widthi][heighti] = 0;
										screen[*((prt[screen[LAYER_TEXT][widthi][heighti - 1] - 1] + 11 * col) + 0)][widthi][heighti] = screen[LAYER_TEXT][widthi][heighti - 1] - 1;
									}

								}
							}

						}*/
					}
				}
			}
		}
	}
	for (int i = baba;i < STAR;i += 2) {
		change_layer(i);
	}
}

int ismoveable(int x, int y, unsigned char ch) {
	int tmp = moveable(x, y, ch);
	/*if (tmp >= (WIDTH + HEIGHT)) {
		int t = 0;
		return 0;
	}
	else tmp;*/
	return (tmp >= (WIDTH + HEIGHT)) ? 0 : tmp;
}

int moveable(int x,int y, unsigned char ch) {
	struct point vector = { 0 };
	switch (ch) {
	case UP:
		vector.y = -1;
		break;
	case DOWN:
		vector.y = 1;
		break;
	case LEFT:
		vector.x = -1;
		break;
	case RIGHT:
		vector.x = 1;
		break;
	}
	if (x + vector.x >= 0 && x + vector.x < WIDTH && y + vector.y >= 0 && y + vector.y < HEIGHT) {
		if (screen[1][x + vector.x][y + vector.y]/* || screen[2][x + vector.x][y + vector.y]*/) {
			int t = STOP;
			if (*((prt[screen[1][x + vector.x][y + vector.y]] + ((t - 128) / 10 + 11) * col) + (t - 128) % 10)) {
				return WIDTH + HEIGHT;
			}
			t = PUSH;
			if (*((prt[screen[1][x + vector.x][y + vector.y]] + ((t - 128) / 10 + 11) * col) + (t - 128) % 10)) {
				return moveable(x + vector.x, y + vector.y, ch) + 1;
				/*int tmp = ismoveable(x + vector.x, y + vector.y, ch);
				return tmp*(tmp+1);*/
			}
			/*if (screen[2][x + vector.x][y + vector.y]) {
				return 1;
			}*/
			//printf("moveable error\nmoveable error\nmoveable error\nmoveable error\nmoveable error\nmoveable error\nmoveable error\nmoveable error\nmoveable error\nmoveable error\nmoveable error\n");
		}
		if (screen[2][x + vector.x][y + vector.y]) {
			return moveable(x + vector.x, y + vector.y, ch) + 1;
		}
		else {
			return 1;
		}
	}
	else
		return WIDTH + HEIGHT;
}

int change_layer(int data) {
	/*if (*((prt[data] + ((t - 128) / 10 + 11) * col) + (t - 128) % 10) == 1 && condition != YOU)
		return 0;*/
	int layer = 0;
	if (*((prt[data] + ((YOU - 128) / 10 + 11) * col) + (YOU - 128) % 10) == 1)
		layer = LAYER_YOU;
	else if (*((prt[data] + ((PUSH - 128) / 10 + 11) * col) + (PUSH - 128) % 10) == 1)
		layer = LAYER_PUSH_STOP;
	else if (*((prt[data] + ((STOP - 128) / 10 + 11) * col) + (STOP - 128) % 10) == 1)
		layer = LAYER_PUSH_STOP;
	else
		layer = 0;
	/*switch (condition) {
	case YOU:
		layer = LAYER_YOU;
		break;
	case STOP:
		layer = LAYER_PUSH_STOP;
		break;
	case PUSH:
		layer = LAYER_PUSH_STOP;
		break;
	default :
		return 0;
	}*/
	/*for (int widthi = 0;widthi < WIDTH;widthi++) {
		for (int heighti = 0;heighti < HEIGHT;heighti++) {
			if (screen[layer][widthi][heighti] == data)
				return 0;
		}
	}*/
	for (int layeri = 0;layeri < LAYER;layeri++) {
		if (layer == layeri) {
			layeri++;
		}
		/*if (LAYER_TEXT == layeri) {
			layeri++;
		}*/
		if (layeri >= LAYER) {
			break;
		}
		for (int widthi = 0;widthi < WIDTH;widthi++) {
			for (int heighti = 0;heighti < HEIGHT;heighti++) {
				if (screen[layeri][widthi][heighti] == data) {
					screen[layer][widthi][heighti] = screen[layeri][widthi][heighti];
					screen[layeri][widthi][heighti] = 0;
				}
			}
		}
	}
}

int iswin() {
	for (int x = 0;x < WIDTH;x++) {
		for (int y = 0;y < HEIGHT;y++) {
			if (screen[LAYER_YOU][x][y]) {
				for (int l = 0;l < LAYER;l++) {
					if (screen[l][x][y]) {
						if (*((prt[screen[l][x][y]] + ((WIN - 128) / 10 + 11) * col) + (WIN - 128) % 10)) {
							return 1;
						}
						else if (*((prt[screen[l][x][y]] + ((LOSE - 128) / 10 + 11) * col) + (LOSE - 128) % 10)) {
							screen[LAYER_YOU][x][y] = 0;
							redraw = 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

void reset_level() {
	cls(BLACK, WHITE);
	for (int l=0;l < LAYER;l++) {
		for (int x = 0;x < WIDTH;x++) {
			for (int y = 0;y < HEIGHT;y++) {
				screen[l][x][y] = 0;
			}
		}
	}
}

void reset_plevel() {
	for (int l = 0;l < LAYER;l++) {
		for (int x = 0;x < WIDTH;x++) {
			for (int y = 0;y < HEIGHT;y++) {
				screen_p[l][x][y] = 0;
			}
		}
	}
}

void set_level_0() {
	reset_level();
	screen[2][18][4] = BABA;
	screen[2][19][4] = IS;
	screen[2][20][4] = YOU;

	screen[2][26][4] = FLAG;
	screen[2][27][4] = IS;
	screen[2][28][4] = WIN;

	screen[2][18][12] = WALL;
	screen[2][19][12] = IS;
	screen[2][20][12] = STOP;

	screen[2][26][12] = ROCK;
	screen[2][27][12] = IS;
	screen[2][28][12] = PUSH;

	screen[2][33][8] = XXXX;
	screen[2][34][8] = IS;
	screen[2][35][8] = LOSE;

	screen[0][18][6] = wall;
	screen[0][19][6] = wall;
	screen[0][20][6] = wall;
	screen[0][21][6] = wall;
	screen[0][22][6] = wall;
	screen[0][23][6] = wall;
	screen[0][24][6] = wall;
	screen[0][25][6] = wall;
	screen[0][26][6] = wall;
	screen[0][27][6] = wall;
	screen[0][28][6] = wall;

	screen[0][18][10] = wall;
	screen[0][19][10] = wall;
	screen[0][20][10] = wall;
	screen[0][21][10] = wall;
	screen[0][22][10] = wall;
	screen[0][23][10] = wall;
	screen[0][24][10] = wall;
	screen[0][25][10] = wall;
	screen[0][26][10] = wall;
	screen[0][27][10] = wall;
	screen[0][28][10] = wall;

	screen[0][23][7] = rock;
	screen[0][23][8] = rock;
	screen[0][23][9] = rock;

	screen[0][10][7] = xxxx;
	screen[0][10][8] = xxxx;
	screen[0][10][9] = xxxx;

	screen[3][19][8] = baba;
	screen[0][27][8] = flag;
}

void set_level_1() {
	reset_level();
	screen[LAYER_TEXT][25][2] = IS;
	screen[LAYER_TEXT][28][4] = WIN;
	screen[LAYER_TEXT][21][6] = FLAG;
	screen[LAYER_TEXT][20][10] = BABA;
	screen[LAYER_TEXT][20][11] = IS;
	screen[LAYER_TEXT][20][12] = YOU;
	screen[LAYER_TEXT][25][10] = WALL;
	screen[LAYER_TEXT][25][11] = IS;
	screen[LAYER_TEXT][25][12] = STOP;

	screen[0][25][6] = flag;
	screen[0][28][11] = baba;

	screen[0][23][0] = wall;
	screen[0][24][0] = wall;
	screen[0][25][0] = wall;
	screen[0][26][0] = wall;
	screen[0][27][0] = wall;
	screen[0][28][0] = wall;
	screen[0][29][0] = wall;
	screen[0][30][0] = wall;
	screen[0][30][1] = wall;
	screen[0][30][2] = wall;
	screen[0][30][3] = wall;
	screen[0][30][4] = wall;
	screen[0][30][5] = wall;
	screen[0][30][6] = wall;
	screen[0][30][7] = wall;
	screen[0][30][8] = wall;
	screen[0][30][9] = wall;
	screen[0][30][10] = wall;
	screen[0][30][11] = wall;
	screen[0][30][12] = wall;
	screen[0][30][13] = wall;
	screen[0][30][14] = wall;
	screen[0][29][14] = wall;
	screen[0][28][14] = wall;
	screen[0][27][14] = wall;
	screen[0][26][14] = wall;
	screen[0][25][14] = wall;
	screen[0][24][14] = wall;
	screen[0][23][14] = wall;
	screen[0][23][13] = wall;
	screen[0][23][12] = wall;
	screen[0][23][11] = wall;
	screen[0][23][10] = wall;
	screen[0][23][9] = wall;
	screen[0][23][8] = wall;
	/*screen[0][23][7] = wall;
	screen[0][23][6] = wall;*/
	screen[0][24][8] = wall;
	screen[0][25][8] = wall;
	screen[0][26][8] = wall;
	screen[0][27][8] = wall;
	screen[0][28][8] = wall;
	screen[0][29][8] = wall;
	screen[0][22][8] = wall;
	screen[0][21][8] = wall;
	screen[0][20][8] = wall;
	screen[0][19][8] = wall;
	screen[0][19][7] = wall;
	screen[0][19][6] = wall;
	screen[0][19][5] = wall;
	screen[0][19][4] = wall;
	screen[0][20][4] = wall;
	screen[0][21][4] = wall;
	screen[0][22][4] = wall;
	screen[0][23][4] = wall;
	screen[0][23][3] = wall;
	screen[0][23][2] = wall;
	screen[0][23][1] = wall;

}

void set_level_2() {
	reset_level();

	screen[LAYER_TEXT][25][2] = IS;
	screen[LAYER_TEXT][28][4] = WIN;
	screen[LAYER_TEXT][21][6] = BABA;
	screen[LAYER_TEXT][20][10] = WALL;
	screen[LAYER_TEXT][20][11] = IS;
	screen[LAYER_TEXT][20][12] = YOU;
	screen[LAYER_TEXT][25][10] = FLAG;
	screen[LAYER_TEXT][25][11] = IS;
	screen[LAYER_TEXT][25][12] = STOP;

	screen[0][28][11] = wall;

	screen[0][23][0] = flag;
	screen[0][24][0] = flag;
	screen[0][25][0] = flag;
	screen[0][26][0] = flag;
	screen[0][27][0] = flag;
	screen[0][28][0] = flag;
	screen[0][29][0] = flag;
	screen[0][30][0] = flag;
	screen[0][30][1] = flag;
	screen[0][30][2] = flag;
	screen[0][30][3] = flag;
	screen[0][30][4] = flag;
	screen[0][30][5] = flag;
	screen[0][30][6] = flag;
	screen[0][30][7] = flag;
	screen[0][30][8] = flag;
	screen[0][30][9] = flag;
	screen[0][30][10] = flag;
	screen[0][30][11] = flag;
	screen[0][30][12] = flag;
	screen[0][30][13] = flag;
	screen[0][26][13] = flag;
	screen[0][29][13] = flag;
	screen[0][28][13] = flag;
	screen[0][27][13] = flag;
	screen[0][26][13] = flag;
	screen[0][25][14] = flag;
	screen[0][24][14] = flag;
	screen[0][23][14] = flag;
	screen[0][23][13] = flag;
	screen[0][23][12] = flag;
	screen[0][23][11] = flag;
	screen[0][23][10] = flag;
	screen[0][23][9] = flag;
	screen[0][23][8] = flag;
	/*screen[0][23][7] = flag;
	screen[0][23][6] = flag;*/
	screen[0][24][8] = flag;
	screen[0][25][8] = flag;
	screen[0][26][8] = flag;
	screen[0][27][8] = flag;
	screen[0][28][8] = flag;
	screen[0][29][8] = flag;
	screen[0][22][8] = flag;
	screen[0][21][8] = flag;
	screen[0][20][8] = flag;
	screen[0][19][8] = flag;
	screen[0][19][7] = flag;
	screen[0][19][6] = flag;
	screen[0][19][5] = flag;
	screen[0][19][4] = flag;
	screen[0][20][4] = flag;
	screen[0][21][4] = flag;
	screen[0][22][4] = flag;
	screen[0][23][4] = flag;
	screen[0][23][3] = flag;
	screen[0][23][2] = flag;
	screen[0][23][1] = flag;
}

void set_level_3() {
	reset_level();

	screen[LAYER_TEXT][0][0] = FLAG;
	screen[LAYER_TEXT][1][0] = IS;
	screen[LAYER_TEXT][2][0] = WIN;
	screen[LAYER_TEXT][0][1] = BABA;
	screen[LAYER_TEXT][1][1] = IS;
	screen[LAYER_TEXT][2][1] = YOU;
	screen[LAYER_TEXT][13][7] = ROCK;
	screen[LAYER_TEXT][14][7] = IS;
	screen[LAYER_TEXT][15][7] = PUSH;
	screen[LAYER_TEXT][26][7] = XXXX;
	screen[LAYER_TEXT][26][8] = IS;
	screen[LAYER_TEXT][26][9] = LOSE;

	screen[0][14][15] = xxxx;
	screen[0][14][14] = xxxx;
	screen[0][14][13] = xxxx;
	screen[0][14][12] = xxxx;
	screen[0][14][11] = xxxx;

	screen[0][20][15] = xxxx;
	screen[0][20][14] = xxxx;
	screen[0][20][13] = xxxx;
	screen[0][20][12] = xxxx;
	screen[0][20][11] = xxxx;

	screen[0][15][11] = xxxx;
	screen[0][16][11] = xxxx;
	screen[0][18][11] = xxxx;
	screen[0][19][11] = xxxx;

	screen[0][16][10] = xxxx;
	screen[0][16][9] = xxxx;
	screen[0][18][10] = xxxx;
	screen[0][18][9] = xxxx;

	screen[0][17][10] = rock;
	screen[0][17][11] = rock;
	screen[0][17][12] = rock;

	screen[0][17][14] = baba;
	screen[0][29][11] = flag;

	for (int i = 0;i < 9;i++) {
		screen[0][24 + i][5] = xxxx;
		screen[0][24 + i][13] = xxxx;
	}
	for (int i = 0;i < 7;i++) {
		screen[0][24][6 + i] = xxxx;
		screen[0][32][6 + i] = xxxx;
	}

}

void set_level_4() {
	reset_level();
	screen[LAYER_TEXT][0][1] = ROCK;
	screen[LAYER_TEXT][1][1] = IS;
	screen[LAYER_TEXT][2][1] = STOP;
	screen[LAYER_TEXT][0][3] = XXXX;
	screen[LAYER_TEXT][1][3] = IS;
	screen[LAYER_TEXT][2][3] = LOSE;
	screen[LAYER_TEXT][0][5] = FLAG;
	screen[LAYER_TEXT][1][5] = IS;
	screen[LAYER_TEXT][2][5] = WIN;
	screen[LAYER_TEXT][24][9] = WALL;
	screen[LAYER_TEXT][25][9] = IS;
	screen[LAYER_TEXT][26][9] = STOP;
	screen[LAYER_TEXT][20][10] = BABA;
	screen[LAYER_TEXT][20][11] = IS;
	screen[LAYER_TEXT][20][12] = YOU;

	screen[0][4][7] = rock;
	screen[0][4][6] = rock;
	screen[0][4][5] = rock;
	screen[0][4][4] = rock;
	screen[0][4][3] = rock;
	screen[0][4][2] = rock;
	screen[0][4][1] = rock;
	screen[0][4][0] = rock;
	screen[0][3][7] = rock;
	screen[0][2][7] = rock;
	screen[0][1][7] = rock;
	screen[0][0][7] = rock;

	screen[0][18][4] = wall;
	screen[0][19][4] = wall;
	screen[0][20][4] = wall;
	screen[0][21][4] = wall;
	screen[0][22][4] = wall;
	screen[0][22][5] = wall;
	screen[0][22][3] = wall;
	screen[0][22][2] = wall;
	screen[0][22][1] = wall;
	screen[0][23][1] = wall;
	screen[0][25][1] = wall;
	screen[0][26][1] = wall;
	screen[0][27][1] = wall;
	screen[0][27][2] = wall;
	screen[0][28][1] = wall;
	screen[0][29][1] = wall;
	screen[0][30][1] = wall;
	screen[0][31][1] = wall;
	screen[0][31][2] = wall;
	screen[0][31][3] = wall;
	screen[0][31][4] = wall;
	screen[0][31][5] = wall;
	screen[0][30][5] = wall;
	screen[0][29][5] = wall;
	screen[0][28][5] = wall;
	screen[0][27][5] = wall;
	screen[0][27][4] = wall;
	screen[0][27][6] = wall;
	screen[0][26][6] = wall;
	screen[0][25][6] = wall;
	screen[0][27][8] = wall;
	screen[0][27][9] = wall;
	screen[0][27][10] = wall;
	screen[0][27][11] = wall;
	screen[0][26][11] = wall;
	screen[0][25][11] = wall;
	screen[0][24][11] = wall;
	screen[0][23][11] = wall;
	screen[0][22][11] = wall;
	screen[0][22][10] = wall;
	screen[0][22][9] = wall;
	screen[0][22][8] = wall;
	screen[0][22][7] = wall;
	screen[0][21][8] = wall;
	screen[0][20][8] = wall;
	screen[0][19][8] = wall;
	screen[0][18][8] = wall;
	screen[0][18][7] = wall;
	screen[0][18][6] = wall;
	screen[0][18][5] = wall;

	for (int i = 0;i < 8;i++) {
		screen[0][24][i] = xxxx;
	}
	for (int i = 0;i < 23;i++) {
		screen[0][25+i][7] = xxxx;
	}
	screen[0][29][3] = flag;
	screen[0][20][6] = baba;

	
	

}

void set_level_5() {
	reset_level();
	screen[LAYER_TEXT][19][5] = BABA;
	screen[LAYER_TEXT][20][5] = IS;
	screen[LAYER_TEXT][21][5] = YOU;
	screen[LAYER_TEXT][26][9] = FLAG;
	screen[LAYER_TEXT][28][9] = WIN;
	screen[LAYER_TEXT][47][7] = STAR;
	screen[LAYER_TEXT][47][8] = IS;
	screen[LAYER_TEXT][47][9] = STOP;

	for (int i = 0;i < 14;i++) {
		screen[0][17 + i][3] = wall;
		screen[0][17 + i][12] = wall;
	}
	for (int i = 0;i < 8;i++) {
		screen[0][17][4 + i] = wall;
		screen[0][30][4 + i] = wall;
	}

	screen[0][23][7] = baba;
	screen[0][28][5] = flag;

	screen[0][22][4] = star;
	screen[0][18][6] = star;
	screen[0][25][6] = star;
	screen[0][26][7] = star;
	screen[0][28][7] = star;
	screen[0][27][8] = star;
	screen[0][29][8] = star;
	screen[0][24][8] = star;
	screen[0][18][9] = star;
	screen[0][24][9] = star;
	screen[0][19][10] = star;
	screen[0][24][10] = star;
	screen[0][27][10] = star;
	screen[0][22][11] = star;
	screen[0][25][11] = star;

}

void set_level_6() {
	reset_level();

	screen[LAYER_TEXT][21][5] = BABA;
	screen[LAYER_TEXT][22][5] = IS;
	screen[LAYER_TEXT][23][5] = YOU;
	screen[LAYER_TEXT][29][5] = WIN;
	screen[LAYER_TEXT][21][9] = ROCK;
	screen[LAYER_TEXT][23][9] = PUSH;
	screen[LAYER_TEXT][29][9] = WALL;
	screen[LAYER_TEXT][29][10] = IS;
	screen[LAYER_TEXT][29][11] = STOP;

	for (int i = 17;i < 28;i++) {
		screen[0][i][2] = wall;
		screen[0][i][13] = wall;
	}
	for (int i = 3;i < 14;i++) {
		screen[0][17][i] = wall;
	}
	for (int i = 3;i < 8;i++) {
		screen[0][27][i] = wall;
	}
	for (int i = 7;i < 14;i++) {
		screen[0][30][i] = wall;
	}
	screen[0][28][7] = wall;
	screen[0][29][7] = wall;
	screen[0][28][13] = wall;
	screen[0][29][13] = wall;

	screen[0][21][7] = baba;
	screen[0][23][7] = rock;

}

void set_level_7() {
	reset_level();

	screen[LAYER_TEXT][21][5] = BABA;
	screen[LAYER_TEXT][22][5] = IS;
	screen[LAYER_TEXT][23][5] = YOU;
	screen[LAYER_TEXT][29][5] = WIN;
	screen[LAYER_TEXT][21][9] = ROCK;
	screen[LAYER_TEXT][22][9] = IS;
	screen[LAYER_TEXT][29][9] = WALL;
	screen[LAYER_TEXT][29][10] = IS;
	screen[LAYER_TEXT][29][11] = STOP;

	for (int i = 17;i < 28;i++) {
		screen[0][i][2] = wall;
		screen[0][i][13] = wall;
	}
	for (int i = 3;i < 14;i++) {
		screen[0][17][i] = wall;
	}
	for (int i = 3;i < 8;i++) {
		screen[0][27][i] = wall;
	}
	for (int i = 7;i < 14;i++) {
		screen[0][30][i] = wall;
	}
	screen[0][28][7] = wall;
	screen[0][29][7] = wall;
	screen[0][28][13] = wall;
	screen[0][29][13] = wall;

	screen[0][21][7] = baba;
	screen[0][23][7] = rock;

}

void set_level_error() {
	reset_level();

	screen[LAYER_TEXT][0][0] = FLAG;
	screen[LAYER_TEXT][1][0] = IS;
	screen[LAYER_TEXT][2][0] = WIN;

	screen[LAYER_TEXT][17][3] = ROCK;
	screen[LAYER_TEXT][18][3] = IS;
	screen[LAYER_TEXT][19][3] = PUSH;

	screen[LAYER_TEXT][0][7] = WALL;
	screen[LAYER_TEXT][0][8] = IS;
	screen[LAYER_TEXT][0][9] = STOP;

	screen[LAYER_TEXT][17][13] = BABA;
	screen[LAYER_TEXT][18][13] = IS;
	screen[LAYER_TEXT][19][13] = YOU;

	screen[LAYER_TEXT][45][15] = STAR;
	screen[LAYER_TEXT][46][15] = IS;
	screen[LAYER_TEXT][47][15] = LOSE;

	screen[0][20][7] = wall;
	screen[0][20][6] = wall;
	screen[0][19][6] = wall;
	screen[0][18][6] = wall;
	screen[0][17][6] = wall;
	screen[0][16][6] = wall;
	screen[0][16][7] = wall;
	screen[0][16][8] = wall;
	screen[0][16][9] = wall;
	screen[0][16][10] = wall;
	screen[0][17][10] = wall;
	screen[0][18][10] = wall;
	screen[0][19][10] = wall;
	screen[0][20][10] = wall;
	screen[0][20][9] = wall;

	screen[0][18][8] = baba;

	screen[0][31][7] = star;
	screen[0][31][6] = star;
	screen[0][30][6] = star;
	screen[0][29][6] = star;
	screen[0][28][6] = star;
	screen[0][27][6] = star;
	screen[0][27][7] = star;
	screen[0][27][8] = star;
	screen[0][27][9] = star;
	screen[0][27][10] = star;
	screen[0][28][10] = star;
	screen[0][29][10] = star;
	screen[0][30][10] = star;
	screen[0][31][10] = star;
	screen[0][31][9] = star;
	screen[0][31][8] = star;

	screen[0][29][8] = flag;

	screen[0][20][8] = rock;
	screen[0][22][3] = rock;
	screen[0][24][4] = rock;
	screen[0][30][2] = rock;
	screen[0][23][12] = rock;
	screen[0][29][13] = rock;
}

void set_level(int level) {
	switch (level)
	{
	case 0:
		set_level_0();
		break;
	case 1:
		set_level_1();
		break;
	case 2:
		set_level_2();
		break;
	case 3:
		set_level_3();
		break;
	case 4:
		set_level_4();
		break;
	case 5:
		set_level_5();
		break;
	case 6:
		set_level_6();
		break;
	case 7:
		set_level_7();
		break;
	default:
		
		break;
	}
}

void print_main(int level) {
	cls(BLACK, WHITE);

	draw(24, 3, baba);

	draw(22, 6, BABA);
	draw(24, 6, IS);
	draw(26, 6, YOU);

	draw(21, 10, flag);
	draw(21, 12, flag);
	draw(23, 10, rock);
	draw(23, 12, rock);
	draw(25, 10, wall);
	draw(25, 12, wall);
	draw(27, 10, star);
	draw(27, 12, star);
	/*switch (level)
	{
	case 0:
		draw(21, 10, select);
		break;
	case 1:
		draw(23, 10, select);
		break;
	case 2:
		draw(25, 10, select);
		break;
	case 3:
		draw(27, 10, select);
		break;
	case 4:
		draw(21, 12, select);
		break;
	case 5:
		draw(23, 12, select);
		break;
	case 6:
		draw(25, 12, select);
		break;
	case 7:
		draw(27, 12, select);
		break;
	default:
	
		break;
	}*/
}

void print_win() {
	cls(BLACK, WHITE);
	draw(22, 6, YOU);
	draw(24, 6, IS);
	draw(26, 6, WIN);
	getch();
	cls(BLACK, WHITE);
}

void print_howtoplay(){
	FILE *outfile;
	outfile = fopen("HowToPlay.txt", "w");
	fprintf(outfile, "속성(properties) : 왼쪽위에 클릭(left up side)\n레거시 콘솔 사용 체크 해제\n글씨크기 (font size) : 5\n창크기 (windowsize) : 480 x 160\n\n키(key)\n방향키(Arrow keys) : 움직이기(move) \n'R' : 레벨 초기화(level reset)\n'Z' : 한번 무르기(back)\n'ESC' : 나가기(quit)");
	fclose(outfile);
}

int main()
{
	print_howtoplay();
	loading();
	/*print_baba(3,3);
	getch();
	remove_pix(3, 3);
	print_baba(1, 0);
	remove_pix(1, 0);
	getch();*/
	/*int i = 0;
	while (1) {
		draw(i, 6,baba);
		draw(i, 7,BABA);
		getch();
		remove_pix(i, 6);
		remove_pix(i++, 7);
	}*/
	int layeri, widthi, heighti;



	/*for (layeri = 0;layeri < LAYER;layeri++) {
		for (widthi = 0;widthi < WIDTH;widthi++) {
			for (heighti = 0;heighti < HEIGHT;heighti++) {
				if (screen[layeri][widthi][heighti])
					draw(widthi, heighti, screen[layeri][widthi][heighti]);
			}
		}
	}
	check_state();
	print_state();*/
	unsigned char ch;
	int level = 0;
	print_main(level);
	while (1) {
		switch (level)
		{
		case 0:
			draw(21, 10, select);
			break;
		case 1:
			draw(23, 10, select);
			break;
		case 2:
			draw(25, 10, select);
			break;
		case 3:
			draw(27, 10, select);
			break;
		case 4:
			draw(21, 12, select);
			break;
		case 5:
			draw(23, 12, select);
			break;
		case 6:
			draw(25, 12, select);
			break;
		case 7:
			draw(27, 12, select);
			break;
		default:

			break;
		}
		ch = getch();
		switch (level)
		{
		case 0:
			draw(21, 10, empty);
			draw(21, 10, flag);
			break;
		case 1:
			draw(23, 10, empty);
			draw(23, 10, rock);
			break;
		case 2:
			draw(25, 10, empty);
			draw(25, 10, wall);
			break;
		case 3:
			draw(27, 10, empty);
			draw(27, 10, star);
			break;
		case 4:
			draw(21, 12, empty);
			draw(21, 12, flag);
			break;
		case 5:
			draw(23, 12, empty);
			draw(23, 12, rock);
			break;
		case 6:
			draw(25, 12, empty);
			draw(25, 12, wall);
			break;
		case 7:
			draw(27, 12, empty);
			draw(27, 12, star);
			break;
		default:

			break;
		}
		if (ch == SPECIAL1 || ch == SPECIAL2) {
			ch = getch();
			switch (ch) 
			{
			case UP:
				if (level > 3)
					level -= 4;
				break;
			case DOWN:
				if (level < 4)
					level += 4;
				break;
			case LEFT:
				if (level > 0)
					level -= 1;
				break;
			case RIGHT:
				if (level < 7)
					level += 1;
				break;
			}
			
			
		}
		else {
			if (ch == ENTER) {
				
				set_level(level);
				check_state();
				for (layeri = 0;layeri < LAYER;layeri++) {
					for (widthi = 0;widthi < WIDTH;widthi++) {
						for (heighti = 0;heighti < HEIGHT;heighti++) {
							if (screen[layeri][widthi][heighti])
								draw(widthi, heighti, screen[layeri][widthi][heighti]);
						}
					}
				}
				while (1) {
					struct point del[768];
					int count = 0;
					ch = getch(); // key 값을 읽는다
						//
						// ESC 누르면 프로그램 종료
						//
					if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
						// 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.

						reset_plevel();
						for (layeri = 0;layeri < LAYER;layeri++) {
							for (widthi = 0;widthi < WIDTH;widthi++) {
								for (heighti = 0;heighti < HEIGHT;heighti++) {
									if (screen[layeri][widthi][heighti]) {
										screen_p[layeri][widthi][heighti] = screen[layeri][widthi][heighti];
									}
								}
							}
						}

						ch = getch();
						// Player1은 방향키로 움직인다.
						switch (ch) {
						case UP:
							for (widthi = 0;widthi < WIDTH;widthi++) {
								for (heighti = 0;heighti < HEIGHT;heighti++) {
									if (screen[LAYER_YOU][widthi][heighti]) {
										int movement = ismoveable(widthi, heighti, ch);
										if (movement) {
											for (int i = movement;i != 1;i--) {
												if (screen[LAYER_PUSH_STOP][widthi][heighti - i + 1]) {
													screen[LAYER_PUSH_STOP][widthi][heighti - i] = screen[LAYER_PUSH_STOP][widthi][heighti - i + 1];
													screen[LAYER_PUSH_STOP][widthi][heighti - i + 1] = 0;
												}
												if (screen[LAYER_TEXT][widthi][heighti - i + 1]) {
													screen[LAYER_TEXT][widthi][heighti - i] = screen[LAYER_TEXT][widthi][heighti - i + 1];
													screen[LAYER_TEXT][widthi][heighti - i + 1] = 0;
												}
												del[count].x = widthi;
												del[count++].y = heighti - i;
											}
											del[count].x = widthi;
											del[count++].y = heighti - 1;

											/*draw(widthi, heighti - 1, screen[LAYER_YOU][widthi][heighti]);*/
											screen[LAYER_YOU][widthi][heighti - 1] = screen[LAYER_YOU][widthi][heighti];
											screen[LAYER_YOU][widthi][heighti] = 0;
											del[count].x = widthi;
											del[count++].y = heighti;
										}
									}
								}
							}
							break;
						case DOWN:
							for (widthi = 0;widthi < WIDTH;widthi++) {
								for (heighti = HEIGHT - 1;heighti >= 0;heighti--) {
									if (screen[LAYER_YOU][widthi][heighti]) {
										int movement = ismoveable(widthi, heighti, ch);
										if (movement) {
											for (int i = movement;i != 1;i--) {
												if (screen[LAYER_PUSH_STOP][widthi][heighti + i - 1]) {
													screen[LAYER_PUSH_STOP][widthi][heighti + i] = screen[LAYER_PUSH_STOP][widthi][heighti + i - 1];
													screen[LAYER_PUSH_STOP][widthi][heighti + i - 1] = 0;
												}
												if (screen[LAYER_TEXT][widthi][heighti + i - 1]) {
													screen[LAYER_TEXT][widthi][heighti + i] = screen[LAYER_TEXT][widthi][heighti + i - 1];
													screen[LAYER_TEXT][widthi][heighti + i - 1] = 0;
												}
												del[count].x = widthi;
												del[count++].y = heighti + i;
											}
											del[count].x = widthi;
											del[count++].y = heighti + 1;

											//draw(widthi, heighti + 1, screen[LAYER_YOU][widthi][heighti]);
											screen[LAYER_YOU][widthi][heighti + 1] = screen[LAYER_YOU][widthi][heighti];
											screen[LAYER_YOU][widthi][heighti] = 0;
											del[count].x = widthi;
											del[count++].y = heighti;
										}
									}
								}
							}
							break;
						case LEFT:
							for (widthi = 0;widthi < WIDTH;widthi++) {
								for (heighti = 0;heighti < HEIGHT;heighti++) {
									if (screen[LAYER_YOU][widthi][heighti]) {
										int movement = ismoveable(widthi, heighti, ch);
										if (movement) {
											for (int i = movement;i != 1;i--) {
												if (screen[LAYER_PUSH_STOP][widthi - i + 1][heighti]) {
													screen[LAYER_PUSH_STOP][widthi - i][heighti] = screen[LAYER_PUSH_STOP][widthi - i + 1][heighti];
													screen[LAYER_PUSH_STOP][widthi - i + 1][heighti] = 0;
												}
												if (screen[LAYER_TEXT][widthi - i + 1][heighti]) {
													screen[LAYER_TEXT][widthi - i][heighti] = screen[LAYER_TEXT][widthi - i + 1][heighti];
													screen[LAYER_TEXT][widthi - i + 1][heighti] = 0;
												}
												del[count].x = widthi - i;
												del[count++].y = heighti;
											}
											del[count].x = widthi - 1;
											del[count++].y = heighti;

											//draw(widthi - 1, heighti, screen[LAYER_YOU][widthi][heighti]);
											screen[LAYER_YOU][widthi - 1][heighti] = screen[LAYER_YOU][widthi][heighti];
											screen[LAYER_YOU][widthi][heighti] = 0;
											del[count].x = widthi;
											del[count++].y = heighti;
										}
									}
								}
							}
							break;
						case RIGHT:
							for (widthi = WIDTH - 1;widthi >= 0;widthi--) {
								for (heighti = 0;heighti < HEIGHT;heighti++) {
									if (screen[LAYER_YOU][widthi][heighti]) {
										int movement = ismoveable(widthi, heighti, ch);
										if (movement) {
											for (int i = movement;i != 1;i--) {
												if (screen[LAYER_PUSH_STOP][widthi + i - 1][heighti]) {
													screen[LAYER_PUSH_STOP][widthi + i][heighti] = screen[LAYER_PUSH_STOP][widthi + i - 1][heighti];
													screen[LAYER_PUSH_STOP][widthi + i - 1][heighti] = 0;
												}
												if (screen[LAYER_TEXT][widthi + i - 1][heighti]) {
													screen[LAYER_TEXT][widthi + i][heighti] = screen[LAYER_TEXT][widthi + i - 1][heighti];
													screen[LAYER_TEXT][widthi + i - 1][heighti] = 0;
												}
												del[count].x = widthi + i;
												del[count++].y = heighti;
											}
											del[count].x = widthi + 1;
											del[count++].y = heighti;

											//draw(widthi + 1, heighti, screen[LAYER_YOU][widthi][heighti]);
											screen[LAYER_YOU][widthi + 1][heighti] = screen[LAYER_YOU][widthi][heighti];
											screen[LAYER_YOU][widthi][heighti] = 0;
											del[count].x = widthi;
											del[count++].y = heighti;
										}
									}
								}
							}
							break;
							//default:
							// 특수키 이지만 방향키가 아닌 경우

						}
						while (count--) {
							remove_pix(del[count].x, del[count].y);
							for (layeri = 0;layeri < LAYER;layeri++) {
								if (screen[layeri][del[count].x][del[count].y])
									draw(del[count].x, del[count].y, screen[layeri][del[count].x][del[count].y]);
							}
						}

						/*
						for (layeri = 0;layeri < LAYER;layeri++) {
							for (widthi = 0;widthi < WIDTH;widthi++) {
								for (heighti = 0;heighti < HEIGHT;heighti++) {
									if (screen[layeri][widthi][heighti])
										draw(widthi, heighti, screen[layeri][widthi][heighti]);
								}
							}
						}
						*/
						check_state();
						if (redraw) {
							redraw = 0;
							cls(BLACK, BLACK);
							for (layeri = 0;layeri < LAYER;layeri++) {
								for (widthi = 0;widthi < WIDTH;widthi++) {
									for (heighti = 0;heighti < HEIGHT;heighti++) {
										if (screen[layeri][widthi][heighti])
											draw(widthi, heighti, screen[layeri][widthi][heighti]);
									}
								}
							}
						}
						if (iswin()) {
							print_win();
							break;
						}
						if (redraw) {
							redraw = 0;
							cls(BLACK, BLACK);
							for (layeri = 0;layeri < LAYER;layeri++) {
								for (widthi = 0;widthi < WIDTH;widthi++) {
									for (heighti = 0;heighti < HEIGHT;heighti++) {
										if (screen[layeri][widthi][heighti])
											draw(widthi, heighti, screen[layeri][widthi][heighti]);
									}
								}
							}
						}
						//print_state();
					} //if 방향키 조건문

					else {
						if (ch == 'r' || ch == 'R') {
							set_level(level);
							for (layeri = 0;layeri < LAYER;layeri++) {
								for (widthi = 0;widthi < WIDTH;widthi++) {
									for (heighti = 0;heighti < HEIGHT;heighti++) {
										if (screen[layeri][widthi][heighti])
											draw(widthi, heighti, screen[layeri][widthi][heighti]);
									}
								}
							}
						}

						else if (ch == 'z' || ch == 'Z') {
							reset_level();
							for (layeri = 0;layeri < LAYER;layeri++) {
								for (widthi = 0;widthi < WIDTH;widthi++) {
									for (heighti = 0;heighti < HEIGHT;heighti++) {
										if (screen_p[layeri][widthi][heighti]) {
											screen[layeri][widthi][heighti] = screen_p[layeri][widthi][heighti];
											draw(widthi, heighti, screen[layeri][widthi][heighti]);
										}
									}
								}
							}
						}
						else if (ch == ESC)
							break;
					}
					
				}
				print_main(level);
			}
			else if (ch == ESC) {
				break;
			}
			
		}
		
	}
}
