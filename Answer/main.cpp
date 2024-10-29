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

#include <string>
constexpr string_view commands[] = { "add", "remove", "check", "toggle", "all", "empty" };
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

void solve() {
	bitmask bm{};
	int N; cin >> N;
	string incom;
	while (N--) {
		cin >> incom;

		if (incom == "add") {
			int val; cin >> val;
			bm.add(val);
		}
		else if (incom == "remove") {
			int val; cin >> val;
			bm.remove(val);
		}
		else if (incom == "check") {
			int val; cin >> val;
			cout << bm.check(val) << '\n';
		}
		else if (incom == "toggle") {
			int val; cin >> val;
			bm.toggle(val);
		}
		else if (incom == "all") {
			bm.all();
		}
		else if (incom == "empty") {
			bm.empty();
		}
	}
}