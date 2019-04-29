/*
 * GraphUnitTest.h
 *
 *  Created on: Oct 22, 2016
 *      Author: aherne
 */

#ifndef SRC_UNIT_TESTS_GRAPHUNITTEST_H_
#define SRC_UNIT_TESTS_GRAPHUNITTEST_H_

#include "../Hashing.h"
#include "../Comparator.h"
#include <iostream>
#include "../graph/DirectedUnweightedGraph.h"
#include "../graph/DirectedWeightedGraph.h"
#include "../graph/UndirectedWeightedGraph.h"
#include "../graph/WeightedGraphIterator.h"
#include "../graph/UnweightedGraphIterator.h"
#include "../graph/UndirectedUnweightedGraph.h"

class GraphUnitTest {
public:
	void execute();
private:
	void testUnweightedGraph(UnweightedGraph<long,comparator,hash>*);
	void testWeightedGraph(WeightedGraph<long,long,comparator,hash>*);
};

#endif /* SRC_UNIT_TESTS_GRAPHUNITTEST_H_ */
