#include "utilis.h"
#include "menu_back.h"
#define back_color COLOR(40, 41, 43) //culoare backgroundului
#define primary COLOR(54, 114, 174) //bleu
#define secondary COLOR(236, 160, 64) //orange


int mouse_x, mouse_y, hover_x, hover_y;
void Menu();
void MainGame();
void desenArb(string);
void info_s();
string openDialog();
void reset(char**&, int&, int&, char*);

void Menu() {
	int mouse_x = 0, mouse_y = 0, hover_x = 0, hover_y = 0;
	
	cleardevice();
	readimagefile("./Resources/Images/background_logo.jpg", 0, 0, screen_width, screen_height);

	MainLoop = true;

	Buton start, exit_b;
	start.createButton(midx-120, midy+100, 300, 75, "START", colors(COLOR(236, 160, 64)), colors(COLOR(30, 63, 97)), midx-60, midy+117, 5);
	exit_b.createButton(midx-120, midy+200, 300, 75, "EXIT", colors(COLOR(236, 160, 64)), colors(COLOR(30, 63, 97)), midx-35, midy+217, 5);
	
	int offset = 2; ///cati pixeli merg in spate

	while (MainLoop) {

		try {
			if (ismouseclick(WM_LBUTTONUP))
				getmouseclick(WM_LBUTTONUP, mouse_x, mouse_y);
			if (ismouseclick(WM_MOUSEMOVE))
				getmouseclick(WM_MOUSEMOVE, hover_x, hover_y);
		}
		catch (invalid_argument& e) {
			cout << e.what() << '\n';
		}

		///Start Hover
		if (start.contains(hover_x, hover_y)) {
			setlinestyle(0, SOLID_LINE, 10);
			setcolor(primary);
			rectangle(start.x - offset, start.y - offset, start.x + start.size_x + offset, start.y + start.size_y + offset);
			setlinestyle(0, SOLID_LINE, 1);
		}
		else {
			setlinestyle(0, SOLID_LINE, 10);
			setcolor(back_color);
			rectangle(start.x - offset, start.y - offset, start.x + start.size_x + offset, start.y + start.size_y + offset);
			setlinestyle(0, SOLID_LINE, 1);
		}
		///Exit Hover
		if (exit_b.contains(hover_x, hover_y)) {
			setlinestyle(0, SOLID_LINE, 10);
			setcolor(primary);
			rectangle(exit_b.x - offset, exit_b.y - offset, exit_b.x + exit_b.size_x + offset, exit_b.y + exit_b.size_y + offset);
			setlinestyle(0, SOLID_LINE, 1);
		}
		else {
			setlinestyle(0, SOLID_LINE, 10);
			setcolor(back_color);
			rectangle(exit_b.x - offset, exit_b.y - offset, exit_b.x + exit_b.size_x + offset, exit_b.y + exit_b.size_y + offset);
			setlinestyle(0, SOLID_LINE, 1);
		}

		if (start.contains(mouse_x, mouse_y))
		{
			MainGame();
			mouse_x = mouse_y = 0;
			cleardevice();
			readimagefile("./Resources/Images/background_logo.jpg", 0, 0, screen_width, screen_height);
			start.createButton(midx - 120, midy + 100, 300, 75, "START", colors(COLOR(236, 160, 64)), colors(COLOR(30, 63, 97)), midx - 60, midy + 117, 5);
			exit_b.createButton(midx - 120, midy + 200, 300, 75, "EXIT", colors(COLOR(236, 160, 64)), colors(COLOR(30, 63, 97)), midx - 35, midy + 217, 5);
		}
		if (exit_b.contains(mouse_x, mouse_y)) {
			closegraph();
			exit(0);
		}
	}
}

