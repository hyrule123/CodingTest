#pragma once
#include <iostream> //cout

/*
��� ���� ���� �ƴϸ� ���̴�.
��Ʈ ���� ���̴�.
��� NIL ���� ���̴�.
���� ���� ���� ��带 �ڽ����� ���� �� ����.����... ��� ���� ����� �θ�� ���̴�.
���� ���� �������� ����(Double red)�� �� ����.
������ �� ��忡�� NIL ������ �����ϴ� ��� ��ο��� �׻� ���� ���� �� ��尡 �ִ�.
*/
class RedBlackTree {
public:
	enum class Color { Red, Black };

	class Node {
		friend class RedBlackTree;
	private:
		Node() : parent{}, left{}, right{}, data{}, color{ Color::Red } {}
		Node(int _data)
			: Node()
		{
			data = _data;
		}
		Node(const Node& _other)
			: parent(_other.parent)
			, left(_other.left)
			, right(_other.right)
			, data(_other.data)
			, color(_other.color)
		{}
		~Node() {
			if (left) { delete left; }
			if (right) { delete right; }
		}

		bool IsLeftChild() const { return this == parent->left; }
		bool IsRightChild() const { return this == parent->right; }

		Node* Uncle() {
			if (nullptr == parent || nullptr == parent->parent) {
				return nullptr;
			}

			if (parent->IsLeftChild()) {
				return parent->parent->right;
			}
			else {
				return parent->parent->left;
			}
		}

		Node* Sibling() {
			if (nullptr == parent) {
				return nullptr;
			}

			if (IsLeftChild()) {
				return parent->right;
			}
			else {
				return parent->left;
			}
		}

		//_parent�� �ڽ����� ��
		void MoveDown(Node* _parent) {
			if (parent) {
				if (IsLeftChild()) {
					parent->left = _parent;
				}
				else {
					parent->right = _parent;
				}
			}

			_parent->parent = parent;
			parent = _parent;
		}

		bool HasRedChild() const {
			return (left && left->color == Color::Red)
				|| (right && right->color == Color::Red);
		}

		Node* parent, * left, * right;
		Color color;

	public:
		int data;
	};

	RedBlackTree() : root{} {}
	~RedBlackTree() { if (root) { delete root; } }

	void Insert(int _data);
	void Erase(int _data);
	void Traverse() const;
	const Node* Search(int _data) const { return Search(_data); }
	Node* Root() const { return root; }

private:
	void LeftRotate(Node* _x);
	void RightRotate(Node* _x);
	void FixRedRed(Node* _node);

	//Deletion �۾� �� �� �ڸ��� �� �� �ִ� Node�� ã���ش�.
	//�ĺ�: Left ���� ��ĭ ���� ������ ���������� �̵��� �������
	//, �Ǵ� Right ���� ��ĭ ���� ������ �������� �� �������(���� ä��)
	Node* MinNode(Node* _node);
	//������ ��带 ��ü�� ��� Ž��
	Node* BSTReplace(Node* _node);
	void Delete(Node* _node);			//recursive
	void FixDoubleBlack(Node* _node);	//recursive

	Node* Search(int _data);

	void TraverseRecursive(Node* node) const;

	Node* root;
};

void RedBlackTree::Insert(int _data)
{
	//root���� ����(root�� parent�� ����)
	Node* parent = nullptr;
	Node* current = root;

	//���������� Ž�� ����(NIL�� ���ö����� ��������)
	while (current != nullptr) {
		parent = current;
		if (_data == current->data) {
			return;
		}
		else if (_data < current->data) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}

	Node* newNode = new Node(_data);
	newNode->parent = parent;

	//�θ��尡 ���� �� root, �ƴ� �� ���� ���� ����
	if (parent == nullptr) {
		root = newNode;
		root->color = Color::Black;
	}
	else if (newNode->data < parent->data) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}

	//��Ʈ��尡 �ƴ� ��� ����� Ʈ�� ��Ģ�� ����
	FixRedRed(newNode);
}

void RedBlackTree::Erase(int _data)
{
	Node* find = Search(_data);
	if (find) {
		Delete(find);
	}
}

