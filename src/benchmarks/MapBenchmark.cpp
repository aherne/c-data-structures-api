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
#include <sys/time.h>

template <class _Tp>
struct my_equal_to
{
	bool operator()(const _Tp& __x, const _Tp& __y) const
	{ return strcmp( __x, __y ) == 0; }
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
	testMap();

	std::cout << "std::unordered_map<long,long>" << std::endl;
	testUnorderedMapLong();

	std::cout << "std::unordered_map<char*,char*>" << std::endl;
	testUnorderedMapString();

	HashMap<long, long> hml;
	std::cout << "HashMap<long,long>" << std::endl;
	test(&hml);

	LinkedHashMap<long, long> lhml;
	std::cout << "LinkedHashMap<long,long>" << std::endl;
	test(&lhml);

	TreeMap<long, long> tml;
	std::cout << "TreeMap<long,long>" << std::endl;
	test(&tml);

	HashMap<char*, char*> hms;
	std::cout << "HashMap<char*,char*>" << std::endl;
	test(&hms);

	LinkedHashMap<char*, char*> lhms;
	std::cout << "LinkedHashMap<char*,char*>" << std::endl;
	test(&lhms);

	TreeMap<char*, char*> tms;
	std::cout << "TreeMap<char*,char*>" << std::endl;
	test(&tms);
}
std::size_t MapBenchmark::getTime() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

void MapBenchmark::testUnorderedMapLong() {
	std::size_t start, end;

	start = getTime();
	std::unordered_map<long,long> ht;
	for(long i=0; i<1000000; ++i) {
		ht[i]=i;
	}
	end = getTime();
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

	int start, end;

	std::unordered_map<char*, char*, my_hash_function> ht;
	// create strings
	std::vector<char*> list;
	for(long i=0; i<1000000; ++i) {
		char* temp = (char*) malloc(20*sizeof(char));
		sprintf(temp, "%ld", i);
		list.push_back(temp);
	}

	// foreach strings, add to map
	start = getTime();
	for(char* item: list) {
		ht[item]= item;
	}
	end = getTime();
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

void MapBenchmark::testMap() {
	std::size_t start, end;

	start = getTime();
	std::map<long,long> ht;
	for(long i=0; i<1000000; ++i) {
		ht[i]=i;
	}
	end = getTime();
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

void MapBenchmark::test(Map<long, long>* ht) {
	std::size_t start, end;
	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht->set(i,i);
	}
	end = getTime();
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
	int start, end;

	// create strings
	std::vector<char*> list;
	for(long i=0; i<1000000; ++i) {
		char* temp = (char*) malloc(20*sizeof(char));
		sprintf(temp, "%ld", i);
		list.push_back(temp);
	}

	// foreach strings, add to map
	start = getTime();
	for(char* item: list) {
		ht->set(item, item);
	}
	end = getTime();
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
