/*
 * Tree.h
 *
 *  Created on: Sep 19, 2016
 *      Author: Lucian
 */

#ifndef TREE_H_
#define TREE_H_

#include "TreeNode.h"
#include "TreeDealocator.h"

template<typename T>
class Tree {
	public:
		explicit Tree(const T& data) {
			root = new TreeNode<T>(data);
		}

		virtual ~Tree() {
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

		virtual TreeNode<T>* createNode(const T& data, TreeNode<T>*& parent) {
			TreeNode<T>* newNode = new TreeNode<T>(data);
			parent->addChild(newNode);
			return newNode;
		}

		virtual void removeNode(TreeNode<T>*& node) {
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
			delete node;
		}

		virtual void removeBranch(TreeNode<T>*& node) {
			if(node == root) throw std::logic_error("Root cannot be removed without deallocating the whole tree!");

			// gets node's parent
			TreeNode<T>* parent = node->getParent();

			// removes node as child of parent
			parent->removeChild(node);

			// deallocates node
			TreeDeallocator<T> deallocate(node);
		}
	protected:
		TreeNode<T>* root;
};



#endif /* TREE_H_ */
