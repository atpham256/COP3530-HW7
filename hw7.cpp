// Name: Anthony T. Pham
// UF ID: 5038-1111
// Discussion section #: 1079
// test linked binary tree class

#include <iostream>
#include "linkedBinaryTree.h"

using namespace std;

int main(void)
{
   /*linkedBinaryTree<int> a,x,y,z;
   y.makeTree(1,a,a);
   z.makeTree(2,a,a);
   x.makeTree(3,y,z);
   y.makeTree(4,x,a);*/
	   linkedBinaryTree<int> a,x,y,z,b,c,d,e,f;
	   /*x.makeTree(1,a,a);
	   z.makeTree(2,x,a);
	   b.makeTree(3,z,a);
	   y.makeTree(4,b,a);*/
	   y.makeTree(1,a,a);
	   z.makeTree(2,a,a);
	   x.makeTree(3,y,z);
	   b.makeTree(1,a,a);
	   c.makeTree(2,a,a);
	   d.makeTree(3,b,c);
	   e.makeTree(4,x,d);

	   f.makeTree(5,a,e);
	   y.makeTree(6,a,f);
   cout << "Number of nodes = ";
   cout << y.size() << endl;
   cout << "height = ";
   cout << y.height() << endl;
   cout << "Preorder sequence is ";
   y.preOrderOutput();
   cout << "Inorder sequence is ";
   y.inOrderOutput();
   cout << "Postorder sequence is ";
   y.postOrderOutput();
   cout << "Level order sequence is ";
   y.levelOrderOutput();
   
   
   /////////////////// test for iterator
   //INORDER ITERATOR
   cout << "Test for InOrder Iterator: ";
   linkedBinaryTree<int>::inOrderIterator io = y.beginIO() ;
   while(io.hasNext())
     y.output(io.next()) ;
   cout << endl;
   //POSTORDER ITERATOR
   cout << "Test for PostOrder Iterator: ";
   linkedBinaryTree<int>::postOrderIterator ip = y.beginPO() ;
   while(ip.hasNext())
     y.output(ip.next()) ;
   cout << endl;
   
  

   return 0;
}