void MainGame() {
	int mouse_x = 0, mouse_y = 0, hover_x = 0, hover_y = 0;

	cleardevice();
	readimagefile("./Resources/Images/main.jpg", 0, 0, screen_width, screen_height);
	MainLoop = true; 
	int offset = 2; 

	InputBox box_var, box_ecuatie;
	Buton back, arbbuton, info, loadFromFile, trash; 
	back.createButton(100, 50, 150, 60, "BACK", colors(back_color), colors(secondary), 115, 65, 4);
	box_var.createBox(350, 170, 500, 700);
	box_ecuatie.createBox(900, 170, 700, 300);
	console.createConsole(900, 540, 700, 330); ///Console e in structuri.h (e globala)
	arbbuton.createButton(1400, 480, 190, 50, "TREE", colors(back_color), colors(secondary), 1435, 490, 4);
	info.createButton_Image(1480, 126, 16, 30, "./Resources/Images/info.gif");
	loadFromFile.createButton_Image(1515, 130, 30, 0.85*30, "./Resources/Images/load.gif");
	trash.createButton_Image(1560, 130, 25, 25, "./Resources/Images/trash.gif");

	setcolor(secondary); setbkcolor(back_color);

	char* text = _strdup("Define variables here..."); ///_strdup converteste un const sir in pointer
	outtextxy(360, 130, text); 
	text = _strdup("Write equations here...");
	outtextxy(910, 130, text);
	text = _strdup("Console:");
	outtextxy(910, 500, text);

	char** inputbuf = new char* [20], ** expresie = new char* [100000], *temp= new char [100000* 33], c;
	int input_pos = 0, expresie_pos = 0, level = 0, levelec = 0;
	string aux, expr_s; coada infix;
	double val_expression;
	bool ok_variable, ok_expression = 1, was_ecuation = 0, changeWin = 0, ok_for_arb = 0, loaded_from_file = false, overflow = false;

	for (int i = 0; i < 20; i++) 
		inputbuf[i] = new char[50]{};
	for (int i = 0; i < 1024; i++) 
		expresie[i] = new char[50]{};
	
	
	while (MainLoop) {

		try {
			if (ismouseclick(WM_LBUTTONDOWN))
				getmouseclick(WM_LBUTTONDOWN, mouse_x, mouse_y);
			//Hover
			if (ismouseclick(WM_MOUSEMOVE))
				getmouseclick(WM_MOUSEMOVE, hover_x, hover_y);
		}
		catch (invalid_argument& e) {
			cout << e.what() << '\n';
		}
			

		///Back Hover
		if (back.contains(hover_x, hover_y)) {
			setlinestyle(0, SOLID_LINE, 6);
			setcolor(primary);
			rectangle(back.x - offset, back.y - offset, back.x + back.size_x + offset, back.y + back.size_y + offset);
			setlinestyle(0, SOLID_LINE, 1);
		}
		else {
			setlinestyle(0, SOLID_LINE, 6);
			setcolor(back_color);
			rectangle(back.x - offset, back.y - offset, back.x + back.size_x + offset, back.y + back.size_y + offset);
			setlinestyle(0, SOLID_LINE, 1);
		}
		///Arbore Hover
		if (arbbuton.contains(hover_x, hover_y)) {
			setlinestyle(0, SOLID_LINE, 6);
			setcolor(primary);
			rectangle(arbbuton.x - offset, arbbuton.y - offset, arbbuton.x + arbbuton.size_x + offset, arbbuton.y + arbbuton.size_y + offset);
			setlinestyle(0, SOLID_LINE, 1);
		}
		else {
			setlinestyle(0, SOLID_LINE, 6);
			setcolor(back_color);
			rectangle(arbbuton.x - offset, arbbuton.y - offset, arbbuton.x + arbbuton.size_x + offset, arbbuton.y + arbbuton.size_y + offset);
			setlinestyle(0, SOLID_LINE, 1);
		}
		///Info Hover
		if (info.contains(hover_x, hover_y)) {
			setlinestyle(0, SOLID_LINE, 3);
			setcolor(primary);
			circle(info.x + info.size_x / 2, info.y + info.size_y / 2, sqrt(pow(info.size_y + 5, 2) + pow(info.size_x + 5, 2)) / 2);
			setlinestyle(0, SOLID_LINE, 1);
		}
		else {
			setlinestyle(0, SOLID_LINE, 8);
			setcolor(back_color);
			circle(info.x + info.size_x / 2, info.y + info.size_y / 2, sqrt(pow(info.size_y + 7, 2) + pow(info.size_x + 7, 2)) / 2);
			setlinestyle(0, SOLID_LINE, 1);
		}
		///LoadFormFile Hover
		if (loadFromFile.contains(hover_x, hover_y)) {
			setlinestyle(0, SOLID_LINE, 3);
			setcolor(primary);
			rectangle(loadFromFile.x - 5, loadFromFile.y - 5, loadFromFile.x + loadFromFile.size_x + 5, loadFromFile.y + loadFromFile.size_y + 5);
			setlinestyle(0, SOLID_LINE, 1);
		}
		else {
			setlinestyle(0, SOLID_LINE, 3);
			setcolor(back_color);
			rectangle(loadFromFile.x - 5, loadFromFile.y - 5, loadFromFile.x + loadFromFile.size_x + 5, loadFromFile.y + loadFromFile.size_y + 5);
			setlinestyle(0, SOLID_LINE, 1);
		}
		///Trash Hover
		if (trash.contains(hover_x, hover_y)) {
			setlinestyle(0, SOLID_LINE, 3);
			setcolor(primary);
			rectangle(trash.x - 5, trash.y - 5, trash.x + trash.size_x + 5, trash.y + trash.size_y + 5);
			setlinestyle(0, SOLID_LINE, 1);
		}
		else {
			setlinestyle(0, SOLID_LINE, 3);
			setcolor(back_color);
			rectangle(trash.x - 5, trash.y - 5, trash.x + trash.size_x + 5, trash.y + trash.size_y + 5);
			setlinestyle(0, SOLID_LINE, 1);
		}



		if (back.contains(mouse_x, mouse_y)) {
			mouse_x = mouse_y = 0;
			delete_variables();
			delete []inputbuf;
			delete []expresie;
			delete temp;
			return;
		}
		if (arbbuton.contains(mouse_x, mouse_y)) {

			mouse_x = mouse_y = 0;
			int current_window = getcurrentwindow();
			if (temp == "")
				console.log("No string to generate tree!", colors(secondary));
			else if (!ok_for_arb) 
				console.log("String must be a valid equation!", colors(secondary));
			else {
				try {
					desenArb(temp); // <- aici fac un new window
				}
				catch (invalid_argument& e) {
					setcurrentwindow(current_window);
					console.log(e.what(), colors(secondary));
				}
				setcurrentwindow(current_window);
			}
		}
		if (info.contains(mouse_x, mouse_y)) {
			int current_window = getcurrentwindow();
			info_s(); 
			setcurrentwindow(current_window);
			console.clear();
			mouse_x = mouse_y = 0;
		}
		if (loadFromFile.contains(mouse_x, mouse_y)) {
			char c, buf[256];
			GetCurrentDirectory(256, buf);
			string response = openDialog();
			SetCurrentDirectory(buf);

			if (!response.empty()) {

				console.clear();
				reset(expresie, levelec, expresie_pos, temp);
				overflow = false;
				ifstream fin(response);
				int level = 0, pos = 0;
				levelec = expresie_pos = 0;
				ok_for_arb = false;
				while (fin.get(c)) {
					if (c >= ' ' && c <= '~') {
						expresie[level][pos++] = c;
						expresie[level][pos] = 0;
						expresie_pos++;
					}
					if (pos > 33) {
						level++; levelec++;
						pos = 0; expresie_pos = 0;						
					}
				}
				if (levelec >= 5) {
					setcolor(WHITE);
					outtextxy(910, 180 + 0, _strdup("Press 'Enter' to evaluate"));
					outtextxy(910, 180 + 40, _strdup("Press the 'Trash' icon to delete"));
					outtextxy(910, 180 + 80, _strdup("Press the 'File' icon to reupload"));
					if (response.size() > 190) {
						response = response.substr(0, 190);
						response += "...";
					}
					console.log("Too much text for this window!   Content from " + response + " saved in background!", colors(secondary));
					overflow = true;
				}
				loaded_from_file = true;
				setcolor(WHITE);
				for(int i=0; i<levelec && !overflow; i++)
					outtextxy(910, 180 + (i * 40), expresie[i]);
			}
			mouse_x = box_ecuatie.x + 10;
			mouse_y = box_ecuatie.y + 10;
		}
		if (trash.contains(mouse_x, mouse_y)) {
			reset(expresie, levelec, expresie_pos, temp);
			mouse_x = box_ecuatie.x + 10;
			mouse_y = box_ecuatie.y + 10;
			loaded_from_file = overflow = false;
		}
	
		/// InputBox ul de variabile	
		if (box_var.contains(mouse_x, mouse_y)) {
			box_var.state = CLICKED;
			setcolor(primary);
			setlinestyle(0, SOLID_LINE, 3);
			rectangle(box_var.x+1, box_var.y + 1, box_var.x + box_var.size_x - 1, box_var.y + box_var.size_y - 1);
			setcolor(WHITE);
			setlinestyle(0, SOLID_LINE, 1);
		}
		else {
			box_var.state = ACTIVE;
			setlinestyle(0, SOLID_LINE, 10);
			setcolor(back_color);
			rectangle(box_var.x, box_var.y, box_var.x + box_var.size_x, box_var.y + box_var.size_y );
			setlinestyle(0, SOLID_LINE, 1);

		}
		if (box_var.state == CLICKED) {
			bool ok;
			char s[10];
			do {
				ok = true;
				if (level != 17) {
					aux = string(to_string(level + 1) + ".");
					s[0] = 0;
					strcpy(s, aux.c_str());
					outtextxy(360, 180 + (level * 40), s);
					outtextxy(420, 180 + (level * 40), inputbuf[level]);
				}
				if (kbhit()) c = getch(); ///daca apas o tasta, mi- inregistreaza in variabila C
				else break;
				//console.log(to_string(input_pos));
				if (input_pos > 19) {
					input_pos = 19;
					console.log("Error: Maximum number of characters reached!", colors(secondary));
					setcolor(WHITE);
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
						s[0] = 0;
						strcpy(s, aux.c_str());
						setcolor(back_color);
						outtextxy(360, 180 + (level * 40), s);

						setcolor(WHITE);
						level--;
						//Scriu nivelul curent
						aux = string(to_string(level + 1) + ".");
						s[0] = 0;
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
					else if (input_pos < 0) input_pos = 0;

					break;
				case 13: //return
					console.clear();
					if (level >= 17) {
						console.log("Error: Maximum number of variables reached!", colors(secondary));
						level = 17;  break;
					}
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

						input_pos = 0;
						level++;
					}
					break;

				case 9: ///Tab
					box_var.state = INACTIVE;
					mouse_x = box_ecuatie.x + 10;
					mouse_y = box_ecuatie.y + 10;
					break;
				default:
					if (input_pos < 10000 && c >= ' ' && c <= '~' && level < 17) {
						inputbuf[level][input_pos++] = c;
						inputbuf[level][input_pos] = 0;
					}
				}
			} while (ok && box_var.state == CLICKED);
		}
	
		/// InputBox ul de Expresie
		if (box_ecuatie.contains(mouse_x, mouse_y)) {
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
				setcolor(WHITE);
				///Scriu expresia
				if(!overflow) outtextxy(910, 180 + (levelec * 40), expresie[levelec]);
				
				if (kbhit()) c = getch();
				else break;
				

				if (expresie_pos > 33 && levelec < 6) {
					levelec++;
					expresie_pos = 0;
				}
				else if (expresie_pos > 33 && levelec == 6) expresie_pos = 33;
					
				if(!loaded_from_file || loaded_from_file && !overflow || loaded_from_file && (c == 13 || c == 8))
					switch (c) {
					case 8: //backspace
						console.clear();
						if (overflow) {
							reset(expresie, levelec, expresie_pos, temp);
							loaded_from_file = overflow = false;
							break;
						}
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
							while (!infix.empty()) infix.pop();
							expr_s = temp;
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
							ok_for_arb = 0;
						}
						if (ok_expression) {
							console.log(to_string(val_expression));
							ok_for_arb = 1;
						}
						break;

					case 9: ///Tab
						box_ecuatie.state = INACTIVE;
						mouse_x = box_var.x + 10;
						mouse_y = box_var.y + 10;
						break;

					default:
						if (expresie_pos < 10000 && c >= ' ' && c <= '~') {
							console.clear();
							expresie[levelec][expresie_pos++] = c;
							expresie[levelec][expresie_pos] = 0;
						}
					}
			} while (ok && box_ecuatie.state == CLICKED);
		}
		
	}
}

