#pragma once
bool check_variable(char*);
void delete_var(char*);
void delete_variables();



bool check_variable(char* s) {
	char variabila[NMAX]; strcpy(variabila, s);
	char* pch = strchr(variabila, '=');
	char valoare[1024];
	if (pch != NULL && *(pch+1)!=NULL)
		strcpy(valoare, pch + 1);
	else return 0;

	string x = valoare;
	variables(x);
	strcpy(valoare, x.c_str());
	///dau check sa vad daca exista ")("
	for (int i = 1; i < strlen(valoare); i++)
		if (x[i] = '(' && x[i - 1] == ')') throw invalid_argument("Operator missing!");
	
	if (valoare[strlen(valoare) - 1] == ';') valoare[strlen(valoare) - 1] = 0;
	*pch = 0;
	int i = 0; bool isokvar = 1, isokval = 1;
	for (i = 0; i < strlen(variabila); i++) {
		if (i == 0 && !isalpha(variabila[0])) isokvar = 0;
		else if (!(isalnum(variabila[i]) || variabila[i]=='_')) isokvar = 0;
	}
	if (!isokvar) return 0;
	coada infix; string val_s = valoare, var_s = variabila;
	
	double val=NULL;
	try {
		parse(val_s);
		init_coada(val_s, infix);
		val = valpostfix(infix);
	}
	catch (invalid_argument& e) {
		throw invalid_argument(e.what());
		return 0;
	}
	if (val!=INFINITE && variabila) {
		if (variabile_map.find(var_s) != variabile_map.end()) {
			/*string err ="'" + var_s + "' was already defined!";
			throw invalid_argument(err);*/
			variabile_map.erase(var_s);
		}
		variabile_map.insert({ var_s, val });
	}
	return 1;
}
void delete_var(char* s) {
	char variabila[NMAX]; strcpy(variabila, s);
	char* pch = strchr(variabila, '=');
	*pch = 0;
	variabile_map.erase(variabila);
	//cout << "Am sters din map variabila: " << variabila << '\n';
}
void delete_variables() {
	variabile_map.erase(variabile_map.begin(), variabile_map.end());
}