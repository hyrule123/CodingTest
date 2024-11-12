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

#include <unordered_set>
constexpr int alphabets = 'z' - 'a' + 1;

struct trie {
	~trie() {
		for (auto* p : childs) {
			delete p;
		}
	}

	void add(const string& s) {
		if (level == (int)s.size()) {
			is_eow = true;
			return;
		}

		if (level < (int)s.size()) {
			trie*& next = childs[s[level] - 'a'];

			if (next == nullptr) {
				next = new trie;
				next->level = level + 1;
			}

			next->add(s);
		}
	}

	bool find(const string& s) {
		//종료 조건
		if (is_eow && level == (int)s.size()) {
			return true;
		}

		trie*& next = childs[s[level] - 'a'];
		if (next) {
			return next->find(s);
		}

		return false;
	}

	int level = -1;
	bool is_eow = false;
	trie* childs[alphabets]{};
};

void solve() {
	trie root;
	root.level = 0;
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