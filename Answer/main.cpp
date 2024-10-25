#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

struct node {
    int group, rank;
};

int solution(int nodes, vector<vector<int>> costs) {
    int answer = 0;

    //disjoint set 준비
    vector<node> dj_set((size_t)(nodes + 1));
    for (int i = 0; i < (int)dj_set.size(); ++i) {
        dj_set[i].group = i;
    }

    function<int(int)> find_union =
        [&](int node)->int {
        if (dj_set[node].group != node) {
            dj_set[node].group = find_union(dj_set[node].group);
            }
        return dj_set[node].group;
        };

    function<void(int, int)> make_union =
        [&](int group_a, int group_b)->void {

        if (dj_set[group_a].rank < dj_set[group_b].rank) {
            dj_set[group_a].group = group_b;
        }
        else {
            dj_set[group_b].group = group_a;
        }

        if (dj_set[group_a].rank == dj_set[group_b].rank) {
            dj_set[group_a].rank += 1;
        }
        };

    //원 데이터 정렬
    sort(costs.begin(), costs.end(), 
        [](const vector<int>& a, const vector<int>& b)->bool
        {
            return a[2] < b[2];
        }
    );

    //Kruskal MST
    int max_edges = nodes - 1;
    for (const vector<int>& edge : costs) {
        int g_a = find_union(edge[0]);
        int g_b = find_union(edge[1]);

        //사이클이 형성되면 넣지 않는다.
        if (g_a == g_b) { continue; }

        answer += edge[2];
        if (--max_edges == 0) {
            break;
        }
        
        make_union(g_a, g_b);
    }


    return answer;
}

int main() {
    auto ans = solution(4, {{0, 1, 1}, {0, 2, 2}, {1, 2, 5}, {1, 3, 1}, {2, 3, 8}});
    return 0;
}