#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "../bst/bst.h"

/**
* A special kind of node for an AVL tree, which adds the height as a data member, plus 
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
	// Constructor/destructor.
	AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
	virtual ~AVLNode();

	// Getter/setter for the node's height.
	int getHeight() const;
	void setHeight(int height);

	// Getters for parent, left, and right. These need to be redefined since they 
	// return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
	// for more information.
	virtual AVLNode<Key, Value>* getParent() const override;
	virtual AVLNode<Key, Value>* getLeft() const override;
	virtual AVLNode<Key, Value>* getRight() const override;

protected:
	int mHeight;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a height of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
	: Node<Key, Value>(key, value, parent)
	, mHeight(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* Getter function for the height. 
*/
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* Setter function for the height. 
*/
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
	mHeight = height;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
	return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods. 
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	void remove(const Key& key);

private:
	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */
	AVLNode<Key, Value>* r_rotate(Node<Key, Value>* y);
	//should i make rotate proteced since spaly tree may also use it?
	AVLNode<Key, Value>* l_rotate(Node<Key, Value>* x);
	AVLNode<Key, Value>* l_r_rotate(Node<Key, Value>* node);
	AVLNode<Key, Value>* r_l_rotate(Node<Key, Value>* node);
	int getBalance(Node<Key, Value>* node);
	int max(int a, int b);
	int height(Node<Key, Value>* node);
	void update_height(Node<Key, Value>* node);
	void balance(Node<Key, Value>* node);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree. 
*/

template<typename Key, typename Value>
void AVLTree<Key, Value>::update_height(Node<Key, Value>* node)
{
	static_cast<AVLNode<Key,Value>*>(node)->setHeight(1+max(height(node->getLeft()),height(node->getRight())));
}


