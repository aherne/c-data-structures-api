/*
 * TreeIterator.h
 *
 *  Created on: Sep 20, 2016
 *      Author: Lucian
 */

#ifndef TREEITERATOR_H_
#define TREEITERATOR_H_

#include "../container/Queue.h"

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class TreeNodeVisitor {
public:
	virtual ~TreeNodeVisitor(){};

	virtual bool visit(TreeNode<T,compare,hash>* const& element) = 0;
};

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline void PreOrderTreeIterator(TreeNode<T,compare,hash>* const& node, TreeNodeVisitor<T,compare,hash>* const& visitor) {
	if(!visitor->visit(node)) return;
	HashSet<TreeNode<T,compare,hash>*, compareTreeNode<T,compare,hash>, hashTreeNode<T,compare,hash>>* children = node->getChildren();
	for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
		PreOrderTreeIterator(*(*it), visitor);
	}
}

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline void PostOrderTreeIterator(TreeNode<T,compare,hash>* const& node, TreeNodeVisitor<T,compare,hash>* const& visitor) {
	HashSet<TreeNode<T,compare,hash>*, compareTreeNode<T,compare,hash>, hashTreeNode<T,compare,hash>>* children = node->getChildren();
	for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
		PreOrderTreeIterator(*(*it), visitor);
	}
	if(!visitor->visit(node)) return;
}

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline void LevelOrderTreeIterator(TreeNode<T,compare,hash>* const& root, TreeNodeVisitor<T,compare,hash>* const& visitor) {
	Queue<TreeNode<T,compare,hash>*> q;
	q.push(root);
	while(!q.isEmpty()) {
		TreeNode<T,compare,hash>* node = q.pop();
		if(!visitor->visit(node)) return;
		HashSet<TreeNode<T,compare,hash>*, compareTreeNode<T,compare,hash>, hashTreeNode<T,compare,hash>>* children = node->getChildren();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			q.push(*(*it));
		}
	}
}

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
inline void LevelOrderTreeIterator(TreeNode<T,compare,hash>* const& root, std::size_t depth, TreeNodeVisitor<T,compare,hash>* const& visitor) {
	Queue<TreeNode<T,compare,hash>*> q;
	q.push(root);
	while(!q.isEmpty()) {
		TreeNode<T,compare,hash>* node = q.pop();
		if(!visitor->visit(node)) return;
		HashSet<TreeNode<T,compare,hash>*, compareTreeNode<T,compare,hash>, hashTreeNode<T,compare,hash>>* children = node->getChildren();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			if((*(*it))->getDepth() <= depth) {
				q.push(*(*it));
			}
		}
	}
}



#endif /* TREEITERATOR_H_ */
