#pragma once
#include <algorithm>

class AVLTree {
public:
	class Node {
		friend class AVLTree;
	private:
		Node(int _key) : left{}, right{}, height{ 1 }, key(_key) {}
		~Node() {
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

	//�������� ���
	if (balance < -1) {
		//�ڽ��� ���������� ��� -> �ڽ��� �������� ȸ��
		if (_n->left->key < _key) {
			_n->left = LeftRotate(_n->left);
		}

		//���������� ȸ��
		return RightRotate(_n);
	}
	//���������� ���
	else if (1 < balance) {
		//�ڽ��� �������� ��� -> �ڽ��� ���������� ȸ��
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

	//��� �߰�
	else {
		//�Ѵ� ������: ������ ����� �� ���� ���(�ڽź��� ū���� ���� ������) ���� �����´�
		if (_n->left && _n->right) {
			Node* replace = Node::MinValue(_n->left);

			_n->key = replace->key;

			//�ش� ��� ����
			_n->left = _Delete(_n->left, replace->key);
		}

		//�ϳ��� ���� ��: �ڽ��� ����ø��� �ڽ��� ����
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

		//�Ѵ� ������: root
		else {
			if (root == _n) { root = nullptr; }
			delete _n;
			_n = nullptr;
		}
	}

	//���� ���� �ܰ�
	if (nullptr == _n) { return _n; }

	_n->CalcHeight();
	int balance = Node::Balance(_n);

	//�������� ������
	if (balance < -1) {
		//�ڽ��� ���������� �����ٸ� �ڽ��� �������� ȸ����Ų��.
		if (0 < Node::Balance(_n->left)) {
			_n->left = LeftRotate(_n->left);
		}

		//���������� ȸ�����Ѽ� �ұ��� ����
		Node* ret = RightRotate(_n);
		if (_n == root) { root = ret; }
		return ret;
	}
	//���������� ������
	else if (1 < balance) {
		//�ڽ��� �������� �����ٸ� �ڽ��� ���������� ȸ����Ų��
		if (Node::Balance(_n->right) < 0) {
			_n->right = RightRotate(_n->right);
		}

		//�������� ȸ�����Ѽ� �ұ��� ����
		Node* ret = LeftRotate(_n);
		if (_n == root) { root = ret; }
		return ret;
	}

	return _n;
}