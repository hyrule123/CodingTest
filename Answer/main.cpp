#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <iostream>
#include <limits>
#include <cstring> //memset

void solve();

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false); LOCAL_IO;
	solve();
	return 0;
}

#include <unordered_map>
#include <string>
constexpr int board_size = 8;
struct coord {
	int x, y;
	coord operator +(const coord& other) {
		return { this->x + other.x, this->y + other.y };
	}
	bool operator != (const coord& other) {
		return { this->x != other.x || this->y != other.y };
	}
	bool valid() {
		return { 0 <= x && 0 <= y && x < board_size && y < board_size };
	}
};

std::unordered_map<std::string, coord> directions;
coord king_pos, stone_pos;

void push(const coord& dir) {
	coord next_king_pos = king_pos + dir;

	//밀고 난 위치가 올바르지 않을경우 이동 취소
	if (false == next_king_pos.valid()) {
		return;
	}

	//돌을 밀지 않았으면 여기서 중단
	if (stone_pos != next_king_pos) {
		king_pos = next_king_pos;
		return;
	}

	//돌을 민다
	coord next_stone_pos = stone_pos + dir;

	//돌의 밀고난 위치가 올바르지 않을경우 이동 취소
	if (false == next_stone_pos.valid()) {
		return;
	}

	//돌을 밀었으면 위치 갱신
	king_pos = next_king_pos;
	stone_pos = next_stone_pos;
}

void solve()
{
	directions["R"] = { 0, 1 };
	directions["L"] = { 0, -1 };
	directions["B"] = { -1, 0 };
	directions["T"] = { 1, 0 };
	directions["RT"] = { 1, 1 };
	directions["LT"] = { 1, -1 };
	directions["RB"] = { -1, 1 };
	directions["LB"] = { -1, -1 };

	int row; 
	char col;
	std::cin >> col >> row;
	king_pos = { row - 1, (int)(col - 'A')};
	std::cin >> col >> row;
	stone_pos = { row - 1, (int)(col - 'A')};

	int moves; std::cin >> moves;
	while (moves--) {
		std::string input; std::cin >> input;

		push(directions[input]);
	}

	std::cout << (char)(king_pos.y + 'A') << king_pos.x + 1 << '\n'
		<< (char)(stone_pos.y + 'A') << stone_pos.x + 1;
}