/*
 * RedBlackTree.h
 *
 *  Created on: Aug 14, 2016
 *      Author: aherne
 */

#ifndef SRC_REDBLACKTREE_H_
#define SRC_REDBLACKTREE_H_

#include <iostream>
#include "../list/ArrayList.h"

enum RedBlackTreeNodeColor { RED, BLACK };

template<typename VALUE>
struct RedBlackTreeNode {
	VALUE data;
	RedBlackTreeNode<VALUE>* left;
	RedBlackTreeNode<VALUE>* right;
	RedBlackTreeNode<VALUE>* parent;
	RedBlackTreeNodeColor color;
};

/**
 * Red Black Tree implementation with fundamentally based on pseudocode from CLR Introduction to Algorithms: 3rd Edition
 */
template<typename VALUE>
class RedBlackTree {
public:
	RedBlackTree(int (*comparator)(const VALUE&,const VALUE&)) {
		compare = comparator;
		nil = new RedBlackTreeNode<VALUE>;
		nil->color = BLACK;
		nil->left = nil->right = nil->parent = nil;

		root = nil;

		count = 0;
	}

	~RedBlackTree() {
		clear(root);
		delete nil;
	}

	bool hasNode(const VALUE& value) const {
		return findNode(value)!=nullptr;
	}

	const VALUE* getNodeValue(const VALUE& value) const {
		RedBlackTreeNode<VALUE>* node = findNode(value);
		if(node==nullptr) throw std::out_of_range("Element not found!");
		return &(node->data);
	}

	void deleteNode(const VALUE& value) {
		RedBlackTreeNode<VALUE>* node = findNode(value);
		if(node==nullptr) throw std::out_of_range("Element not found!");
		deleteNode(node);
	}

	void insertNode(const VALUE& value) {
		// find parent or update
		RedBlackTreeNode<VALUE>* y = nil;
		RedBlackTreeNode<VALUE>* x = root;
		while(x!=nil) {
			y = x;
			int comparison = compare(value, x->data);
			if(comparison<0) {
				x = x->left;
			} else if(comparison==0) {
				x->data = value;
				return;
			} else {
				x = x->right;
			}
		}
		// create node
		RedBlackTreeNode<VALUE>* z = new RedBlackTreeNode<VALUE>;
		z->data = value;
		z->parent = y;
		if(y==nil) {
			root = z;
		} else if(compare(value, y->data)<0) {
			y->left = z;
		} else {
			y->right = z;
		}
		z->left = nil;
		z->right = nil;
		z->color = RED;
		// rebalance
		insertFixup(z);
		// increment size
		++ count;
	}

	const std::size_t& getSize() const {
		return count;
	}

	bool hasMatches(const VALUE& value, int (*custom_comparator)(const VALUE&,const VALUE&)) {
		if(custom_comparator == nullptr) return false;
		ArrayList<RedBlackTreeNode<VALUE>*> results;
		findNodes(root, value, custom_comparator, &results);
		return results.size()>0;
	}

	void deleteMatches(const VALUE& value, int (*custom_comparator)(const VALUE&,const VALUE&)) {
		if(custom_comparator == nullptr) return;
		ArrayList<RedBlackTreeNode<VALUE>*> results;
		findNodes(root, value, custom_comparator, &results);
		if(results.size()==0) throw std::out_of_range("No match found!");
		for(auto it = results.begin(); *it!=*(results.end()); ++(*it)) {
			deleteNode(*(*it));
		}

	}

	// iterator stuff
	RedBlackTreeNode<VALUE>* min() {
		return min(root);
	}

	RedBlackTreeNode<VALUE>* getNextNode(RedBlackTreeNode<VALUE>* x) {
		if (x->right != nil) {
			x = x->right;
			while (x->left != nil){
				x = x->left;
			}
		} else {
			RedBlackTreeNode<VALUE>* y = x->parent;
			while (x == y->right) {
				x = y;
				y = y->parent;
			}
			if (x->right != y) {
				x = y;
			}
		}
		return x;
	}
private:

	void show(RedBlackTreeNode<VALUE>* const& h) {
		std::cout << "Element: " << h->data.key << " Color: " << h->color << std::endl;
		if(h->left!=nil) std::cout <<"Left: " << h->left->data.key << std::endl;
		if(h->right!=nil) std::cout <<"Right: " << h->right->data.key << std::endl;
		if(h->left!=nil) {
			show(h->left);
		}
		if(h->right!=nil) {
			show(h->right);
		}
	}

