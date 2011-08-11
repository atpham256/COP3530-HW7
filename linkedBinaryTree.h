
// linked binary tree using nodes of type binaryTreeNode
// derives from the abstract class binaryTree

#ifndef linkedBinaryTree_
#define linkedBinaryTree_

using namespace std;


#include <iostream>
#include <stack>
#include "binaryTree.h"
#include "arrayQueue.h"
#include "binaryTreeNode.h"
#include "myExceptions.h"
#include "booster.h"
#include "treeIterator.h"


template<class E>
class linkedBinaryTree : public binaryTree<binaryTreeNode<E> >
{
   public:
      linkedBinaryTree() {root = NULL; treeSize = 0;}
      ~linkedBinaryTree(){erase();}; 
      bool empty() const {return treeSize == 0;}
      int size() const {return treeSize;}
      E* rootElement() const;
      void makeTree(const E& element,
           linkedBinaryTree<E>&, linkedBinaryTree<E>&);
      linkedBinaryTree<E>& removeLeftSubtree();
      linkedBinaryTree<E>& removeRightSubtree();
      void preOrder(void(*theVisit)(binaryTreeNode<E>*))
           {visit = theVisit; preOrder(root);}
      void inOrder(void(*theVisit)(binaryTreeNode<E>*))
           {visit = theVisit; inOrder(root);}
      void postOrder(void(*theVisit)(binaryTreeNode<E>*))
           {visit = theVisit; postOrder(root);}
      void levelOrder(void(*)(binaryTreeNode<E> *));
      void preOrderOutput() {preOrder(output); cout << endl;}
      void inOrderOutput() {inOrder(output); cout << endl;}
      void postOrderOutput() {postOrder(output); cout << endl;}
      void levelOrderOutput() {levelOrder(output); cout << endl;}
      void erase()
           {
              postOrder(dispose);
              root = NULL;
              treeSize = 0;
           }
      int height() const {return height(root);}
      static void output(binaryTreeNode<E> *t)
                  {cout << t->element << ' ';}
                  
                  
      // inOrderIterator class
      class inOrderIterator : public treeIterator<E>
      {
		public:

          // constructor
          inOrderIterator(binaryTreeNode<E> *t = 0)
          {
        	  while(t != NULL)
        	  {
        		  inOrderStack.push(t);
        		  t = t->leftChild;
        	  }
          }
          // methods
          // tells the user whether there is another node in the in order sequence or not
		  bool hasNext()
		  {
        	  // if the stack is empty, then there is no next node, if the stack isn't empty
        	  // there is still a next node
        	  return (!inOrderStack.empty());
		  }
          // updates the stack so that the top element is the next node in the inorder sequence
		  // and returns the current node in the inorder sequence
		  binaryTreeNode<E> * next()
		  {
        	  // currentNode = already visited node at this point
        	  binaryTreeNode<E>* currentNode;
        	  // updateNode = random node to update stack
        	  binaryTreeNode<E>* updateNode;
        	  // if the stack is not empty that means there's still nodes left to traverse
       		  if(!inOrderStack.empty())
       		  {
				  // currentNode = next node in the inorder sequence at this point
				  currentNode = inOrderStack.top();
				  // pop out node that was already visited
				  inOrderStack.pop();
				  if(currentNode->rightChild != NULL)
				  {
					  // updateNode = right child is node already visited
					  updateNode = currentNode->rightChild;
					  // push in the right child
					  inOrderStack.push(updateNode);
					  // push in all the left childs of the right child
					  while(updateNode->leftChild != NULL)
					  {
						  inOrderStack.push(updateNode->leftChild);
						  updateNode = updateNode->leftChild;
					  }
				  }
       		  }
       		  return currentNode;
		  }
    	 protected:
           // stack to hold nodes
           stack<binaryTreeNode<E>*> inOrderStack;
      } ; // end of inOrderIterator class
      // iterator for the start of the inorder sequence
      inOrderIterator beginIO() {return inOrderIterator(root) ;}

      // postOrderIterator class
      class postOrderIterator : public treeIterator<E>
      {
		public:
          // constructor
          postOrderIterator(binaryTreeNode<E> *t = 0)
          {
        	  binaryTreeNode<E>* tempNode;
        	  if(t == NULL)
        	  {
        		  // do nothing
        	  }
        	  else // calculate postorder sequence
        	  {
        		  //push in root
        		  tempStack.push(t);
        		  // keep calculating postorder sequence while tempStack is not empty
        		  while(!tempStack.empty())
        		  {
        			  // pop out top node of tempStack and push it into postOrderStack
        			  tempNode = tempStack.top();
        			  tempStack.pop();
        			  postOrderStack.push(tempNode);
        			  // if the node that was popped out has subtrees
        			  // push in the left subtree if it has one into the tempStack
        			  // then push in the right subtree if it has one into the tempStack
        			  if(tempNode->leftChild != NULL)
        			  {
        				  tempStack.push(tempNode->leftChild);
        			  }
        			  if(tempNode->rightChild != NULL)
        			  {
        				  tempStack.push(tempNode->rightChild);
        			  }
        		  }
        		  // postOrderStack now has postorder sequence from top to bottom
        	  }
          }
          // methods
          // tells the user whether there is another node in the postorder sequence or not
			bool hasNext()
			{
          	  // if the stack is empty, then there is no next node, if the stack isn't empty
          	  // there is still a next node
          	  return (!postOrderStack.empty());
			}
            // updates the stack so that the top element is the next node in the postorder sequence
			// and returns the current node in the postorder sequence
			binaryTreeNode<E> * next()
			{
				binaryTreeNode<E>* currentNode;
          	  // if the stack is not empty, pop out the top node
          	  // the new top node is now the next node in the postorder sequence
          	  if(!postOrderStack.empty())
          	  {
          		  currentNode = postOrderStack.top();
          		  postOrderStack.pop();
          	  }
          	  return currentNode;
			}
    	  protected:
            // stack to hold the nodes in postorder order
            stack<binaryTreeNode<E>*> postOrderStack;
            // stack to hold nodes to calculate postorder order
            stack<binaryTreeNode<E>*> tempStack;
      } ; // end of postOrderIterator class
      // iterator for the start of the postorder sequence
      postOrderIterator beginPO() {return postOrderIterator(root) ;}

