#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1956 (운동)
*/
//다익스트라 사용

using uint = unsigned int;
uint V, E;
#include <vector>
template <typename T>
struct PriorityQueue {
	void Insert(T t) {
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

	T Pop() {
		T ret = cont.front();
		std::swap(cont.front(), cont.back());

		cont.resize(cont.size() - 1);
		if (cont.size() < 2) { return ret; }

		size_t cur = 0;
		const size_t end = (cont.size() - 1) / 2;
		while (cur < end) {
			size_t minIdx = cur;
			size_t left = cur * 2 + 1;
			size_t right = left + 1;
			if (left < cont.size() && cont[left] < cont[minIdx]) {
				minIdx = left;
			}
			if (right < cont.size() && cont[right] < cont[minIdx]) {
				minIdx = right;
			}

			if (minIdx != cur) {
				std::swap(cont[minIdx], cont[cur]);
				cur = minIdx;
			}
			else { break; }
		}

		return ret;
	}

	std::vector<T> cont;
};
struct Path {
	uint pos, dist;
	auto operator <=> (const Path& other) const {
		return dist <=> other.dist;
	}
};
PriorityQueue<Path> pq;
std::vector<Path> edges[401];
constexpr uint INF = std::numeric_limits<uint>::max();
uint dists[401]; //dp

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//Input
	pq.cont.reserve(500);
	std::cin >> V >> E;
	for (uint i = 0; i < E; ++i) {
		uint a, b, c; std::cin >> a >> b >> c;
		edges[a].push_back({ b, c });
	}

	uint shortest = INF;
	for (uint from = 1; from <= V; ++from) {
		memset(dists, 0xff, sizeof(uint) * 401);
		pq.cont.clear();

		for (const Path& edge : edges[from]) {
			pq.Insert(edge);
			dists[edge.pos] = edge.dist;
		}

		while (false == pq.cont.empty()) {
			Path cur = pq.Pop();

			//pq에서 꺼낸 기록 중 최초로 시작점과 끝점이 같은게 나오면 최단거리이므로 출력 후 return
			if (from == cur.pos) {
				shortest = std::min(shortest, cur.dist);
				break;
			}

			//현재 기록된 거리보다 짧거나 같을시에만 갱신한다.(거리가 같을시에도 시행해야 우선순위 큐 데이터를 추가 가능)
			else if (cur.dist <= dists[cur.pos]) {

				for (const Path& edge : edges[cur.pos]) {
					//간선이 있을 경우
					if (edge.dist != INF) {
						//from부터 next까지의 거리
						uint nextDist = cur.dist + edge.dist;

						//from->next 거리가 기록된 거리보다 짧을 경우에만 갱신하고 우선순위 큐에 넣어준다.
						if (nextDist < dists[edge.pos]) {
							dists[edge.pos] = nextDist;
							pq.Insert({ edge.pos, nextDist });
						}
					}
				}
			}
		}
	}

	if (shortest == INF) {
		std::cout << -1;
	}
	else {
		std::cout << shortest;
	}

	return 0;
}