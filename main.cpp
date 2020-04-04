#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/* 4-приближенный алгоритм нахождения наименьшей общей надстроки*/
int main() {
	char c;
	vector <string> string_set;
	string curr_string;
	/* считывание всех строк в string_set*/
    for (;;) {
		cin.get(c);
		while (c != ' ' && c != '\n') {
			curr_string.push_back(c);
			cin.get(c);
		}
		string_set.push_back(curr_string);
		curr_string.clear();
		if ((int)c == 10) {  /* 10 - ASCII код символа конца строки*/
			break;
		}
	}
	/* считаем и храним в матрице overlap для всех строк*/
	int n = string_set.size();
	vector <vector<int>> overlaps;
	for (int i = 0; i < n; i++) {
		overlaps.push_back(vector<int>());
		for (int j = 0; j < n; j++) {
			overlaps[i].push_back(overlap(string_set[i], string_set[j]));
		}
	}
	vector <vector<int>> cycles;
	vector <int> cycle;
	vector <int > assign = Assignment(overlaps);
	vector <bool> mark(assign.size(), false);

    /* нвходим покрытие циклами */
	for (int i = 0; i < assign.size(); i++) {
		if (mark[i]) {
			continue;
		}
		cycle.push_back(i);
		mark[i] = true;

		if (assign[i] == cycle[0]) {
			cycles.push_back(cycle);
			cycle.clear();
			i = 0;
		}
		else {
			i = assign[i] - 1;
		}
	}
    /* переставляем строки в каждом цикле так, чтобы overlap последней и первой строки был минимален*/
	vector <string> superstrings;
	for (vector<int> c: cycles) {
		string str = "";
		vector <int> ovs;
		ovs.reserve(c.size() - 1);
		for (int i = 0; i < c.size() - 1; i++) {
			ovs.push_back(overlaps[c[i]][c[i + 1]]);
		}

		int min = overlaps[c[c.size() - 1]][c[0]];
		int shift = 0;

		for (int i = 0; i < ovs.size(); i++) {
			if (ovs[i] < min) {
				min = ovs[i];
				shift = i + 1;
			}
		}
		rotate(c.begin(), c.begin() + shift, c.end());
		for (int i = 0; i < c.size() - 1; i++) {
			str += Prefix(string_set[c[i]], overlaps[c[i]][c[i + 1]]);
			
		}
		str += string_set[c[c.size() - 1]];
		superstrings.push_back(str);
	}
	/*конкатенация всех надстрок в одну*/
    string superstring = "";
	for (string str : superstrings) {
		superstring += str;
	}
	cout << superstring << endl;
	system("pause");
	return 0;
}