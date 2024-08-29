#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 4195 (친구 네트워크)
*/
/* 계속 오답 나왔던 이유
gcc에서는 문자열 해싱에 'MurMurHash2'라는 알고리즘을 사용 중.
내가 사용한 단순한 해쉬함수보다 당연히 훨씬 효율적이고 빠를 거고, 
해시 충돌 해결은 collision chaining 방식으로 해결하는데 아마 여기도 더 좋은 알고리즘을 사용중일 것임.
아마 차이는 여기서 온게 아닌가 싶음.
*/

#include <unordered_map>
#include <string>
int tc, n_link;
using str = std::string;
struct group {
	str leader;
	int count;
};
std::unordered_map<str, group> group_leader;

str const& find_group(str const& name) {
	if (group_leader[name].leader != name) {
		group_leader[name].leader = find_group(group_leader[name].leader);
	}

	return group_leader[name].leader;
}

void union_group(str const& a, str const& b) {
	str leader_a = find_group(a);
	str leader_b = find_group(b);

	if (leader_a == leader_b) { return; }

	//union rank는 문자 사전순으로 대체
	if (leader_a < leader_b) {
		group_leader[leader_a].leader = leader_b;
		group_leader[leader_b].count += group_leader[leader_a].count;
	}
	else {
		group_leader[leader_b].leader = leader_a;
		group_leader[leader_a].count += group_leader[leader_b].count;
	}
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> tc;
	while (tc--) {
		group_leader.clear();

		std::cin >> n_link;
		
		for (int i = 0; i < n_link; ++i) {
			str a, b; std::cin >> a >> b;
			
			//그룹 리더가 비어있을 경우 새로운 인원이 들어온것. 새 그룹을 생성해준다.
			auto& group_a = group_leader[a];
			if (group_a.leader.empty()) {
				group_a.leader = a;
				group_a.count = 1;
			}
			auto& group_b = group_leader[b];
			if (group_b.leader.empty()) {
				group_b.leader = b;
				group_b.count = 1;
			}

			//a와 b를 합친다.
			union_group(a, b);
			
			//a가 속한 그룹의 인원을 출력한다.
			std::cout << group_leader[find_group(b)].count << '\n';
		}
	}

	return 0;
}