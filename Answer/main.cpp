#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <cstring> //memset
/*
백준 7569 (토마토) - 7576번 3d 버전
*/
int X, Y, Z;
struct Coord { int x, y, z; };
struct CircleQueue {
	bool Empty() { return size == 0; }
	bool Full() { return size == capacity; }
	int Next(int cur) { if (++cur >= capacity) { cur -= capacity; } return cur; }
	void PushBack(Coord c) { 
		if (Full()) { Reserve(capacity * 2); } 
		cont[end] = c; 
		end = Next(end); 
		++size; 
	}
	Coord PopFront() { Coord ret = cont[start]; start = Next(start); --size; return ret; }
	void Reserve(int cap) {
		if (cap <= capacity) { return; }

		Coord* temp = new Coord[cap];
		if (cont) {
			if (false == Empty()) {
				if (start < end) {
					memcpy(temp, cont + start, sizeof(Coord) * size);
				}
				else {
					int startPartSize = capacity - start;
					memcpy(temp, cont + start, sizeof(Coord) * startPartSize);
					memcpy(temp + startPartSize, cont, sizeof(Coord) * end);
				}
			}
			delete[] cont;
		}
		start = 0;
		end = size;
		capacity = cap;
		cont = temp;
	}

	Coord* cont{};
	int capacity{}, size{}, start{}, end{};
} q;

int farm[102][102][102]{};
void Check(int x, int y, int z, const Coord& orig) {
	if (farm[x][y][z] == 0) {
		farm[x][y][z] = farm[orig.x][orig.y][orig.z] + 1;
		q.PushBack({x, y, z});
	}
}

int BFS() {
	Coord last{};
	while (false == q.Empty()) {
		last = q.PopFront();
		
		Check(last.x, last.y, last.z - 1, last);
		Check(last.x, last.y, last.z + 1, last);
		Check(last.x, last.y - 1, last.z, last);
		Check(last.x, last.y + 1, last.z, last);
		Check(last.x - 1, last.y, last.z, last);
		Check(last.x + 1, last.y, last.z, last);
	}
	return farm[last.x][last.y][last.z] - 1;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//3차원 배열 -> 입력과 차원을 맞추기 위해서는 Z Y X 역순으로 받아줘야 함 
	//_____ /  
	//|	   | / 
	//|____|/
	std::cin >> Z >> Y >> X;
	//BFS 탐색을 해야하는 범위 주변으로 -1을 둘러쳐 준다.
	for (int x = 0; x <= X + 1; ++x) {
		for (int y = 0; y <= Y + 1; ++y) {
			farm[x][y][0] = -1;
			farm[x][y][Z + 1] = -1;
		}
		for (int z = 0; z <= Z + 1; ++z) {
			farm[x][0][z] = -1;
			farm[x][Y + 1][z] = -1;
		}
	}
	for (int y = 0; y <= Y + 1; ++y) {
		for (int z = 0; z <= Z + 1; ++z) {
			farm[0][y][z] = -1;
			farm[X + 1][y][z] = -1;
		}
	}

	q.Reserve(std::max(X, std::max(Y, Z)));
	for (int x = 1; x <= X; ++x) {
		for (int y = 1; y <= Y; ++y) {
			for (int z = 1; z <= Z; ++z) {
				std::cin >> farm[x][y][z];
				if (1 == farm[x][y][z]) {
					q.PushBack({x, y, z});
				}
			}
		}
	}
	int days = BFS();

	//혹시나 안 익은 토마토(0)이 남아있을 경우 -1을 출력하고 프로그램 종료
	for (int x = 1; x <= X; ++x) {
		for (int y = 1; y <= Y; ++y) {
			for (int z = 1; z <= Z; ++z) {
				if (0 == farm[x][y][z]) {
					std::cout << -1;
					return 0;
				}
			}
		}
	}
	std::cout << days;

	return 0;
}