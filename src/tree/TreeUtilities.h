/*
 * TreeUtilities.h
 *
 *  Created on: Mar 10, 2019
 *      Author: aherne
 */

#ifndef SRC_TREE_TREEUTILITIES_H_
#define SRC_TREE_TREEUTILITIES_H_

template<typename T, int (*comparator)(const T&, const T&)>
static inline int compareTreeNode(TreeNode<T>* const& left, TreeNode<T>* const& right) {
	return comparator(left->getData(), right->getData());
}

template<typename T, std::size_t (*hash)(const T&)>
static inline std::size_t hashTreeNode(TreeNode<T>* const& node) {
	return hash(node->getData());
}

#endif /* SRC_TREE_TREEUTILITIES_H_ */
