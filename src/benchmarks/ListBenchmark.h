/*
 * ListBenchmark.h
 *
 *  Created on: May 7, 2016
 *      Author: aherne
 */

#ifndef BENCHMARKS_LISTBENCHMARK_H_
#define BENCHMARKS_LISTBENCHMARK_H_

#include "../StringListGenerator.h"
#include "../list/ArrayList.h"
#include "../list/LinkedList.h"
#include "../list/DoublyLinkedList.h"
#include <sys/time.h>
#include <forward_list>
#include <list>
#include <vector>

class ListBenchmark {
public:

	void execute() {
//		std::cout << "=====std::vector<long>=====" << std::endl;
//		testVector();
//		std::cout << "=====ArrayList<long>=====" << std::endl;
//		testArrayList();
//		std::cout << "=====std::forward_list<long>=====" << std::endl;
//		testForwardList();
		std::cout << "=====LinkedList<long>=====" << std::endl;
		testLinkedList();
//		std::cout << "=====std::list<long>=====" << std::endl;
//		testList();
//		std::cout << "=====DoublyLinkedList<long>=====" << std::endl;
//		testDoublyLinkedList();
//		StringListGenerator slg(1000000);
//		std::cout << "=====ArrayList<char*>=====" << std::endl;
//		testArrayList(&slg);
//		std::cout << "=====std::vector<char*>=====" << std::endl;
//		testVector(&slg);
//		std::cout << "=====LinkedList<char*>=====" << std::endl;
//		testLinkedList(&slg);
//		std::cout << "=====std::forward_list<char*>=====" << std::endl;
//		testForwardList(&slg);
//		std::cout << "=====DoublyLinkedList<char*>=====" << std::endl;
//		testDoublyLinkedList(&slg);
//		std::cout << "=====std::list<char*>=====" << std::endl;
//		testList(&slg);
	}
private:
	std::size_t getTime() {
		struct timeval tp;
		gettimeofday(&tp, NULL);
		return tp.tv_sec * 1000 + tp.tv_usec / 1000;
	}

