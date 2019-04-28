/*
 * UniqueTree.h
 *
 *  Created on: Sep 28, 2016
 *      Author: Lucian
 */

#ifndef SRC_TREE_UNIQUETREE_H_
#define SRC_TREE_UNIQUETREE_H_

#include "Tree.h"
#include "../set/HashSet.h"
#include "TreeUtilities.h"
#include "../Comparator.h"
#include "../Hashing.h"

// http://cdncontribute.geeksforgeeks.org/wp-content/uploads/order-of-constructor.png
template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class UniqueTree : public Tree<T> {
	public:
		using Tree<T>::Tree;

		UniqueTree(const T& data):Tree<T>(data) {
			nodes.add(this->root);
		}

		virtual ~UniqueTree() {
		}

		TreeNode<T>* search(const T& data) {
			TreeNode<T> temp(data);
			if(!nodes.contains(&temp)) return nullptr;
			return *(nodes.find(&temp));
		}

		// tested
		bool contains(const T& data) const {
			TreeNode<T> temp(data);
			return nodes.contains(&temp);
		}

		TreeNode<T>* createNode(const T& data, TreeNode<T>*& parent) {
			if(contains(data)) {
				throw std::logic_error("Node with that value already exists!");
			}
			TreeNode<T>* newNode = Tree<T>::createNode(data, parent);
			nodes.add(newNode);
			return newNode;
		}

		void removeNode(TreeNode<T>*& node) {
			if(node == this->root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");

			// empty parent & children
			nodes.remove(node);

			// deallocates branch
			Tree<T>::removeNode(node);
		}

		void removeBranch(TreeNode<T>*& node) {
			if(node == this->root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");

			// removes each descendant from nodes
			ArrayList<TreeNode<T>*>* children = node->getDescendants();
			for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
				nodes.remove(*(*it));
			}
			nodes.remove(node);
			delete children;

			// deallocates branch
			Tree<T>::removeBranch(node);
		}
	private:
		HashSet<TreeNode<T>*, compareTreeNode<T, compare>, hashTreeNode<T, hash>> nodes;
};



#endif /* SRC_TREE_UNIQUETREE_H_ */
