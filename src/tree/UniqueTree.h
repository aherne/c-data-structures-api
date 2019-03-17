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
#include "TreeUtilities.h"
// http://cdncontribute.geeksforgeeks.org/wp-content/uploads/order-of-constructor.png
template<typename T, int (*compare)(const T&, const T&), std::size_t (*hash)(const T&)>
class UniqueTree : public Tree<T> {
	public:
		using Tree<T>::Tree;

		UniqueTree(const T& data):Tree<T>(data) {
			hashTable = new HashTable<TreeNode<T>*>(compareTreeNode<T, compare>, hashTreeNode<T, hash>);
			hashTable->set(this->root);
		}

		virtual ~UniqueTree() {
			delete hashTable;
		}

		TreeNode<T>* search(const T& data) {
			TreeNode<T> temp(data);
			if(!hashTable->contains(&temp)) return nullptr;
			return *(hashTable->get(&temp));
		}

		// tested
		bool contains(const T& data) const {
			TreeNode<T> temp(data);
			return hashTable->contains(&temp);
		}

		TreeNode<T>* createNode(const T& data, TreeNode<T>*& parent) {
			if(contains(data)) {
				throw std::logic_error("Node with that value already exists!");
			}
			TreeNode<T>* newNode = Tree<T>::createNode(data, parent);
			hashTable->set(newNode);
			return newNode;
		}

		void removeNode(TreeNode<T>*& node) {
			if(node == this->root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");

			// empty parent & children
			hashTable->remove(node);

			// deallocates branch
			Tree<T>::removeNode(node);
		}

		void removeBranch(TreeNode<T>*& node) {
			if(node == this->root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");

			// removes each descendant from hashtable
			std::vector<TreeNode<T>*> children = node->getDescendants();
			for(auto it = children.begin(); it!=children.end(); ++it) {
				hashTable->remove(*it);
			}
			hashTable->remove(node);

			// deallocates branch
			Tree<T>::removeBranch(node);
		}
	private:
		HashTable<TreeNode<T>*>* hashTable;
};



#endif /* SRC_TREE_UNIQUETREE_H_ */
