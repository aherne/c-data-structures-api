/*
 * TreeNode.h
 *
 *  Created on: Aug 23, 2016
 *      Author: Lucian
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include <vector>
#include <stdexcept>
#include "../list/ArrayList.h"
#include "../set/HashSet.h"
#include "../Comparator.h"
#include "../Hashing.h"

template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class TreeNode;

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline int compareTreeNode(TreeNode<T, compare, hash>* const& left, TreeNode<T, compare, hash>* const& right) {
	return compare(left->getData(), right->getData());
}

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline std::size_t hashTreeNode(TreeNode<T, compare, hash>* const& node) {
	return hash(node->getData());
}

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class TreeNode {
public:
	TreeNode(const T& data) {
		parent = nullptr;
		this->data = data;
		children = new HashSet<TreeNode<T,compare,hash>*, compareTreeNode<T,compare,hash>, hashTreeNode<T,compare,hash>>;
	}

	~TreeNode() {
		delete children;
	}

	// tested
	void setParent(TreeNode<T,compare,hash>* const& parent) {
		this->parent = parent;
	}

	// tested
	TreeNode<T,compare,hash>* const& getParent() {
		return parent;
	}

	// tested
	void setData(const T& data) {
		this->data = data;
	}

	// tested
	const T& getData() const {
		return data;
	}

	// tested
	HashSet<TreeNode<T,compare,hash>*, compareTreeNode<T,compare,hash>, hashTreeNode<T,compare,hash>>* const& getChildren() const {
		return children;
	}

	bool hasChild(TreeNode<T,compare,hash>* const& node) const {
		return children->contains(node);
	}

	// tested
	void addChild(TreeNode<T,compare,hash>* const& node) {
		node->setParent(this);
		children->add(node);
	}

	// tested
	void removeChild(TreeNode<T,compare,hash>* const& node) {
		children->remove(node);
	}

	void removeChildren() {
		children->clear();
	}

	// tested
	bool isDescendantOf(TreeNode<T,compare,hash>* const& node) {
		TreeNode<T,compare,hash>* root = this;
		while(root->getParent()!=nullptr) {
			if(root->getParent()==node) {
				return true;
			}
			root = root->getParent();
		}
		return false;
	}

	// tested
	bool isAncestorOf(TreeNode<T,compare,hash>* const& node) const {
		TreeNode<T,compare,hash>* root = node;
		while(root->getParent()!=nullptr) {
			if(root->getParent()==this) {
				return true;
			}
			root = root->getParent();
		}
		return false;
	}

	// Root - upmost element in tree
	// tested
	TreeNode<T,compare,hash>* getRoot() {
		TreeNode<T,compare,hash>* root = this;
		while(root->getParent()!=nullptr) {
			root = root->getParent();
		}
		return root;
	}

	// Path – a sequence of nodes and edges connecting a node with a descendant.
	// tested
	ArrayList<TreeNode<T,compare,hash>*>* getAncestors() {
		ArrayList<TreeNode<T,compare,hash>*>* output = new ArrayList<TreeNode<T,compare,hash>*>;
		TreeNode<T,compare,hash>* root = this;
		while(root->getParent()!=nullptr) {
			output->addToBottom(root->getParent());
			root = root->getParent();
		}
		return output;
	}

	// tested
	ArrayList<TreeNode<T,compare,hash>*>* getDescendants() const {
		ArrayList<TreeNode<T,compare,hash>*>* output = new ArrayList<TreeNode<T,compare,hash>*>;
		for(auto it1 = children->begin(); *it1!=*(children->end()); ++(*it1)) {
			output->addToBottom(*(*it1));
			ArrayList<TreeNode<T,compare,hash>*>* temp = (*(*it1))->getDescendants();
			for(auto it2 = temp->begin(); *it2!=*(temp->end()); ++(*it2)) {
				output->addToBottom(*(*it2));
			}
			delete temp;
		}
		return output;

	}

	// Size - number of elements in tree
	// tested
	std::size_t getSize() const {
		std::size_t output = (parent==nullptr?1:0)+children->size();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			output += (*(*it))->getSize();
		}
		return output;
	}
	// The height of a node is the number of edges on the longest downward path between that node and a leaf.
	// tested
	std::size_t getHeight() const {
		std::size_t height = 0;
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			std::size_t tmp_height = (*(*it))->getHeight();
			if(tmp_height>height) {
				height = tmp_height;
			}
		}
		return 1+height;
	}

	// The depth of a node is the number of edges from the node to the tree's root node.
	// tested
	std::size_t getDepth() const {
		std::size_t depth = 0;
		TreeNode<T,compare,hash>* root = parent;
		while(root!=nullptr) {
			++depth;
			root = root->getParent();
		}
		return depth;
	}
private:
	TreeNode<T,compare,hash>* parent;
	T data;
	HashSet<TreeNode<T,compare,hash>*, compareTreeNode<T,compare,hash>, hashTreeNode<T,compare,hash>>* children;
};

#endif /* TREENODE_H_ */
