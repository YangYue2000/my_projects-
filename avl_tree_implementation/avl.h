#ifndef SPLAY_H
#define SPLAY_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "../bst/bst.h"
#include <cmath>

/**
* A templated binary search tree implemented as a Splay tree.
*/
template <class Key, class Value>
class SplayTree : public BinarySearchTree<Key, Value>
{
public:
	// Methods for inserting/removing elements from the tree. You must implement
	// both of these methods.
	SplayTree();
	virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
	void remove(const Key& key);
	int report() const;

private:
	/* You'll need this for problem 5. Stores the total number of inserts where the
	   node was added at level strictly worse than 2*log n (n is the number of nodes
	   including the added node. The root is at level 0). */
	int badInserts = 0;
	int total = 0;
	Node<Key, Value>* l_rotate(Node<Key, Value>* node);
	Node<Key, Value>* r_rotate(Node<Key, Value>* node);
	Node<Key, Value>* l_r_rotate(Node<Key, Value>* node);
	Node<Key, Value>* r_l_rotate(Node<Key, Value>* node); 
	void splay(Node<Key, Value>* node);
	/* Helper functions are encouraged. */
};

/*
--------------------------------------------
Begin implementations for the SplayTree class.
--------------------------------------------
*/

template<typename Key, typename Value>
SplayTree<Key, Value>::SplayTree() : badInserts(0) { }

template<typename Key, typename Value>
int SplayTree<Key, Value>::report() const {
	return badInserts;
}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::l_rotate(Node<Key, Value>* node)
{
	Node<Key, Value>* g = node;
	Node<Key, Value>* p = g->getRight();
	Node<Key, Value>* x = p->getRight();
	Node<Key, Value>* T1 = p->getLeft();
	Node<Key, Value>* T2 = x->getLeft();
	this->update(x, g->getParent(), g->getKey());
	x->setLeft(p);
	p->setParent(x);
	p->setRight(T2);
	if(T2 != NULL){
		T2->setParent(p);
	}
	p->setLeft(g);
	g->setParent(p);
	g->setRight(T1);
	if(T1 != NULL){
		T1->setParent(g);
	}
	if(this->mRoot == g){
		this->mRoot = x;
	}
	return x;
}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::l_r_rotate(Node<Key, Value>* node)
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
	if(this->mRoot == g){
		this->mRoot = x;
	}
	return x;
}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::r_rotate(Node<Key, Value>* node)
{
	Node<Key, Value>* g = node;
	Node<Key, Value>* p = g->getLeft();
	Node<Key, Value>* x = p->getLeft();
	Node<Key, Value>* T1 = x->getRight();
	Node<Key, Value>* T2 = p->getRight();
	this->update(x, g->getParent(), g->getKey());
	x->setRight(p);
	p->setParent(x);
	p->setLeft(T1);
	if(T1 != NULL){
		T1->setParent(p);
	}
	p->setRight(g);
	g->setParent(p);
	g->setLeft(T2);
	if(T2 != NULL){
		T2->setParent(g);
	}
	if(this->mRoot == g){
		this->mRoot = x;
	}
	return x;
}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::r_l_rotate(Node<Key, Value>* node)
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
	if(this->mRoot == g){
		this->mRoot = x;
	}
	return x;
}


template<typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key,Value>* node)
{
	Node<Key, Value>* index = node;
	Node<Key, Value>* parent = index->getParent(); 
	Key key = index->getKey();
	//node is the first node in the tree, so its parent is NULL
	//no need to splay
	if(parent == NULL){
		return;
	}
	while(parent != NULL){
		Node<Key, Value>* g_parent = parent->getParent();
		if(g_parent == NULL){
			if(parent->getKey() > key){
				Node<Key, Value>* T2 = index->getRight();
				index->setParent(NULL);
				index->setRight(parent);
				parent->setParent(index);
				parent->setLeft(T2);
				if(T2 != NULL){
					T2->setParent(parent);
				}
				this->mRoot = index;
			}
			else if(parent->getKey() < key){
				Node<Key, Value>* T2 = index->getLeft();
				index->setParent(NULL);
				index->setLeft(parent);
				parent->setParent(index);
				parent->setRight(T2);
				if(T2 != NULL){
					T2->setParent(parent);
				}
				this->mRoot = index;
			}
			break;
		}
		Key g_key = g_parent->getKey();
		Key p_key = parent->getKey();
		//left left case
		if(p_key < g_key && key < p_key){
			index = r_rotate(g_parent);
		}
		//left right case
		if(p_key <g_key && key > p_key){
			index = l_r_rotate(g_parent);
		}
		//right right case
		if(p_key > g_key && key > p_key){
			index = l_rotate(g_parent);
		}
		//right left case
		if(p_key > g_key && key < p_key){
			index = r_l_rotate(g_parent);
		}
		parent = index->getParent();
	}
}

/**
* Insert function for a key value pair. Finds location to insert the node and then splays it to the top.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	// TODO
	BinarySearchTree<Key, Value>::insert(keyValuePair);
	total++;
	int height = this->level;
	if(height > 2*(log2(total))){
		badInserts++;
	}
	Key key = keyValuePair.first;
	Node<Key, Value>* index = this->internalFind(key);
	splay(index);
}

/**
* Remove function for a given key. Finds the node, reattaches pointers, and then splays the parent
* of the deleted node to the top.
*/
template<typename Key, typename Value>
void SplayTree<Key, Value>::remove(const Key& key)
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
			if(index == this->mRoot){
				this->mRoot = successor;
			}
			successor->setLeft(left);
			left->setParent(successor);
			if(successor != right){
				Node<Key, Value>* s_parent = successor->getParent();
				if(successor->getRight() != NULL){
					successor->getRight()->setParent(s_parent);
					s_parent->setLeft(successor->getRight());
				}
				else{
					s_parent->setLeft(NULL);
				} 
				successor->setRight(right);
			//update successor's children
				right->setParent(successor);
			// index's children's parent 
			//update index's parent's child and successor's parent;
				this->update(successor, i_parent, key);
				splay(s_parent);
			}
			else{
				this->update(successor, i_parent, key);
				splay(successor);
			}
		}
		else{
			if(left == NULL){
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
			else{
				//doesn't have any child
				this->update(NULL, i_parent, key);
				if(index == this->mRoot){
					this->mRoot = NULL;
				}
			}
			splay(i_parent);
		}
		delete index;
	}
}

/*
------------------------------------------
End implementations for the SplayTree class.
------------------------------------------
*/

#endif
