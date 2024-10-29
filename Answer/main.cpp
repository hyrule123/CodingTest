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
#include <unordered_map>
#include <functional>
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

unordered_map<string, function<void()>> actions;

void solve() {
	bitmask bm{};

	//unordered_map으로 하면 얼마나 느린지 테스트용
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
	string incom;
	while (N--) {
		cin >> incom;
		actions[incom]();
	}
}