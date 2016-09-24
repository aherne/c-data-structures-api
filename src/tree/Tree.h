/*
 * Tree.h
 *
 *  Created on: Sep 19, 2016
 *      Author: Lucian
 */

#ifndef TREE_H_
#define TREE_H_

#include "TreeNode.h"
#include "TreeIterator.h"

template<typename T>
class TreeDeallocator {
public:
	TreeDeallocator(TreeNode<T>* root) {
		deleteRecursive(root);
		delete root;
	}
private:
	void deleteRecursive(TreeNode<T>*& node) {
		std::vector<TreeNode<T>*> children = node->getChildren();
		for(auto it = children.begin(); it!=children.end(); ++it) {
			deleteRecursive(*it);
			delete (*it);
		}
	}
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
class Tree {
	public:
		Tree(const T& data) {
			root = new TreeNode<T>(data);
		}

		~Tree() {
			TreeDeallocator<T> deallocate(root);
		}

		TreeNode<T>* getRoot() {
			return root;
		}

		std::size_t getSize() {
			return root->getSize();
		}

		std::size_t getHeight() {
			return root->getHeight();
		}

		std::vector<TreeNode<T>*> search(const T& data, int (*comparator)(const T&, const T&)) {
			SearchVisitor<T> visitor(data, comparator);
			LevelOrderTreeIterator(root,&visitor);
			return visitor.getResults();
		}

		// tested
		void removeNode(TreeNode<T>* node) {
			if(node == root) throw std::out_of_range("Root cannot be removed without deallocating the whole tree!");

			// gets node's parent
			TreeNode<T>* parent = node->getParent();

			// removes node as child of parent
			parent->removeChild(node);

			// migrate my children to parent
			std::vector<TreeNode<T>*> children = node->getChildren();
			for(auto it = children.begin(); it!=children.end(); ++it) {
				parent->addChild(*it);
			}

			// empty parent & children
			delete node;
		}

		// tested
		void removeBranch(TreeNode<T>* node) {
			if(node == root) throw std::out_of_range("Root cannot be removed without deallocating the whole tree!");
			TreeNode<T>* parent = node->getParent();
			parent->removeChild(node);
			TreeDeallocator<T> deallocate(node);
		}

		// tested
		bool contains(const T& data, int (*comparator)(const T&, const T&)) const {
			Queue<TreeNode<T>*> q;
			q.push(root);
			while(!q.isEmpty()) {
				TreeNode<T>* node = q.pop();
				if(comparator(data, node->getData())) return true;
				std::vector<TreeNode<T>*> children = node->getChildren();
				for(auto it = children.begin(); it!=children.end(); ++it) {
					q.push(*it);
				}
			}
			return false;
		}
	private:
		TreeNode<T>* root;
};



#endif /* TREE_H_ */
