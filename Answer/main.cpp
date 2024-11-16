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

//백준 1269 (대칭 차집합) 복습
#include <unordered_set>
unordered_set<int> a, b;

void solve() {
	int na, nb; cin >> na >> nb;
	for (int i = 0; i < na; ++i) {
		int ma; cin >> ma;
		a.insert(ma);
	}

	for (int i = 0; i < nb; ++i) {
		int mb; cin >> mb;
		
		auto iter = a.find(mb);

		if (a.end() == iter) {
			b.insert(mb);
		}
		else {
			a.erase(iter);
		}
	}

	cout << a.size() + b.size();
}