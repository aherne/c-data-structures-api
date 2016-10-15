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
#include "../set/HashSet.h"

template<>
struct comparator<TreeNode<T>*> {
	int operator()(const TreeNode<T>*& left, const TreeNode<T>*& right) const {
		if(left<right) return -1;
		else if (left>right) return 1;
		else return 0;
	}
};

template<typename T>
int hashTreeNode(const TreeNode<T>*& node) {
	hash<T> temp;
	return temp(node->getData());
}

template<typename T>
class UniqueValueTree {
	public:
		UniqueValueTree(const T& data) {
			root = new TreeNode<T>(data);
		}

		~UniqueValueTree() {
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

		TreeNode<T>* createNode(const T& data, TreeNode<T>* parent) {
			TreeNode<T>* newNode = new TreeNode<T>(data);
			if(set.contains(newNode)) {
				delete newNode;
				throw std::logic_error("Node with that value already exists!");
			}
			set.add(newNode);
			parent->addChild(newNode);
			return newNode;
		}

		const TreeNode<T>*& search(const T& data) {
			TreeNode<T> temp(data);
			return set.get(&temp);
		}

		// tested
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
			set.remove(node);
			delete node;
		}

		// tested
		void removeBranch(TreeNode<T>* node) {
			if(node == root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");
			TreeNode<T>* parent = node->getParent();
			parent->removeChild(node);
			TreeDeallocator<T> deallocate(node);
		}

		// tested
		bool contains(const T& data) const {
			TreeNode<T> temp(data);
			return set.contains(&temp);
		}
	private:
		TreeNode<T>* root;
		HashSet<TreeNode<T>*> set;
};



#endif /* SRC_TREE_UNIQUETREE_H_ */
