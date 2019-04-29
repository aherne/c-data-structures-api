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

	virtual bool visit(TreeNode<T>* const& element) = 0;
};

template<typename T>
inline void PreOrderTreeIterator(TreeNode<T>* const& node, TreeNodeVisitor<T>* const& visitor) {
	if(!visitor->visit(node)) return;
	ArrayList<TreeNode<T>*>* children = node->getChildren();
	for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
		PreOrderTreeIterator(*(*it), visitor);
	}
}

template<typename T>
inline void PostOrderTreeIterator(TreeNode<T>* const& node, TreeNodeVisitor<T>* const& visitor) {
	ArrayList<TreeNode<T>*>* children = node->getChildren();
	for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
		PreOrderTreeIterator(*(*it), visitor);
	}
	if(!visitor->visit(node)) return;
}

template<typename T>
inline void LevelOrderTreeIterator(TreeNode<T>* const& root, TreeNodeVisitor<T>* const& visitor) {
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
inline void LevelOrderTreeIterator(TreeNode<T>* const& root, std::size_t depth, TreeNodeVisitor<T>* const& visitor) {
	Queue<TreeNode<T>*> q;
	q.push(root);
	while(!q.isEmpty()) {
		TreeNode<T>* node = q.pop();
		if(!visitor->visit(node)) return;
		ArrayList<TreeNode<T>*>* children = node->getChildren();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			if((*(*it))->getDepth() <= depth) {
				q.push(*(*it));
			}
		}
	}
}



#endif /* TREEITERATOR_H_ */
