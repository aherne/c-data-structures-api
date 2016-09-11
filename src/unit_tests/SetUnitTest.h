/*
 * SetUnitTest.h
 *
 *  Created on: Mar 27, 2016
 *      Author: aherne
 */

#ifndef UNIT_TESTS_SETUNITTEST_H_
#define UNIT_TESTS_SETUNITTEST_H_

#include "../set/Set.h"

class SetUnitTest {
	public:
		void execute();
	private:
		void test(Set<long>* ht);
		void test(Set<char*>* ht);
		void testLinkedHashSet();
		void testHashSet();
		void testTreeSet();
};



#endif /* UNIT_TESTS_SETUNITTEST_H_ */
