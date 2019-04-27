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

template<typename T>
class TreeNode {
public:
	TreeNode(const T& data) {
		parent = nullptr;
		this->data = data;
		children = new ArrayList<TreeNode<T>*>;
	}

	~TreeNode() {
		delete children;
	}

	// tested
	void setParent(TreeNode<T>* const& parent) {
		this->parent = parent;
	}

	// tested
	TreeNode<T>*& getParent() {
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
	ArrayList<TreeNode<T>*>* const& getChildren() const {
		return children;
	}

	// tested
	void addChild(TreeNode<T>* const& node) {
		node->setParent(this);
		children->addToBottom(node);
	}

	// tested
	void removeChild(TreeNode<T>*& node) {
		std::size_t index = 0;
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			if(*(*it) == node) {
				children->removeIndex(index);
				return;
			}
			++ index;
		}
		throw std::out_of_range("Child not found!");
	}

	void removeChildren() {
		children->clear();
	}

	// tested
	bool isDescendantOf(TreeNode<T>*& node) {
		TreeNode<T>* root = this;
		while(root->getParent()!=nullptr) {
			if(root->getParent()==node) {
				return true;
			}
			root = root->getParent();
		}
		return false;
	}

	// tested
	bool isAncestorOf(TreeNode<T>*& node) const {
		TreeNode<T>* root = node;
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
	TreeNode<T>* getRoot() {
		TreeNode<T>* root = this;
		while(root->getParent()!=nullptr) {
			root = root->getParent();
		}
		return root;
	}

	// Path – a sequence of nodes and edges connecting a node with a descendant.
	// tested
	ArrayList<TreeNode<T>*>* getAncestors() {
		ArrayList<TreeNode<T>*>* output = new ArrayList<TreeNode<T>*>;
		TreeNode<T>* root = this;
		while(root->getParent()!=nullptr) {
			output->addToBottom(root->getParent());
			root = root->getParent();
		}
		return output;
	}

	// tested
	ArrayList<TreeNode<T>*>* getDescendants() const {
		ArrayList<TreeNode<T>*>* output = new ArrayList<TreeNode<T>*>;
		for(auto it1 = children->begin(); *it1!=*(children->end()); ++(*it1)) {
			output->addToBottom(*(*it1));
			ArrayList<TreeNode<T>*>* temp = (*(*it1))->getDescendants();
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
		TreeNode<T>* root = parent;
		while(root!=nullptr) {
			++depth;
			root = root->getParent();
		}
		return depth;
	}
private:
	TreeNode<T>* parent;
	T data;
	ArrayList<TreeNode<T>*>* children;
};

#endif /* TREENODE_H_ */
