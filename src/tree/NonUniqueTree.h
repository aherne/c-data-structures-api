/*
 * NonUniqueTree.h
 *
 *  Created on: Dec 22, 2016
 *      Author: aherne
 */

#ifndef SRC_TREE_NONUNIQUETREE_H_
#define SRC_TREE_NONUNIQUETREE_H_

#include "Tree.h"
#include "TreeIterator.h"
#include "../container/Queue.h"

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
class NonUniqueTree : public Tree<T> {
	public:
		using Tree<T>::Tree;

		std::vector<TreeNode<T>*> search(const T& data, int (*comparator)(const T&, const T&)) {
			SearchVisitor<T> visitor(data, comparator);
			LevelOrderTreeIterator(this->root,&visitor);
			return visitor.getResults();
		}

		bool contains(const T& data, int (*comparator)(const T&, const T&)) const {
			Queue<TreeNode<T>*> q;
			q.push(this->root);
			while(!q.isEmpty()) {
				TreeNode<T>* node = q.pop();
				if(comparator(data, node->getData())==0) return true;
				std::vector<TreeNode<T>*> children = node->getChildren();
				for(auto it = children.begin(); it!=children.end(); ++it) {
					q.push(*it);
				}
			}
			return false;
		}
};


#endif /* SRC_TREE_NONUNIQUETREE_H_ */