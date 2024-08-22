#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
/*
백준 9019 (DSLR)
*/
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
					memcpy(temp + front_part_size, cont, end);
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

	T* cont{};
	int cap{}, size{}, start{}, end{};
};

struct record {
	int count; char type;
};
struct q_data {
	int idx; 
	record t;
};
Queue<q_data> q;
record dp[10000]; //dp[i]: 숫자 i를 만들기 한 연산 횟수
int T, A, B;

void reset() {
	A = B = 0;
	memset(dp, -1, sizeof(dp));
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


int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	std::cin >> T;
	while (T--) {
		reset();
		std::cin >> A >> B;
	}

	Queue<int> q;
	q.resize(1000);
	for (int i = 0; i < 10000; ++i) {
		q.push(i);
	}

	for (int i = 0; i < 10000; ++i) {
		int r = q.top(); q.pop();

		if (r != i) {
			int a = 1;
		}
	}
	

	return 0;
}