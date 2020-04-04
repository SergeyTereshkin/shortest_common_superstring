#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
/*функция вычисляет полное назначение максимального веса*/
vector <int> Assignment(vector <vector<int>> a) {
	int n = a.size();
	vector <vector<bool>> notallow;
	for (int i = 0; i < n; i++) {
		notallow.push_back(vector<bool>());
		for (int j = 0; j < n; j++) {
			notallow[i].push_back(false);
		}
	}
	vector <int> result_assignment(a.size());
	while (true) {
		int max = -1;
		int max_j = -1;
		int max_i = -1;
		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < a.size(); j++) {
				if (notallow[i][j]) continue;
				if (a[i][j] > max) {
					max = a[i][j];
					max_i = i;
					max_j = j;
				}
			}
		}
		if (max == -1) {
			break;
		}
		result_assignment[max_i] = max_j;
		for (int i = 0; i < a.size(); i++) {
			notallow[max_i][i] = true;
			notallow[i][max_j] = true;
		}
	}
	return result_assignment;
}