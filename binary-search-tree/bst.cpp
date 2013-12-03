#include "bst.h"

using namespace std;
using namespace cop4530;

template <typename T>
BST<T>::BST( int th ) : threshold_value( th ), root( NULL ) {}

template <typename T>
BST<T>::BST( const string input, int th ) : threshold_value( th ), root( NULL )
{
	buildFromInputString( input );
}

template <typename T>
BST<T>::BST( const BST& rhs ) : root( NULL )
{
	operator=( rhs );
}

template <typename T>
BST<T>::~BST()
{
	makeEmpty();
}

template <typename T>
void BST<T>::buildFromInputString(const string input)
{
    vector<T> tokens;

    istringstream iss( input );
	copy(istream_iterator<T>(iss),
         istream_iterator<T>(),
         back_inserter<vector<T> >(tokens));

	if( empty() ){
		for( unsigned i = 0; i < tokens.size(); ++i ){
			insert( tokens.at( i ) );
		}
	} else {
		makeEmpty();

		for( unsigned i = 0; i < tokens.size(); ++i ){
			insert( tokens.at( i ) );
		}
	}
}

template <typename T>
const BST<T> & BST<T>::operator=(const BST & rhs)
{
	if( this != &rhs ){
		makeEmpty();
		root = clone( rhs.root );
	}
	return *this;
}

template <typename T>
bool BST<T>::empty()
{
	if( root == NULL ){
		return true;
	} else {
		return false;
	}
}

template <typename T>
void BST<T>::printInOrder() const
{
	printInOrder( root, true );
}

template <typename T>
void BST<T>::printLevelOrder() const
{
	printLevelOrder( root );
}

template <typename T>
int BST<T>::numOfNodes() const
{
	return numOfNodes( root );
}

template <typename T>
int BST<T>::height() const
{
	return height( root );
}

template <typename T>
void BST<T>::makeEmpty()
{
	makeEmpty( root );
}

template <typename T>
void BST<T>::insert(const T& v)
{
	insert( v, root );
}

template <typename T>
void BST<T>::remove(const T& v)
{
	remove( v, root );
}

template <typename T>
bool BST<T>::contains(const T& v)
{
	return contains( v, root, root );
}

/*
	Private member functions
*/

template <typename T>
void BST<T>::printInOrder(BSTNode *t, bool addNewline) const
{
	if( t == NULL ){
		return;
	}
	printInOrder( t->left, false );
	cout << t->element << " ";
	printInOrder( t-> right, false );
	
	if( addNewline ){
		cout << "\n";
	}
}

template <typename T>
void BST<T>::printLevelOrder(BSTNode *t) const
{
	queue<BSTNode*> q;

    if ( t ) {
        q.push( t );
    }
    while (!q.empty())
    {
        const BSTNode * const temp_node = q.front();
        q.pop();
        cout<< temp_node->element << " ";

        if (temp_node->left) {
            q.push(temp_node->left);
        }
        if (temp_node->right) {
            q.push(temp_node->right);
        }
    }
    cout << "\n";
}

template <typename T>
void BST<T>::makeEmpty(BSTNode* &t)
{
	// if( t->left != NULL ){
	// 	makeEmpty( t->left );
	// } 
	// if( t->right != NULL ){
	// 	makeEmpty( t->right );
	// }
	// delete t;
	if( t != NULL ){
		makeEmpty( t->left );
		makeEmpty( t-> right );
		delete t;
	}
	t = NULL;
}

template <typename T>
void BST<T>::insert(const T& v, BSTNode *&t)
{
	if( t == NULL ){
		t = new BSTNode( v, NULL, NULL );
	} else if( v < t->element ){
		if( t->left == NULL ){
			t->left = new BSTNode( v, NULL, NULL);
		} else {
			insert( v, t->left );
		}
	} else if( t->element < v ){
		if( t->right == NULL ){
			t->right = new BSTNode( v, NULL, NULL );
		} else {
			insert( v, t->right );
		}
	} 
}

template <typename T>
void BST<T>::remove(const T& v, BSTNode *&t)
{
	if( t == NULL ){
		return; 
	}

	if( v < t->element ){
		remove( v, t->left );
	} else if( t->element < v ){
		remove( v, t->right );
	} else 
	{
		BSTNode *temp = new BSTNode( v, NULL, NULL );
 
        if ( t->left == NULL )
        {
            temp = t->right;
            delete t;
            t = temp;
        }
        else if (t->right==NULL)
        {
            temp = t->left;
            delete t;
            t = temp;
        }
        else    //2 children
        {
            temp = t->right;
            BSTNode *parent = new BSTNode( v, NULL, NULL );
 
            while(temp->left!=NULL)
            {
                parent = temp;
                temp = temp->left;
            }
            t->element = temp->element;
            if (parent != NULL)
                remove( parent->left->element, parent->left );
            else
                remove( t->right->element, t->right );
        }
	}
}

template <typename T>
bool BST<T>::contains(const T& v, BSTNode *&t, BSTNode *&p )
{
	if( t == NULL ){
		return false;
	} else if( v < t->element ){
		return contains( v, t->left, t );
	} else if( t->element < v ){
		return contains( v, t->right, t );
	} else {
		t->search_count++;
		if( t->search_count == threshold_value ){
			
			t->search_count = 0; 

			if( p->left == NULL ){
				rotateWithRightChild( p );
			} else if( p->right == NULL ){
				rotateWithLeftChild( p );
			} else if( !(p->left->element < t->element) && !( t->element < p->left->element )){
				rotateWithLeftChild( p );
			} else {
				rotateWithRightChild( p );
			}
		}
		return true;
	}
}

template <typename T>
int BST<T>::numOfNodes(BSTNode *t) const
{
	if( t == NULL ){
		return 0;
	} 
	return 1 + numOfNodes( t->left ) + numOfNodes( t->right );
	
}

template <typename T>
int BST<T>::height(BSTNode *t) const
{
	if( t == NULL ){
		return -1;
	}
	int left = height( t->left );
	int right = height( t->right );

	if( left > right ){
		return left + 1;
	} else {
		return right + 1;
	}
}

template <typename T>
void BST<T>::rotateWithLeftChild(BSTNode *&p) const
{
	// 1. switch p and p->left ( t ) values
	// 2. p->left = p->left->right ( t->right )
	// 3. p->left->right ( t->right ) = p 
	BSTNode *t = new BSTNode( p->left->element, p->left->left, p );
	t = p->left;
	p->left = t->right;
	t->right = p;
	p = t;
}

template <typename T>
void BST<T>::rotateWithRightChild(BSTNode *&p) const
{
	BSTNode *t = new BSTNode( p->right->element, p->right->right, p );
	t = p->right;
	p->right = t->left;
	t->left = p;
	p = t;
}


