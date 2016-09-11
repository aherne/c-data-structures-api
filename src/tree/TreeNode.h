/*
 * TreeNode.h
 *
 *  Created on: Aug 23, 2016
 *      Author: Lucian
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include <vector>
#include "../container/Queue.h"

template<typename T>
class TreeNode {
public:
	TreeNode(const T& data) {
		parent = nullptr;
		this->data = data;
	}

	~TreeNode() {
		for(auto it=children.begin(); it!=children.end(); ++it) {
			delete *it;
		}
	}

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

	// tested
	void detach() {
		// remove me as child of parent
		parent->removeChild(this);

		// migrate my children to parent
		for(auto it = children.begin(); it!=children.end(); ++it) {
			parent->addChild(*it);
		}

		// empty parent & children
		parent = nullptr;
		children.clear();
	}

	// tested
	void remove(const T& data, int (*comparator)(const T&, const T&)) {
		std::vector<TreeNode<T>*> results = search(data, comparator);
		if(results.size()==0) throw std::out_of_range("Value not found!");
		for(auto it = results.begin(); it!=results.end(); ++it) {
			TreeNode<T>* parent = (*it)->getParent();
			if(parent==nullptr) { // root is deleted (tree must be cleared)
				delete (*it);
				return;
			}
			(*it)->detach();
			delete (*it);
		}
	}

	// tested
	void removeBranch(const T& data, int (*comparator)(const T&, const T&)) {
		std::vector<TreeNode<T>*> results = search(data, comparator);
		if(results.size()==0) throw std::out_of_range("Value not found!");
		for(auto it = results.begin(); it!=results.end(); ++it) {
			TreeNode<T>* parent = (*it)->getParent();
			if(parent==nullptr) { // root is deleted (tree must be cleared)
				delete (*it);
				return;
			}
			parent->removeChild(*it);
			delete (*it);
		}
	}

	// tested
	std::vector<TreeNode<T>*> search(const T& data, int (*comparator)(const T&, const T&));

	// tested
	bool contains(const T& data, int (*comparator)(const T&, const T&)) const {
		if(comparator(this->data, data)==0) return true;
		for(auto it=children.begin(); it!=children.end(); ++it) {
			if((*it)->contains(data, comparator)) return true;
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
	// Height of node – The height of a node is the number of edges on the longest downward path between that node and a leaf.
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

	// Depth –The depth of a node is the number of edges from the node to the tree's root node.
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


template<typename T>
class TreeNodeVisitor {
public:
	virtual ~TreeNodeVisitor(){};

	virtual void visit(TreeNode<T>*& element) = 0;
};

template<typename T>
class SearchVisitor : public TreeNodeVisitor<T> {
public:
	SearchVisitor(T data, int (*comparator)(const T&, const T&)) {
		this->data = data;
		this->comparator = comparator;
	}

	~SearchVisitor() {}

	void visit(TreeNode<T>*& element) {
		if(comparator(data, element->getData())==0) {
			results.push_back(element);
		}
	}

	const std::vector<TreeNode<T>*>& getResults() {
		return results;
	}
private:
	std::vector<TreeNode<T>*> results;
	T data;
	int (*comparator)(const T&, const T&);
};

template<typename T>
inline void PreOrderTreeIterator(TreeNode<T>* node, TreeNodeVisitor<T>* visitor) {
	visitor->visit(node);
	std::vector<TreeNode<T>*> children = node->getChildren();
	for(auto it = children.begin(); it!=children.end(); ++it) {
		PreOrderTreeIterator(*it, visitor);
	}
}

template<typename T>
inline void PostOrderTreeIterator(TreeNode<T>* node, TreeNodeVisitor<T>* visitor) {
	std::vector<TreeNode<T>*> children = node->getChildren();
	for(auto it = children.begin(); it!=children.end(); ++it) {
		PreOrderTreeIterator(*it, visitor);
	}
	visitor->visit(node);
}

template<typename T>
inline void LevelOrderTreeIterator(TreeNode<T>* root, TreeNodeVisitor<T>* visitor) {
	Queue<TreeNode<T>*> q;
	q.push(root);
	while(!q.isEmpty()) {
		TreeNode<T>* node = q.pop();
		visitor->visit(node);
		std::vector<TreeNode<T>*> children = node->getChildren();
		for(auto it = children.begin(); it!=children.end(); ++it) {
			q.push(*it);
		}
	}
}

template<typename T>
inline void LevelOrderTreeIterator(TreeNode<T>* root, std::size_t depth, TreeNodeVisitor<T>* visitor) {
	Queue<TreeNode<T>*> q;
	q.push(root);
	while(!q.isEmpty()) {
		TreeNode<T>* node = q.pop();
		visitor->visit(node);
		std::vector<TreeNode<T>*> children = node->getChildren();
		for(auto it = children.begin(); it!=children.end(); ++it) {
			if((*it)->getDepth() <= depth) {
				q.push(*it);
			}
		}
	}
}

template<typename T>
inline std::vector<TreeNode<T>*> TreeNode<T>::search(const T& data, int (*comparator)(const T&, const T&)) {
	SearchVisitor<T> visitor(data, comparator);
	LevelOrderTreeIterator(this,&visitor);
	return visitor.getResults();
}

#endif /* TREENODE_H_ */
