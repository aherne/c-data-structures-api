/*
 * MapBenchmark.h
 *
 *  Created on: Mar 25, 2016
 *      Author: aherne
 */

#ifndef BENCHMARKS_MAPBENCHMARK_H_
#define BENCHMARKS_MAPBENCHMARK_H_

#include <cstring>
#include "../map/Map.h"

class MapBenchmark {
public:
	void execute();
private:
	std::size_t getTime();
	void testUnorderedMapLong();
	void testUnorderedMapString();
	void testMap();
	void test(Map<long, long>* ht);
	void test(Map<char*, char*>* ht);
};



#endif /* BENCHMARKS_MAPBENCHMARK_H_ */
