/*
 * SetBenchmark.h
 *
 *  Created on: Mar 27, 2016
 *      Author: aherne
 */

#ifndef BENCHMARKS_SETBENCHMARK_H_
#define BENCHMARKS_SETBENCHMARK_H_

#include <cstring>
#include "../set/Set.h"

class SetBenchmark {
public:
	void execute();
private:
	std::size_t getTime();
	void testUnorderedSetLong();
	void testUnorderedSetString();
	void testSet();
	void test(Set<long>* ht);
	void test(Set<char*>* ht);
};


#endif /* BENCHMARKS_SETBENCHMARK_H_ */
