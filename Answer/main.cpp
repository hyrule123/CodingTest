#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

class AVLTree {
public:
	class Node {
		friend class AVLTree;
	private:
		Node(int _key) : left{}, right{}, height{ 1 }, key(_key) {}
		~Node(){
			if (left) { delete left; }
			if (right) { delete right; }
		}

		static int Height(Node* _n) { if (_n) return _n->height; return 0; }
		static int Balance(Node* _n) { 
			if (_n) {
				return Height(_n->right) - Height(_n->left);
			}
			return 0;
		}
		static Node* MinValue(Node* _n);
		void CalcHeight() { height = 1 + std::max(Height(left), Height(right)); }

		Node* left, * right;
		int height;
		int key;
	};

public:
	AVLTree() : root(nullptr) {}
	~AVLTree() { if (root) { delete root; } }

	const Node* Search(int _key) { return _Search(_key); }
	void Insert(int _key) { root = _Insert(root, _key); }
	void Delete(int _key) { _Delete(root, _key); };
	void Clear() { delete root; root = nullptr; }

private:
	static Node* LeftRotate(Node* _n);
	static Node* RightRotate(Node* _n);

	Node* _Search(int _key);
	Node* _Insert(Node* _n, int _key);
	Node* _Delete(Node* _n, int _key);

	Node* root;
};


AVLTree::Node* AVLTree::LeftRotate(Node* _n)
{
	Node* right = _n->right;

	_n->right = right->left;
	right->left = _n;

	_n->CalcHeight();
	right->CalcHeight();

	return right;
}

AVLTree::Node* AVLTree::RightRotate(Node* _n)
{
	Node* left = _n->left;
	
	_n->left = left->right;
	left->right = _n;

	_n->CalcHeight();
	left->CalcHeight();

	return left;
}

AVLTree::Node* AVLTree::Node::MinValue(Node* _n)
{
	while (_n->right) {
		_n = _n->right;
	}
	return _n;
}

AVLTree::Node* AVLTree::_Search(int _key)
{
	Node* ret = root;
	while (ret) {
		if (_key == ret->key) { break; }
		else if (_key < ret->key) { ret = ret->left; }
		else { ret = ret->right; }
	}
	return ret;
}

AVLTree::Node* AVLTree::_Insert(Node* _n, int _key)
{
	if (nullptr == _n) { return new Node(_key); }
	else if (_key < _n->key) {
		_n->left = _Insert(_n->left, _key);
	}
	else if (_n->key < _key) {
		_n->right = _Insert(_n->right, _key);
	}
	else {
		return _n;
	}

	_n->CalcHeight();
	int balance = Node::Balance(_n);

	//왼쪽으로 기움
	if (balance < -1) {
		//자식은 오른쪽으로 기움 -> 자식을 왼쪽으로 회전
		if (_n->left->key < _key) {
			_n->left = LeftRotate(_n->left);
		}
		
		//오른쪽으로 회전
		return RightRotate(_n);
	}
	//오른쪽으로 기움
	else if (1 < balance) {
		//자식은 왼쪽으로 기움 -> 자식을 오른쪽으로 회전
		if (_key < _n->right->key) {
			_n->right = RightRotate(_n->right);
		}

		return LeftRotate(_n);
	}

	return _n;
}

AVLTree::Node* AVLTree::_Delete(Node* _n, int _key)
{
	if (nullptr == _n) { return _n; }

	if (_key < _n->key) {
		_n->left = _Delete(_n->left, _key);
	}
	else if (_n->key < _key) {
		_n->right = _Delete(_n->right, _key);
	}

	//노드 발견
	else {
		//둘다 있을때: 오른쪽 노드의 맨 왼쪽 노드(자신보다 큰값중 제일 작은거) 값만 가져온다
		if (_n->left && _n->right) {
			Node* replace = Node::MinValue(_n->left);

			_n->key = replace->key;

			//해당 노드 제거
			_n->left = _Delete(_n->left, replace->key);
		}

		//하나만 있을 때: 자식을 끌어올리고 자식을 제거
		else if (_n->left) {
			Node* del = _n->left;
			(*_n) = *del;
			del->left = nullptr;
			del->right = nullptr;
			delete del;
		}
		else if (_n->right) {
			Node* del = _n->right;
			(*_n) = *del;
			del->left = nullptr;
			del->right = nullptr;
			delete del;
		}

		//둘다 없을때: root
		else {
			if (root == _n) { root = nullptr; }
			delete _n;
			_n = nullptr;
		}
	}

	//높이 재계산 단계
	if (nullptr == _n) { return _n; }

	_n->CalcHeight();
	int balance = Node::Balance(_n);

	//왼쪽으로 기운상태
	if (balance < -1) {
		//자식이 오른쪽으로 기울었다면 자식을 왼쪽으로 회전시킨다.
		if (0 < Node::Balance(_n->left)) {
			_n->left = LeftRotate(_n->left);
		}

		//오른쪽으로 회전시켜서 불균형 제거
		Node* ret = RightRotate(_n);
		if (_n == root) { root = ret; }
		return ret;
	}
	//오른쪽으로 기운상태
	else if (1 < balance) {
		//자식이 왼쪽으로 기울었다면 자식을 오른쪽으로 회전시킨다
		if (Node::Balance(_n->right) < 0) {
			_n->right = RightRotate(_n->right);
		}

		//왼쪽으로 회전시켜서 불균형 제거
		Node* ret = LeftRotate(_n);
		if (_n == root) { root = ret; }
		return ret;
	}

	return _n;
}


int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	AVLTree tree{};
	int size; std::cin >> size;
	for (int i = 0; i < size; ++i) {
		int input; std::cin >> input;
		tree.Insert(input);
	}

	std::cin >> size;
	for (int i = 0; i < size; ++i) {
		int input; std::cin >> input;
		const AVLTree::Node* result = tree.Search(input);
		if (result) {
			std::cout << 1 << '\n';
		}
		else {
			std::cout << 0 << '\n';
		}
	}

	return 0;
}