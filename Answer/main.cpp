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
백준 1927 (최소 힙) [힙][복습]
*/
#include <vector>

int N;
struct min_heap {
	void heapify_up(int idx) {
		int cur = idx;
		while (0 < cur) {
			int par = (cur - 1) / 2;

			if (cont[cur] < cont[par]) {
				swap(cont[cur], cont[par]);
				cur = par;
			}
			else {
				break;
			}
		}
	}

	void heapify_down(int cur) {
		while (cur < size) {
			int least = cur;
			int l = cur * 2 + 1, r = l + 1;

			if (l < size && cont[least] > cont[l]) {
				least = l;
			}
			if (r < size && cont[least] > cont[r]) {
				least = r;
			}

			if (cur == least) {
				break;
			}
			else {
				swap(cont[cur], cont[least]);
				cur = least;
			}
		}
	}

	void insert(int i) {
		cont[size] = i;
		heapify_up(size);
		++size;
	}

	int pop() {
		if (size == 0) { return 0; }
		if (size == 1) { --size; return cont[0]; }

		int ret = cont[0];

		swap(cont[0], cont[--size]);
		heapify_down(0);

		return ret;
	}

	int size, cont[100'000];
} heap;

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		int input; cin >> input;
		if (input == 0) {
			cout << heap.pop() << '\n';
		}
		else {
			heap.insert(input);
		}
	}
}