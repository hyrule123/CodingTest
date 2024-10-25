#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
template <class CharType, class Traits>
struct hash<basic_string_view<CharType, Traits>>
{
    typedef basic_string_view<CharType, Traits> argument_type;
    typedef size_t result_type;

    size_t operator()(const basic_string_view<CharType, Traits>) const
        noexcept;
};
struct node {
    int dist = -1;
    vector<string_view> convert_to;
};

unordered_map<string_view, node> nodes;

int solution(string begin, string target, vector<string> words) {
    words.push_back(begin);
    const size_t convertable = words[0].size() - 1;
    for (size_t i = 0; i < words.size(); ++i) {
        for (size_t j = i + 1; j < words.size(); ++j) {
            size_t matches = 0;
            for (size_t k = 0; k < words[i].size(); ++k) {
                matches += (size_t)(words[i][k] == words[j][k]);
            }
            if(matches == convertable){
                nodes[words[i]].convert_to.push_back(words[j]);
                nodes[words[j]].convert_to.push_back(words[i]);
            }
        }
    }
    
    //node 포인터를 보관
    struct travel {
        string_view key; int dist;
    };
    queue<travel> q;
    nodes[begin].dist = 0;
    q.push({ begin, -1 });
    while (false == q.empty()) {
        travel t = q.front(); q.pop();

        node& cur = nodes[t.key];
        cur.dist += t.dist + 1;
        if (t.key == target) {
            return cur.dist;
        }

        for (const string_view& next_name : cur.convert_to) {
            node& next = nodes[next_name];
            if (next.dist != -1) { continue; }
            next.dist = 0;
            q.push({ next_name, cur.dist });
        }
    }


    return 0;
}

int main() {
    auto ans = solution("hit", "cog", { "hot", "dot", "dog", "lot", "log", "cog" });
    return 0;
}