template<typename Key, typename Value>
int AVLTree<Key, Value>::height(Node<Key, Value>* node)
{
	if(node == NULL){
		return 0;
	}
	return static_cast<AVLNode<Key,Value>*>(node)->getHeight();
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::max(int a, int b)
{
	if(a > b){
		return a;
	}
	else if(a < b){
		return b;
	}
	else{
		return a;
	}
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key,Value>::r_rotate(Node<Key, Value>* y)
{
	//this functoin assumes y, the root node, and x, its left child, both exist 
	//note that many BinarySearchTree function called here's parameters are of
	//Node* data type, but it should be okay to use AVLNode* data type too because 
	//the latter is just an instance of the former.
	Node<Key, Value>* x = y->getLeft();
	Node<Key, Value>* T2 = x->getRight();
	//new relationship between x and y's parent
	this->update(x,y->getParent(),y->getKey());
	//new relationship between x and y
	x->setRight(y);
	y->setParent(x);
	//new relatoinshpi between y and T2, if T2 exists.
	y->setLeft(T2);
	if(T2 != NULL){
		T2->setParent(y);
	}
	update_height(y);
	//need to update y's height first because x's height is based on the updated y's height
	update_height(x);
	//only update heights for x and y because only their children and corresponding heights change
	if(this->mRoot == y){
		this->mRoot = x;
	}
	return static_cast<AVLNode<Key,Value>*>(x);
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key,Value>::r_l_rotate(Node<Key, Value>* node)
{
	Node<Key, Value>* g = node;
	Node<Key, Value>* p = g->getRight();
	Node<Key, Value>* x = p->getLeft();
	Node<Key, Value>* T1 = x->getLeft();
	Node<Key, Value>* T2 = x->getRight();
	this->update(x, g->getParent(), g->getKey());
	x->setLeft(g);
	g->setParent(x);
	x->setRight(p);
	p->setParent(x);
	p->setLeft(T2);
	if(T2 != NULL){
		T2->setParent(p);
	}
	g->setRight(T1);
	if(T1 != NULL){
		T1->setParent(g);
	}
	update_height(g);
	update_height(p);
	update_height(x);
	if(this->mRoot == g){
		this->mRoot = x;
	}
	return static_cast<AVLNode<Key,Value>*>(x);
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::l_rotate(Node<Key, Value>* x)
{
	Node<Key, Value>* y = x->getRight();
	Node<Key, Value>* T2 = y->getLeft();
	this->update(y, x->getParent(), x->getKey());
	y->setLeft(x);
	x->setParent(y);
	x->setRight(T2);
	if(T2 != NULL){
		T2->setParent(x);
	}
	update_height(x);
	update_height(y);
	if(this->mRoot == x){
		this->mRoot = y;
	}
	return static_cast<AVLNode<Key, Value>*>(y);
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::l_r_rotate(Node<Key, Value>* node)
{
	Node<Key, Value>* g = node;
	Node<Key, Value>* p = g->getLeft();
	Node<Key, Value>* x = p->getRight();
	Node<Key, Value>* T1 = x->getLeft();
	Node<Key, Value>* T2 = x->getRight();
	this->update(x, g->getParent(), g->getKey());
	x->setLeft(p);
	p->setParent(x);
	x->setRight(g);
	g->setParent(x);
	g->setLeft(T2);
	if(T2 != NULL){
		T2->setParent(g);
	}
	p->setRight(T1);
	if(T1 != NULL){
		T1->setParent(p);
	}
	update_height(p);
	update_height(g);
	update_height(x);
	if(this->mRoot == g){
		this->mRoot = x;
	}
	return static_cast<AVLNode<Key,Value>*>(x);
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::getBalance(Node<Key, Value>* node){
	if(node == NULL){
		return 0;
	}
	return height(node->getLeft()) - height(node->getRight());
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::balance(Node<Key, Value>* node){
	//this functoin will check all the ancestors of the input node
	//and balance all of them
	//it will not when 
	if(node != NULL){
	//if it's not a duplicate entry for insert
		
		Node<Key, Value>* INDEX = node;
		//the following while loop keep updating the inserted node's ancestors' height
		//and perfom rotations if necessary
		while(INDEX != NULL){
			//need to update INDEX's height because 
			//the substree rooted at INDEX has been inserted a new node
			update_height(INDEX);
			int balance = getBalance(INDEX);
			Node<Key, Value>* left = INDEX->getLeft();
			Node<Key, Value>* right = INDEX->getRight();
			
			
			if(balance > 1){
				Node<Key, Value>* left_left = left->getLeft();
				Node<Key, Value>* left_right = left->getRight();
				//left left case
				if(height(left_left) >= height(left_right)){
					INDEX = r_rotate(INDEX);
				}
				//left right case
				else if(height(left_left) < height(left_right) ){
					left = l_rotate(left);
					INDEX = r_rotate(INDEX);
				}
			}
			else if(balance < -1){
				Node<Key, Value>* right_right = right->getRight();
				Node<Key, Value>* right_left = right->getLeft();
				//right right case
				if(height(right_right) >= height(right_left)){
					INDEX = l_rotate(INDEX);
				}
				//right left case
				else if(height(right_right) < height(right_left)){
					right = r_rotate(right);
					INDEX = l_rotate(INDEX);
				}
			}
			INDEX = INDEX->getParent();
			//keep updating
		}
	}
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// TODO
	//the following is exact same as BST insert, except that the new_node is 
	//a Node* pointer that points to an AVLNode object
	//so 
	Key key = keyValuePair.first;
	Value value = keyValuePair.second;
	Node<Key, Value>* new_node = new AVLNode<Key, Value>(key, value, NULL);

	if(this->mRoot == NULL){
		this->mRoot = new_node;
	}
	else{
		Node<Key, Value>* index = this->mRoot;
		while(index!= NULL){
			if(key < index->getKey()){
				new_node->setParent(index);
				index = index->getLeft();
				//note that this index is a Node pointer that points to an AVLNode object
				//so the AVLtree getLeft() is called(because getLeft() is a virtual function)
				//so the index's data type is an AVLNode pointer
				if(index == NULL){
					new_node->getParent()->setLeft(new_node);
				}
			}
			else if(key > index->getKey()){
				new_node->setParent(index);
				index = index->getRight();
				if(index == NULL){
					new_node->getParent()->setRight(new_node);
				}
			}
			else if(key == index->getKey()){
				index->setValue(value);
				delete new_node;
				//the key already existed,so there is no need to keep
				//the new_node, then delete it
				//otherwise the deconstructor cannot track and delete
				//this new_node
				return;
			}
		}
	}
	//finish BST insert, new_node is at the right position in the tree
	static_cast<AVLNode<Key,Value>*>(new_node)->setHeight(1);
	//all newly inserted nodes have the height 1
	balance(new_node->getParent());
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished. 
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
	// TODO
	Node<Key, Value>* index = this->internalFind(key);
	if(index != NULL){
		Node<Key, Value>* left = index->getLeft();
		Node<Key, Value>* right = index->getRight();
		Node<Key, Value>* i_parent = index->getParent();
		if(left!= NULL && right != NULL){
			//has two children 
			Node<Key,Value>* successor = right;
			while(successor->getLeft() != NULL){
				successor = successor->getLeft();
			}
			//the while loop finds the successor
			if(this->mRoot == index){
				this->mRoot = successor;
			}
			Node<Key, Value>* s_parent = successor->getParent();
			Node<Key, Value>* s_right = successor->getRight();
			successor->setLeft(left);
			left->setParent(successor);
			this->update(successor, i_parent, key);
			if(successor != right){
				successor->setRight(right);
			    //update successor's children
				right->setParent(successor);
			    // index's children's parent 
				if(s_right != NULL){
					s_right->setParent(s_parent);
					s_parent->setLeft(s_right);
				}
				else{
					s_parent->setLeft(NULL);
				}
				balance(s_parent);
			}
			else{
				balance(successor);
			}
		}
		else{
			if(left == NULL && right == NULL){
				//doesn't have any child
				this->update(NULL, i_parent, key);
				if(index == this->mRoot){
					this->mRoot = NULL;
				}			}
			else if(left == NULL){
				//only has one right child
				this->update(right, i_parent, key);
				if(index == this->mRoot){
					this->mRoot = right;
				}
			}
			else if(right == NULL){
				//only has one left child
				this->update(left, i_parent, key);
				if(index == this->mRoot){
					this->mRoot = left;
				}
			}
			balance(i_parent);
		}
		delete index;
	}
}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif
