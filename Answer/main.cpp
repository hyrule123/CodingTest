#include <vector>
#include <queue>
using namespace std;

int end_x, end_y;
struct coord {
    int x, y, dist;
    coord operator +(const coord& other) const {
        return { x + other.x, y + other.y };
    }
    bool invalid() {
        return x < 0 || y < 0 || end_x < x || end_y < y;
    }
};
constexpr coord directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
constexpr int numdir = sizeof(directions) / sizeof(coord);

int solution(vector<vector<int>> maps)
{
    end_x = (int)maps.size() - 1; end_y = (int)maps[0].size() - 1;

    vector<vector<int>> dist;
    queue<coord> q;
    q.push({ 0, 0, 0 });
    while (false == q.empty()) {
        const coord& c = q.front();

        maps[c.x][c.y] = c.dist - 1;
        if (c.x == end_x && c.y == end_y) {
            return -maps[c.x][c.y];
        }

        for (int i = 0; i < numdir; ++i) {
            coord next = c + directions[i];
            if (next.invalid() || maps[next.x][next.y] != 1) { continue; }
            maps[next.x][next.y] = 0;
            next.dist = c.dist - 1;
            q.push(next);
        }

        q.pop();
    }

    return -1;
}


int main() {
    auto ans = solution({{1, 0, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 0, 1, 1, 1}, {1, 1, 1, 0, 1}, {0, 0, 0, 0, 1}} );
    return 0;
}