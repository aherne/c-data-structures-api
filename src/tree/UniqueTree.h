/*
 * UniqueTree.h
 *
 *  Created on: Sep 28, 2016
 *      Author: Lucian
 */

#ifndef SRC_TREE_UNIQUETREE_H_
#define SRC_TREE_UNIQUETREE_H_

#include "TreeNode.h"
#include "TreeDealocator.h"
#include "TreeIterator.h"
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
class UniqueTree {
	public:
		UniqueTree(const T& data) {
			root = new TreeNode<T>(data);
		}

		~UniqueTree() {
			TreeDeallocator<T> deallocate(root);
		}

		TreeNode<T>* getRoot() {
			return root;
		}

		std::size_t getSize() {
			return root->getSize();
		}

		std::size_t getHeight() {
			return root->getHeight();
		}

		TreeNode<T>* search(const T& data) {
			TreeNode<T> temp(data);
			if(!hashTable.contains(&temp)) return nullptr;
			return *(hashTable.get(&temp));
		}

		TreeNode<T>* createNode(const T& data, TreeNode<T>* parent) {
			TreeNode<T>* newNode = new TreeNode<T>(data);
			if(hashTable.contains(newNode)) {
				delete newNode;
				throw std::logic_error("Node with that value already exists!");
			}
			hashTable.set(newNode);
			parent->addChild(newNode);
			return newNode;
		}

		void removeNode(TreeNode<T>* node) {
			if(node == root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");

			// gets node's parent
			TreeNode<T>* parent = node->getParent();

			// removes node as child of parent
			parent->removeChild(node);

			// migrate my children to parent
			std::vector<TreeNode<T>*> children = node->getChildren();
			for(auto it = children.begin(); it!=children.end(); ++it) {
				parent->addChild(*it);
			}

			// empty parent & children
			hashTable.remove(node);
			delete node;
		}

		void removeBranch(TreeNode<T>* node) {
			if(node == root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");

			// gets node's parent
			TreeNode<T>* parent = node->getParent();

			// removes node as child of parent
			parent->removeChild(node);

			// removes each descendant from hashtable
			std::vector<TreeNode<T>*> children = node->getDescendants();
			for(auto it = children.begin(); it!=children.end(); ++it) {
				hashTable.remove(*it);
			}
			hashTable.remove(node);

			TreeDeallocator<T> deallocate(node);
		}

		// tested
		bool contains(const T& data) const {
			TreeNode<T> temp(data);
			return hashTable.contains(&temp);
		}
	private:
		TreeNode<T>* root;
		HashTable<TreeNode<T>*, compareNode, hashNode> hashTable;
};



#endif /* SRC_TREE_UNIQUETREE_H_ */
