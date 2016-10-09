/*
 * ListBenchmark.cpp
 *
 *  Created on: Sep 11, 2016
 *      Author: aherne
 */

#include "ListBenchmark.h"
#include "../list/ArrayList.h"
#include "../list/LinkedList.h"
#include "../list/DoublyLinkedList.h"
#include <forward_list>
#include <list>
#include <vector>

void ListBenchmark::execute() {
	std::cout << "=====std::vector<long>=====" << std::endl;
	testVector();
	std::cout << "=====std::forward_list<long>=====" << std::endl;
	testForwardList();
	std::cout << "=====std::list<long>=====" << std::endl;
	testSTDList();

	std::cout << "=====ArrayList<long>=====" << std::endl;
	ArrayList<long> al(1000001);
	testList(&al);
	std::cout << "=====LinkedList<long>=====" << std::endl;
	LinkedList<long> ll;
	testList(&ll);
	std::cout << "=====DoublyLinkedList<long>=====" << std::endl;
	DoublyLinkedList<long> dll;
	testList(&dll);

	StringListGenerator slg(1000000);

	std::cout << "=====std::vector<char*>=====" << std::endl;
	testVector(&slg);
	std::cout << "=====std::forward_list<char*>=====" << std::endl;
	testForwardList(&slg);
	std::cout << "=====std::list<char*>=====" << std::endl;
	testSTDList(&slg);

	std::cout << "=====ArrayList<char*>=====" << std::endl;
	ArrayList<char*> als(1000001);
	testList(&als, &slg);
	std::cout << "=====LinkedList<char*>=====" << std::endl;
	LinkedList<char*> lls;
	testList(&lls, &slg);
	std::cout << "=====DoublyLinkedList<char*>=====" << std::endl;
	DoublyLinkedList<char*> dlls;
	testList(&dlls, &slg);
}

void ListBenchmark::testVector() {
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	std::vector<long> ht;
	for(long i=0; i<1000000; ++i) {
		ht.push_back(i);
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
		ht[i];
	}
	end = getTime();
	std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(long i=999999; i>=0; --i) {
		ht.erase(ht.begin()+i);
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void ListBenchmark::testVector(StringListGenerator* slg) {
	std::vector<char*> items = slg->getList();
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	std::vector<char*> ht;
	for(auto it = items.begin(); it!=items.end(); ++it) {
		ht.push_back(*it);
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
		ht[i];
	}
	end = getTime();
	std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(long i=999999; i>=0; --i) {
		ht.erase(ht.begin()+i);
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void ListBenchmark::testForwardList() {
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	std::forward_list<long> ht;
	for(long i=0; i<1000000; ++i) {
		ht.push_front(i);
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
	for(long i=999999; i>=0; --i) {
		ht.erase_after( ht.before_begin() );
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void ListBenchmark::testForwardList(StringListGenerator* slg) {
	std::vector<char*> items = slg->getList();
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	std::forward_list<char*> ht;
	for(auto it = items.begin(); it!=items.end(); ++it) {
		ht.push_front(*it);
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
	for(long i=999999; i>=0; --i) {
		ht.erase_after( ht.before_begin() );
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void ListBenchmark::testSTDList() {
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	std::list<long> ht;
	for(long i=0; i<1000000; ++i) {
		ht.push_back(i);
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
	for(auto it = ht.begin(); it!=ht.end(); ++it) {
		(*it);
	}
	end = getTime();
	std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;

	start = getTime();
	for(long i=999999; i>=0; --i) {
		ht.erase(ht.begin());
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void ListBenchmark::testSTDList(StringListGenerator* slg) {
	std::vector<char*> items = slg->getList();
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	std::list<char*> ht;
	for(auto it = items.begin(); it!=items.end(); ++it) {
		ht.push_front(*it);
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
	for(long i=999999; i>=0; --i) {
		ht.erase(ht.begin());
	}
	end = getTime();
	std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
}

void ListBenchmark::testList(List<long>* ht) {
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	for(long i=0; i<1000000; ++i) {
		ht->addToBottom(i);
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
		ht->get(i);
	}
	end = getTime();
	std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;


	if(LinkedList<long>* v = dynamic_cast<LinkedList<long>*>(ht)) {
		start = getTime();
		for(long i=0; i<1000000; ++i) {
			v->removeIndex(0);
		}
		end = getTime();
		std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	} else {
		start = getTime();
		for(long i=999999; i>=0; --i) {
			ht->removeIndex(i);
		}
		end = getTime();
		std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	}
}

void ListBenchmark::testList(List<char*>* ht, StringListGenerator* slg) {
	std::vector<char*> items = slg->getList();
	std::size_t start, end, start_memory, end_memory;

	start_memory = getMemory();
	start = getTime();
	for(auto it = items.begin(); it!=items.end(); ++it) {
		ht->addToBottom(*it);
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
		ht->get(i);
	}
	end = getTime();
	std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;

	if(LinkedList<char*>* v = dynamic_cast<LinkedList<char*>*>(ht)) {
		start = getTime();
		for(long i=0; i<1000000; ++i) {
			v->removeIndex(0);
		}
		end = getTime();
		std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	} else {
		start = getTime();
		for(long i=999999; i>=0; --i) {
			ht->removeIndex(i);
		}
		end = getTime();
		std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	}
}

