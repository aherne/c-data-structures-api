/*
 * StackUnitTest.h
 *
 *  Created on: May 23, 2016
 *      Author: aherne
 */

#ifndef UNIT_TESTS_CONTAINERUNITTEST_H_
#define UNIT_TESTS_CONTAINERUNITTEST_H_

#include "../container/Container.h"

class ContainerUnitTest {
public:
	void execute();
private:
	void testStack(Container<long>* container);
	void testStack(Container<char*>* container);
	void testQueue(Container<long>* container);
	void testQueue(Container<char*>* container);
};



#endif /* UNIT_TESTS_CONTAINERUNITTEST_H_ */
