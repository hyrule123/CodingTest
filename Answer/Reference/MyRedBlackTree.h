#pragma once
#include <iostream> //cout

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

		//_parent의 자식으로 들어감
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

	//Deletion 작업 시 이 자리에 올 수 있는 Node를 찾아준다.
	//후보: Left 노드로 한칸 가서 끝까지 오른쪽으로 이동한 리프노드
	//, 또는 Right 노드로 한칸 가서 끝까지 왼쪽으로 간 리프노드(현재 채택)
	Node* MinNode(Node* _node);
	//삭제될 노드를 대체할 노드 탐색
	Node* BSTReplace(Node* _node);
	void Delete(Node* _node);			//recursive
	void FixDoubleBlack(Node* _node);	//recursive

	Node* Search(int _data);

	void TraverseRecursive(Node* node) const;

	Node* root;
};

void RedBlackTree::Insert(int _data)
{
	//root부터 시작(root의 parent는 없음)
	Node* parent = nullptr;
	Node* current = root;

	//리프노드까지 탐색 삽입(NIL이 나올때까지 내려간다)
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

	//부모노드가 없을 시 root, 아닐 시 하위 노드로 들어간다
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

	//루트노드가 아닐 경우 레드블랙 트리 규칙을 유지
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
	//반시계방향(왼쪽) 회전: 오른쪽 자식이 새 부모가 된다.
	Node* nParent = _node->right;

	if (_node == root) { root = nParent; }

	//Parent의 자식으로 들어간다
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

	//Red의 부모는 Red일 수 없다
	if (parent->color == Color::Red) {
		if (uncle && uncle->color == Color::Red) {
			parent->color = Color::Black;
			uncle->color = Color::Black;
			grandParent->color = Color::Red;

			//위쪽 노드에 대해 재귀 Red-Red 검사
			FixRedRed(grandParent);
		}
		else {
			if (parent->IsLeftChild()) {
				//Outer child일 경우: 색상만 변경
				if (_node->IsLeftChild()) {
					std::swap(parent->color, grandParent->color);
				}
				//Inner child일 경우: parent 기준 왼쪽 회전, parent가 outer child가 되고 _node가 parent가 됨
				else {
					LeftRotate(parent);
					std::swap(_node->color, grandParent->color);
				}

				//GrandParent를 기준으로 다시 오른쪽으로 회전시킨다
				//GrandParent 자리에는 _node 또는 parent가 오게 된다.
				RightRotate(grandParent);
			}
			//좌우 반전
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
	//자식 둘다 있을 경우
	if (_node->left && _node->right) {
		return MinNode(_node->right);
	}

	//둘중 하나 있을 경우
	else if (_node->left) {
		return _node->left;
	}
	else if (_node->right) {
		return _node->right;
	}

	//둘다 없을경우(Leaf)
	return nullptr;
}

void RedBlackTree::Delete(Node* _node)
{
	Node* replace = BSTReplace(_node);

	//삭제 대상 + 교체 대상 모두 black인 경우를 Double Black condition이라고 한다.
	//nullptr은 NIL 노드이고, NIL 노드는 항상 Black이다
	bool isDoubleBlack = (_node->color == Color::Black) && (nullptr == replace || replace->color == Color::Black);

	//replace == NIL
	if (nullptr == replace) {
		if (root == _node) { root = nullptr; }
		else {
			if (isDoubleBlack) {
				FixDoubleBlack(_node);
			}
			//Double Black이 아닌 경우(둘중 하나는 Red인 경우)
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

	//replace 있음 + 자녀가 1개뿐일 때
	else if (_node->left == nullptr || _node->right == nullptr) {

		//노드가 루트일 경우 replace의 값만 끌올
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
	//자식을 2개 가지고 있을 경우 replace의 값을 가져온뒤, replace를 제거(재귀 호출)
	else {
		std::swap(_node->data, replace->data);
		Delete(replace);
	}
}

void RedBlackTree::FixDoubleBlack(Node* _node)
{
	if (root == _node) { return; }

	Node* sibling = _node->Sibling(), * parent = _node->parent;

	//검사할 자매 노드 없음 -> 부모 노드로 재귀 호출
	if (nullptr == sibling) {
		FixDoubleBlack(_node->parent);
	}
	else {
		if (sibling->color == Color::Red) {
			parent->color = Color::Red;
			sibling->color = Color::Black;

			//sibling을 부모 노드 위치로 옮겨준다(== 알맞게 회전시킨다)
			if (sibling->IsLeftChild()) {
				RightRotate(parent);
			}
			else {
				LeftRotate(parent);
			}

			//Sibling Right 또는 Left를 새로운 Sibling으로 해서 검사한다.
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
					//sibling->left가 outer child일 경우(left left)
					if (sibling->IsLeftChild()) {
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						RightRotate(parent);//sibling이 parent 자리로 오게됨, sibling Left가 sibling 자리로 옴
					}
					//inner child
					else {
						sibling->left->color = parent->color;
						RightRotate(sibling);//sibling의 왼쪽 자식을 끌어온다.
						LeftRotate(parent);//parent를 왼쪽으로 돌리면 sibling의 왼쪽 자식이 parent 위치에 옴
					}
				}
				//좌우반전
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
			//2개의 Black child->자신이 Red가 되면 됨
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