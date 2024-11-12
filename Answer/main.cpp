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

#include <list>
#include <vector>
#include <string>
#include <map>

struct trie {
	void add_child(int _level, const vector<string_view>& branch) {
		if (level < _level) {
			trie& child = childs[branch[level]];

			//새로 생성 되었다면
			if (-1 == child.level) {
				child.level = level + 1;
				child.s = branch[level];
			}

			child.add_child(_level, branch);
		}
	}
	
	void print_recursive() const {
		
		for (int i = 2; i <= level; ++i) {
			cout << "--";
		}

		if (0 < level) {
			cout << s << '\n';
		}

		for (const auto& child : childs) {
			child.second.print_recursive();
		}
	}

	int level = -1;
	string_view s;
	map<string_view, trie> childs;
};

void solve() {
	trie root;
	root.level = 0;

	int N; cin >> N;

	//string은 list에 저장해두고 string_view를 사용
	list<string> strings;

	for (int i = 0; i < N; ++i) {
		int level;
		vector<string_view> branches;
		cin >> level;
		for (int i = 1; i <= level; ++i) {
			string s; cin >> s;
			strings.push_back(s);
			branches.push_back(strings.back());
		}

		root.add_child(level, branches);
	}

	root.print_recursive();
}