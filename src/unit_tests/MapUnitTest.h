/*
 * MapUnitTest.h
 *
 *  Created on: Mar 25, 2016
 *      Author: aherne
 */

#ifndef UNIT_TESTS_MAPUNITTEST_H_
#define UNIT_TESTS_MAPUNITTEST_H_

#include "../map/Map.h"

class MapUnitTest {
	public:
		void execute();
	private:
		void test(Map<long, long>* ht);
		void test(Map<char*, char*>* ht);
		void testLinkedHashMap();
		void testHashMap();
		void testTreeMap();
};



#endif /* UNIT_TESTS_MAPUNITTEST_H_ */
