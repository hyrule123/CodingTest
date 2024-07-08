#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
std::vector<int> heap;
void HeapifyDown(size_t _idx, size_t _size) {

	while (_idx < _size) {
		size_t biggest = _idx;
		size_t left = _idx * 2 + 1;
		size_t right = left + 1;

		if (left < _size && heap[biggest] > heap[left]) {
			biggest = left;
		}
		if (right < _size && heap[biggest] > heap[right]) {
			biggest = right;
		}

		if (biggest != _idx) {
			std::swap(heap[biggest], heap[_idx]);
			_idx = biggest;
		}
		else { break; }
	}
}

void InsertHeap(int _i) {
	heap.push_back(_i);

	//Heapify Up
	size_t idx = heap.size() - 1;
	while (idx > 0) {
		size_t parent = (idx - 1) / 2;

		if (heap[idx] < heap[parent]) {
			std::swap(heap[idx], heap[parent]);
		}
		idx = parent;
	}
}

int PopHeap() {
	int ret = 0;
	if (heap.empty()) { return ret; }

	ret = heap[0];
	heap[0] = heap.back();
	heap.resize(heap.size() - 1);
	if (1 < heap.size()) {
		HeapifyDown(0, heap.size());
	}

	return ret;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	int N; std::cin >> N;
	heap.reserve(N);
	for (int i = 0; i < N; ++i) {
		int input; std::cin >> input;
		if (input) {
			InsertHeap(input);
		}
		else {
			std::cout << PopHeap() << '\n';
		}
	}

	return 0;
}