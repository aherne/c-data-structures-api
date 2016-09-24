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

template<typename T>
class TreeNode {
public:
	TreeNode(const T& data) {
		parent = nullptr;
		this->data = data;
	}

	~TreeNode() {}

	// tested
	void setParent(TreeNode<T>* parent) {
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
	const T& getData() {
		return data;
	}

	// tested
	const std::vector<TreeNode<T>*>& getChildren() {
		return children;
	}

	// tested
	TreeNode<T>* addChild(const T& data) {
		TreeNode<T>* node = new TreeNode<T>(data);
		node->setParent(this);
		children.push_back(node);
		return node;
	}

	// tested
	void addChild(TreeNode<T>*& node) {
		node->setParent(this);
		children.push_back(node);
	}

	// tested
	void removeChild(TreeNode<T>* node) {
		for(auto it=children.begin(); it!=children.end(); ++it) {
			if(*it == node) {
				it = children.erase(it);
				return;
			}
		}
		throw std::out_of_range("Child not found!");
	}

	void removeChildren() {
		children.clear();
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
	bool isAncestorOf(TreeNode<T>*& node) {
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
	std::vector<TreeNode<T>*> getAncestors() {
		std::vector<TreeNode<T>*> output;
		TreeNode<T>* root = this;
		while(root->getParent()!=nullptr) {
			output.push_back(root->getParent());
			root = root->getParent();
		}
		return output;
	}

	// Size - number of elements in tree
	// tested
	std::size_t getSize() {
		std::size_t output = (parent==nullptr?1:0)+children.size();
		for(auto it=children.begin(); it!=children.end(); ++it) {
			output += (*it)->getSize();
		}
		return output;
	}
	// The height of a node is the number of edges on the longest downward path between that node and a leaf.
	// tested
	std::size_t getHeight() {
		std::size_t height = 0;
		for(auto it=children.begin(); it!=children.end(); ++it) {
			std::size_t tmp_height = (*it)->getHeight();
			if(tmp_height>height) {
				height = tmp_height;
			}
		}
		return 1+height;
	}

	// The depth of a node is the number of edges from the node to the tree's root node.
	// tested
	std::size_t getDepth() {
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
	std::vector<TreeNode<T>*> children;
};

#endif /* TREENODE_H_ */
