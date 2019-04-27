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

	virtual bool visit(TreeNode<T>*& element) = 0;
};

template<typename T>
inline void PreOrderTreeIterator(TreeNode<T>* node, TreeNodeVisitor<T>* visitor) {
	if(!visitor->visit(node)) return;
	ArrayList<TreeNode<T>*>* children = node->getChildren();
	for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
		PreOrderTreeIterator(*(*it), visitor);
	}
}

template<typename T>
inline void PostOrderTreeIterator(TreeNode<T>* node, TreeNodeVisitor<T>* visitor) {
	ArrayList<TreeNode<T>*>* children = node->getChildren();
	for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
		PreOrderTreeIterator(*(*it), visitor);
	}
	if(!visitor->visit(node)) return;
}

template<typename T>
inline void LevelOrderTreeIterator(TreeNode<T>* root, TreeNodeVisitor<T>* visitor) {
	Queue<TreeNode<T>*> q;
	q.push(root);
	while(!q.isEmpty()) {
		TreeNode<T>* node = q.pop();
		if(!visitor->visit(node)) return;
		ArrayList<TreeNode<T>*>* children = node->getChildren();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			q.push(*(*it));
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
		ArrayList<TreeNode<T>*>* children = node->getChildren();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			if((*(*it))->getDepth() <= depth) {
				q.push(*(*it));
			}
		}
	}
}



#endif /* TREEITERATOR_H_ */
