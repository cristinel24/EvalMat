#pragma once
#include <queue>
#include <stack>
#include <map>
map<string, int> priot;

void init() {
	priot.insert({ "+", 1 });
	priot.insert({ "%", 1 });
	priot.insert({ "-", 1 });
	priot.insert({ "*", 2 });
	priot.insert({ "/", 2 });
	priot.insert({ "(", 3 });
	priot.insert({ ")", 3 });
}
queue<string> infix, postfix;

