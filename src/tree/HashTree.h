/*
 * HashTree.h
 *
 *  Created on: Sep 28, 2016
 *      Author: Lucian
 */

#ifndef SRC_TREE_HASHTREE_H_
#define SRC_TREE_HASHTREE_H_

#include "Tree.h"
#include "TreeNode.h"
#include "TreeDealocator.h"
#include "../set/HashSet.h"
#include "TreeUtilities.h"
#include "../Comparator.h"
#include "../Hashing.h"

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class HashTree : public Tree<TreeNode<T>> {
protected:
	public:
		HashTree(const T& data) {
			root = new TreeNode<T>(data);
			nodes.add(root);
		}

		~HashTree() {
			TreeDeallocator<T> deallocate(root);
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

		TreeNode<T>* createNode(const T& data, TreeNode<T>* const& parent) {
			if(contains(data)) {
				throw std::logic_error("Node with that value already exists!");
			}
			TreeNode<T>* newNode = new TreeNode<T>(data);
			parent->addChild(newNode);
			nodes.add(newNode);
			return newNode;
		}

		TreeNode<T>* getRoot() {
			return root;
		}

		const std::size_t& getSize() const {
			return nodes.size();
		}

		std::size_t getHeight() {
			return root->getHeight();
		}

		void removeNode(TreeNode<T>* const& node) {
			if(node == root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");

			// empty parent & children
			nodes.remove(node);

			// deallocates branch
			TreeNode<T>* parent = node->getParent();

			// removes node as child of parent
			parent->removeChild(node);

			// migrate my children to parent
			ArrayList<TreeNode<T>*>* children = node->getChildren();
			for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
				parent->addChild(*(*it));
			}

			// empty parent & children
			delete node;
		}

		void removeBranch(TreeNode<T>* const& node) {
			if(node == root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");

			// removes each descendant from nodes
			ArrayList<TreeNode<T>*>* children = node->getDescendants();
			for(auto it = children->begin(); *it!=*(children->end()); ++(*it)) {
				nodes.remove(*(*it));
			}
			nodes.remove(node);
			delete children;

			// gets node's parent
			TreeNode<T>* parent = node->getParent();

			// removes node as child of parent
			parent->removeChild(node);

			// deallocates node
			TreeDeallocator<T> deallocate(node);
		}
	private:
		TreeNode<T>* root;
		HashSet<TreeNode<T>*, compareTreeNode<T, compare>, hashTreeNode<T, hash>> nodes;
};



#endif /* SRC_TREE_HASHTREE_H_ */
