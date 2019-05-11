/*
 * TreeUnitTest.cpp
 *
 *  Created on: Sep 11, 2016
 *      Author: aherne
 */

#include "TreeUnitTest.h"
#include "../tree/HashTree.h"
#include "../tree/TreeIterator.h"

template<typename T, int (*compare)(const T&, const T&) = comparator<T>, std::size_t (*hash)(const T&) = hash<T>>
class PrintNodeVisitor: public TreeNodeVisitor<T,compare,hash> {
public:
	virtual ~PrintNodeVisitor(){};

	bool visit(TreeNode<T,compare,hash>* const& element) {
		std::cout << "\t" << element->getData() << std::endl;
		return true;
	}
};

void TreeUnitTest::execute() {
	/**
	 * 		 1
	 * 		/ | \
	 * 		2 3	4
	 * 	   / \ \ \
	 * 	   5 6 9 10
	 * 	  / \
	 * 	  7 8
	 * 	  |
	 * 	  11
	 */
	std::cout << "HashTree<long>" << std::endl;
	treeTest();
	std::cout << "[ITERATORS]" << std::endl;
	iteratorsTest();
}

void TreeUnitTest::treeTest() {
	HashTree<long>* tree = new HashTree<long>(1);
	TreeNode<long>* root = tree->getRoot();
	TreeNode<long>* c1 = tree->createNode(2, root);
	TreeNode<long>* c2 = tree->createNode(3, root);
	TreeNode<long>* c3 = tree->createNode(4, root);
	TreeNode<long>* c1_1 = tree->createNode(5, c1);
	tree->createNode(6, c1);
	TreeNode<long>* c1_1_1 = tree->createNode(7, c1_1);
	tree->createNode(8, c1_1);
	tree->createNode(9, c2);
	TreeNode<long>* c3_1 = tree->createNode(10, c3);
	TreeNode<long>* c1_1_1_1 = tree->createNode(11, c1_1_1);
	std::cout << "\t" << "getSize: " << (tree->getSize()==11?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "getHeight: " << (tree->getHeight()==5?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "getDepth: " << (c1_1_1_1->getDepth()==4?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "isDescendantOf: " << (c1_1_1_1->isDescendantOf(root)==true?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "isAncestorOf: " << (root->isAncestorOf(c1_1_1_1)==true?"OK":"FAILED") << std::endl;
	std::cout << "\t" << "getRoot: " << (c1_1_1_1->getRoot()==root?"OK":"FAILED") << std::endl;

	std::cout << "\t" << "getAncestors: " << std::endl;
	List<TreeNode<long>*>* ancestors = c1_1_1_1->getAncestors();
	for(auto it = ancestors->begin(); *it!=*(ancestors->end()); ++(*it)) {
		std::cout << "\t" << "\t" << (*(*it))->getData() << std::endl;
	}
	delete ancestors;

	c1_1_1_1->setParent(c1);
	std::cout << "\t" << "getParent: " << (c1_1_1_1->getParent()==c1?"OK":"FAILED") << std::endl;
	c1_1_1_1->setParent(c1_1_1);

	c1_1_1_1->setData(17);
	std::cout << "\t" << "getData: " << (c1_1_1_1->getData()==17?"OK":"FAILED") << std::endl;
	c1_1_1_1->setData(11);

	Set<TreeNode<long>*>* children = root->getChildren();
	std::cout << "\t" << "getChildren: " << (children->size()==3?"OK":"FAILED") << std::endl;

	TreeNode<long>* test = new TreeNode<long>(12);
	c3->addChild(test);
	std::cout << "\t" << "addChild: " << (c3->getChildren()->size()==2?"OK":"FAILED") << std::endl;

	std::cout << "\t" << "hasChild: " << (c3->hasChild(test)?"OK":"FAILED") << std::endl;

	c3->removeChild(test);
	delete test;
	std::cout << "\t" << "removeChild: " << (c3->getChildren()->size()==1?"OK":"FAILED") << std::endl;

	std::cout << "\t" << "getDescendants: " << std::endl;
	List<TreeNode<long>*>* descendants = root->getDescendants();
	for(auto it = descendants->begin(); *it!=*(descendants->end()); ++(*it)) {
		std::cout << "\t" << "\t" << (*(*it))->getData() << std::endl;
	}
	delete descendants;

	std::cout << "\t" << "contains: " << (tree->contains(11)?"OK":"FAILED") << std::endl;
	const TreeNode<long>* search = tree->search(10);
	std::cout << "\t" << "search: " << (search!=nullptr && search==c3_1?"OK":"FAILED") << std::endl;

	tree->removeNode(c2);
	std::cout << "\t" << "removeNode: " << (root->getChildren()->size()==3?"OK":"FAILED") << std::endl;

	tree->removeBranch(c1);
	std::cout << "\t" << "removeBranch: " << (root->getChildren()->size()==2?"OK":"FAILED") << std::endl;

	delete tree;
}

void TreeUnitTest::iteratorsTest() {
	TreeNode<long>* root = new TreeNode<long>(1);

	TreeNode<long>* c1 = new TreeNode<long>(2);
	root->addChild(c1);

	TreeNode<long>* c2 = new TreeNode<long>(3);
	root->addChild(c2);

	TreeNode<long>* c3 = new TreeNode<long>(4);
	root->addChild(c3);

	TreeNode<long>* c1_1 = new TreeNode<long>(5);
	c1->addChild(c1_1);

	TreeNode<long>* c1_2 = new TreeNode<long>(6);
	c1->addChild(c1_2);

	TreeNode<long>* c1_1_1 = new TreeNode<long>(7);
	c1_1->addChild(c1_1_1);

	TreeNode<long>* c1_1_2 = new TreeNode<long>(8);
	c1_1->addChild(c1_1_2);

	TreeNode<long>* c2_1 = new TreeNode<long>(9);
	c2->addChild(c2_1);

	TreeNode<long>* c3_1 = new TreeNode<long>(10);
	c3->addChild(c3_1);


	TreeNode<long>* c3_2 = new TreeNode<long>(11);
	c1_1_1->addChild(c3_2);

	PrintNodeVisitor<long> visitor;

	std::cout << "LEVEL ORDER TRAVERSAL" << std::endl;

	LevelOrderTreeIterator(root, &visitor);

	std::cout << "LEVEL ORDER TRAVERSAL WITH DEPTH" << std::endl;

	LevelOrderTreeIterator(root,1, &visitor);

	std::cout << "PRE ORDER TRAVERSAL" << std::endl;

	PreOrderTreeIterator(root, &visitor);

	std::cout << "POST ORDER TRAVERSAL" << std::endl;

	PostOrderTreeIterator(root, &visitor);

	TreeDeallocator<long> deallocate(root);
}