   protected:
      binaryTreeNode<E> *root;                // pointer to root
      int treeSize;                           // number of nodes in tree
      static void (*visit)(binaryTreeNode<E>*);      // visit function
      static int count;         // used to count nodes in a subtree
      static void preOrder(binaryTreeNode<E> *t);
      static void inOrder(binaryTreeNode<E> *t);
      static void postOrder(binaryTreeNode<E> *t);
      static void countNodes(binaryTreeNode<E> *t)
                  {
                     visit = addToCount; 
                     count = 0;
                     preOrder(t);
                  }
      static void dispose(binaryTreeNode<E> *t) {delete t;}
      
      static void addToCount(binaryTreeNode<E> *t)
                  {count++;}
      static int height(binaryTreeNode<E> *t);
};

// the following should work but gives an internal compiler error
 template <class E> void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);
// so the explicit declarations that follow are used for our purpose instead
//void (*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
//void (*linkedBinaryTree<booster>::visit)(binaryTreeNode<booster>*);
//void (*linkedBinaryTree<pair<int,int> >::visit)(binaryTreeNode<pair<int,int> >*);
//void (*linkedBinaryTree<pair<const int,char> >::visit)(binaryTreeNode<pair<const int,char> >*);
//void (*linkedBinaryTree<pair<const int,int> >::visit)(binaryTreeNode<pair<const int,int> >*);

template<class E>
E* linkedBinaryTree<E>::rootElement() const
{// Return NULL if no root. Otherwise, return pointer to root element.
   if (treeSize == 0)
      return NULL;  // no root
   else
      return &root->element;
}

template<class E>
void linkedBinaryTree<E>::makeTree(const E& element,
           linkedBinaryTree<E>& left, linkedBinaryTree<E>& right)
{// Combine left, right, and element to make new tree.
 // left, right, and this must be different trees.
   // create combined tree
   root = new binaryTreeNode<E> (element, left.root, right.root);
   treeSize = left.treeSize + right.treeSize + 1;

   // deny access from trees left and right
   left.root = right.root = NULL;
   left.treeSize = right.treeSize = 0;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeLeftSubtree()
{// Remove and return the left subtree.
   // check if empty
   if (treeSize == 0)
      throw emptyTree();

   // detach left subtree and save in leftSubtree
   linkedBinaryTree<E> leftSubtree;
   leftSubtree.root = root->leftChild;
   count = 0;
   leftSubtree.treeSize = countNodes(leftSubtree.root);
   root->leftChild = NULL;
   treeSize -= leftSubtree.treeSize;
  
   return leftSubtree;
}

template<class E>
linkedBinaryTree<E>& linkedBinaryTree<E>::removeRightSubtree()
{// Remove and return the right subtree.
   // check if empty
   if (treeSize == 0)
      throw emptyTree();

   // detach right subtree and save in rightSubtree
   linkedBinaryTree<E> rightSubtree;
   rightSubtree.root = root->rightChild;
   count = 0;
   rightSubtree.treeSize = countNodes(rightSubtree.root);
   root->rightChild = NULL;
   treeSize -= rightSubtree.treeSize;
  
   return rightSubtree;
}

template<class E>
void linkedBinaryTree<E>::preOrder(binaryTreeNode<E> *t)
{// Preorder traversal.
   if (t != NULL)
   {
      linkedBinaryTree<E>::visit(t);
      preOrder(t->leftChild);
      preOrder(t->rightChild);
   }
}

template<class E>
void linkedBinaryTree<E>::inOrder(binaryTreeNode<E> *t)
{// Inorder traversal.
   if (t != NULL)
   {
      inOrder(t->leftChild);
      linkedBinaryTree<E>::visit(t);
      inOrder(t->rightChild);
   }
}

template<class E>
void linkedBinaryTree<E>::postOrder(binaryTreeNode<E> *t)
{// Postorder traversal.
   if (t != NULL)
   {
      postOrder(t->leftChild);
      postOrder(t->rightChild);
      linkedBinaryTree<E>::visit(t);
   }
}

template <class E>
void linkedBinaryTree<E>::levelOrder(void(*theVisit)(binaryTreeNode<E> *))
{// Level-order traversal.
   arrayQueue<binaryTreeNode<E>*> q;
   binaryTreeNode<E> *t = root;
   while (t != NULL)
   {
      theVisit(t);  // visit t

      // put t's children on queue
      if (t->leftChild != NULL)
         q.push(t->leftChild);
      if (t->rightChild != NULL)
         q.push(t->rightChild);

      // get next node to visit
      try {t = q.front();}
      catch (queueEmpty) {return;}
      q.pop();
   }
}

template <class E>
int linkedBinaryTree<E>::height(binaryTreeNode<E> *t)
{// Return height of tree rooted at *t.
   if (t == NULL)
      return 0;                    // empty tree
   int hl = height(t->leftChild);  // height of left
   int hr = height(t->rightChild); // height of right
   if (hl > hr)
      return ++hl;
   else
      return ++hr;
}

#endif
