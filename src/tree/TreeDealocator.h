/*
 * TreeDealocator.h
 *
 *  Created on: Sep 28, 2016
 *      Author: Lucian
 */

#ifndef SRC_TREE_TREEDEALOCATOR_H_
#define SRC_TREE_TREEDEALOCATOR_H_

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class TreeDeallocator {
public:
	TreeDeallocator(TreeNode<T,compare,hash>* root) {
		deleteRecursive(root);
		delete root;
	}
private:
	void deleteRecursive(TreeNode<T,compare,hash>* const& node) {
		HashSet<TreeNode<T,compare,hash>*, compareTreeNode<T,compare,hash>, hashTreeNode<T,compare,hash>>* children = node->getChildren();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			deleteRecursive(*(*it));
			delete (*(*it));
		}
	}
};



#endif /* SRC_TREE_TREEDEALOCATOR_H_ */
