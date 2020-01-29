#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
};

/* 
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the destructor in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/* 
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();

	virtual void insert(const std::pair<Key, Value>& keyValuePair);
	virtual void remove(Key key);
	void clear();
	void print() const;

public:
	/**
	* An internal iterator class for traversing the contents of the BST.
	*/ 
	class iterator
	{
	public:
		iterator(Node<Key,Value>* ptr);
		iterator();

		std::pair<Key,Value>& operator*();
		std::pair<Key,Value>* operator->();

		bool operator==(const iterator& rhs) const;
		bool operator!=(const iterator& rhs) const;
		iterator& operator=(const iterator& rhs);

		iterator& operator++();

	protected:
		Node<Key, Value>* mCurrent;
	};

public:
	iterator begin();
	iterator end();
	iterator find(const Key& key) const;

protected:
	int level; 
	Node<Key, Value>* internalFind(const Key& key) const;
	Node<Key, Value>* getSmallestNode() const;
	void printRoot (Node<Key, Value>* root) const;
	void destroy(Node<Key, Value>* root);//helper function
	void update(Node<Key, Value>* child, Node<Key, Value>* parent, Key key);

	/* Helper functions are strongly encouraged to help separate the problem
	   into smaller pieces. You should not need additional data members. */

protected:
	Node<Key, Value>* mRoot;
};

/* 
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/ 

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*()
{
	return mCurrent->getItem(); 
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->()
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/* 
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/* 
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::destroy(Node<Key, Value>* root)
{
	if(root != NULL){
		destroy(root->getLeft());
		destroy(root->getRight());
		delete root;
	} 
}

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	// TODO
	mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	// TODO
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// TODO
	level = -1;
	//level count starts from -1 because the smallest is 0
	//in every insert opertaion, initialize level to -1 
	//because each insert has a specific level value.
	Key key = keyValuePair.first;
	Value value = keyValuePair.second;
	Node<Key, Value>* new_node = new Node<Key, Value>(key, value, NULL);

	if(mRoot == NULL){
		mRoot = new_node;
		level++;
	}
	else{
		Node<Key, Value>* index = mRoot;
		while(index!= NULL){
			level++;
			//whenever the index is null, it means 
			if(key < index->getKey()){
				new_node->setParent(index);
				index = index->getLeft();
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
				break;
			}
		}
		level++;
		//after index is at the right position,
		//increment its level one last time
	}
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::update(Node<Key, Value>* child, Node<Key, Value>* parent, Key key){
	if(parent != NULL){
		if(key < parent->getKey()){
			parent->setLeft(child);
		}
		else if(key > parent->getKey()){
			parent->setRight(child);
		}
	}
	if(child != NULL){
		child->setParent(parent);
	}
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(Key key)
{
	Node<Key, Value>* index = internalFind(key);
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
			successor->setLeft(left);
			left->setParent(successor);
			if(successor != right){
				if(successor->getRight() != NULL){
					successor->getRight()->setParent(successor->getParent());
					successor->getParent()->setLeft(successor->getRight());
				}
				else{
					successor->getParent()->setLeft(NULL);
				} 
				successor->setRight(right);
			//update successor's children
				right->setParent(successor);
			// index's children's parent 
			//update index's parent's child and successor's parent;
			}
			update(successor, i_parent, key);
			if(index == mRoot){
				mRoot = successor;
			}
		}
		else{
			if(left == NULL){
				//only has one right child
				update(right, i_parent, key);
				if(index == mRoot){
					mRoot = right;
				}
			}
			else if(right == NULL){
				//only has one left child
				update(left, i_parent, key);
				if(index == mRoot){
					mRoot = left;
				}
			}
			else{
				//doesn't have any child
				update(NULL, i_parent, key);
				if(index == mRoot){
					mRoot = NULL;
				}
			}
		}
		delete index;
	}
}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// TODO
	destroy(mRoot);
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// TODO
	Node<Key, Value>* index = mRoot;
	if(mRoot == NULL){
		return NULL;
	}
	else{
		while(index->getLeft() != NULL){
			index = index->getLeft();
		}
		return index;
	}
	return NULL;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	// TODO
	if(mRoot == NULL){
		return NULL;
	}
	Node<Key, Value>* index = mRoot;
	while(index->getKey() != key){
		if(index->getKey() < key){
			index = index->getRight();
		}
		else if(index->getKey() > key){
			index = index->getLeft();
		}
		if(index == NULL){
			return NULL;
		}
	}
	return index;
}

/**
* Helper function to print the tree's contents
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}
/* 
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
