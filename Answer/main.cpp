#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 9370 (미확인 도착지)
*/
using uint = unsigned int;
#include <vector>
struct travel {
	uint pos, dist;
	auto operator <=>(const travel& other) const {
		return dist <=> other.dist;
	}
};

template <typename T>
void Heapify(std::vector<T>& cont, size_t start, size_t end) {
	if (end < 1) { return; }
	size_t parentEnd = (end - 1) / 2;
	while (start <= parentEnd) {
		size_t minIdx = start;
		size_t left = minIdx * 2 + 1;
		size_t right = left + 1;

		if (left <= end && cont[left] < cont[minIdx]) {
			minIdx = left;
		}
		if (right <= end && cont[right] < cont[minIdx]) {
			minIdx = right;
		}

		if (minIdx != start) {
			std::swap(cont[minIdx], cont[start]);
			start = minIdx;
		}
		else { return; }
	}
}

//내림차순으로 정렬되므로 주의
template <typename T>
void HeapSort(std::vector<T>& cont) {
	if (cont.size() < 2) { return; }

	for (size_t i = (cont.size() - 2) / 2; i != -1; --i) {
		Heapify(cont, i, cont.size() - 1);
	}

	size_t size = cont.size();
	while (--size) {
		std::swap(cont[0], cont[size]);

		Heapify(cont, 0, size - 1);
	}
}

template <typename T>
void InsertHeap(std::vector<T>& cont, T t) {
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

template <typename T>
T PopHeap(std::vector<T>& cont) {
	T ret = cont.front();

	std::swap(cont.front(), cont.back());
	cont.resize(cont.size() - 1);
	if (2 <= cont.size()) {
		Heapify(cont, 0, cont.size() - 1);
	}

	return ret;
}
/*
* 용의자는 s에서 시작한다.
* s에서 g -> h 또는 h -> g로 이동
* h -> t로 이동 또는 g -> t로 이동
* 경우의 수: 2 * t
*/
uint T, n, m, t, s, g, h;
std::vector<travel> edges[2001];
uint dp[2001];
constexpr uint INF = (uint)1e9;
std::vector<travel> heap;
struct answer { 
	uint minDist, result = INF;
};
std::vector<uint> dests;
std::vector<answer> ans;

void Djikstra(travel start, const std::vector<uint>& dests) {
	heap.clear();
	for (size_t i = 0; i < 2001; ++i) {
		dp[i] = INF;
	}

	InsertHeap(heap, start);
	while (false == heap.empty()) {
		travel from = PopHeap(heap);

		if (INF != dp[from.pos]) { continue; }
		dp[from.pos] = from.dist;

		bool allFound = true;
		for (size_t i = 0; i < dests.size(); ++i) {
			if (dp[dests[i]] == INF) {
				allFound = false;
				break;
			}
		}
		if (allFound) { return; }

		for (size_t to = 0; to < edges[from.pos].size(); ++to){
			travel dest;
			dest.pos = edges[from.pos][to].pos;
			dest.dist = from.dist + edges[from.pos][to].dist;
			InsertHeap(heap, dest);
		}
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	std::cin >> T;
	while (T--) {
		//초기화
		for (uint i = 0; i < 2001; ++i) {
			edges[i].clear();
		}
		heap.clear();

		//INPUT
		std::cin >> n >> m >> t >> s >> g >> h;
		for (uint i = 0; i < m; ++i) {
			uint a, b, d; std::cin >> a >> b >> d;
			edges[a].push_back({ b, d });
			edges[b].push_back({ a, d });
		}

		dests.clear(); dests.resize(t);
		ans.clear(); ans.resize(t);
		for (uint i = 0; i < t; ++i) {
			std::cin >> dests[i];
		}
		//내림차순 정렬
		HeapSort(dests);

		//먼저, s -> t를 계산한다.
		Djikstra({ s, 0 }, dests);

		//최단거리를 기록
		for (size_t i = 0; i < dests.size(); ++i) {
			ans[i].minDist = dp[dests[i]];
		}
		
		//g, h를 도착점으로 검사
		Djikstra({ s, 0 }, { g, h });
		uint s2g = dp[g];
		uint s2h = dp[h];
		
		//g-h 사이의 간선 길이를 확인
		uint gh{};
		for (size_t i = 0; i < edges[g].size(); ++i) {
			if (edges[g][i].pos == h) {
				gh = edges[g][i].dist;
				break;
			}
		}

		//s->h->g->t
		if (s2h != INF) {
			Djikstra({ g, s2h + gh }, dests);
			for (size_t i = 0; i < dests.size(); ++i) {
				ans[i].result = std::min(ans[i].result, dp[dests[i]]);
			}
		}

		//s->g->h->t
		if (s2g != INF) {
			Djikstra({ h, s2g + gh }, dests);
			for (size_t i = 0; i < dests.size(); ++i) {
				ans[i].result = std::min(ans[i].result, dp[dests[i]]);
			}
		}

		//내림차순으로 정렬되었으므로 역순회
		for (size_t i = ans.size() - 1; i != -1; --i) {
			//최소 거리가 INF가 아니면서 최소거리와 gh 경유 거리가 같을 경우 답안 작성
			if (ans[i].minDist != INF && ans[i].minDist == ans[i].result) {
				std::cout << dests[i] << ' ';
			}
		}

		std::cout << '\n';
	}

	return 0;
}