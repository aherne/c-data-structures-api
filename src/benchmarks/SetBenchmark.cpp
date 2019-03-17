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

struct my_comparator
{
	bool operator()(char* const& left, char* const& right) const
	{ return strcmp( left, right )<0?true:false; }
};

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
	testSetLong();

	std::cout << "std::set<char*>" << std::endl;
	testSetString();

	std::cout << "std::unordered_set<long>" << std::endl;
	testUnorderedSetLong();

	std::cout << "std::unordered_set<char*>" << std::endl;
	testUnorderedSetString();

	HashSet<long, comparator, hash> hml(1000001);
	std::cout << "HashSet<long>" << std::endl;
	test(&hml);

	LinkedHashSet<long, comparator, hash> lhml(1000001);
	std::cout << "LinkedHashSet<long>" << std::endl;
	test(&lhml);

	TreeSet<long, comparator> tml;
	std::cout << "TreeSet<long>" << std::endl;
	test(&tml);

	TreeSet<char*, comparator> tms;
	std::cout << "TreeSet<char*>" << std::endl;
	test(&tms);

	HashSet<char*, comparator, hash> hms(1000001);
	std::cout << "HashSet<char*>" << std::endl;
	test(&hms);

	LinkedHashSet<char*, comparator, hash> lhms(1000001);
	std::cout << "LinkedHashSet<char*>" << std::endl;
	test(&lhms);
}

void SetBenchmark::testUnorderedSetLong() {
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	std::unordered_set<long> ht;
	ht.reserve(1000001);
	for(long i=0; i<1000000; ++i) {
		ht.insert(i);
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
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
	std::size_t start, end, start_memory, end_memory;

	std::unordered_set<char*, my_hash_function> ht;
	ht.reserve(1000001);
	// create strings
	std::vector<char*> list;
	for(long i=0; i<1000000; ++i) {
		char* temp = (char*) malloc(20*sizeof(char));
		sprintf(temp, "%ld", i);
		list.push_back(temp);
	}

	// foreach strings, add to set
	start_memory = getMemory();
	start = getTime();
	for(char* item: list) {
		ht.insert(item);
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
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

void SetBenchmark::testSetLong() {
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	std::set<long> ht;
	for(long i=0; i<1000000; ++i) {
		ht.insert(i);
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
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

void SetBenchmark::testSetString() {
	std::size_t start, end, start_memory, end_memory;

	std::set<char*, my_comparator> ht;
	// create strings
	std::vector<char*> list;
	for(long i=0; i<1000000; ++i) {
		char* temp = (char*) malloc(20*sizeof(char));
		sprintf(temp, "%ld", i);
		list.push_back(temp);
	}

	// foreach strings, add to set
	start_memory = getMemory();
	start = getTime();
	for(char* item: list) {
		ht.insert(item);
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
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

void SetBenchmark::test(Set<long>* ht) {
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht->add(i);
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
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
	std::size_t start, end, start_memory, end_memory;

	// create strings
	std::vector<char*> list;
	for(long i=0; i<1000000; ++i) {
		char* temp = (char*) malloc(20*sizeof(char));
		sprintf(temp, "%ld", i);
		list.push_back(temp);
	}

	// foreach strings, add to set
	start_memory = getMemory();
	start = getTime();
	for(char* item: list) {
		ht->add(item);
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
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

