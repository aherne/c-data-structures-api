/*
 * TreeUnitTest.cpp
 *
 *  Created on: Sep 11, 2016
 *      Author: aherne
 */

#include "TreeUnitTest.h"
#include "../tree/NonUniqueTree.h"
#include "../tree/UniqueTree.h"

int comparator1(const long& left, const long& right) {
	return left-right;
}

template<typename T>
class PrintNodeVisitor: public TreeNodeVisitor<T> {
public:
	virtual ~PrintNodeVisitor(){};

	void visit(TreeNode<T>*& element) {
		std::cout << element->getData() << std::endl;
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
//	std::cout << "=====NonUniqueTree<long>=====" << std::endl;
//	treeTest();
	std::cout << "=====UniqueTree<long>=====" << std::endl;
	uniqueTreeTest();
//	std::cout << "=====[ITERATORS]=====" << std::endl;
//	iteratorsTest();
}

void TreeUnitTest::treeTest() {
	NonUniqueTree<long>* tree = new NonUniqueTree<long>(1);
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
	std::cout << "getSize: " << (tree->getSize()==11?"OK":"FAILED") << std::endl;
	std::cout << "getHeight: " << (tree->getHeight()==5?"OK":"FAILED") << std::endl;
	std::cout << "getDepth: " << (c1_1_1_1->getDepth()==4?"OK":"FAILED") << std::endl;
	std::cout << "isDescendantOf: " << (c1_1_1_1->isDescendantOf(root)==true?"OK":"FAILED") << std::endl;
	std::cout << "isAncestorOf: " << (root->isAncestorOf(c1_1_1_1)==true?"OK":"FAILED") << std::endl;
	std::cout << "getRoot: " << (c1_1_1_1->getRoot()==root?"OK":"FAILED") << std::endl;

	std::vector<TreeNode<long>*> ancestors = c1_1_1_1->getAncestors();
	bool success = true;
	if(ancestors[0] != c1_1_1) success = false;
	if(ancestors[1] != c1_1) success = false;
	if(ancestors[2] != c1) success = false;
	if(ancestors[3] != root) success = false;
	std::cout << "getAncestors: " << (success?"OK":"FAILED") << std::endl;

	c1_1_1_1->setParent(c1);
	std::cout << "getParent: " << (c1_1_1_1->getParent()==c1?"OK":"FAILED") << std::endl;
	c1_1_1_1->setParent(c1_1_1);

	c1_1_1_1->setData(17);
	std::cout << "getData: " << (c1_1_1_1->getData()==17?"OK":"FAILED") << std::endl;
	c1_1_1_1->setData(11);

	std::vector<TreeNode<long>*> children = root->getChildren();
	std::cout << "getChildren: " << (children[0]==c1 && children[1]==c2 && children[2]==c3?"OK":"FAILED") << std::endl;

	TreeNode<long>* test = new TreeNode<long>(12);
	c3->addChild(test);
	std::vector<TreeNode<long>*> children1 = c3->getChildren();
	std::cout << "addChild: " << (children1[1]==test?"OK":"FAILED") << std::endl;

	c3->removeChild(test);
	delete test;
	children1 = c3->getChildren();
	std::cout << "removeChild: " << (children1.size()==1?"OK":"FAILED") << std::endl;

	std::cout << "descendants: " << std::endl;
	std::vector<TreeNode<long>*> descendants = root->getDescendants();
	for(auto it=descendants.begin(); it!=descendants.end(); ++it) {
		std::cout << (*it)->getData() << std::endl;
	}

	std::cout << "contains: " << (tree->contains(11, &comparator1)?"OK":"FAILED") << std::endl;
	std::vector<TreeNode<long>*> search = tree->search(10, &comparator1);
	std::cout << "search: " << (search.size()>0 && search[0]==c3_1?"OK":"FAILED") << std::endl;

	tree->removeNode(c2);
	std::cout << "removeNode: " << (tree->search(3,&comparator1).empty() && root->getChildren()[2]->getData()==9?"OK":"FAILED") << std::endl;

	tree->removeBranch(c1);
	std::cout << "removeBranch: " << (tree->search(2,&comparator1).empty() && tree->search(8,&comparator1).empty() && root->getChildren().size()==2?"OK":"FAILED") << std::endl;

	delete tree;
}

void TreeUnitTest::uniqueTreeTest() {
	UniqueTree<long>* tree = new UniqueTree<long>(1);
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
	std::cout << "getSize: " << (tree->getSize()==11?"OK":"FAILED") << std::endl;
	std::cout << "getHeight: " << (tree->getHeight()==5?"OK":"FAILED") << std::endl;
	std::cout << "getDepth: " << (c1_1_1_1->getDepth()==4?"OK":"FAILED") << std::endl;
	std::cout << "isDescendantOf: " << (c1_1_1_1->isDescendantOf(root)==true?"OK":"FAILED") << std::endl;
	std::cout << "isAncestorOf: " << (root->isAncestorOf(c1_1_1_1)==true?"OK":"FAILED") << std::endl;
	std::cout << "getRoot: " << (c1_1_1_1->getRoot()==root?"OK":"FAILED") << std::endl;

	std::vector<TreeNode<long>*> ancestors = c1_1_1_1->getAncestors();
	bool success = true;
	if(ancestors[0] != c1_1_1) success = false;
	if(ancestors[1] != c1_1) success = false;
	if(ancestors[2] != c1) success = false;
	if(ancestors[3] != root) success = false;
	std::cout << "getAncestors: " << (success?"OK":"FAILED") << std::endl;

	c1_1_1_1->setParent(c1);
	std::cout << "getParent: " << (c1_1_1_1->getParent()==c1?"OK":"FAILED") << std::endl;
	c1_1_1_1->setParent(c1_1_1);

	c1_1_1_1->setData(17);
	std::cout << "getData: " << (c1_1_1_1->getData()==17?"OK":"FAILED") << std::endl;
	c1_1_1_1->setData(11);

	std::vector<TreeNode<long>*> children = root->getChildren();
	std::cout << "getChildren: " << (children[0]==c1 && children[1]==c2 && children[2]==c3?"OK":"FAILED") << std::endl;

	TreeNode<long>* test = new TreeNode<long>(12);
	c3->addChild(test);
	std::vector<TreeNode<long>*> children1 = c3->getChildren();
	std::cout << "addChild: " << (children1[1]==test?"OK":"FAILED") << std::endl;

	c3->removeChild(test);
	delete test;
	children1 = c3->getChildren();
	std::cout << "removeChild: " << (children1.size()==1?"OK":"FAILED") << std::endl;

	std::cout << "descendants: " << std::endl;
	std::vector<TreeNode<long>*> descendants = root->getDescendants();
	for(auto it=descendants.begin(); it!=descendants.end(); ++it) {
		std::cout << (*it)->getData() << std::endl;
	}

	std::cout << "contains: " << (tree->contains(11)?"OK":"FAILED") << std::endl;
	const TreeNode<long>* search = tree->search(10);
	std::cout << "search: " << (search!=nullptr && search==c3_1?"OK":"FAILED") << std::endl;

	tree->removeNode(c2);
	std::cout << "removeNode: " << (tree->search(3)==nullptr && root->getChildren()[2]->getData()==9?"OK":"FAILED") << std::endl;

	tree->removeBranch(c1);
	std::cout << "removeBranch: " << (tree->search(2)==nullptr && tree->search(8)==nullptr && root->getChildren().size()==2?"OK":"FAILED") << std::endl;

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
