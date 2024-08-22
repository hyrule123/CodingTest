#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 13913 (숨바꼭질 4)
*/
//N은 현재 위치에서 3가지 선택지를 가진다
//-1, +1, *2
//최단 거리를 구해야 하므로 BFS를 사용
//BFS가 이미 들렀던 곳은 최단거리 -> 다시 들를 필요가 없다.(메모할 공간이 필요)
//
#include <queue>
#include <stack>
constexpr int MAX = 100001;
int N, K;
enum move_type {
	NONE, mul2, sub1, add1
};
struct m { 
	int time = -1, type = NONE; //어떤 방식으로 해당 위치에 도달했는지
};
m memo[MAX];	//dp[i]: N->i로 가는 데 걸린 시간

struct travel {
	int pos, time;
	move_type type;
};
std::queue<travel> trace;

void BFS() {
	trace.push({ N, 0 });

	while (false == trace.empty()) {
		travel t = trace.front();
		trace.pop();

		if (memo[t.pos].time != -1) { continue; }

		memo[t.pos].time = t.time;
		memo[t.pos].type = t.type;
		if (t.pos == K) {
			break;
		}

		//*2 했을 때 도착값보다 2 이상 크다면 차라리 -1 하고 * 2 하는게 더 빠름
		//ex) 현재 7, 목적지 11: 7 -> 6 -> 12 -> 11
		travel next;
		next.time = t.time + 1;

		next.pos = t.pos * 2;
		if (next.pos < MAX && next.pos <= K + 2) {
			next.type = mul2;
			trace.push(next);
		}

		next.pos = t.pos - 1;
		if (0 <= next.pos) {
			next.type = sub1;
			trace.push(next);
		}

		next.pos = t.pos + 1;
		if (next.pos <= K) {
			next.type = move_type::add1;
			trace.push(next);
		}
	}
}

//K부터 기록을 역순으로 타고 N으로 이동하면서 stack에 넣는다
void trace_back() {
	std::stack<int> ans;
	int pos = K;
	while (pos != N) {
		ans.push(pos);

		switch (memo[pos].type)
		{
		case move_type::mul2:
			pos /= 2;
			break;
		case move_type::sub1:
			pos += 1;
			break;
		case move_type::add1:
			pos -= 1;
			break;
		default:
			return;
		}
	}

	std::cout << N << ' ';
	while (false == ans.empty()) {
		std::cout << ans.top() << ' ';
		ans.pop();
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N >> K;

	//BFS
	BFS();
	//최단시간 출력
	std::cout << memo[K].time << '\n';
	trace_back();

	return 0;
}