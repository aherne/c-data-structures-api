/*
 * ListUnitTest.h
 *
 *  Created on: May 3, 2016
 *      Author: aherne
 */

#ifndef UNIT_TESTS_LISTUNITTEST_H_
#define UNIT_TESTS_LISTUNITTEST_H_

#include "../list/List.h"

class ListUnitTest {
public:
	void execute();
private:
	void testList(List<long>* list);
	void testList(List<char*>* list);
	void testArrayList();
	void testLinkedList();
	void testDoublyLinkedList();
};


#endif /* UNIT_TESTS_LISTUNITTEST_H_ */
