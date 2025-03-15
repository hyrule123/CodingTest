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
백준 19638 (센티와 마법의 뿅망치) [priority queue]
*/

#include <vector>
template <typename T>
struct pr_q
{
	void reserve(int cap)
	{
		cont.reserve(cap + 1);
	}

	void push(const T& data)
	{
		cont.push_back(data);
		heapify_up(cont.size() - 1);
	}
	T top()
	{
		return cont[1];
	}
	void pop()
	{
		if (cont.size() >= 2)
		{
			swap(cont[1], cont[cont.size() - 1]);
			cont.pop_back();

			heapify_down(1);
		}
	}

	void heapify_up(int cur)
	{
		while (cur / 2 > 0)
		{
			int par = cur / 2;
			if (cont[par] < cont[cur])
			{
				swap(cont[par], cont[cur]);
				cur = par;
			}
			else
			{
				break;
			}
		}
	}

	void heapify_down(int cur)
	{
		const int size = cont.size();
		while (cur < size)
		{
			int l = cur * 2, r = l + 1, target = cur;

			if (l < size && cont[target] < cont[l])
			{
				target = l;
			}
			if (r < size && cont[target] < cont[r])
			{
				target = r;
			}

			if (target != cur)
			{
				swap(cont[cur], cont[target]);
				cur = target;
			}
			else
			{
				break;
			}
		}
	}

	vector<T> cont = { 0 };
};

int N, H, T;

void solve()
{
	cin >> N >> H >> T;
	pr_q<int> pq;
	pq.reserve(N);
	for (int i = 0; i < N; ++i)
	{
		int h; cin >> h;
		pq.push(h);
	}

	int count = 0;
	while(T--)
	{
		//맨위에꺼 꺼낸다
		int t = pq.top();

		//가장 큰 값이 H보다 작으면 -> 종료
		//t가 1이면 -> 더이상 할필요가 없음 -> 종료
		if (t < H || t <= 1)
		{
			break;
		}

		//카운트 늘려주고 키를 반으로 줄인다
		++count;
		t /= 2;

		//다시 pq에 넣어준다
		pq.pop();
		pq.push(t);
	}

	if (H > pq.top())
	{
		cout << "YES\n" << count;
	}
	else
	{
		cout << "NO\n" << pq.top();
	}
}