	void findNodes(RedBlackTreeNode<VALUE>*& h, const VALUE& value, int (*custom_comparator)(const VALUE&,const VALUE&), ArrayList<RedBlackTreeNode<VALUE>*>* const& results) {
		if(h->left!=nil) findNodes(h->left, value, custom_comparator, results);
		if(custom_comparator(value, h->data)==0) {
			results->addToBottom(h);
		}
		if(h->right!=nil) findNodes(h->right, value, custom_comparator, results);
	}

	RedBlackTreeNode<VALUE>* findNode(const VALUE& value) const {
		RedBlackTreeNode<VALUE>* x = root;
		while(x!=nil) {
			int comparison = compare(value, x->data);
			if(comparison<0) {
				x = x->left;
			} else if(comparison==0) {
				return x;
			} else {
				x = x->right;
			}
		}
		return nullptr;
	}

	void clear(RedBlackTreeNode<VALUE>* const& h) {
		if(h==nil) return;
		clear(h->left);
		clear(h->right);
		delete h;
	}

	void deleteNode(RedBlackTreeNode<VALUE>* z) {
		RedBlackTreeNode<VALUE>* x = nil;
		RedBlackTreeNode<VALUE>* y = z;
		RedBlackTreeNodeColor yOriginalColor = y->color;
		if(z->left == nil) { // ok
			x = z->right;
			transplant(z, z->right);
		} else if (z->right == nil) {
			x = z->left;
			transplant(z, z->left);
		} else {
			y = min(z->right);
			yOriginalColor = y->color;
			x = y->right;
			if(y->parent == z) {	// ok
				x->parent = y;
			} else {
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if(yOriginalColor == BLACK) {
			deleteFixup(x);
		}
		// decrement size
		-- count;
	}

	void insertFixup(RedBlackTreeNode<VALUE>*& z) {
		RedBlackTreeNode<VALUE>* y = nullptr;
		while(z!=root && z->parent->color == RED) {
			if(z->parent == z->parent->parent->left) {
				y = z->parent->parent->right;
				if(y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				} else {
					if (z == z->parent->right) {
						z = z->parent;
						leftRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					rightRotate(z->parent->parent);
				}
			} else {
				y = z->parent->parent->left;
				if(y->color == RED) {
					z->parent->color = BLACK;
					y->color = BLACK;
					z->parent->parent->color = RED;
					z = z->parent->parent;
				} else {
					if (z == z->parent->left) {
						z = z->parent;
						rightRotate(z);
					}
					z->parent->color = BLACK;
					z->parent->parent->color = RED;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}

	void deleteFixup(RedBlackTreeNode<VALUE>*& x) {
		RedBlackTreeNode<VALUE>* w = nullptr;
		while(x!=root && x->color == BLACK) {
			if(x == x->parent->left) {
				w = x->parent->right;
				if(w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					leftRotate(x->parent);
					w = x->parent->right;
				}
				if(w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				} else {
					if(w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED;
						rightRotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					leftRotate(x->parent);
					x = root;
				}
			} else {
				w = x->parent->left;
				if(w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					rightRotate(x->parent);
					w = x->parent->left;
				}
				if(w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					x = x->parent;
				} else {
					if(w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						leftRotate(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}

	void leftRotate(RedBlackTreeNode<VALUE>* x) {
		RedBlackTreeNode<VALUE>* y = x->right;
		x->right = y->left;
		if (y->left != nil) {
			y->left->parent=x;
		}
		y->parent=x->parent;
		if(x->parent == nil) {
			root=y;
		} else if (x == x->parent->left) {
			x->parent->left=y;
		} else {
			x->parent->right=y;
		}
		y->left=x;
		x->parent=y;
	}

	void rightRotate(RedBlackTreeNode<VALUE>* x) {
		RedBlackTreeNode<VALUE>* y = x->left;
		x->left = y->right;
		if (y->right != nil) {
			y->right->parent=x;
		}
		y->parent=x->parent;
		if(x->parent == nil) {
			root=y;
		} else if (x == x->parent->right) {
			x->parent->right=y;
		} else {
			x->parent->left=y;
		}
		y->right=x;
		x->parent=y;
	}

	void transplant(RedBlackTreeNode<VALUE>* u, RedBlackTreeNode<VALUE>* v) {
		if(u->parent == nil) {
			root = v;
		} else if(u==u->parent->left) {
			u->parent->left = v;
		} else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	RedBlackTreeNode<VALUE>* min(RedBlackTreeNode<VALUE>* x) {
		while(x->left != nil) {
			x = x->left;
		}
		return x;
	}

	std::size_t count;
	RedBlackTreeNode<VALUE>* root;
	RedBlackTreeNode<VALUE>* nil;
	int (*compare)(const VALUE&,const VALUE&);
};


#endif /* SRC_REDBLACKTREE_H_ */