void RedBlackTree::Traverse() const
{
	TraverseRecursive(root);
	std::cout << '\n';
}

void RedBlackTree::LeftRotate(Node* _node)
{
	//�ݽð����(����) ȸ��: ������ �ڽ��� �� �θ� �ȴ�.
	Node* nParent = _node->right;

	if (_node == root) { root = nParent; }

	//Parent�� �ڽ����� ����
	if (_node->parent) {
		if (_node == _node->parent->left) {
			_node->parent->left = nParent;
		}
		else {
			_node->parent->right = nParent;
		}
	}
	nParent->parent = _node->parent;
	_node->parent = nParent;

	//  nP
	//n   nPr
	//  nr
	_node->right = nParent->left;

	if (_node->right) {
		_node->right->parent = _node;
	}

	nParent->left = _node;
}

void RedBlackTree::RightRotate(Node* _node)
{
	Node* nParent = _node->left;

	if (root == _node) { root = nParent; }

	if (_node->parent) {
		if (_node == _node->parent->left) {
			_node->parent->left = nParent;
		}
		else {
			_node->parent->right = nParent;
		}
	}
	nParent->parent = _node->parent;
	_node->parent = nParent;

	_node->left = nParent->right;
	if (_node->left) {
		_node->left->parent = _node;
	}

	nParent->right = _node;
}

void RedBlackTree::FixRedRed(Node* _node)
{
	if (_node == root) { root->color = Color::Black; return; }

	Node* parent = _node->parent
		, * grandParent = parent->parent
		, * uncle = _node->Uncle();

	//Red�� �θ�� Red�� �� ����
	if (parent->color == Color::Red) {
		if (uncle && uncle->color == Color::Red) {
			parent->color = Color::Black;
			uncle->color = Color::Black;
			grandParent->color = Color::Red;

			//���� ��忡 ���� ��� Red-Red �˻�
			FixRedRed(grandParent);
		}
		else {
			if (parent->IsLeftChild()) {
				//Outer child�� ���: ���� ����
				if (_node->IsLeftChild()) {
					std::swap(parent->color, grandParent->color);
				}
				//Inner child�� ���: parent ���� ���� ȸ��, parent�� outer child�� �ǰ� _node�� parent�� ��
				else {
					LeftRotate(parent);
					std::swap(_node->color, grandParent->color);
				}

				//GrandParent�� �������� �ٽ� ���������� ȸ����Ų��
				//GrandParent �ڸ����� _node �Ǵ� parent�� ���� �ȴ�.
				RightRotate(grandParent);
			}
			//�¿� ����
			else {
				if (_node->IsRightChild()) {
					std::swap(parent->color, grandParent->color);
				}
				else {
					RightRotate(parent);
					std::swap(_node->color, grandParent->color);
				}
				LeftRotate(grandParent);
			}
		}
	}
}


RedBlackTree::Node* RedBlackTree::MinNode(Node* _node)
{
	while (nullptr != _node->left) {
		_node = _node->left;
	}
	return _node;
}

RedBlackTree::Node* RedBlackTree::BSTReplace(Node* _node)
{
	//�ڽ� �Ѵ� ���� ���
	if (_node->left && _node->right) {
		return MinNode(_node->right);
	}

	//���� �ϳ� ���� ���
	else if (_node->left) {
		return _node->left;
	}
	else if (_node->right) {
		return _node->right;
	}

	//�Ѵ� �������(Leaf)
	return nullptr;
}

