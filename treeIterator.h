// Name: Anthony T. Pham
// UF ID: 5038-1111
// Discussion section #: 1079

#ifndef TREEITERATOR_H
#define TREEITERATOR_H

#include <iostream>

using namespace std;

template<class E>
class treeIterator
{
	public:
		virtual bool hasNext() = 0;
		virtual binaryTreeNode<E>* next() = 0;
};

#endif
