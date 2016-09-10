/*
 * TreeTest.h
 *
 *  Created on: Sep 10, 2016
 *      Author: aherne
 */

#ifndef SRC_UNIT_TESTS_TREEUNITTEST_H_
#define SRC_UNIT_TESTS_TREEUNITTEST_H_

#include "../tree/TreeNode.h"

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

class TreeUnitTest {
public:
	void execute() {
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
//		methodsTest();
		iteratorsTest();
	}
private:
	void methodsTest() {
		TreeNode<long>* root = new TreeNode<long>(1);
		TreeNode<long>* c1 = root->addChild(2);
		TreeNode<long>* c2 = root->addChild(3);
		TreeNode<long>* c3 = root->addChild(4);
		TreeNode<long>* c1_1 = c1->addChild(5);
		c1->addChild(6);
		TreeNode<long>* c1_1_1 = c1_1->addChild(7);
		c1_1->addChild(8);
		c2->addChild(9);
		TreeNode<long>* c3_1 = c3->addChild(10);
		TreeNode<long>* c1_1_1_1 = c1_1_1->addChild(11);
		std::cout << "getSize: " << (root->getSize()==11?"OK":"FAILED") << std::endl;
		std::cout << "getHeight: " << (root->getHeight()==5?"OK":"FAILED") << std::endl;
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

		c1_1_1->detach();
		delete c1_1_1;
		std::cout << "detach: " << (root->search(7, &comparator1).empty() && c1_1->getChildren()[1]->getData()==11?"OK":"FAILED") << std::endl;


		std::cout << "contains: " << (root->contains(11, &comparator1)?"OK":"FAILED") << std::endl;
		std::vector<TreeNode<long>*> search = root->search(10, &comparator1);
		std::cout << "search: " << (search.size()>0 && search[0]==c3_1?"OK":"FAILED") << std::endl;

		root->remove(3, &comparator1);
		std::cout << "remove: " << (root->search(3,&comparator1).empty() && root->getChildren()[2]->getData()==9?"OK":"FAILED") << std::endl;

		root->removeBranch(2, &comparator1);
		std::cout << "removeBranch: " << (root->search(2,&comparator1).empty() && root->search(8,&comparator1).empty() && root->getChildren().size()==2?"OK":"FAILED") << std::endl;

		delete root;
	}

	void iteratorsTest() {
		TreeNode<long>* root = new TreeNode<long>(1);
		TreeNode<long>* c1 = root->addChild(2);
		TreeNode<long>* c2 = root->addChild(3);
		TreeNode<long>* c3 = root->addChild(4);
		TreeNode<long>* c1_1 = c1->addChild(5);
		c1->addChild(6);
		TreeNode<long>* c1_1_1 = c1_1->addChild(7);
		c1_1->addChild(8);
		c2->addChild(9);
		c3->addChild(10);
		c1_1_1->addChild(11);

		PrintNodeVisitor<long> visitor;

		std::cout << "LEVEL ORDER TRAVERSAL" << std::endl;

		LevelOrderTreeIterator(root, &visitor);

		std::cout << "LEVEL ORDER TRAVERSAL WITH DEPTH" << std::endl;

		LevelOrderTreeIterator(root,1, &visitor);

		std::cout << "PRE ORDER TRAVERSAL" << std::endl;

		PreOrderTreeIterator(root, &visitor);

		std::cout << "POST ORDER TRAVERSAL" << std::endl;

		PostOrderTreeIterator(root, &visitor);


		delete root;
	}
};


#endif /* SRC_UNIT_TESTS_TREEUNITTEST_H_ */
