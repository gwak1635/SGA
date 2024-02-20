#include <iostream>
using namespace std;
#include "BinaryTree.h"

void main() {

	typedef BTree<char> Tree;
	
	Tree tree;
	//	BTree<char>::Node
	Tree::Node* A = Tree::CreateNode('A');
	Tree::Node* B = Tree::CreateNode('B');
	Tree::Node* C = Tree::CreateNode('C');
	Tree::Node* D = Tree::CreateNode('D');
	Tree::Node* E = Tree::CreateNode('E');
	Tree::Node* F = Tree::CreateNode('F');
	Tree::Node* G = Tree::CreateNode('G');

/*
		A
	B       E
C     D   F    G
*/
	tree.Root(A);

	A->Left = B;
	A->Right = E;

	B->Left = C;
	B->Right = D;

	E->Left = F;
	E->Right = G;

	cout << "PreOrder" << endl;
	tree.PreOrder(A);
	cout << endl << endl;

	cout << "InOrder" << endl;
	tree.InOrder(A);
	cout << endl << endl;

	cout << "PostOrder" << endl;
	tree.PostOrder(A);
	cout << endl << endl;
}