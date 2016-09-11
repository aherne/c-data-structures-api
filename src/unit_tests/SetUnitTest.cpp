/*
 * SetUnitTest.cpp
 *
 *  Created on: Sep 11, 2016
 *      Author: aherne
 */

#include "SetUnitTest.h"


#include "../StringListGenerator.h"
#include "../set/LinkedHashSet.h"
#include "../set/HashSet.h"
#include "../set/TreeSet.h"

void SetUnitTest::execute() {
	std::cout << "=====LinkedHashSet<long>=====" << std::endl;
	LinkedHashSet<long> lhml;
	test(&lhml);
	testLinkedHashSet();

	std::cout << "=====HashSet<long>=====" << std::endl;
	HashSet<long> hml;
	test(&hml);
	testHashSet();

	std::cout << "=====TreeSet<long>=====" << std::endl;
	TreeSet<long> tml;
	test(&tml);
	testTreeSet();

	std::cout << "=====LinkedHashSet<char*>=====" << std::endl;
	LinkedHashSet<char*> lhms;
	test(&lhms);

	std::cout << "=====HashSet<char*>=====" << std::endl;
	HashSet<char*> hms;
	test(&hms);

	std::cout << "=====TreeSet<char*>=====" << std::endl;
	TreeSet<char*> tms;
	test(&tms);
}

void SetUnitTest::test(Set<long>* ht) {
	for(long i=0; i<2000; ++i) {
		ht->add(i);
	}

	long keyToCheck = 1820;
	std::cout << "containsValue: " << (ht->contains(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "isEmpty: " << (!ht->isEmpty()?"OK":"ERROR") << std::endl;
	std::cout << "size: " << (ht->size()==2000?"OK":"ERROR") << std::endl;
	ht->remove(keyToCheck);
	std::cout << "removeKey: " << (!ht->contains(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "size: " << (ht->size()==1999?"OK":"ERROR") << std::endl;
	ht->clear();
	std::cout << "clear: " << (ht->size()==0?"OK":"ERROR") << std::endl;
}

void SetUnitTest::test(Set<char*>* ht) {
	StringListGenerator slg(2000);
	std::vector<char*> items = slg.getList();
	for(auto it = items.begin(); it!=items.end(); ++it) {
		ht->add(*it);
	}

	char* keyToCheck = strdup("1820");
	std::cout << "containsKey: " << (ht->contains(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "isEmpty: " << (!ht->isEmpty()?"OK":"ERROR") << std::endl;
	std::cout << "size: " << (ht->size()==2000?"OK":"ERROR") << std::endl;
	ht->remove(keyToCheck);
	std::cout << "removeKey: " << (!ht->contains(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "size: " << (ht->size()==1999?"OK":"ERROR") << std::endl;
	ht->clear();
	std::cout << "clear: " << (ht->size()==0?"OK":"ERROR") << std::endl;


	// deallocate pointers
	free(keyToCheck);
}



void SetUnitTest::testLinkedHashSet() {
	long k;
	// test collisions

	LinkedHashSet<long> ht;
	k=18;ht.add(k);
	k=1;ht.add(k);
	k=150;ht.add(k);
	k=5;ht.add(k);
	k=8;ht.add(k);
	k=6;ht.add(k);
	k=9;ht.add(k);
	k=11;ht.add(k);
	k=22;ht.add(k);

	ht.sort(&compareAsc<long>);

	std::cout << "sort:" << std::endl;
	for(auto it = ht.begin(); *it!=*(ht.end()); ++(*it)) {
		std::cout <<"\t" << (*(*it)) << std::endl;
	}

	ht.clear();
}

void SetUnitTest::testHashSet() {
	long k;
	// test collisions

	HashSet<long> ht;
	k=18;ht.add(k);
	k=1;ht.add(k);
	k=150;ht.add(k);
	k=5;ht.add(k);
	k=8;ht.add(k);
	k=6;ht.add(k);
	k=9;ht.add(k);
	k=11;ht.add(k);
	k=22;ht.add(k);

	std::cout << "iterator:" << std::endl;
	for(auto it = ht.begin(); *it!=*(ht.end()); ++(*it)) {
		std::cout <<"\t" << (*(*it)) << std::endl;
	}

	ht.clear();
}

void SetUnitTest::testTreeSet() {
	long k;
	// test collisions

	TreeSet<long> ht;
	k=18;ht.add(k);
	k=1;ht.add(k);
	k=150;ht.add(k);
	k=5;ht.add(k);
	k=8;ht.add(k);
	k=6;ht.add(k);
	k=9;ht.add(k);
	k=11;ht.add(k);
	k=22;ht.add(k);

	std::cout << "iterator:" << std::endl;
	for(auto it = ht.begin(); *it!=*(ht.end()); ++(*it)) {
		std::cout <<"\t" << (*(*it)) << std::endl;
	}

	ht.clear();
}
