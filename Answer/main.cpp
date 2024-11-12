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

//백준 14425 (문자열 집합) : 동적할당 미사용 + 재귀 미사용(정적할당 + 인덱스)
constexpr int alphabets = 'z' - 'a' + 1;

int idx = 0;
int new_node() { return ++idx; }

struct trie {
	bool is_eow = false;
	int childs[alphabets]{};
};

//단어당 길이 500, 단어 개수 10000개 -> 5백만개(+ 루트노드로 사용할 0번)
trie nodes[500 * 10000 + 1];	//nodes[0]: trie root

void add(const string& s) {
	if (s.empty()) { return; }

	int cur_idx = 0;
	for (size_t i = 0; i < s.size(); ++i) {
		int& next_idx = nodes[cur_idx].childs[s[i] - 'a'];

		if (0 == next_idx) {
			next_idx = new_node();
		}

		cur_idx = next_idx;
	}

	nodes[cur_idx].is_eow = true;
}

bool find(const string& s) {
	if (s.empty()) { return false; }

	int cur_idx = 0;
	for (size_t i = 0; i < s.size(); ++i) {
		int& next_idx = nodes[cur_idx].childs[s[i] - 'a'];

		if (0 == next_idx) {
			return false;
		}

		cur_idx = next_idx;
	}

	return nodes[cur_idx].is_eow;
}

void solve() {
	int N, M; cin >> N >> M;
	while (N--) {
		string s; cin >> s;
		add(s);
	}

	int count = 0;

	while (M--) {
		string s; cin >> s;
		if (find(s)) {
			++count;
		}
	}

	cout << count;
}