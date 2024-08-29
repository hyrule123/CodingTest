#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 4195 (친구 네트워크)
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

group& find_group(str const& name) {
	if (group_leader[name].leader != name) {
		group_leader[name] = find_group(group_leader[name].leader);
	}

	return group_leader[name];
}

//항상 a < b
void union_group(str const& a, str const& b) {
	group& group_a = find_group(a);
	group& group_b = find_group(b);

	//a그룹과 b그룹의 리더가 다르다면 리더를 b그룹 쪽으로 통일시켜준다.
	//그룹 인원수도 병합
	if (group_a.leader != group_b.leader) {
		group_a.leader = group_b.leader;
		group_b.count += group_a.count;
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

			//무조건 a < b가 되도록 만들어줌
			if (a > b) { std::swap(a, b); }
			
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

			std::cout << group_b.count << '\n';
		}
	}

	return 0;
}