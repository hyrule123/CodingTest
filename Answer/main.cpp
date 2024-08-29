#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 4195 (친구 네트워크)
*/

#include <vector>
constexpr int MAX = 120'119, p1 = 31, p2 = 53;
struct str {
	char s[21];
	int len;

	void clear() {
		s[0] = '\0';
		len = 0;
	}

	bool operator ==(const str& other) const {
		if (len != other.len) {
			return false;
		}
		for (int i = 0; i < len; ++i) {
			if (s[i] != other.s[i]) {
				return false;
			}
		}

		return true;
	}
};
std::istream& operator>>(std::istream& stream, str& string) {
	stream >> string.s;
	string.len = (int)strlen(string.s);
	return stream;
}
struct pair {
	str id;
	int group_hash;
	int friend_count;
};

struct hash_map {
	static int str_hash(const str& p) {
		int ret = 0;

		for (int i = 0; i < p.len; ++i) {
			ret = (ret * p1 + p.s[i]) % MAX;
		}

		return ret;
	}

	void clear() {
		memset(cont, 0, sizeof(cont));
	}

	int insert(const str& key) {
		int hash = str_hash(key);

		//linear probing
		while (true) {
			if (cont[hash].id.len == 0) {
				cont[hash].id = key;
				cont[hash].group_hash = hash;
				cont[hash].friend_count = 1;
				return hash;
			}
			else if (cont[hash].id == key) {
				return hash;
			}
			++hash;
			if (hash >= MAX) {
				hash -= MAX;
			}
		}

		cont[hash].id = key;

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
		map.cont[hash].group_hash = find_group(map.cont[hash].group_hash);
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