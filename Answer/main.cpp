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

#include <vector>
#include <iomanip>
#include <cmath>

constexpr int alphabets = 'z' - 'a' + 1;

struct trie {
	bool is_word_end;
	char num_childs;	//등록된 자식의 수
	int childs[alphabets];
};

int N, allocater_idx = 0;
vector<string> inputs;

//단어의 총합 길이가 10e6을 넘지 않는다고 했으므로 정적 배열을 사용
trie tries[(int)1e6 + 1];
int new_trie() { return ++allocater_idx; }

void clear() {
	allocater_idx = 0;
	memset(tries, 0, sizeof(tries));
	inputs.clear();
}

void add_trie(const string& str) {
	int cur = 0;
	for (size_t i = 0; i < str.size(); ++i) {
		int& child_idx = tries[cur].childs[str[i] - 'a'];
		if (0 == child_idx) {
			++(tries[cur].num_childs);
			child_idx = new_trie();
		}
		cur = child_idx;
	}
	tries[cur].is_word_end = true;
}

int get_input_count(const string& str) {
	int count = 1;	//첫 분기 입력은 무조건 수동

	int cur = tries[0].childs[str[0] - 'a'];
	for (size_t i = 1; i < str.size(); ++i) {
		//(안 끝났는데) 단어의 끝 발견 시 또는 분기 발견 시 +1
		if (tries[cur].is_word_end || 1 < tries[cur].num_childs) {
			++count;
		}
		cur = tries[cur].childs[str[i] - 'a'];
	}

	return count;
}

void solve() {
	cout << fixed << setprecision(2);
	while (cin >> N) {
		clear();

		inputs.resize(N);
		for (int i = 0; i < N; ++i) {
			inputs[i].reserve(80);
			cin >> inputs[i];
			add_trie(inputs[i]);
		}

		int count = 0;
		for (const string& s : inputs) {
			count += get_input_count(s);
		}
		double ans = (double)count / (double)N;
		cout << round(ans * 100.0) / 100.0 << '\n';
	}
}