	void testVector() {
		std::size_t start, end;

		start = getTime();
		std::vector<long> ht;
		for(long i=0; i<1000000; ++i) {
			ht.push_back(i);
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

	void testVector(StringListGenerator* slg) {
		std::vector<char*> items = slg->getList();
		std::size_t start, end;

		start = getTime();
		std::vector<char*> ht;
		for(auto it = items.begin(); it!=items.end(); ++it) {
			ht.push_back(*it);
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

	void testForwardList() {
		std::size_t start, end;

		start = getTime();
		std::forward_list<long> ht;
		for(long i=0; i<1000000; ++i) {
			ht.push_front(i);
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
		for(long i=999999; i>=0; --i) {
			ht.erase_after( ht.before_begin() );
		}
		end = getTime();
		std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	}

	void testForwardList(StringListGenerator* slg) {
		std::vector<char*> items = slg->getList();
		std::size_t start, end;

		start = getTime();
		std::forward_list<char*> ht;
		for(auto it = items.begin(); it!=items.end(); ++it) {
			ht.push_front(*it);
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
		for(long i=999999; i>=0; --i) {
			ht.erase_after( ht.before_begin() );
		}
		end = getTime();
		std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	}

	void testList() {
		std::size_t start, end;

		start = getTime();
		std::list<long> ht;
		for(long i=0; i<1000000; ++i) {
			ht.push_back(i);
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

	void testArrayList() {
		std::size_t start, end;

		start = getTime();
		ArrayList<long> ht;
		for(long i=0; i<1000000; ++i) {
			ht.addToBottom(i);
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
			ht.get(i);
		}
		end = getTime();
		std::cout << "\t" << "Selection[ASC]:\t" <<  (end-start) << std::endl;

		start = getTime();
		for(long i=999999; i>=0; --i) {
			ht.get(i);
		}
		end = getTime();
		std::cout << "\t" << "Selection[DESC]:\t" <<  (end-start) << std::endl;


		start = getTime();
		for(long i=999999; i>=0; --i) {
			ht.removeIndex(i);
		}
		end = getTime();
		std::cout << "\t" << "Deletion[DESC]:\t" <<  (end-start) << std::endl;
	}

	void testLinkedList() {
		std::size_t start, end;

		start = getTime();
		LinkedList<long> ht;
		for(long i=0; i<1000000; ++i) {
			ht.addToBottom(i);
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
			ht.get(i);
		}
		end = getTime();
		std::cout << "\t" << "Selection[ASC]:\t" <<  (end-start) << std::endl;


		start = getTime();
		for(long i=0; i<1000000; ++i) {
			ht.removeIndex(0);
		}
		end = getTime();
		std::cout << "\t" << "Deletion[ASC]:\t" <<  (end-start) << std::endl;
	}

	void testDoublyLinkedList() {
		std::size_t start, end;

		start = getTime();
		DoublyLinkedList<long> ht;
		for(long i=0; i<1000000; ++i) {
			ht.addToBottom(i);
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
			ht.get(i);
		}
		end = getTime();
		std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;

//		start = getTime();
//		for(long i=0; i<1000000; ++i) {
//			ht.removeIndex(0);
//		}
//		end = getTime();
//		std::cout << "\t" << "Deletion[ASC]:\t" <<  (end-start) << std::endl;

		start = getTime();
		for(long i=999999; i>=0; --i) {
			ht.removeIndex(i);
		}
		end = getTime();
		std::cout << "\t" << "Deletion[DESC]:\t" <<  (end-start) << std::endl;
	}

	void testArrayList(StringListGenerator* slg) {
		std::vector<char*> items = slg->getList();
		std::size_t start, end;

		start = getTime();
		ArrayList<char*> ht;
		for(auto it = items.begin(); it!=items.end(); ++it) {
			ht.addToBottom(*it);
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
			ht.get(i);
		}
		end = getTime();
		std::cout << "\t" << "Selection[ASC]:\t" <<  (end-start) << std::endl;

		start = getTime();
		for(long i=999999; i>=0; --i) {
			ht.get(i);
		}
		end = getTime();
		std::cout << "\t" << "Selection[DESC]:\t" <<  (end-start) << std::endl;


		start = getTime();
		for(long i=999999; i>=0; --i) {
			ht.removeIndex(i);
		}
		end = getTime();
		std::cout << "\t" << "Deletion[DESC]:\t" <<  (end-start) << std::endl;
	}

	void testLinkedList(StringListGenerator* slg) {
		std::vector<char*> items = slg->getList();
		std::size_t start, end;

		start = getTime();
		LinkedList<char*> ht;
		for(auto it = items.begin(); it!=items.end(); ++it) {
			ht.addToTop(*it);
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
			ht.get(i);
		}
		end = getTime();
		std::cout << "\t" << "Selection[ASC]:\t" <<  (end-start) << std::endl;


		start = getTime();
		for(long i=0; i<1000000; ++i) {
			ht.removeIndex(0);
		}
		end = getTime();
		std::cout << "\t" << "Deletion[ASC]:\t" <<  (end-start) << std::endl;
	}

	void testDoublyLinkedList(StringListGenerator* slg) {
		std::vector<char*> items = slg->getList();
		std::size_t start, end;

		start = getTime();
		DoublyLinkedList<char*> ht;
		for(auto it = items.begin(); it!=items.end(); ++it) {
			ht.addToBottom(*it);
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
			ht.get(i);
		}
		end = getTime();
		std::cout << "\t" << "Selection:\t" <<  (end-start) << std::endl;

//		start = getTime();
//		for(long i=0; i<1000000; ++i) {
//			ht.removeIndex(0);
//		}
//		end = getTime();
//		std::cout << "\t" << "Deletion[ASC]:\t" <<  (end-start) << std::endl;

		start = getTime();
		for(long i=999999; i>=0; --i) {
			ht.removeIndex(i);
		}
		end = getTime();
		std::cout << "\t" << "Deletion[DESC]:\t" <<  (end-start) << std::endl;
	}

	void testList(StringListGenerator* slg) {
		std::vector<char*> items = slg->getList();
		std::size_t start, end;

		start = getTime();
		std::list<char*> ht;
		for(auto it = items.begin(); it!=items.end(); ++it) {
			ht.push_front(*it);
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
		for(long i=999999; i>=0; --i) {
			ht.erase(ht.begin());
		}
		end = getTime();
		std::cout << "\t" << "Deletion:\t" <<  (end-start) << std::endl;
	}
};



#endif /* BENCHMARKS_LISTBENCHMARK_H_ */
