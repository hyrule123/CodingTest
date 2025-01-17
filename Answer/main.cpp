#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset
using namespace std;
void solve();
int main() 
{
	cin.tie(nullptr); cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

/*
백준 2220 (힙 정렬) [그리디]

1~6을 힙에 넣을 때
6 5 4 3 2 1 로 구성된 힙은 힙 정렬 시 4회 swap
6 5 3 2 4 1 로 구성된 힙은 힙 정렬 시 6회 swap

키 포인트: 삭제해보기
6 5 3 2 4 1에서 루트를 pop후 다시 힙 빌드를 하면
5 4 3 2 1이 된다. -> 이는 곧 크기 5의 힙에서 swap 횟수를 최대로 하는 배열이다.
4 2 3 1
3 2 1
2 1
1

눈여겨 볼 점 
1. 항상 1로 끝나서 1을 아래로 내려보낸다는 것
2. 6, 5, 4, 3, 2, 1 순으로 pop되었다는 것(다시 말해 1부터 N까지 삽입하면 같은 배열이 만들어진다는 것)
-> 1을 제외하고 힙에 2부터 N까지 차례대로 삽입한 후, 마지막에 1을 끼워넣으면 답지와 같은 배열이 만들어진다.
*/
#include <vector>
vector<int> heap;

void insert_heap(int i)
{
	heap.push_back(i);

	int cur = (int)heap.size() - 1;
	while (0 < cur)
	{
		int par = (cur - 1) / 2;
		if (heap[cur] > heap[par])
		{
			swap(heap[cur], heap[par]);
			cur = par;
		}
		else
		{
			break;
		}
	}
}

void solve()
{
	int n; cin >> n;
	heap.reserve(n);
	for (int i = 2; i <= n; ++i)
	{
		insert_heap(i);
	}
	heap.push_back(1);
	
	for (int i : heap)
	{
		cout << i << ' ';
	}
}