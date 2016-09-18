/*
 * ListBenchmark.h
 *
 *  Created on: May 7, 2016
 *      Author: aherne
 */

#ifndef BENCHMARKS_LISTBENCHMARK_H_
#define BENCHMARKS_LISTBENCHMARK_H_

#include "../Benchmark.h"
#include "../StringListGenerator.h"

class ListBenchmark {
public:
	void execute();
private:
	void testVector();
	void testVector(StringListGenerator* slg);
	void testForwardList();
	void testForwardList(StringListGenerator* slg);
	void testList();
	void testArrayList();
	void testLinkedList();
	void testDoublyLinkedList();
	void testArrayList(StringListGenerator* slg);
	void testLinkedList(StringListGenerator* slg);
	void testDoublyLinkedList(StringListGenerator* slg);
	void testList(StringListGenerator* slg);
};



#endif /* BENCHMARKS_LISTBENCHMARK_H_ */
