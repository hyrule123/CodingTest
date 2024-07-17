#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <cstring> //memset
/*
백준 1697 (숨바꼭질)
*/
struct CircleQueue {

	bool Empty() { return size == 0; }
	int Next(int cur) { if (++cur >= cap) { cur -= cap; } return cur; }

	void PushBack(int i) { cont[end] = i; end = Next(end); ++size; }
	int PopFront() { int ret = cont[start]; start = Next(start); --size; return ret; }

	static constexpr int cap = 50000;
	int cont[cap]{}, size{}, start{}, end{};
} q;
int N, K, K2;
#include <array>
using arr = std::array<int, 100001>;
constexpr arr Fill() { arr a; a.fill(-1); return a; }
arr arriveTime = Fill();
int BFS() {
	arriveTime[N] = 0;
	q.PushBack(N);

	int ret = 0;
	while (false == q.Empty()) {
		int cur = q.PopFront();
		if (cur == K) { 
			ret = arriveTime[cur]; break; }

		int next = cur * 2;
		if (next <= K2 && arriveTime[next] == -1) { 
			arriveTime[next] = arriveTime[cur] + 1;
			q.PushBack(next); 
		}
		next = cur + 1;
		if (next <= K && arriveTime[next] == -1) { 
			arriveTime[next] = arriveTime[cur] + 1;
			q.PushBack(next); 
		}
		next = cur - 1;
		if (0 <= next && arriveTime[next] == -1) { 
			arriveTime[next] = arriveTime[cur] + 1;
			q.PushBack(next); 
		}
	}

	return ret;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N >> K;
	//K * 2 이상 가면 차라리 -1씩 해서 내려오는게 나을듯
	K2 = std::min(100000, K * 2);
	std::cout << BFS();

	return 0;
}