void desenArb(string x) {
	int window = initwindow(screen_width, screen_height, "", 0, 0, 0, 0);
	cleardevice();
	arb T = initArb(x);
	nivels(T, 1);
	int max_column = get_max_column(T);
	int max_level = get_max_level(T);

	if (max_column > 230) {
		closegraph(window);
		throw invalid_argument("Error: Expression too long! Consider moving sub-expressions to variables!");
	}
		
	
	int contor = 0;
	setfillstyle(SOLID_FILL, back_color);
	bar(0, 0, screen_width, screen_height);

	columns(T, screen_height / max_level, screen_width / max_column, contor);
	linii(T, screen_height / max_level, screen_width / max_column);
	getch();
	//delete T;
	closegraph(window);
	return;
}

void reset(char**& expresie, int& level, int& pos, char* temp) {
	console.clear();
	setcolor(back_color);
	for (int i = 0; i <= level; i++) {
		if(i <= 6) outtextxy(910, 180 + (i * 40), expresie[i]);
		expresie[i][0] = 0;
	}
	level = pos = 0;
	strcpy(temp, "");
}

string openDialog() {

	OPENFILENAME ofn{};
	char szFile[102400]{};

	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Text Files\0*.txt\0";
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	GetOpenFileName(&ofn);
	string filename= ofn.lpstrFile;
	
	return filename;

}

