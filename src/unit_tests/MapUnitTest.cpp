/*
 * MapUnitTest.cpp
 *
 *  Created on: Sep 11, 2016
 *      Author: aherne
 */

#include "MapUnitTest.h"
#include "../StringListGenerator.h"
#include "../map/LinkedHashMap.h"
#include "../map/HashMap.h"
#include "../map/TreeMap.h"
#include "../list/ArrayList.h"

void MapUnitTest::execute() {
	std::cout << "=====LinkedHashMap<long,long>=====" << std::endl;
	LinkedHashMap<long, long> lhml;
	test(&lhml);

	std::cout << "=====HashMap<long,long>=====" << std::endl;
	HashMap<long, long> hml;
	test(&hml);

	std::cout << "=====TreeMap<long,long>=====" << std::endl;
	TreeMap<long, long> tml;
	test(&tml);

	std::cout << "=====LinkedHashMap<char*,char*>=====" << std::endl;
	LinkedHashMap<char*, char*> lhms;
	test(&lhms);

	std::cout << "=====HashMap<char*,char*>=====" << std::endl;
	HashMap<char*, char*> hms;
	test(&hms);

	std::cout << "=====TreeMap<char*,char*>=====" << std::endl;
	TreeMap<char*, char*> tms;
	test(&tms);

	testLinkedHashMap();
	testHashMap();
	testTreeMap();
}

void MapUnitTest::test(Map<long, long>* ht) {
	for(long i=0; i<2000; ++i) {
		ht->set(i,i);
	}

	long keyToCheck = 1820;
	std::cout << "containsKey: " << (ht->containsKey(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "containsValue: " << (ht->containsValue(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "isEmpty: " << (!ht->isEmpty()?"OK":"ERROR") << std::endl;
	std::cout << "size: " << (ht->size()==2000?"OK":"ERROR") << std::endl;
	std::cout << "get&set: " << (ht->get(keyToCheck)==keyToCheck?"OK":"ERROR") << std::endl;
	ht->removeKey(keyToCheck);
	std::cout << "removeKey: " << (!ht->containsKey(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "size: " << (ht->size()==1999?"OK":"ERROR") << std::endl;

	long valueToCheck = 123;
	ht->removeValue(valueToCheck);
	std::cout << "removeValue: " << (!ht->containsValue(valueToCheck)?"OK":"ERROR") << std::endl;

	ht->clear();
	std::cout << "clear: " << (ht->size()==0?"OK":"ERROR") << std::endl;
}

void MapUnitTest::test(Map<char*, char*>* ht) {
	StringListGenerator slg(2000);
	std::vector<char*> items = slg.getList();
	for(auto it = items.begin(); it!=items.end(); ++it) {
		ht->set(*it, *it);
	}

	char* keyToCheck = strdup("1820");
	std::cout << "containsKey: " << (ht->containsKey(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "containsValue: " << (ht->containsValue(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "isEmpty: " << (!ht->isEmpty()?"OK":"ERROR") << std::endl;
	std::cout << "size: " << (ht->size()==2000?"OK":"ERROR") << std::endl;
	std::cout << "get&set: " << (strcmp(ht->get(keyToCheck),keyToCheck)==0?"OK":"ERROR") << std::endl;
	ht->removeKey(keyToCheck);
	std::cout << "removeKey: " << (!ht->containsKey(keyToCheck)?"OK":"ERROR") << std::endl;
	std::cout << "size: " << (ht->size()==1999?"OK":"ERROR") << std::endl;

	char* valueToCheck = strdup("123");
	ht->removeValue(valueToCheck);
	std::cout << "removeValue: " << (!ht->containsValue(valueToCheck)?"OK":"ERROR") << std::endl;

	ht->clear();
	std::cout << "clear: " << (ht->size()==0?"OK":"ERROR") << std::endl;


	// deallocate pointers
	free(keyToCheck);
	free(valueToCheck);
}

void MapUnitTest::testLinkedHashMap() {
	long k,v;
	// test collisions

	LinkedHashMap<long, long> ht;
	k=18;v=8;ht.set(k,v);
	k=1;v=2;ht.set(k,v);
	k=150;v=4;ht.set(k,v);
	k=5;v=3;ht.set(k,v);
	k=8;v=5;ht.set(k,v);
	k=6;v=5;ht.set(k,v);
	k=9;v=6;ht.set(k,v);
	k=11;v=7;ht.set(k,v);
	k=22;v=1;ht.set(k,v);

//			long valueToRemove = 5;
//			ht.removeValue(valueToRemove);

	std::cout << "sortByKey:" << std::endl;
	ht.sortByKey(&compareAsc<long>);
	for(auto it = ht.begin(); *it!=*(ht.end()); ++(*it)) {
		std::cout <<"\t"<< (*(*it)).first << ":" << (*(*it)).second << std::endl;
	}

	std::cout << "sortByValue:" << std::endl;
	ht.sortByValue(&compareDesc<long>);
	for(auto it = ht.begin(); *it!=*(ht.end()); ++(*it)) {
		std::cout <<"\t"<< (*(*it)).first << ":" << (*(*it)).second << std::endl;
	}

	ht.clear();
}

void MapUnitTest::testHashMap() {
	long k,v;
	// test collisions

	HashMap<long, long> ht;
	k=18;v=8;ht.set(k,v);
	k=1;v=2;ht.set(k,v);
	k=150;v=4;ht.set(k,v);
	k=5;v=3;ht.set(k,v);
	k=8;v=5;ht.set(k,v);
	k=6;v=5;ht.set(k,v);
	k=9;v=6;ht.set(k,v);
	k=11;v=7;ht.set(k,v);
	k=22;v=1;ht.set(k,v);

	std::cout << "iterator:" << std::endl;
	for(auto it = ht.begin(); *it!=*(ht.end()); ++(*it)) {
		std::cout <<"\t" << (*(*it)).first << ":" << (*(*it)).second << std::endl;
	}

	ht.clear();
}

void MapUnitTest::testTreeMap() {
	long k,v;
	// test collisions

	TreeMap<long, long> ht;
	k=18;v=8;ht.set(k,v);
	k=1;v=2;ht.set(k,v);
	k=150;v=4;ht.set(k,v);
	k=5;v=3;ht.set(k,v);
	k=8;v=5;ht.set(k,v);
	k=6;v=5;ht.set(k,v);
	k=9;v=6;ht.set(k,v);
	k=11;v=7;ht.set(k,v);
	k=22;v=1;ht.set(k,v);

	std::cout << "iterator:" << std::endl;
	for(auto it = ht.begin(); *it!=*(ht.end()); ++(*it)) {
		std::cout <<"\t" << (*(*it)).first << ":" << (*(*it)).second << std::endl;
	}

	ht.clear();
}
