#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 4195 (친구 네트워크)
*/

constexpr int MAX = 120011, p1 = 31, p2 = 53;
struct str {
	char s[21];
	int len;
	
	bool empty() { return len == 0; }

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
	int group;
	int friend_count;
};

struct hash_map {
	static int hash1(const str& p) {
		int ret = 1;

		for (int i = 0; i < p.len; ++i) {
			ret = (ret * p1 + p.s[i]) % MAX;
		}

		return ret;
	}
	static int hash2(const str& p) {
		int ret = 1;

		for (int i = 0; i < p.len; ++i) {
			ret = (ret * p2 + p.s[i]) % MAX;
		}

		return ret;
	}

	void clear() {
		memset(cont, 0, sizeof(cont));
	}

	int insert(const str& key) {
		int hash = hash1(key);

		if (cont[hash].id.empty()) {
			cont[hash].id = key;
			cont[hash].friend_count = 1;
			cont[hash].group = hash;
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
					cont[hash].friend_count = 1;
					cont[hash].group = hash;
					break;
				}
				else if (cont[hash].id == key) {
					break;
				}
			}
		}

		//들어간 해시값을 반환한다.
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
	if (map.cont[hash].group != hash) {
		map.cont[hash].group = find_group(map.cont[hash].group);
	}
	return map.cont[hash].group;
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
				if (group_b > group_a) { std::swap(group_a, group_b); }

				//그룹과 그룹원 수 병합
				map.cont[group_a].group = group_b;
				map.cont[group_b].friend_count += map.cont[group_a].friend_count;
			}

			std::cout << map.cont[group_b].friend_count << '\n';
		}
	}

	return 0;
}