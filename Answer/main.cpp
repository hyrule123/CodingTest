#include <string>
#include <vector>
using namespace std;
vector<bool> visited;

void recursive(int cur, int parent, const vector<vector<int>>& nodes) {
    if (visited[cur]) { return; }

    visited[cur] = true;

    for (int i = 0; i < (int)nodes[cur].size(); ++i) {
        if (i == parent || i == cur) { continue; }

        if (nodes[cur][i] == 1) {
            recursive(i, cur, nodes);
        }
    }
}

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    visited.resize(computers.size(), false);
    for (size_t i = 0; i < computers.size(); ++i) {
        if (visited[i] == false) {
            ++answer;
            recursive((int)i, -1, computers);
        }
    }

    return answer;
}

int main() {
    auto ans = solution(3, {{1, 1, 0}, {1, 1, 1}, {0, 1, 1}} );
    return 0;
}