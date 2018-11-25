/*
 * ContainerUnitTest.cpp
 *
 *  Created on: Sep 11, 2016
 *      Author: aherne
 */

#include "ContainerUnitTest.h"

#include "../StringListGenerator.h"
#include "../container/Stack.h"
#include "../container/Queue.h"
#include <iostream>

void ContainerUnitTest::execute() {
	std::cout << "Stack<long>" << std::endl;
	Stack<long> stack1;
	testStack(&stack1);

	std::cout << "Stack<char*>" << std::endl;
	Stack<char*> stack2;
	testStack(&stack2);

	std::cout << "Queue<long>" << std::endl;
	Queue<long> queue1;
	testQueue(&queue1);

	std::cout << "Queue<char*>" << std::endl;
	Queue<long> queue2;
	testQueue(&queue2);

}

void ContainerUnitTest::testStack(Container<long>* container) {
	for(long i=0; i<2000; ++i) {
		container->push(i);
	}
	long newValue = 1999;
	std::size_t size = 2000;
	std::cout << "\t" << "size: " << (container->size()==size?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "peek: " << (container->peek()==newValue?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "pop: " << (container->pop()==newValue?"OK":"ERROR") << std::endl;
	container->clear();
	std::cout << "\t" << "clear & isEmpty: " << (container->isEmpty()?"OK":"ERROR") << std::endl;
}

void ContainerUnitTest::testStack(Container<char*>* container) {
	StringListGenerator slg(2000);
	std::vector<char*> items = slg.getList();
	for(auto it = items.begin(); it!=items.end(); ++it) {
		container->push(*it);
	}

	char* newValue = strdup("1999");
	std::size_t size = 2000;
	std::cout << "\t" << "size: " << (container->size()==size?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "peek: " << (strcmp(container->peek(),newValue)==0?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "pop: " << (strcmp(container->pop(),newValue)==0?"OK":"ERROR") << std::endl;
	container->clear();
	std::cout << "\t" << "clear & isEmpty: " << (container->isEmpty()?"OK":"ERROR") << std::endl;
	free(newValue);
}

void ContainerUnitTest::testQueue(Container<long>* container) {
	for(long i=0; i<2000; ++i) {
		container->push(i);
	}
	long newValue = 0;
	std::size_t size = 2000;
	std::cout << "\t" << "size: " << (container->size()==size?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "peek: " << (container->peek()==newValue?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "pop: " << (container->pop()==newValue?"OK":"ERROR") << std::endl;
	container->clear();
	std::cout << "\t" << "clear & isEmpty: " << (container->isEmpty()?"OK":"ERROR") << std::endl;
}

void ContainerUnitTest::testQueue(Container<char*>* container) {
	StringListGenerator slg(2000);
	std::vector<char*> items = slg.getList();
	for(auto it = items.begin(); it!=items.end(); ++it) {
		container->push(*it);
	}

	char* newValue = strdup("0");
	std::size_t size = 2000;
	std::cout << "\t" << "size: " << (container->size()==size?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "peek: " << (strcmp(container->peek(),newValue)==0?"OK":"ERROR") << std::endl;
	std::cout << "\t" << "pop: " << (strcmp(container->pop(),newValue)==0?"OK":"ERROR") << std::endl;
	container->clear();
	std::cout << "\t" << "clear & isEmpty: " << (container->isEmpty()?"OK":"ERROR") << std::endl;
	free(newValue);
}

