#include "utilis.h"
void Menu();
void MainGame();

void Menu() {
	cleardevice();
	readimagefile("./Resources/Images/background_logo.jpg", 0, 0, screen_width, screen_height);
	MainLoop = true;
	Buton start;
	start.createButton(midx-100, midy+100, 300, 75, "START", YELLOW, BLACK, midx-40, midy+120);
	
	while (MainLoop) {
		//getmouseclick(WM_MOUSEMOVE, hover_x, hover_y);
		getmouseclick(WM_LBUTTONUP, release_x, release_y);
		//getmouseclick(WM_LBUTTONDOWN, mouse_x, mouse_y);
		/*if (x > -1 && y > -1) {
			cout <<"Coordonate: "<<' ' << x << ' ' << y << '\n';
			cout <<"Buton X: "<<' ' << start.x << ' ' << start.x+start.size_x << '\n';
			cout <<"Buton Y: "<<' ' << start.y << ' ' << start.y+start.size_y << '\n';
		}*/
		if (release_x >= start.x && release_x <= start.x + start.size_x && release_y >= start.y && release_y <= start.y + start.size_y)
		{
			changeWin = 1; break;
		}
	}
	if (changeWin) {
		MainGame();
	}
	while (!kbhit());
}

void MainGame() {
	cleardevice();
	readimagefile("./Resources/Images/main.jpg", 0, 0, screen_width, screen_height);
	MainLoop = true;
	InputBox box1, box2;
	Buton b1;
	b1.createButton(50, 50, 200, 70, "BACK", YELLOW, BLACK, 65, 60);
	box1.createBox(350, 170, 500, 700, true);
	char* text = _strdup("Define variables here...");
	setcolor(BLACK); setbkcolor(WHITE);
	outtextxy(360, 130, text);
	char inputbuf[128][1024] = { "" }, c;
	int input_pos = 0, level = 0;
	string aux;
	while (MainLoop) {
		getmouseclick(WM_LBUTTONDOWN, mouse_x, mouse_y);
		if (mouse_x != -1 && mouse_y != -1 && (mouse_x != last_mouse_x || mouse_y != last_mouse_y)) {
			last_mouse_x = mouse_x;
			last_mouse_y = mouse_y;
		}
		if (box1.contains(last_mouse_x, last_mouse_y)) {
			box1.state = CLICKED;
			setcolor(RED);
			setlinestyle(0, 0, 3);
			rectangle(box1.x+1, box1.y + 1, box1.x + box1.size_x - 1, box1.y + box1.size_y - 1);
			setcolor(BLACK);
			setlinestyle(0, 0, 1);
		}
		else {
			box1.state = ACTIVE;
			setlinestyle(0, 0, 10);
			setcolor(WHITE);
			rectangle(box1.x, box1.y, box1.x + box1.size_x, box1.y + box1.size_y );
			setlinestyle(0, 0, 1);

		}
		//cout << last_mouse_x << ' ' << last_mouse_y << '\n';
		if (b1.contains(last_mouse_x, last_mouse_y)) {
			last_mouse_x = last_mouse_y = 0;
			Menu();
		}
		if (box1.state == CLICKED) {
			bool ok = true;

			do {
				/*getmouseclick(WM_LBUTTONDOWN, mouse_x, mouse_y);
				if (mouse_x != last_mouse_x || mouse_y != last_mouse_y) {
					last_mouse_x = mouse_x;
					last_mouse_y = mouse_y;
				}
				if (box1.contains(last_mouse_x, last_mouse_y)) box1.state = CLICKED;
				else box1.state = ACTIVE;*/
				aux = string(to_string(level + 1) + ".");
				char s[] = "";
				strcpy(s, aux.c_str());
				outtextxy(360, 180 + (level * 40), s);
				outtextxy(420, 180 + (level * 40), inputbuf[level]);
				if (kbhit()) c = getch();
				else break;
				if (input_pos > 19) {
					input_pos = 19;
					outtextxy(420, 180 + level * 40, inputbuf[level]);
				}
				switch (c) {
				case 8: //backspace

					setcolor(WHITE);
					outtextxy(420, 180 + level * 40, inputbuf[level]);
					inputbuf[level][--input_pos] = 0;
					setcolor(BLACK);
					outtextxy(420, 180 + level * 40, inputbuf[level]);

					cout << "pos: " << input_pos << " lvl: " << level << '\n';
					if (input_pos < 0 && level > 0) {
						aux = string(to_string(level + 1) + ".");
						char s[] = "";
						strcpy(s, aux.c_str());
						setcolor(WHITE);
						outtextxy(360, 180 + (level * 40), s);
						setcolor(BLACK);
						if(level!=17) level--;
						int i = 0;
						while (inputbuf[level][i]) {
							cout << inputbuf[level][i++];
						}
						input_pos = i-1;
					}
					else if (input_pos < 0) input_pos = 0;

					break;
				case 13: //return
					if (inputbuf[level][input_pos-1] != ';' && inputbuf[level][input_pos-2] != 0) {
						inputbuf[level][input_pos] = ';';
						setcolor(BLACK);
						outtextxy(420, 180 + level * 40, inputbuf[level]);
					}
					
					if (level >= 16) { level = 16; }
					else {
						input_pos = 0;
						level++;
					}
					break;
				case 27: //Escape
					inputbuf[input_pos][0] = 0;
					ok = false;
					break;
				default:
					if (input_pos < 10000 && c >= ' ' && c <= '~') {
						inputbuf[level][input_pos++] = c;
						inputbuf[level][input_pos] = 0;
					}
				}
			} while (ok && box1.state == CLICKED);
		}
	}
}