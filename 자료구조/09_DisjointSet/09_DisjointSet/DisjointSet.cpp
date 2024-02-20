#include <stdio.h>
#include "DisjointSet.h"

typedef DisjointSet<int> Disjoint;

void main() {
	Disjoint::Set* set1 = Disjoint::CreateSet(1);
	Disjoint::Set* set2 = Disjoint::CreateSet(2);
	Disjoint::Set* set3 = Disjoint::CreateSet(3);
	Disjoint::Set* set4 = Disjoint::CreateSet(4);

	printf("Set1 == Set2 : %d\n", Disjoint::FindSet(set1) == Disjoint::FindSet(set2));

	Disjoint::UnionSet(set1, set3);
	printf("Set1 == Set3 : %d\n", Disjoint::FindSet(set1) == Disjoint::FindSet(set3));

	Disjoint::UnionSet(set3, set4);
	printf("Set3 == Set4 : %d\n", Disjoint::FindSet(set3) == Disjoint::FindSet(set4));

	Disjoint::UnionSet(set1, set2);
	printf("Set1 == Set2 : %d\n", Disjoint::FindSet(set1) == Disjoint::FindSet(set2));
}