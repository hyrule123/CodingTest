#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;

void solve();

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;

	solve();
	return 0;
}
/*
백준 25206 (너의 평점은) [수학?][복습]
*/
#include <string>
#include <map>
constexpr const char* strs[] = { "A+", "A0", "B+", "B0", "C+", "C0", "D+", "D0"};

void solve() {
	map<string, double> grades;
	for (int i = 0; i < sizeof(strs) / sizeof(const char*); ++i) {
		grades[strs[i]] = 4.5 - (0.5 * (double)i);
	}
	grades["F"] = 0;
	grades["P"] = 0;

	double score_sum{}, count{};
	double score{}; string name{}, grade{};
	while (cin >> name >> score >> grade) {
		if (grade == "P") { continue; }
		score_sum += score * grades[grade];
		count += score;
	}

	cout << score_sum / count;
}