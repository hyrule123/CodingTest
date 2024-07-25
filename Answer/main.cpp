#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1504 (특정한 최단 경로)
*/
//양방향 a-b, 길이 c, 반드시 지나야 하는 정점 v1, v2
//v1 -> v2 -> N
//v2 -> v1 -> N
//둘 중 작은 수를 출력한다.
using uint = unsigned int;
#include <vector>
struct travel {
	uint pos{}, dist{};
	bool operator < (const travel& other) const {
		return dist < other.dist;
	}
};
struct minHeap {
	void Insert(travel t) {
		cont.push_back(t);

		size_t cur = cont.size() - 1;
		while (0 < cur) {
			size_t parent = (cur - 1) / 2;

			if (cont[cur] < cont[parent]) {
				std::swap(cont[cur], cont[parent]);

				cur = parent;
			}
			else {
				break;
			}
		}
	}
	travel Pop() {
		travel ret = cont.front();
		std::swap(cont.front(), cont.back());
		cont.pop_back();
		
		if (cont.size() < 2) { return ret; }

		size_t cur = 0;
		size_t end = (cont.size() - 1) / 2;
		while (cur <= end) {
			size_t minIdx = cur;
			size_t left = minIdx * 2 + 1;
			size_t right = left + 1;
			if (left < cont.size() && cont[left] < cont[minIdx]) {
				minIdx = left;
			}
			if (right < cont.size() && cont[right] < cont[minIdx]) {
				minIdx = right;
			}

			if (cur != minIdx) {
				std::swap(cont[cur], cont[minIdx]);
				cur = minIdx;
			}
			else {
				break;
			}
		}
		
		return ret;
	}

	std::vector<travel> cont;
} heap;
uint nodes[801][801], dp[801], N, E, a, b, c, v1, v2;
constexpr uint INF = std::numeric_limits<uint>::max();

void Djikstra(uint _from, uint _to) {
	heap.Insert({ _from, 0 });

	while (false == heap.cont.empty()) {
		travel from = heap.Pop();

		if (INF != dp[from.pos]) { continue; }

		//여행거리를 기록
		dp[from.pos] = from.dist;

		//도착 시 중단
		if (_to == from.pos) {
			break;
		}

		for (uint i = 1; i <= N; ++i) {
			if (nodes[from.pos][i]) {
				//i에 도착, 여행거리 from.dist + 이번 노드 -> 다음노드까지 거리
				heap.Insert({ i, from.dist + nodes[from.pos][i] });
			}
		}
	}
}

void Reset() {
	heap.cont.clear();
	memset(dp, 0xff, sizeof(uint) * 801);
}
uint Stopover(uint first, uint second) {
	uint ret = 0;

	Reset();
	Djikstra(1, first);
	if (dp[first] == INF) { return INF; }
	ret += dp[first];

	Reset();
	Djikstra(first, second);
	if (dp[second] == INF) { return INF; }
	ret += dp[second];

	Reset();
	Djikstra(second, N);
	if (dp[N] == INF) { return INF; }
	ret += dp[N];

	return ret;
}


int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> N >> E;
	for (uint i = 0; i < E; ++i) {
		std::cin >> a >> b >> c;
		nodes[a][b] = c;
		nodes[b][a] = c;
	}
	std::cin >> v1 >> v2;
	//1 -> v1 -> v2 -> N으로 가는 경우와 1 -> v2 -> v1 -> N으로 가는 경우 2개
	uint v1Result = Stopover(v1, v2);
	uint v2Result = Stopover(v2, v1);

	uint output = std::min(v1Result, v2Result);
	if (output == INF) { std::cout << -1; }
	else { std::cout << output; }

	return 0;
}