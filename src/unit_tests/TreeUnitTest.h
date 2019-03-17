/*
 * TreeTest.h
 *
 *  Created on: Sep 10, 2016
 *      Author: aherne
 */

#ifndef SRC_UNIT_TESTS_TREEUNITTEST_H_
#define SRC_UNIT_TESTS_TREEUNITTEST_H_

#include "../Hashing.h"
#include "../Comparator.h"
#include <iostream>

class TreeUnitTest {
public:
	void execute();
private:
	void treeTest();
	void uniqueTreeTest();
	void iteratorsTest();
};


#endif /* SRC_UNIT_TESTS_TREEUNITTEST_H_ */
