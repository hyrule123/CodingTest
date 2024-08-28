#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 1717 (집합의 표현): 유니온 파인드 기초 문제
*/
#define UNI 0
#define INT 1
constexpr int MAX = 1'000'000;
int n_set, n_operation, sets[MAX]; //sets[i] = j: i는 j와 같은 집합에 속해있다.
int find_group(int elem) {
	/*
	재귀 형태로 sets[elem]은 어느 그룹에 속하는지를 찾고, 자신도 그 그룹 번호로 바꾼다
	1-2-3이라고 할때 sets[1] = 2, sets[2] = 3, sets[3] = 3 이라면
	find_group(1) -> find_group(2) -> find_group(3) -> return 3 -> sets[2] = 3 -> sets[1] = 3
	이렇게 되면 차후에 재귀 횟수를 줄일 수 있다.(최적화)
	*/
	if (elem != sets[elem]) {
		sets[elem] = find_group(sets[elem]);
	}
	return sets[elem];
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;
	
	std::cin >> n_set >> n_operation;
	for (int i = 0; i <= n_set; ++i) {
		sets[i] = i;
	}
	for (int i = 1; i <= n_operation; ++i) {
		int op_type, a, b; std::cin >> op_type >> a >> b;

		//무조건 a쪽을 작은쪽으로 둔다.
		if (b < a) { std::swap(a, b); }

		int group_a = find_group(a);
		int group_b = find_group(b);
		
		switch (op_type) {
		case UNI: {
			//둘이 속한 집합이 다를 경우 작은쪽의 원소를 다른쪽과 동일하게 변경
			if (group_a != group_b) {
				sets[group_a] = group_b;
			}
			break;
		}
		case INT: {
			if (group_a == group_b) {
				std::cout << "YES\n";
			}
			else {
				std::cout << "NO\n";
			}

			break;
		}
		}
	}

	return 0;
}