#include <stdio.h>
#include "Tree.h"

void main() {
	typedef Tree<char> T;

	T::Node* Root = T::CreateNode('A');

	T::Node* B = T::CreateNode('B');
	T::Node* C = T::CreateNode('C');
	T::Node* D = T::CreateNode('D');
	T::Node* E = T::CreateNode('E');
	T::Node* F = T::CreateNode('F');
	T::Node* G = T::CreateNode('G');
	T::Node* H = T::CreateNode('H');
	T::Node* I = T::CreateNode('I');
	T::Node* J = T::CreateNode('J');
	T::Node* K = T::CreateNode('K');

	T tree;

	tree.AddChild(Root, B);

	tree.AddChild(B, C);
	tree.AddChild(B, D);

	tree.AddChild(D, E);
	tree.AddChild(D, F);


	tree.AddChild(Root, G);
	tree.AddChild(G, H);

	tree.AddChild(Root, I);
	tree.AddChild(I, J);
	tree.AddChild(J, K);

	tree.PrintNode(Root, 0);

	printf("\n\n");

	tree.PrintNode(B, 0);
}