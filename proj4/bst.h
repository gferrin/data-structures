#ifndef COP4530_BST_H
#define COP4530_BST_H

#include <string>
#include <queue>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

namespace cop4530 {

int default_threshold_value = 1;

template <typename T>
class BST {
public:
	BST(int th=default_threshold_value);
	BST(const string input, int th=default_threshold_value);
	BST(const BST& rhs );
	~BST();
	void buildFromInputString(const string input);
	const BST & operator= (const BST &);
	bool empty();

	void printInOrder() const; // print out the elements in the tree in the in-order traversal.
	void printLevelOrder() const; // print out the elements in the tree in the level-order traversal.	
	int numOfNodes() const; // return the number of nodes in the tree.
	int height() const; // return the height of the tree.
	void makeEmpty(); // delete all nodes from the tree (make the tree empty)
	void insert(const T& v); // insert v into the tree.
	void remove(const T& v); // delete value v from the tree.
	bool contains(const T& v); // search to determine if v is the tree.

private:
	struct BSTNode
	{
		T element;
		BSTNode *left;
		BSTNode *right;
		int search_count;

		BSTNode( const T & el, BSTNode *lt, BSTNode *rt, int count = 0 )
			: element( el ), left( lt ), right( rt ), search_count( count ) {}
	};

	int threshold_value;
	BSTNode *root;

	void printInOrder(BSTNode *t, bool addNewline) const; // print the elements in the subtree rooted at t in the in-order traversal. 
	void printLevelOrder(BSTNode *t) const; // print the elements in the subtree rooted at t in the level-order traversal. 
	void makeEmpty(BSTNode* &t); // delete all nodes in the subtree rooted at t. Called by functions such as the destructor.
	void insert(const T& v, BSTNode *&t); // 
	void remove(const T& v, BSTNode *&t); 
	void rotateWithLeftChild(BSTNode *&t) const;
	void rotateWithRightChild(BSTNode *&t) const;
	bool contains(const T& v, BSTNode *&t, BSTNode *&p ); // , ...other parameters if necessary...); 
	int numOfNodes(BSTNode *t) const; // return the number of nodes in the subtree rooted at t.
	int height(BSTNode *t) const; 
	BSTNode * clone(BSTNode *t) const
	{
		if( t == NULL ){
			return NULL;
		} else {
			return new BSTNode( t->element, clone( t->left ), clone( t->right ), t->search_count );
		}
	} 

};

#include "bst.cpp"

} // end of namespace COP4530
#endif