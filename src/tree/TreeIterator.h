/*
 * TreeIterator.h
 *
 *  Created on: Sep 20, 2016
 *      Author: Lucian
 */

#ifndef TREEITERATOR_H_
#define TREEITERATOR_H_

#include "../container/Queue.h"

template<typename T>
class TreeNodeVisitor {
public:
	virtual ~TreeNodeVisitor(){};

	virtual void visit(TreeNode<T>*& element) = 0;
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



#endif /* TREEITERATOR_H_ */
