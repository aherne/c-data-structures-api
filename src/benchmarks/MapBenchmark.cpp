/*
 * MapBenchmark.cpp
 *
 *  Created on: Sep 11, 2016
 *      Author: aherne
 */

#include "MapBenchmark.h"
#include "../map/LinkedHashMap.h"
#include "../map/HashMap.h"
#include "../map/TreeMap.h"
#include <unordered_map>
#include <map>

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

void MapBenchmark::execute() {
	std::cout << "std::map<long,long>" << std::endl;
	testMapLong();

	std::cout << "std::map<char*,char*>" << std::endl;
	testMapString();

	std::cout << "std::unordered_map<long,long>" << std::endl;
	testUnorderedMapLong();

	std::cout << "std::unordered_map<char*,char*>" << std::endl;
	testUnorderedMapString();

	HashMap<long, long, comparator, hash> hml;
	std::cout << "HashMap<long,long>" << std::endl;
	test(&hml);

	LinkedHashMap<long, long, comparator, hash> lhml;
	std::cout << "LinkedHashMap<long,long>" << std::endl;
	test(&lhml);

	TreeMap<long, long, comparator> tml;
	std::cout << "TreeMap<long,long>" << std::endl;
	test(&tml);

	HashMap<char*, char*, comparator, hash> hms;
	std::cout << "HashMap<char*,char*>" << std::endl;
	test(&hms);

	LinkedHashMap<char*, char*, comparator, hash> lhms;
	std::cout << "LinkedHashMap<char*,char*>" << std::endl;
	test(&lhms);

	TreeMap<char*, char*, comparator> tms;
	std::cout << "TreeMap<char*,char*>" << std::endl;
	test(&tms);
}

void MapBenchmark::testUnorderedMapLong() {
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	std::unordered_map<long,long> ht;
	for(long i=0; i<1000000; ++i) {
		ht[i]=i;
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
	std::cout << "\t" << "Insertion:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(auto it = ht.begin(); it!=ht.end(); ++it) {
		(*it).first;
	}
	end = getTime();
	std::cout << "\t" << "Iteration:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht[i];
	}
	end = getTime();
	std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;


	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht.erase(i);
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void MapBenchmark::testUnorderedMapString() {
	std::size_t start, end, start_memory, end_memory;

	std::unordered_map<char*, char*, my_hash_function> ht;
	// create strings
	std::vector<char*> list;
	for(long i=0; i<1000000; ++i) {
		char* temp = (char*) malloc(20*sizeof(char));
		sprintf(temp, "%ld", i);
		list.push_back(temp);
	}

	// foreach strings, add to map
	start_memory = getMemory();
	start = getTime();
	for(char* item: list) {
		ht[item]= item;
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
	std::cout << "\t" << "Insertion:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(auto it = ht.begin(); it!=ht.end(); ++it) {
		(*it).first;
	}
	end = getTime();
	std::cout << "\t" << "Iteration:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(char* item: list) {
		ht[item];
	}
	end = getTime();
	std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;

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

void MapBenchmark::testMapLong() {
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	std::map<long,long> ht;
	for(long i=0; i<1000000; ++i) {
		ht[i]=i;
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
	std::cout << "\t" << "Insertion:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(auto it = ht.begin(); it!=ht.end(); ++it) {
		(*it).first;
	}
	end = getTime();
	std::cout << "\t" << "Iteration:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht[i];
	}
	end = getTime();
	std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;


	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht.erase(i);
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void MapBenchmark::testMapString() {
	std::size_t start, end, start_memory, end_memory;

	std::map<char*, char*, my_comparator> ht;
	// create strings
	std::vector<char*> list;
	for(long i=0; i<1000000; ++i) {
		char* temp = (char*) malloc(20*sizeof(char));
		sprintf(temp, "%ld", i);
		list.push_back(temp);
	}

	// foreach strings, add to map
	start_memory = getMemory();
	start = getTime();
	for(char* item: list) {
		ht[item]= item;
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
	std::cout << "\t" << "Insertion:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(auto it = ht.begin(); it!=ht.end(); ++it) {
		(*it).first;
	}
	end = getTime();
	std::cout << "\t" << "Iteration:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(char* item: list) {
		ht[item];
	}
	end = getTime();
	std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;

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

void MapBenchmark::test(Map<long, long>* ht) {
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht->set(i,i);
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
	std::cout << "\t" << "Insertion:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(auto it = ht->begin(); *it!=*(ht->end()); ++(*it)) {
		(*(*it)).first;
	}
	end = getTime();
	std::cout << "\t" << "Iteration:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht->get(i);
	}
	end = getTime();
	std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;


	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht->removeKey(i);
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void MapBenchmark::test(Map<char*, char*>* ht) {
	std::size_t start, end, start_memory, end_memory;

	// create strings
	std::vector<char*> list;
	for(long i=0; i<1000000; ++i) {
		char* temp = (char*) malloc(20*sizeof(char));
		sprintf(temp, "%ld", i);
		list.push_back(temp);
	}

	// foreach strings, add to map
	start_memory = getMemory();
	start = getTime();
	for(char* item: list) {
		ht->set(item, item);
	}
	end = getTime();
	end_memory = getMemory();
	std::cout << "\t" << "Memory:\t" <<  (end_memory-start_memory) << std::endl;
	std::cout << "\t" << "Insertion:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(auto it = ht->begin(); *it!=*(ht->end()); ++(*it)) {
		(*(*it)).first;
	}
	end = getTime();
	std::cout << "\t" << "Iteration:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(char* item: list) {
		ht->get(item);
	}
	end = getTime();
	std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(char* item: list) {
		ht->removeKey(item);
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	// delete strings
	for(char* item: list) {
		free(item);
	}
}
