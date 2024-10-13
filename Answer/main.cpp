#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

#include <deque>
struct board {
	board() {}
	board(const board& _other) {
		for (int i = 0; i < 7; ++i) {
			b[i] = _other.b[i];
		}
	}

	int get_elem_size() {
		int ret = 0;
		for (int i = 0; i < 7; ++i) {
			ret += (int)b[i].size();
		}
		return ret;
	}
	
	//col의 경우의는 col.size로 바로 구할수 있지만
	//row의 경우에는 인접한 col들의 사이즈가 자신의 row보다 큰 지 일일히 확인해야 함
	int get_row_group_size(int col, int row) {
		int ret = 0;
		//좌우 컬럼이 나보다 크거나 같으면 하나의 그룹으로 묶임
		for (int c = col - 1; c >= 0; --c) {
			if (b[c].size() > row) {
				++ret;
			}
			else {
				break;
			}
		}
		for (int c = col; c < 7; ++c) {
			if (b[c].size() > row) {
				++ret;
			}
			else {
				break;
			}
		}

		return ret;
	}

	//0으로 바뀐 값들을 모조리 제거하고 남아있는 원소 수를 계산한다.
	int fall() {
		int remain = 0;
		for (int c = 0; c < 7; ++c) {
			std::erase_if(b[c],
				[](int val)->bool
				{
					return val == 0;
				}
			);
			remain += (int)b[c].size();
		}
		return remain;
	}

	//연쇄반응
	int pang_combo() {
		int prev_remain{};
		int cur_remain = get_elem_size();

		while (prev_remain != cur_remain) {
			for (int c = 0; c < 7; ++c) {
				for (int r = 0; r < (int)b[c].size(); ++r) {
					//col group의 갯수가 현재 숫자와 같으면 폭파 처리
					if (b[c][r] == b[c].size()) {
						b[c][r] = 0;
					}
					//또는 row group의 갯수가 현재 숫자와 같을 경우 폭파 처리
					else {
						int row_group_size = get_row_group_size(c, r);
						if (b[c][r] == row_group_size) {
							b[c][r] = 0;
						}
					}
				}
			}

			prev_remain = cur_remain;

			//폭파된 것들 제거(떨어지는) 처리
			cur_remain = fall();
		}

		return cur_remain;
	}

	std::deque<int> b[7];
};

board orig, test;

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	//input
	for (int r = 0; r < 7; ++r) {
		for (int c = 0; c < 7; ++c)
		{
			int input; std::cin >> input;
			if (input != 0) {
				orig.b[c].push_front(input);
			}
		}
	}

	int next_num; std::cin >> next_num;

	int remain_min = std::numeric_limits<int>::max();
	//column마다 공을 집어넣어서 시뮬레이션 돌리고 제일 적게 남은 경우의 수를 구한다
	for (int c = 0; c < 7; ++c)
	{
		//복사 생성자를 통한 판 초기화
		test = orig;
		
		test.b[c].push_back(next_num);

		remain_min = std::min(remain_min, test.pang_combo());
	}
	std::cout << remain_min;

	return 0;
}