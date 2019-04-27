/*
 * TreeDealocator.h
 *
 *  Created on: Sep 28, 2016
 *      Author: Lucian
 */

#ifndef SRC_TREE_TREEDEALOCATOR_H_
#define SRC_TREE_TREEDEALOCATOR_H_


template<typename T>
class TreeDeallocator {
public:
	TreeDeallocator(TreeNode<T>* root) {
		deleteRecursive(root);
		delete root;
	}
private:
	void deleteRecursive(TreeNode<T>* const& node) {
		ArrayList<TreeNode<T>*>* children = node->getChildren();
		for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
			deleteRecursive(*(*it));
			delete (*(*it));
		}
	}
};



#endif /* SRC_TREE_TREEDEALOCATOR_H_ */
