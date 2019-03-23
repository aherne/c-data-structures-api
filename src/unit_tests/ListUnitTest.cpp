/*
 * ListUnitTest.cpp
 *
 *  Created on: Sep 11, 2016
 *      Author: aherne
 */

#include "ListUnitTest.h"
#include "../StringListGenerator.h"
#include "../list/ArrayList.h"
#include "../list/LinkedList.h"
#include "../list/DoublyLinkedList.h"
#include <forward_list>
#include <typeinfo>

void ListUnitTest::execute() {
	std::cout << "ArrayList<long>" << std::endl;
	ArrayList<long, comparator> all;
	testList(&all);

	std::cout << "LinkedList<long>" << std::endl;
	LinkedList<long, comparator> lll;
	testList(&lll);

	std::cout << "DoublyLinkedList<long>" << std::endl;
	DoublyLinkedList<long, comparator> dll;
	testList(&dll);

	std::cout << "ArrayList<char*>" << std::endl;
	ArrayList<char*, comparator> als;
	testList(&als);
	testArrayList();

	std::cout << "LinkedList<char*>" << std::endl;
	LinkedList<char*, comparator> lls;
	testList(&lls);
	testLinkedList();

	std::cout << "DoublyLinkedList<char*>" << std::endl;
	DoublyLinkedList<char*, comparator> dls;
	testList(&dls);
	testDoublyLinkedList();
}

void ListUnitTest::testList(List<long>* list) {
	for(long i=0; i<2000; ++i) {
		list->addToBottom(i);
	}

	long keyToCheck = 1820;
	std::cout << "\t" << "containsIndex: " << (list->containsIndex(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "containsValue: " << (list->containsValue(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "isEmpty: " << (!list->isEmpty()?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "size: " << (list->size()==2000?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "get: " << (list->get(keyToCheck)==keyToCheck?"OK":"ERROR") << std::endl;
	long newValue = 23434545;
	list->set(keyToCheck, newValue);
	std::cout << "\t" << "set & operator[]: " << ((*list)[keyToCheck]==newValue?"OK":"ERROR") << std::endl;
	list->removeIndex(keyToCheck);
	std::cout << "\t" << "removeIndex: " << (!list->containsValue(newValue)?"OK":"ERROR") << std::endl;
	long oldValue = list->get(keyToCheck);
	long newValue1 = 1234;
	list->emplace(keyToCheck, newValue1);
	std::cout << "\t" << "emplace: " << (list->get(keyToCheck)==newValue1?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "emplace: " << (list->get(keyToCheck+1)==oldValue?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "size: " << (list->size()==2000?"OK":"ERROR") << std::endl;

	long valueToCheck = 123;
	list->removeValue(valueToCheck);
	std::cout << "\t" << "removeValue: " << (!list->containsValue(valueToCheck)?"OK":"ERROR") << std::endl;

	list->clear();
	std::cout << "\t" << "clear: " << (list->size()==0?"OK":"ERROR") << std::endl;
}

void ListUnitTest::testList(List<char*>* list) {
	StringListGenerator slg(2000);
	std::vector<char*> items = slg.getList();
	for(auto it = items.begin(); it!=items.end(); ++it) {
		list->addToBottom(*it);
	}

	long keyToCheck = 1820;
	char* valueToCheck1 = strdup("1820");
	std::cout << "\t" << "containsIndex: " << (list->containsIndex(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "containsValue: " << (list->containsValue(valueToCheck1)?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "isEmpty: " << (!list->isEmpty()?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "size: " << (list->size()==2000?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "get: " << (strcmp(list->get(keyToCheck),valueToCheck1)==0?"OK":"ERROR") << std::endl;
	char* valueToCheck2 = strdup("23434545");
	list->set(keyToCheck, valueToCheck2);
	std::cout << "\t" << "set: " << (strcmp(list->get(keyToCheck),valueToCheck2)==0?"OK":"ERROR") << std::endl;
	list->removeIndex(keyToCheck);
	std::cout << "\t" << "removeIndex: " << (!list->containsValue(valueToCheck2)?"OK":"ERROR") << std::endl;
	char* oldValue = list->get(keyToCheck);
	list->emplace(keyToCheck, valueToCheck1);
	std::cout << "\t" << "emplace: " << (strcmp(list->get(keyToCheck),valueToCheck1)==0?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "emplace: " << (strcmp(list->get(keyToCheck+1),oldValue)==0?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "size: " << (list->size()==2000?"OK":"ERROR") << std::endl;

	char* valueToCheck3 = strdup("123");
	list->removeValue(valueToCheck3);
	std::cout << "\t" << "removeValue: " << (!list->containsValue(valueToCheck3)?"OK":"ERROR") << std::endl;

	list->clear();
	std::cout << "\t" << "clear: " << (list->size()==0?"OK":"ERROR") << std::endl;

	free(valueToCheck1);
	free(valueToCheck2);
	free(valueToCheck3);
}

void ListUnitTest::testArrayList() {
	long k;
	// test collisions

	ArrayList<long> ht;
	k=18;ht.addToTop(k);
	k=1;ht.addToTop(k);
	k=150;ht.addToTop(k);
	k=5;ht.addToTop(k);
	k=8;ht.addToTop(k);
	k=6;ht.addToTop(k);
	k=9;ht.addToTop(k);
	k=11;ht.addToTop(k);
	k=22;ht.addToTop(k);

	size_t index = 0;
	long newValue = 2;
	ht.emplace(index, newValue);

	ht.sort(&compareAsc<long>);

	std::cout << "\t" << "sort:" << std::endl;
	for(auto it = ht.begin(); *it!=*(ht.end()); ++(*it)) {
		std::cout << "\t" << "\t" << (*(*it)) << std::endl;
	}

	ht.clear();
}

void ListUnitTest::testLinkedList() {
	long k;
	// test collisions

	LinkedList<long> ht;
	k=18;ht.addToTop(k);
	k=1;ht.addToTop(k);
	k=150;ht.addToTop(k);
	k=5;ht.addToTop(k);
	k=8;ht.addToTop(k);
	k=6;ht.addToTop(k);
	k=9;ht.addToTop(k);
	k=11;ht.addToTop(k);
	k=22;ht.addToTop(k);

	size_t index = 6;
	long newValue = 2;
	ht.emplace(index, newValue);

	ht.sort(&compareAsc<long>);

	std::cout << "\t" << "sort:" << std::endl;
	size_t i=0;
	for(auto it = ht.begin(); *it!=*(ht.end()); ++(*it)) {
		std::cout << "\t" << "\t" << (*(*it)) << std::endl;
		if(i==2) ht.removeIndex(i);
		++i;
	}

	ht.clear();
}

void ListUnitTest::testDoublyLinkedList() {
	long k;
	// test collisions

	DoublyLinkedList<long> ht;
	k=18;ht.addToTop(k);
	k=1;ht.addToTop(k);
	k=150;ht.addToTop(k);
	k=5;ht.addToTop(k);
	k=8;ht.addToTop(k);
	k=6;ht.addToTop(k);
	k=9;ht.addToTop(k);
	k=11;ht.addToTop(k);
	k=22;ht.addToTop(k);

	size_t index = 9;
	long newValue = 2;
	ht.emplace(index, newValue);

	ht.sort(&compareAsc<long>);

	std::cout << "\t" << "\t" << "sort:" << std::endl;
	size_t i=0;
	for(auto it = ht.begin(); *it!=*(ht.end()); ++(*it)) {
		std::cout <<"\t" << (*(*it)) << std::endl;
		if(i==2) ht.removeIndex(i);
		++i;
	}

	ht.clear();
}

