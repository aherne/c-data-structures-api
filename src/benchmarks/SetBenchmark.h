/*
 * SetBenchmark.h
 *
 *  Created on: Mar 27, 2016
 *      Author: aherne
 */

#ifndef BENCHMARKS_SETBENCHMARK_H_
#define BENCHMARKS_SETBENCHMARK_H_

#include "../set/LinkedHashSet.h"
#include "../set/HashSet.h"
#include "../set/TreeSet.h"
#include <unordered_set>
#include <sys/time.h>

class SetBenchmark {
public:
	void execute() {
		std::cout << "LinkedHashSet<long>" << std::endl;
		testLinkedHashSetLong();

//		std::cout << "LinkedHashSet<char*>" << std::endl;
//		testLinkedHashSetString();

		//
		//		std::cout << "HashSet<long>" << std::endl;
		//		testHashSetLong();
		//
		//		std::cout << "TreeSet<long>" << std::endl;
		//		testTreeSet();
		//

		//		HashSet<char*, char*> hms;
		//		std::cout << "HashSet<char*>" << std::endl;
		//		test(&hms);

		//		TreeSet<char*, char*, stringKeyComparator> tms;
		//		std::cout << "TreeSet<char*>" << std::endl;
		//		test(&tms);

		//		std::cout << "std::set<long>" << std::endl;
		//		testSet();

//		std::cout << "std::unordered_set<long>" << std::endl;
//		testUnorderedSet();
	}
private:
	std::size_t getTime() {
		struct timeval tp;
		gettimeofday(&tp, NULL);
		return tp.tv_sec * 1000 + tp.tv_usec / 1000;
	}

	void testUnorderedSet() {
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
			ht.count(i);
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

	void testSet() {
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
			ht.count(i);
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

	void testLinkedHashSetLong() {
		std::size_t start, end;
		LinkedHashSet<long> ht;
		start = getTime();
		for(long i=0; i<1000000; ++i) {
			ht.add(i);
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
			ht.contains(i);
		}
		end = getTime();
		std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;


		start = getTime();
		for(long i=0; i<1000000; ++i) {
			ht.remove(i);
		}
		end = getTime();
		std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	}

	void testHashSet() {
		std::size_t start, end;
		HashSet<long> ht;
		start = getTime();
		for(long i=0; i<1000000; ++i) {
			ht.add(i);
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
			ht.contains(i);
		}
		end = getTime();
		std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;


		start = getTime();
		for(long i=0; i<1000000; ++i) {
			ht.remove(i);
		}
		end = getTime();
		std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	}

	void testTreeSet() {
		std::size_t start, end;

		TreeSet<long> ht;
		start = getTime();
		for(long i=0; i<1000000; ++i) {
			ht.add(i);
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
			ht.contains(i);
		}
		end = getTime();
		std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;


		start = getTime();
		for(long i=0; i<1000000; ++i) {
			ht.remove(i);
		}
		end = getTime();
		std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	}

	void testLinkedHashSetString() {
		int start, end;

		LinkedHashSet<char*> ht;
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
			ht.add(item);
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
			ht.contains(item);
		}
		end = getTime();
		std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;

		start = getTime();
		for(char* item: list) {
			ht.remove(item);
		}
		end = getTime();
		std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
		// delete strings
		for(char* item: list) {
			free(item);
		}
	}
};




#endif /* BENCHMARKS_SETBENCHMARK_H_ */