void info_s() {
	console.log("Close current dialog before using this window!", colors(secondary));
	int info_window = initwindow(screen_width / 2, screen_height / 2, "", 500, 250, 0, 0);
	setcurrentwindow(info_window);
	setbkcolor(back_color);
	cleardevice();
	setcolor(secondary);
	settextstyle(8, HORIZ_DIR, 3);

	setcolor(primary);
	outtextxy(screen_width / 4 - 73, 40, _strdup("Operators:"));
	setcolor(secondary);
	outtextxy(150, 80, _strdup("+, -, /, *, ^, <, >, =, <=, >=, |, &, ()xor(), % "));

	setcolor(primary);
	outtextxy(screen_width / 4 - 73, 160, _strdup("Functions:"));
	setcolor(secondary);

	outtextxy(50, 200, _strdup("sin(), cos(), tg(), lg(), log2(), ln(), sqrt(), cbrt()"));
	outtextxy(screen_width / 4 - 96, 240, _strdup("round(), ln()"));
	
	setcolor(primary);
	outtextxy(screen_width / 4 - 73, 320, _strdup("Constants:"));
	setcolor(secondary);
	outtextxy(445, 360, _strdup("pi, e"));

	settextstyle(8, HORIZ_DIR, 2);
	outtextxy(screen_width / 5 - 72, 500, _strdup("Press any key to continue..."));
	getch();
	closegraph(info_window);
}