void RedBlackTree::Delete(Node* _node)
{
	Node* replace = BSTReplace(_node);

	//���� ��� + ��ü ��� ��� black�� ��츦 Double Black condition�̶�� �Ѵ�.
	//nullptr�� NIL ����̰�, NIL ���� �׻� Black�̴�
	bool isDoubleBlack = (_node->color == Color::Black) && (nullptr == replace || replace->color == Color::Black);

	//replace == NIL
	if (nullptr == replace) {
		if (root == _node) { root = nullptr; }
		else {
			if (isDoubleBlack) {
				FixDoubleBlack(_node);
			}
			//Double Black�� �ƴ� ���(���� �ϳ��� Red�� ���)
			else {
				Node* sib = _node->Sibling();
				if (sib) {
					sib->color = Color::Red;
				}
			}

			if (_node->IsLeftChild()) { _node->parent->left = nullptr; }
			else { _node->parent->right = nullptr; }
		}

		_node->left = _node->right = nullptr;
		delete _node;
	}

	//replace ���� + �ڳడ 1������ ��
	else if (_node->left == nullptr || _node->right == nullptr) {

		//��尡 ��Ʈ�� ��� replace�� ���� ����
		if (_node == root) {
			root->data = replace->data;
			root->left = root->right = nullptr;
			delete replace;
		}
		else {
			if (_node->IsLeftChild()) {
				_node->parent->left = replace;
			}
			else {
				_node->parent->right = replace;
			}
			replace->parent = _node->parent;
			if (isDoubleBlack) {
				FixDoubleBlack(replace);
			}
			else {
				replace->color = Color::Black;
			}

			_node->left = _node->right = nullptr;
			delete _node;
		}
	}
	//�ڽ��� 2�� ������ ���� ��� replace�� ���� �����µ�, replace�� ����(��� ȣ��)
	else {
		std::swap(_node->data, replace->data);
		Delete(replace);
	}
}

void RedBlackTree::FixDoubleBlack(Node* _node)
{
	if (root == _node) { return; }

	Node* sibling = _node->Sibling(), * parent = _node->parent;

	//�˻��� �ڸ� ��� ���� -> �θ� ���� ��� ȣ��
	if (nullptr == sibling) {
		FixDoubleBlack(_node->parent);
	}
	else {
		if (sibling->color == Color::Red) {
			parent->color = Color::Red;
			sibling->color = Color::Black;

			//sibling�� �θ� ��� ��ġ�� �Ű��ش�(== �˸°� ȸ����Ų��)
			if (sibling->IsLeftChild()) {
				RightRotate(parent);
			}
			else {
				LeftRotate(parent);
			}

			//Sibling Right �Ǵ� Left�� ���ο� Sibling���� �ؼ� �˻��Ѵ�.
			//	    P	    SIB(B)
			//	 /    \	     	\
			//	SIB(R) X(B)      P(R)
			//   \			    / \
			//   SIBR	      SIBR X(B)
			FixDoubleBlack(_node);
		}
		//Sibling == Black
		else {
			if (sibling->HasRedChild()) {
				if (sibling->left && sibling->left->color == Color::Red) {
					//sibling->left�� outer child�� ���(left left)
					if (sibling->IsLeftChild()) {
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						RightRotate(parent);//sibling�� parent �ڸ��� ���Ե�, sibling Left�� sibling �ڸ��� ��
					}
					//inner child
					else {
						sibling->left->color = parent->color;
						RightRotate(sibling);//sibling�� ���� �ڽ��� ����´�.
						LeftRotate(parent);//parent�� �������� ������ sibling�� ���� �ڽ��� parent ��ġ�� ��
					}
				}
				//�¿����
				else {
					//outer child case
					if (sibling->IsRightChild()) {
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						LeftRotate(parent);
					}
					else {
						sibling->right->color = parent->color;
						LeftRotate(sibling);
						RightRotate(parent);
					}
				}
				parent->color = Color::Black;
			}
			//2���� Black child->�ڽ��� Red�� �Ǹ� ��
			else {
				sibling->color = Color::Red;
				if (parent->color == Color::Black) {
					FixDoubleBlack(parent);
				}
				else {
					parent->color = Color::Black;
				}
			}
		}
	}
}

RedBlackTree::Node* RedBlackTree::Search(int _data)
{
	Node* node = root;
	while (node != nullptr) {
		if (node->data == _data) { break; }
		else if (_data < node->data) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	return node;
}

void RedBlackTree::TraverseRecursive(Node* node) const
{
	if (node == nullptr) { return; }
	TraverseRecursive(node->left);
	std::cout << node->data << ' ';
	TraverseRecursive(node->right);
}