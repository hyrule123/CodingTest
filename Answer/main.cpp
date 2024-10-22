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

#include <vector>
//모두 같은 키로 50만명이 서있을 때 (50만)Combination(2) -> 1000억 넘어감
using int64 = std::int64_t;
struct person {
	int64 same_height_count;
	int height;
};
int N;
std::vector<person> stk;

void solve() {
	std::cin >> N;
	
	stk.reserve(500000);
	int64 pair_count = 0;
	for (int i = 0; i < N; ++i) {
		person p;
		p.same_height_count = 1;
		std::cin >> p.height;

		//자신보다 키가 작은 사람이 있을 경우 전부 꺼내서 pair 수를 포함시킨다
		while (false == stk.empty() && stk.back().height < p.height) {
			pair_count += stk.back().same_height_count;
			stk.pop_back();
		}

		if (false == stk.empty()) {
			//키가 같으면
			if (stk.back().height == p.height) {
				//합쳐준다. 키 같은사람이 또 추가되면 그만큼의 조합이 또 만들어지므로 
				p.same_height_count += stk.back().same_height_count;

				//기존의 같은키 여러명으로 만들어지는 조합을 pair에 포함.
				pair_count += stk.back().same_height_count;
				
				//합쳤으므로 기존건 제거
				stk.pop_back();

				//앞 사람이 서있다면 그걸로 pair + 1
				if (false == stk.empty()) {
					++pair_count;
				}
			}

			//앞사람이 나보다 키가 클 경우 +1 조합이 만들어짐
			else {
				++pair_count;
			}
		}

		stk.push_back(p);
	}

	std::cout << pair_count;
}