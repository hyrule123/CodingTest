#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

class BST {
public:
	class Node {
		friend class BST;
	private:
		Node(int _key) :left{}, right{}, key{ _key } {};
		~Node() {
			if (left) { delete left; }
			if (right) { delete right; }
		}

		static Node* MaxNode(Node* _n) {
			while (_n->right) {
				_n = _n->right;
			}
			return _n;
		}

		Node* left, * right;
		int key;
	};

	BST() : root{ nullptr } {};
	~BST() { if (root) { delete root; } }

	void Insert(int _key) { root = _Insert(root, _key); }
	const Node* Search(int _key) { return _Search(root, _key); }
	void Delete(int _key) { root = _Delete(root, _key); }

private:
	static Node* _Insert(Node* _n, int _key);
	static Node* _Search(Node* _n, int _key);
	static Node* _Delete(Node* _n, int _key);

	Node* root;
};

BST::Node* BST::_Insert(Node* _n, int _key)
{
	if (nullptr == _n) { return new Node(_key); }
	else if (_key < _n->key) {
		_n->left = _Insert(_n->left, _key);
	}
	else if (_n->key < _key) {
		_n->right = _Insert(_n->right, _key);
	}
	return _n;
}

BST::Node* BST::_Search(Node* _n, int _key)
{
	if (nullptr == _n) { return nullptr; }
	else if (_key < _n->key) {
		return _Search(_n->left, _key);
	}
	else if (_n->key < _key) {
		return _Search(_n->right, _key);
	}

	return _n;
}

BST::Node* BST::_Delete(Node* _n, int _key)
{
	if (nullptr == _n) { return nullptr; }
	else if (_key < _n->key) {
		_n->left = _Delete(_n->left, _key);
	}
	else if (_n->key < _key) {
		_n->right = _Delete(_n->right, _key);
	}
	else {
		if (_n->left && _n->right) {
			Node* parent = _n;
			Node* maxNode = _n->left;
			while (maxNode->right) {
				parent = maxNode;
				maxNode = parent->right;
			}

			_n->key = maxNode->key;
			
			parent->right = nullptr;
			delete maxNode;
		}
		else if (_n->left) {
			(*_n) = *(_n->left);
			_n->left->left = nullptr;
			_n->left->right = nullptr;
			delete _n->left;
			_n->left = nullptr;
		}
		else if (_n->right) {
			(*_n) = *(_n->right);
			_n->right->left = nullptr;
			_n->right->right = nullptr;
			delete _n->right;
			_n->right = nullptr;
		}
		else {
			delete _n;
			_n = nullptr;
		}
	}

	return _n;
}

int main() {
	std::cin.tie(nullptr); std::cin.sync_with_stdio(false);
	LOCAL_IO;

	BST tree;
	int size; std::cin >> size;
	for (int i = 0; i < size; ++i) {
		int input; std::cin >> input;
		tree.Insert(input);
	}

	std::cin >> size;
	for (int i = 0; i < size; ++i) {
		int input; std::cin >> input;
		if (tree.Search(input)) {
			std::cout << 1 << '\n';
		}
		else {
			std::cout << 0 << '\n';
		}
	}

	return 0;
}


