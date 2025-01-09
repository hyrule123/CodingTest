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
백준 1091 (카드 섞기) [구현]
* 카드를 정해진 규칙대로 섞는 것은 곧 '순열'을 의미한다.
* 순열은 반드시 사이클을 가진다. 언젠가 다시 원점으로 돌아온다는 뜻
*/
int N, cards[48][2], shuffle_order[48], player[48];
bool cur;

bool check_cards() {
	for (int i = 0; i < N; ++i) {
		int card_owner = i % 3;
		int cur_card = cards[i][cur];
		if (player[cur_card] != card_owner) {
			return false;
		}
	}
	return true;
}

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cards[i][cur] = i;
		cin >> player[i];
	}
	for (int i = 0; i < N; ++i) {
		cin >> shuffle_order[i];
	}

	int shuffle_count = 0;
	if (check_cards()) {
		cout << shuffle_count;
	}
	else {
		while (true) {
			++shuffle_count;
			cur = !cur;
			for (int i = 0; i < N; ++i) {
				cards[shuffle_order[i]][cur] = cards[i][!cur];
			}

			bool cycle = true;
			for (int i = 0; i < N; ++i) {
				cycle = cycle && (cards[i][cur] == i);
			}
			if (cycle) {
				cout << -1;
				break;
			}

			else if (check_cards()) {
				cout << shuffle_count;
				break;
			}
		}
	}
}