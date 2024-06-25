#ifndef LOCAL
#define LOCAL_IO (void)0
#endif
#include <stdio.h>
#include <iostream>
#include <limits>
#include <cstring>  //memset
//////////////////

#include <vector>
/*
모든 노드는 레드 아니면 블랙이다.
루트 노드는 블랙이다.
모든 NIL 노드는 블랙이다.
레드 노드는 레드 노드를 자식으로 가질 수 없다.따라서... 모든 레드 노드의 부모는 블랙이다.
레드 노드는 연속으로 존재(Double red)할 수 없다.
임의의 한 노드에서 NIL 노드까지 도달하는 모든 경로에는 항상 같은 수의 블랙 노드가 있다.
*/
class RedBlackTree {
public:
	enum class Color { Red, Black };

	class Node {
		friend class RedBlackTree;
	private:
		Node() : parent{ nullptr }, left{ &nil }, right{ &nil }, data{}, color{ Color::Red } {}
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

		static Node* NIL() { return &nil; }
		static bool IsNil(Node* _node) { return (&nil == _node); }

		Node * parent, * left, * right;
		int data;
		Color color;

		static Node nil;
	};

	RedBlackTree() : root{ &Node::nil } { root->color = Color::Black; }
	~RedBlackTree() {}

	void Insert(int _data);
	void Delete(int _data);
	void Traverse() const;
	const Node* Search(int _data) const { return Search(_data); }
	Node* Root() const { return root; }

private:
	void LeftRotate(Node* _x);
	void RightRotate(Node* _x);
	void FixInsert(Node* _node);
	Node* Search(int _data);

	void TraverseRecursive(Node* _node) const;
	
	Node* root;
};
RedBlackTree::Node RedBlackTree::Node::nil{};

void RedBlackTree::Insert(int _data)
{
	//root부터 시작(root의 parent는 없음)
	Node* parent = nullptr;
	Node* current = root;

	//리프노드까지 탐색 삽입(NIL이 나올때까지 내려간다)
	while (current != Node::NIL()) {
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

	//부모노드가 없을 시 root, 아닐 시 하위 노드로 들어간다
	if (parent == nullptr) {
		root = newNode;
	}
	else if (newNode->data < parent->data) {
		parent->left = newNode;
	}
	else {
		parent->right = newNode;
	}

	//루트노드는 BLACK
	if (nullptr == newNode->parent) {
		newNode->color = Color::Black;
		return;
	}

	//루트노드 밑에 삽입되었을 경우: 규칙이 유지되므로 return
	if (nullptr == newNode->parent->parent) {
		return;
	}

	//루트노드가 아닐 경우 레드블랙 트리 규칙을 유지
	FixInsert(newNode);
}

void RedBlackTree::Traverse() const
{
	TraverseRecursive(root);
}

void RedBlackTree::LeftRotate(Node* _x)
{
	//반시계방향(왼쪽) 회전: 오른쪽 자식(y)을 현재 _x 자리로 올린다
	Node* y = _x->right;

	//y의 자식 중 작은 노드를 x의 오른쪽으로 옮긴다(y의 자식은 무조건 x보다 크다)
	_x->right = y->left;
	if (Node::NIL() != _x->right) {
		_x->right->parent = _x;
	}

	//부모 변경(없을 경우 root, 있을 경우 부모의 자식 x를 y로 변경
	y->parent = _x->parent;
	if (nullptr == y->parent) {
		root = y;
	}
	else if (_x->parent->left == _x){
		y->parent->left = y;
	}
	else {
		y->parent->right = y;
	}

	y->left = _x;
	_x->parent = y;
}

void RedBlackTree::RightRotate(Node* _x)
{
	Node* y = _x->left;
	_x->left = y->right;
	if (Node::NIL() != _x->left) {
		_x->left->parent = _x;
	}

	y->parent = _x->parent;
	if (nullptr == y->parent) {
		root = y;
	}
	else if (y->parent->left == _x) {
		y->parent->left = y;
	}
	else {
		y->parent->right = y;
	}

	_x->parent = y;
	y->right = _x;
}


void RedBlackTree::FixInsert(Node* _node)
{
	//_node는 삽입 규칙에 따라 Red 노드이다.

	//부모 노드가 있는데 레드 노드일 경우: 규칙 위반(연속된 레드 노드 존재 불가)
	while (_node != root && _node->parent->color == Color::Red) {
		//Red 노드는 Black 부모가 반드시 존재하므로, 조부모 노드가 있다는 건 확실
		
		//부모 노드가 조부모의 left인지, right인지에 따라 다르게 처리
		if (_node->parent == _node->parent->parent->left) {
			Node* uncle = _node->parent->parent->right;

			//삼촌이 red-> 규칙 위반이므로 변경
			//부모+삼촌을 black으로, 조부모는 red로
			if (uncle->color == Color::Red) {
				_node->parent->color = Color::Black;
				uncle->color = Color::Black;
				uncle->parent->color = Color::Red;
				
				//이러면 조부모와 고조부모가 규칙 위반이 될 수 있으므로
				//루프를 통해 다시 검사
				_node = uncle->parent;
			}

			//삼촌이 Black(규칙 일치)
			else {
				//Node가 안쪽 자손일 경우(지그재그일 경우)
				//부모 = 조부모 왼쪽(위에서 체크함), 나 = 부모 오른쪽
				//부모를 기준으로 바꾸고, 왼쪽 회전시켜 부모를 바깥쪽 자식으로 만든다
				//cf)부모 노드는 Red 상태
				if (_node == _node->parent->right) {
					_node = _node->parent;
					LeftRotate(_node);
				}

				//Node가 바깥쪽 자손, Red
				//Node 부모는 Black, 조부모는 Red가 되어야 한다.
				//cf)새로 삽입된 노드는 형제 노드를 가지고 있지 않으므로(NIL) 
				//	형제 노드가 어떻게 되는지는 고려 안해도 됨
				_node->parent->color = Color::Black;
				_node->parent->parent->color = Color::Red;
				RightRotate(_node->parent->parent);
			}
		}
		//위와 반대
		else {
			Node* uncle = _node->parent->parent->left;
			if (uncle->color == Color::Red) {
				_node->parent->color = Color::Black;
				uncle->color = Color::Black;
				uncle->parent->color = Color::Red;
				_node = uncle->parent;
			}
			else {
				if (_node == _node->parent->left) {
					_node = _node->parent;
					RightRotate(_node);
				}
				_node->parent->color = Color::Black;
				_node->parent->parent->color = Color::Red;
				LeftRotate(_node->parent->parent);
			}
		}
	}
	//루트노드 무조건 Black
	root->color = Color::Black;
}

RedBlackTree::Node* RedBlackTree::Search(int _data)
{
	Node* node = root;
	while (node != Node::NIL()) {
		if (node->data == _data) {
			return node;
		}
		else if (_data < node->data) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}

	if (node == Node::NIL()) {
		node = nullptr;
	}

	return node;
}

void RedBlackTree::TraverseRecursive(Node* _node) const
{
	if (_node == Node::NIL()) { return; }
	TraverseRecursive(_node->left);
	std::cout << _node->data << '\n';
	TraverseRecursive(_node->right);
}

int main() {
	std::cin.tie(nullptr); std::ios_base::sync_with_stdio(false);
	LOCAL_IO;

	RedBlackTree rbtree;
	rbtree.Insert(1);
	rbtree.Insert(2);
	rbtree.Insert(3);
	rbtree.Insert(4);
	rbtree.Insert(5);
	rbtree.Insert(6);
	rbtree.Traverse();

	return 0;
}
