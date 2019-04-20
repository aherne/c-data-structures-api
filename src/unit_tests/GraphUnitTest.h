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

class GraphUnitTest {
public:
	void execute();
private:
	void simpleUniqueGraphTest();
	void weightedUniqueGraphTest();
};

#endif /* SRC_UNIT_TESTS_GRAPHUNITTEST_H_ */
