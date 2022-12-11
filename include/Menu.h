#include "utilis.h"
#include "menu_back.h"
#define back_color COLOR(40, 41, 43) //culoare backgroundului
#define primary COLOR(54, 114, 174) //bleu
#define secondary COLOR(236, 160, 64) //orange
void Menu();
void MainGame();

void Menu() {
	cleardevice();
	readimagefile("./Resources/Images/background_logo.jpg", 0, 0, screen_width, screen_height);
	MainLoop = true;
	Buton start, exit_b;
	start.createButton(midx-120, midy+100, 300, 75, "START", colors(COLOR(236, 160, 64)), BLACK, midx-60, midy+120);
	exit_b.createButton(midx-120, midy+200, 300, 75, "EXIT", colors(COLOR(236, 160, 64)), BLACK, midx-35, midy+220);
	
	while (MainLoop) {
		getmouseclick(WM_LBUTTONUP, release_x, release_y);
		
		if (release_x >= start.x && release_x <= start.x + start.size_x && release_y >= start.y && release_y <= start.y + start.size_y)
		{
			changeWin = 1; break;
		}
		if (exit_b.contains(release_x, release_y)) {
			closegraph();
			exit(0);
		}
	}
	if (changeWin) {
		MainGame();
		exit(0);
	}
}

