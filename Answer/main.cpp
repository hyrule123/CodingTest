#include <string>
#include <vector>
#include <queue>
using namespace std;

struct edge {
    int dest, cost;
    auto operator <(const edge& other) const {
        return this->cost > other.cost;
    }
};
vector<vector<edge>> edges;
vector<bool> visited;
priority_queue<edge> pq;

int solution(int nodes, vector<vector<int>> costs) {
    int total_cost = 0;

    edges.resize(nodes);
    visited.resize(nodes);
    for (const vector<int>& e : costs) {
        edges[e[0]].push_back({ e[1], e[2] });
        edges[e[1]].push_back({ e[0], e[2] });
    }

    //0부터 Prim MST
    visited[0] = true;
    for (const edge& e : edges[0]) {
        pq.push(e);
    }

    int left_edge = nodes - 1;
    while (false == pq.empty()) {
        edge e = pq.top(); pq.pop();

        if (visited[e.dest]) { continue; }
        visited[e.dest] = true;
        total_cost += e.cost;
        --left_edge;
        if (left_edge == 0) {
            break;
        }

        for (const edge& next : edges[e.dest]) {
            pq.push(next);
        }
    }

    return total_cost;
}

int main() {
    auto ans = solution(4, {{0, 1, 1}, {0, 2, 2}, {1, 2, 5}, {1, 3, 1}, {2, 3, 8}});
    return 0;
}