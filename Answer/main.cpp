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

//red-black tree를 사용하는 set을 통해 이중 우선순위큐 구현
#include <string>
#include <vector>
#include <map>
using namespace std;

map<int, int> dpq;
void pop_max() {
    if (dpq.empty()) { return; }
    auto iter = --(dpq.end());
    --(iter->second);
    if (iter->second <= 0) {
        dpq.erase(iter);
    }
}

void pop_min() {
    if (dpq.empty()) { return; }
    auto iter = dpq.begin();
    --(iter->second);
    if (iter->second <= 0) {
        dpq.erase(iter);
    }
}

int T, k;
void solve() {
    std::cin >> T;
    while (T--) {
        dpq.clear();

        std::cin >> k;
        while (k--) {
            char type; int input;
            std::cin >> type >> input;

            if (type == 'I') {
                dpq[input] += 1;
            }
            else {
                if (-1 == input) {
                    pop_min();
                }
                else {
                    pop_max();
                }
            }
        }

        if (dpq.empty()) {
            std::cout << "EMPTY\n";
        }
        else {
            std::cout << (--dpq.end())->first << ' ' << (dpq.begin())->first << '\n';
        }
    }
}