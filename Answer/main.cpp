#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

struct matrix {
	matrix() : r{}, c{}, size{}, elem{} {}
	matrix(int _r, int _c) { 
		r = _r; 
		c = _c; 
		size = r * c;
		elem = new int[size];
		memset(elem, 0, size * sizeof(int));
	}
	~matrix() { if (elem) { delete[] elem; } }

	matrix(const matrix& _other) {
		r = _other.r;
		c = _other.c;
		size = _other.size;
		elem = new int[size];
		memcpy(elem, _other.elem, size * sizeof(int));
	}

	void operator =(matrix&& _move) noexcept {
		if (this != &_move) {
			Move(std::move(_move));
		}
	}
	matrix(matrix&& _move) noexcept : matrix() { Move(std::move(_move)); }
	inline void Move(matrix&& _move) noexcept {
		r = _move.r;
		c = _move.c;
		size = _move.size;
		std::swap(elem, _move.elem);
	}

	int* operator[] (int _row) { return &(elem[_row * c]); }
	matrix operator * (matrix& _other) {
		matrix ret(r, _other.c);

		for (int _r = 0; _r < ret.r; ++_r) {
			int rIdx = _r * ret.c;
			for (int _c = 0; _c < ret.c; ++_c) {
				for (int _e = 0; _e < c; ++_e) {
					(ret.elem[rIdx + _c] += (*this)[_r][_e] * _other[_e][_c]) %= 1000;
				}
			}
		}

		return ret;
	}
	matrix operator % (int _div) {
		matrix ret = *this;
		for (int i = 0; i < ret.size; ++i) {
			ret.elem[i] %= _div;
		}
		return ret;
	}

	int r, c, size;
	int* elem;
};

matrix PowRecursive(matrix& _base, size_t _exp) {
	if (_exp == 1) { return _base % 1000; }

	bool isOdd = (_exp % 2 == 1);
	if (isOdd) { --_exp; }
	matrix ret = PowRecursive(_base, _exp / 2);
	ret = ret * ret;
	if (isOdd) { ret = ret * _base; }

	return ret;
}

int main() {	
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;

	int size; size_t exp; std::cin >> size >> exp;
	matrix A(size, size); 
	for (int i = 0; i < A.size; ++i) {
		std::cin >> A.elem[i];
	}

	matrix result = PowRecursive(A, exp);

	for (int r = 0; r < result.r; ++r) {
		for (int c = 0; c < result.c; ++c) {
			std::cout << result[r][c] << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}