void MainGame() {

	cleardevice();
	readimagefile("./Resources/Images/main.jpg", 0, 0, screen_width, screen_height);
	MainLoop = true;

	InputBox box_var, box_ecuatie;
	Buton back; 
	back.createButton(80, 50, 200, 70, "BACK", colors(COLOR(59, 125, 186)), BLACK, 95, 60);
	box_var.createBox(350, 170, 500, 700);
	box_ecuatie.createBox(900, 170, 700, 300);
	console.createConsole(900, 540, 700, 330); ///Console e in structuri.h (e globala)

	setcolor(secondary); setbkcolor(back_color);

	char* text = _strdup("Define variables here..."); ///_strdup converteste un const sir in pointer
	outtextxy(360, 130, text); ///
	text = _strdup("Write equations here...");
	outtextxy(910, 130, text);
	text = _strdup("Console:");
	outtextxy(910, 500, text);

	char inputbuf[128][1024] = { "" }, expresie[128][1024] = {""}, temp[NMAX], c;
	int input_pos = 0, expresie_pos = 0, level = 0, levelec=0;
	string aux; coada infix;
	double val_expression;
	bool ok_variable, ok_expression = 1, was_ecuation = 0, changeWin = 0;

	while (MainLoop) {
		getmouseclick(WM_LBUTTONDOWN, mouse_x, mouse_y);
		///functia getmouseclick se activeaza doar in milisecunda cand apas click, 
		//iar in rest returneaza valoarea -1
		if (mouse_x != -1 && mouse_y != -1 && (mouse_x != last_mouse_x || mouse_y != last_mouse_y)) {
			last_mouse_x = mouse_x;
			last_mouse_y = mouse_y;
		}
		///Cand apas click sa fie click uit mereu (last_mouse_x && (last_mouse_y)
		
		if (back.contains(last_mouse_x, last_mouse_y)) {
			changeWin = 1; break;
		}

		/// <summary>
		/// InputBox ul de variabile
		if (box_var.contains(last_mouse_x, last_mouse_y)) {
			box_var.state = CLICKED;
			setcolor(primary);
			setlinestyle(0, 0, 3);
			rectangle(box_var.x+1, box_var.y + 1, box_var.x + box_var.size_x - 1, box_var.y + box_var.size_y - 1);
			setcolor(WHITE);
			setlinestyle(0, 0, 1);
		}
		else {
			box_var.state = ACTIVE;
			setlinestyle(0, 0, 10);
			setcolor(back_color);
			rectangle(box_var.x, box_var.y, box_var.x + box_var.size_x, box_var.y + box_var.size_y );
			setlinestyle(0, 0, 1);

		}
		if (box_var.state == CLICKED) {
			bool ok;
			do {
				ok = true;
				aux = string(to_string(level + 1) + ".");
				char s[] = "";
				strcpy(s, aux.c_str());
				outtextxy(360, 180 + (level * 40), s);
				outtextxy(420, 180 + (level * 40), inputbuf[level]);
				if (kbhit()) c = getch(); ///daca apas o tasta, mi- inregistreaza in variabila C
				else break;
				if (input_pos > 19) {
					input_pos = 19;
					console.log("Error: Maximum number of characters reached!", colors(secondary));
					outtextxy(420, 180 + level * 40, inputbuf[level]);
				}
				switch (c) {
				case 8: //backspace
					console.clear();

					///Sterg poza "X" sau "Check" din stanga variabilei
					setfillstyle(SOLID_FILL, back_color);
					bar(300, 180 + (level * 40), 340, 180 + (level * 40) + 40);

					///Simulez backspace ul
					setcolor(back_color);
					outtextxy(420, 180 + level * 40, inputbuf[level]);
					inputbuf[level][--input_pos] = 0;
					setcolor(WHITE);
					outtextxy(420, 180 + level * 40, inputbuf[level]);

					if (input_pos < 0 && level > 0) {

						///Scriu nivelul levelui cu back_color ca sa il sterg
						aux = string(to_string(level + 1) + ".");
						char s[] = "";
						strcpy(s, aux.c_str());
						setcolor(back_color);
						outtextxy(360, 180 + (level * 40), s);

						setcolor(WHITE);
						if (level != 17) {
							level--;
							//Scriu nivelul curent
							aux = string(to_string(level + 1) + ".");
							char s[] = "";
							strcpy(s, aux.c_str());

							setcolor(back_color);
							//Sterg variabila din memorie
							delete_var(inputbuf[level]);

							///Sterg poza "X" sau "Check" din stanga variabilei
							setfillstyle(SOLID_FILL, back_color);
							bar(300, 180 + (level * 40), 340, 180 + (level * 40) + 40);

							outtextxy(360, 180 + (level * 40), s);
							outtextxy(420, 180 + (level * 40), inputbuf[level]);


							///Sterg sirul de pe nivelul curent
							for (int j = 19; j > -1; j--)
								inputbuf[level][j] = 0;
							inputbuf[level][input_pos] = 0;
							input_pos = 0;
						}
					}
					else if (input_pos < 0) input_pos = 0;

					break;
				case 13: //return
					try {
						ok_variable = check_variable(inputbuf[level]);
					}
					catch (invalid_argument& e) {

						///Sterg poza "X" sau "Check" din stanga variabilei
						setfillstyle(SOLID_FILL, back_color);
						bar(300, 180 + (level * 40), 340, 180 + (level * 40) + 40);
						///Pun poza "X" in stanga variabila
						readimagefile("./Resources/Images/x.gif", 300, 180 + (level * 40), 340, 180 + (level * 40) + 40);
						///Afisez eroarea in consola
						string err = "Error: " + string(e.what());
						console.log(err, colors(COLOR(236, 160, 64)));
						ok_variable = 0;
					}
					if (ok_variable) {
						///Daca ultimul caracter introdus NU a fost ';', il pun eu de mana
						if (inputbuf[level][input_pos - 1] != ';' && inputbuf[level][input_pos - 2] != 0) {
							if (input_pos == 19 && inputbuf[level][input_pos]!=';') inputbuf[level][++input_pos] = ';';
							else  inputbuf[level][input_pos] = ';';
							setcolor(WHITE);
							outtextxy(420, 180 + level * 40, inputbuf[level]);
						}
						outtextxy(420, 180 + (level * 40), inputbuf[level]);

						///Sterg poza "X" sau "Check" din stanga variabilei
						setfillstyle(SOLID_FILL, back_color);
						bar(300, 180 + (level * 40), 340, 180 + (level * 40) + 40);
						///Pun poza "Check"
						readimagefile("./Resources/Images/check.gif", 300, 180 + (level * 40), 340, 180 + (level * 40) + 40);
						setcolor(back_color);

						if (level >= 16) { level = 16; }
						else {
							input_pos = 0;
							level++;
						}
					}
					break;

				case 9: ///Tab
					box_var.state = INACTIVE;
					last_mouse_x = box_ecuatie.x + 10;
					last_mouse_y = box_ecuatie.y + 10;
					break;
				default:
					if (input_pos < 10000 && c >= ' ' && c <= '~') {
						inputbuf[level][input_pos++] = c;
						inputbuf[level][input_pos] = 0;
					}
				}
			} while (ok && box_var.state == CLICKED);
		}
		/// </summary>

		/// <summary>
		/// InputBox ul de Expresie
		if (box_ecuatie.contains(last_mouse_x, last_mouse_y)) {
			box_ecuatie.state = CLICKED;
			setcolor(primary);
			setlinestyle(0, 0, 3);
			rectangle(box_ecuatie.x + 1, box_ecuatie.y + 1, box_ecuatie.x + box_ecuatie.size_x - 1, box_ecuatie.y + box_ecuatie.size_y - 1);
			setcolor(WHITE);
			setlinestyle(0, 0, 1);
		}
		else {
			box_ecuatie.state = ACTIVE;
			setlinestyle(0, 0, 10);
			setcolor(back_color);
			rectangle(box_ecuatie.x, box_ecuatie.y, box_ecuatie.x + box_ecuatie.size_x, box_ecuatie.y + box_ecuatie.size_y);
			setlinestyle(0, 0, 1);

		}
		if (box_ecuatie.state == CLICKED) {
			bool ok;
			do {
				ok = true;
				///Scriu expresia
				outtextxy(910, 180 + (levelec * 40), expresie[levelec]);
				if (kbhit()) c = getch();
				else break;
				
				if (expresie_pos > 33 && levelec < 6) {
					levelec++;
					expresie_pos = 0;
				}
				else if (expresie_pos > 33 && levelec == 6) expresie_pos = 33;
					
				switch (c) {
				case 8: //backspace
					console.clear();
					if (expresie_pos > 0) {

						///Sterg ultimul caracter
						setcolor(back_color);
						outtextxy(910, 180 + levelec * 40, expresie[levelec]);
						expresie[levelec][--expresie_pos] = 0;
					}
					///Scriul noul sir
					setcolor(WHITE);
					outtextxy(910, 180 + levelec * 40, expresie[levelec]);

					if (expresie_pos < 0) expresie_pos = 0;
					else if (expresie_pos == 0 && levelec > 0) {
						levelec--;
						int i = 0;
						expresie_pos = 33;
					}
					

					break;
				case 13: //return
					try {
						strcpy(temp, "");
						for(int j=0; j<levelec + 1; j++)
							strcat(temp, expresie[j]);
						if (strlen(temp) == 0) throw invalid_argument("No string to evaluate!");

						string expr_s = temp;
						//cout << expr_s << ' ' << expr_s.size()<< '\n';
						variables(expr_s); ///inlocuiesc fiecare variabila
						parse(expr_s);
						init_coada(expr_s, infix);
						val_expression = valpostfix(infix);
						ok_expression = 1;
					}
					catch (invalid_argument& e) {
						string err = "Error: " + string(e.what());
						console.log(err, colors(COLOR(236, 160, 64)));
						ok_expression = 0;
					}
					if (ok_expression) {
						console.log(to_string(val_expression));
					}
					break;

				case 9: ///Tab
					box_ecuatie.state = INACTIVE;
					last_mouse_x = box_var.x + 10;
					last_mouse_y = box_var.y + 10;
					break;

				default:
					if (expresie_pos < 10000 && c >= ' ' && c <= '~') {
						expresie[levelec][expresie_pos++] = c;
						expresie[levelec][expresie_pos] = 0;
					}
				}
			} while (ok && box_ecuatie.state == CLICKED);
		}
		/// </summary>
	}
	if (changeWin) {
		last_mouse_x = last_mouse_y = 0;
		delete_variables();
		Menu(); exit(0);
	}
}