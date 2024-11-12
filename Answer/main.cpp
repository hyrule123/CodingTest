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

//백준 14425 (문자열 집합) : 동적할당 사용 + 재귀 미사용
//메모리 사용량 동일, 시간 1644 ms(늘어남)
constexpr int alphabets = 'z' - 'a' + 1;

struct trie {
	~trie() {
		for (auto* p : childs) {
			delete p;
		}
	}

	void add(const string& s) {
		if (s.empty()) { return; }

		trie* cur = this;
		for (size_t i = 0; i < s.size(); ++i) {
			trie*& next = cur->childs[s[i] - 'a'];
			if (nullptr == next) {
				next = new trie;
			}
			cur = next;
		}

		cur->is_eow = true;
	}

	bool find(const string& s) {
		if (s.empty()) { return false; }

		trie* cur = this;
		for (size_t i = 0; i < s.size(); ++i) {
			trie* next = cur->childs[s[i] - 'a'];

			if (nullptr == next) {
				return false;
			}
			
			cur = next;
		}

		return cur->is_eow;
	}

	bool is_eow = false;
	trie* childs[alphabets]{};
};

void solve() {
	trie root;
	int N, M; cin >> N >> M;
	while (N--) {
		string s; cin >> s;
		root.add(s);
	}

	int count = 0;

	while (M--) {
		string s; cin >> s;
		if (root.find(s)) {
			++count;
		}
	}

	cout << count;
}