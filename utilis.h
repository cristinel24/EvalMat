#pragma once
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
const DWORD screen_width = GetSystemMetrics(SM_CXSCREEN);
const DWORD screen_height = GetSystemMetrics(SM_CYSCREEN);
const double midx = screen_width / 2;
const double midy = screen_height / 2;
int last_mouse_x, last_mouse_y, mouse_x, mouse_y, hover_x, hover_y, release_x, release_y;
bool MainLoop, changeWin;

enum State { INACTIVE, ACTIVE, HOVERED, CLICKED };
struct Buton {
	double x, y;
	double size_x, size_y;
	State state;
	colors background, text_color;
	string text;
	void changeColor(colors colorbk, colors colortxt) {
		background = colorbk;
		text_color = colortxt;
		setfillstyle(SOLID_FILL, background);
		setbkcolor(background);
		settextstyle(6, HORIZ_DIR, 5);
		rectangle(x, y, x + size_x, y + size_y);
		floodfill(x + size_x / 2, y + size_y / 2, WHITE);
		setcolor(text_color);
		char* textc = _strdup(text.c_str());
		outtextxy(x + 60, y + 20, textc);
		setcolor(0);
		//createButton(x, y, size_x, size_y, text, RED, BLACK);
	}
	void createButton(double pozx, double pozy, double size_xx, double size_yy, const string s, colors bkcolor, colors txt_color, double txt_x, double txt_y) {
		state = ACTIVE;
		background = bkcolor;
		text_color = txt_color;
		x = pozx; y = pozy;
		size_x = size_xx; size_y = size_yy;
		text = s;
		
		setfillstyle(SOLID_FILL, bkcolor);
		setbkcolor(bkcolor);
		setcolor(text_color);
		settextstyle(6, HORIZ_DIR, 5);
		rectangle(x, y, x + size_x, y + size_y);
		floodfill(x + size_x / 2, y + size_y / 2, text_color);
		char* textc = _strdup(s.c_str());
		outtextxy(txt_x, txt_y, textc);
		setcolor(0);
		setbkcolor(0);
	}
	bool contains(int mouse_x, int mouse_y) {
		return (mouse_x >= x && mouse_x <= x + size_x && mouse_y >= y && mouse_y <= y + size_y);
	}
};

struct InputBox {
	double x, y, size_x, size_y;
	State state;
	string text;
	void createBox(double pozx, double pozy, double top_x, double top_y) {
		state = ACTIVE;
		x = pozx; y = pozy; size_x = top_x; size_y = top_y;
		setfillstyle(SOLID_FILL, COLOR(40, 41, 43));
		settextstyle(8, HORIZ_DIR, 4);
		rectangle(x, y, x + size_x, y + size_y);
		floodfill(x + size_x / 2, y + size_y / 2, BLACK);
	}
	bool contains(int mouse_x, int mouse_y) {
		return (mouse_x >= x && mouse_x <= x + size_x && mouse_y >= y && mouse_y <= y + size_y);
	}
};
struct Console {
	double x, y, size_x, size_y;
	string last_text = "a";
	State state = INACTIVE;
	int level;
	void log(const string sir, colors col = WHITE) {
		setbkcolor(BLACK);
		setfillstyle(SOLID_FILL, COLOR(40, 41, 43));
		///Sterg consola
		setcolor(BLACK);
		int levelsir = last_text.size() / 33;
		for (int i = 0; i < levelsir + 1; i++) {
			string temp = last_text.substr(i * 33, 33);
			char* aux = new char[temp.size() + 1]; //inittializez dinamic pentru a putea sterge memoria
			strcpy(aux, temp.c_str());
			outtextxy(x + 10, y + 10 + (i * 40), aux);
			delete aux;
		}
		///Scriu in consola sirul curent
		setcolor(col);
		levelsir = sir.size() / 33;
		if (levelsir > 7) levelsir = 6;
		for (int i = 0; i < levelsir + 1; i++) {
			string temp = sir.substr(i * 33, 33);
			char* aux = new char[temp.size() + 1];
			strcpy(aux, temp.c_str());
			outtextxy(x + 10, y + 10 + (i * 40), aux);
			delete aux;
		}
		if (sir.size() > 32) level++;
		if (level > 6) level = 5;
		last_text = sir;
		setbkcolor(COLOR(40, 41, 43));
	}
	void clear() {
		///Sterg consola
		setcolor(BLACK);
		setbkcolor(BLACK);
		int levelsir = last_text.size() / 33;
		for (int i = 0; i < levelsir + 1; i++) {
			string temp = last_text.substr(i * 33, 33);
			char* aux = new char[temp.size() + 1];
			strcpy(aux, temp.c_str());
			outtextxy(x + 10, y + 10 + (i * 40), aux);
			delete aux;
		}
		setbkcolor(COLOR(40, 41, 43));
	}
	void createConsole(double pozx, double pozy, double top_x, double top_y) {
		state = ACTIVE;
		x = pozx; y = pozy; size_x = top_x; size_y = top_y;
		
		settextstyle(8, HORIZ_DIR, 4);

		///Chenarul albaastru
		setfillstyle(SOLID_FILL, COLOR(54, 114, 174)); ///culoare asta e culoarea albastru
		int thickness = 3;
		bar(x - thickness, y - thickness, x + size_x + thickness, y + size_y + thickness);
		
		///desenez consola
		setfillstyle(SOLID_FILL, BLACK);
		bar(x, y, x + size_x, y + size_y);
		
	}
};