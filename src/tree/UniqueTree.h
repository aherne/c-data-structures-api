/*
 * UniqueTree.h
 *
 *  Created on: Sep 28, 2016
 *      Author: Lucian
 */

#ifndef SRC_TREE_UNIQUETREE_H_
#define SRC_TREE_UNIQUETREE_H_

#include "Tree.h"
#include "../HashTable.h"
#include "../Comparator.h"
#include "../Hashing.h"

template<typename T>
int compareNode(TreeNode<T>* const& left, TreeNode<T>* const& right) {
	return comparator(left->getData(), right->getData());
}

template<typename T>
std::size_t hashNode(TreeNode<T>* const& node) {
	return hash(node->getData());
}

template<typename T>
class UniqueTree : public Tree<T> {
	public:
		using Tree<T>::Tree;

		TreeNode<T>* search(const T& data) {
			TreeNode<T> temp(data);
			if(!hashTable.contains(&temp)) return nullptr;
			return *(hashTable.get(&temp));
		}

		// tested
		bool contains(const T& data) const {
			TreeNode<T> temp(data);
			return hashTable.contains(&temp);
		}

		TreeNode<T>* createNode(const T& data, TreeNode<T>* parent) {
			if(contains(data)) {
				throw std::logic_error("Node with that value already exists!");
			}
			TreeNode<T>* newNode = Tree<T>::createNode(data, parent);
			hashTable.set(newNode);
			return newNode;
		}

		void removeNode(TreeNode<T>* node) {
			if(node == this->root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");

			// empty parent & children
			hashTable.remove(node);

			// deallocates branch
			Tree<T>::removeNode(node);
		}

		void removeBranch(TreeNode<T>* node) {
			if(node == this->root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");

			// removes each descendant from hashtable
			std::vector<TreeNode<T>*> children = node->getDescendants();
			for(auto it = children.begin(); it!=children.end(); ++it) {
				hashTable.remove(*it);
			}
			hashTable.remove(node);

			// deallocates branch
			Tree<T>::removeBranch(node);
		}
	private:
		HashTable<TreeNode<T>*, compareNode, hashNode> hashTable;
};



#endif /* SRC_TREE_UNIQUETREE_H_ */
