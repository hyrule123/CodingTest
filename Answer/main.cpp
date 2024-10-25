#include <vector>
#include <queue>
using namespace std;

int end_x, end_y;
struct coord {
    int x, y, dist;
    coord operator +(const coord& other) {
        return { x + other.x, y + other.y };
    }
    bool operator == (const coord& other) const {
        return { x == other.x && y == other.y };
    }
    bool valid() {
        return (0 <= x && 0 <= y && x <= end_x && y <= end_y);
    }
};
constexpr coord directions[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
constexpr int numdir = sizeof(directions) / sizeof(coord);

int solution(vector<vector<int>> maps)
{
    int answer = 0;
    end_x = (int)maps.size() - 1; end_y = (int)maps[0].size() - 1;

    queue<coord> q;
    q.push({ 0, 0, 0 });
    while (false == q.empty()) {
        coord c = q.front(); q.pop();

        maps[c.x][c.y] = c.dist - 1;
        if (c.x == end_x && c.y == end_y) {
            answer = -maps[c.x][c.y];
            break;
        }

        for (int i = 0; i < numdir; ++i) {
            coord next = c + directions[i];
            next.dist = c.dist - 1;
            if (false == next.valid() || maps[next.x][next.y] != 1) { continue; }
            q.push(next);
        }
    }

    if (maps[end_x][end_y] == 1) {
        answer = -1;
    }

    return answer;
}


int main() {
    auto ans = solution({{1, 0, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 0, 1, 1, 1}, {1, 1, 1, 0, 1}, {0, 0, 0, 0, 1}} );
    return 0;
}