#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

/* функция вычисляет максимальную длину суффикса строки s1, совпадающей с префиксом строки s2*/
int overlap(string s_suff, string s_preff) {
	int s1_last = s_suff.size() - 1;
	int overlap = 0;
	for (int i = s1_last, j = 1; i > 0 && j < s_preff.size(); i--, j++) {
		string suff = s_suff.substr(i);
		string preff = s_preff.substr(0, j);
		if (suff == preff) {
			overlap = j;
		}
	}
	return overlap;
}
/*функция возвращает часть строки без overlapa*/
string Prefix(string s1, int ovrlp) {
	return s1.substr(0, s1.size() - ovrlp);
}