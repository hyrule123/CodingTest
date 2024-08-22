#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 9019 (DSLR)
*/
#include <stack>
template <typename T>
struct Queue {
	bool empty() { return size == 0; }
	bool full() { return cap == size; }
	void resize(int _cap) {
		if (_cap <= cap) { return; }

		T* temp = new T[_cap];
		if (cont) {
			if (false == empty()) {
				if (start < end) {
					memcpy(temp, cont + start, sizeof(T) * size);
				}
				else {
					int front_part_size = cap - start;
					memcpy(temp, cont + start, sizeof(T) * front_part_size);
					memcpy(temp + front_part_size, cont, sizeof(T) * end);
				}
			}
			delete[] cont;
		}
		cont = temp;
		cap = _cap;
		start = 0;
		end = size;
	}
	
	int next(int i) { if (++i >= cap) { i -= cap; } return i; }
	void push(const T& t) { 
		if (full()) { resize(cap * 2); } 
		cont[end] = t;
		end = next(end);
		++size;
	}
	T top() {
		return cont[start];
	}
	void pop() {
		start = next(start);
		--size;
	}

	void clear() {
		size = start = end = 0;
	}

	T* cont{};
	int cap{}, size{}, start{}, end{};
};

struct record {
	int prev; bool visited; char type;
};
std::stack<char> ans;
Queue<int> q;
//memo[i]: i 방문 여부, 어디서 i로 방문했는지, 어떤 연산을 통해 방문했는지를 기록
record memo[10000]; 
int T, A, B;

void reset() {
	q.resize(1024);
	q.clear();
	A = B = 0;
	memset(memo, 0, sizeof(memo));
}

int D(int i) {
	return i * 2 % 10000;
}
int S(int i) {
	i -= 1;
	if (i < 0) { i = 9999; }
	return i;
}
int L(int i) {
	i *= 10;
	int first_digit = i / 10000;
	i = i - first_digit * 10000 + first_digit;
	return i;
}
int R(int i) {
	i = i + (i % 10) * 10000;
	i /= 10;
	return i;
}

void write_memo(int from, int to, char type) {
	//DSLR 모두 10000 미만 값이 보장되므로 범위 확인은 필요 없다
	//방문하지 않았을 경우 이전 인덱스와 어떤 타입을 통해 도착했는지를 저장
	if (memo[to].visited == false) {
		memo[to].visited = true;
		memo[to].prev = from;
		memo[to].type = type;
		q.push(to);
	}


}

void BFS() {
	q.push(A);
	memo[A].visited = true;

	while (false == q.empty()) {
		int idx = q.top(); q.pop();

		if (idx == B) { break; }
		
		write_memo(idx, D(idx), 'D');
		write_memo(idx, S(idx), 'S');
		write_memo(idx, L(idx), 'L');
		write_memo(idx, R(idx), 'R');
	}
}

void trace_back() {
	int pos = B;
	while (pos != A) {
		ans.push(memo[pos].type);
		pos = memo[pos].prev;
	}

	while (false == ans.empty()) {
		std::cout << ans.top();
		ans.pop();
	}
	std::cout << '\n';
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> T;
	while (T--) {
		reset();
		std::cin >> A >> B;

		BFS();
		trace_back();
	}

	return 0;
}