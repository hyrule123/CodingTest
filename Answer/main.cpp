#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

using namespace std;
#include <unordered_map>
#include <functional>

//바로 hash로 변환하면 얼마나 빠를지
struct str {
	str() {}

	str(const char* s) {
		strcpy(cont.s, s);
	}

	union str_to_size_t {
		size_t hash;
		char s[8];
	} cont{};

	friend void operator >> (istream& i, str& st) {
		st.cont.hash = 0;
		i >> st.cont.s;
	}

	struct hasher {
		size_t operator()(const str& s) const {
			return s.cont.hash;
		}
	};

	bool operator == (const str& s) const {
		return cont.hash == s.cont.hash;
	}
};

struct bitmask {

	void add(int s) {
		mask = mask | (1 << s);
	}
	void remove(int s) {
		mask = mask & ~(1 << s);
	}
	int check(int s) {
		return !!(mask & (1 << s));
	}
	void toggle(int s) {
		mask = mask ^ (1 << s);
	}
	void all() {
		mask = 0xff'ff'ff'ff;
	}
	void empty() {
		mask = 0;
	}

	int mask{};
};

unordered_map<str, function<void()>, str::hasher> actions;

void solve() {
	bitmask bm{};

	actions["add"] =
		[&]() ->void {
		int val; cin >> val;
		bm.add(val);
		};
	actions["remove"] =
		[&]() ->void {
		int val; cin >> val;
		bm.remove(val);
		};
	actions["check"] =
		[&]() ->void {
		int val; cin >> val;
		cout << bm.check(val) << '\n';
		};
	actions["toggle"] =
		[&]() ->void {
		int val; cin >> val;
		bm.toggle(val);
		};
	actions["all"] =
		[&]() ->void {
		bm.all();
		};
	actions["empty"] =
		[&]() ->void {
		bm.empty();
		};

	int N; cin >> N;
	str incom;
	while (N--) {
		cin >> incom;
		actions[incom]();
	}
}