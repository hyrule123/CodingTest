#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 4195 (친구 네트워크)
*/

#include <string>
#include <vector>
constexpr int MAX = 120'119, p1 = 31, p2 = 53;
using str = std::string;
struct pair {
	std::string id;
	int group_hash;
	int friend_count = 1;
};

struct hash_map {
	static int hash1(const str& p) {
		int ret = 0;

		for (int i = 0; p[i] != '\0'; ++i) {
			ret = (ret * p1 + p[i]) % MAX;
		}

		return ret;
	}
	static int hash2(const str& p) {
		int ret = 0;

		for (int i = 0; p[i] != '\0'; ++i) {
			ret = (ret * p2 + p[i]) % MAX;
		}

		return ret;
	}
	void clear() {
		for (int i = 0; i < MAX; ++i) {
			cont[i].id.clear();
			cont[i].group_hash = i;
			cont[i].friend_count = 1;
		}
	}

	int insert(const str& key) {
		int hash = hash1(key);

		if (cont[hash].id.empty()) {
			cont[hash].id = key;
		}
		else if (cont[hash].id == key) {
		}
		//해시 충돌이 있을 경우 double hashing
		else {
			int h2 = hash2(key);
					
			while (true) {
				hash = (hash + h2) % MAX;
				
				if (cont[hash].id.empty()) {
					cont[hash].id = key;
					break;
				}
				else if(cont[hash].id == key) {
					break;
				}
			}
		}

		//들어간 컨테이너 인덱스(해시값)을 반환한다.
		return hash;
	}

	pair cont[MAX];
};

hash_map map;
int tc, n_link;

void reset() {
	n_link = 0;
	map.clear();
}

int find_group(int hash) {
	if (map.cont[hash].group_hash != hash) {
		int prev = map.cont[hash].group_hash;
		map.cont[hash].group_hash = find_group(map.cont[hash].group_hash);
		//새로 갱신되는 그룹쪽으로 그룹원을 이동시킨다
		map.cont[hash].friend_count += map.cont[prev].friend_count;
	}

	return map.cont[hash].group_hash;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> tc;
	while (tc--) {
		reset();

		std::cin >> n_link;
		for (int i = 0; i < n_link; ++i) {
			str a, b; std::cin >> a >> b;

			//문자열 해싱
			int hash_a = map.insert(a);
			int hash_b = map.insert(b);

			//해시값으로 속한 그룹을 탐색
			int group_a = find_group(hash_a);
			int group_b = find_group(hash_b);

			//그룹이 다를 경우 그룹을 합친다
			if (group_a != group_b) {
				if (group_a > group_b) {
					std::swap(group_a, group_b);
				}
				map.cont[group_a].group_hash = group_b;

				map.cont[group_b].friend_count += map.cont[group_a].friend_count;
			}
			
			//합쳐진 그룹원 수를 출력
			std::cout << map.cont[group_b].friend_count << '\n';
		}
	}

	return 0;
}