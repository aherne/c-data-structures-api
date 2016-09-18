/*
 * SetBenchmark.cpp
 *
 *  Created on: Sep 11, 2016
 *      Author: aherne
 */

#include "SetBenchmark.h"
#include "../set/LinkedHashSet.h"
#include "../set/HashSet.h"
#include "../set/TreeSet.h"
#include <unordered_set>
#include <set>

struct my_hash_function{
	//BKDR hash algorithm
	int operator()(char * str)const
	{
		unsigned long hash = 5381;
		int c;

		while ((c = *str++)) {
			hash = ((hash << 5) + hash) + c;
		}

		return hash;
	}
};

void SetBenchmark::execute() {
	std::cout << "std::set<long>" << std::endl;
	testSet();

	std::cout << "std::unordered_set<long>" << std::endl;
	testUnorderedSetLong();

	std::cout << "std::unordered_set<char*>" << std::endl;
	testUnorderedSetString();

	HashSet<long> hml;
	std::cout << "HashSet<long>" << std::endl;
	test(&hml);

	LinkedHashSet<long> lhml;
	std::cout << "LinkedHashSet<long>" << std::endl;
	test(&lhml);

	TreeSet<long> tml;
	std::cout << "TreeSet<long>" << std::endl;
	test(&tml);

	HashSet<char*> hms;
	std::cout << "HashSet<char*>" << std::endl;
	test(&hms);

	LinkedHashSet<char*> lhms;
	std::cout << "LinkedHashSet<char*>" << std::endl;
	test(&lhms);

	TreeSet<char*> tms;
	std::cout << "TreeSet<char*>" << std::endl;
	test(&tms);
}

void SetBenchmark::testUnorderedSetLong() {
	std::size_t start, end;

	start = getTime();
	std::unordered_set<long> ht;
	for(long i=0; i<1000000; ++i) {
		ht.insert(i);
	}
	end = getTime();
	std::cout << "\t" << "Insertion:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(auto it = ht.begin(); it!=ht.end(); ++it) {
		(*it);
	}
	end = getTime();
	std::cout << "\t" << "Iteration:\t" <<  (end-start) << std::endl;


	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht.erase(i);
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void SetBenchmark::testUnorderedSetString() {

	int start, end;

	std::unordered_set<char*, my_hash_function> ht;
	// create strings
	std::vector<char*> list;
	for(long i=0; i<1000000; ++i) {
		char* temp = (char*) malloc(20*sizeof(char));
		sprintf(temp, "%ld", i);
		list.push_back(temp);
	}

	// foreach strings, add to set
	start = getTime();
	for(char* item: list) {
		ht.insert(item);
	}
	end = getTime();
	std::cout << "\t" << "Insertion:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(auto it = ht.begin(); it!=ht.end(); ++it) {
		(*it);
	}
	end = getTime();
	std::cout << "\t" << "Iteration:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(char* item: list) {
		ht.erase(item);
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	// delete strings
	for(char* item: list) {
		free(item);
	}
}

void SetBenchmark::testSet() {
	std::size_t start, end;

	start = getTime();
	std::set<long> ht;
	for(long i=0; i<1000000; ++i) {
		ht.insert(i);
	}
	end = getTime();
	std::cout << "\t" << "Insertion:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(auto it = ht.begin(); it!=ht.end(); ++it) {
		(*it);
	}
	end = getTime();
	std::cout << "\t" << "Iteration:\t" <<  (end-start) << std::endl;


	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht.erase(i);
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void SetBenchmark::test(Set<long>* ht) {
	std::size_t start, end;
	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht->add(i);
	}
	end = getTime();
	std::cout << "\t" << "Insertion:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(auto it = ht->begin(); *it!=*(ht->end()); ++(*it)) {
		(*(*it));
	}
	end = getTime();
	std::cout << "\t" << "Iteration:\t" <<  (end-start) << std::endl;


	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht->remove(i);
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void SetBenchmark::test(Set<char*>* ht) {
	int start, end;

	// create strings
	std::vector<char*> list;
	for(long i=0; i<1000000; ++i) {
		char* temp = (char*) malloc(20*sizeof(char));
		sprintf(temp, "%ld", i);
		list.push_back(temp);
	}

	// foreach strings, add to set
	start = getTime();
	for(char* item: list) {
		ht->add(item);
	}
	end = getTime();
	std::cout << "\t" << "Insertion:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(auto it = ht->begin(); *it!=*(ht->end()); ++(*it)) {
		(*(*it));
	}
	end = getTime();
	std::cout << "\t" << "Iteration:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(char* item: list) {
		ht->remove(item);
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	// delete strings
	for(char* item: list) {
		free(item);
	}
}

