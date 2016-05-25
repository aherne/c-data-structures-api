/*
 * StackUnitTest.h
 *
 *  Created on: May 23, 2016
 *      Author: aherne
 */

#ifndef UNIT_TESTS_CONTAINERUNITTEST_H_
#define UNIT_TESTS_CONTAINERUNITTEST_H_

#include "../container/Stack.h"
#include "../container/Queue.h"

class ContainerUnitTest {
public:
	void execute() {
		std::cout << "=====Stack<long>=====" << std::endl;
		Stack<long> stack1;
		testStack(&stack1);

		std::cout << "=====Queue<long>=====" << std::endl;
		Queue<long> queue1;
		testQueue(&queue1);

		std::cout << "=====Stack<char*>=====" << std::endl;
		Stack<char*> stack2;
		testStack(&stack2);

		std::cout << "=====Queue<char*>=====" << std::endl;
		Queue<long> queue2;
		testQueue(&queue2);

	}
private:
	void testStack(Container<long>* container) {
		for(long i=0; i<2000; ++i) {
			container->push(i);
		}
		long newValue = 1999;
		std::size_t size = 2000;
		std::cout << "size: " << (container->size()==size?"OK":"ERROR") << std::endl;
		std::cout << "peek: " << (container->peek()==newValue?"OK":"ERROR") << std::endl;
		std::cout << "pop: " << (container->pop()==newValue?"OK":"ERROR") << std::endl;
		container->clear();
		std::cout << "clear & isEmpty: " << (container->isEmpty()?"OK":"ERROR") << std::endl;
	}

	void testStack(Container<char*>* container) {
		StringListGenerator slg(2000);
		std::vector<char*> items = slg.getList();
		for(auto it = items.begin(); it!=items.end(); ++it) {
			container->push(*it);
		}

		char* newValue = strdup("1999");
		std::size_t size = 2000;
		std::cout << "size: " << (container->size()==size?"OK":"ERROR") << std::endl;
		std::cout << "peek: " << (strcmp(container->peek(),newValue)==0?"OK":"ERROR") << std::endl;
		std::cout << "pop: " << (strcmp(container->pop(),newValue)==0?"OK":"ERROR") << std::endl;
		container->clear();
		std::cout << "clear & isEmpty: " << (container->isEmpty()?"OK":"ERROR") << std::endl;
		free(newValue);
	}

	void testQueue(Container<long>* container) {
		for(long i=0; i<2000; ++i) {
			container->push(i);
		}
		long newValue = 0;
		std::size_t size = 2000;
		std::cout << "size: " << (container->size()==size?"OK":"ERROR") << std::endl;
		std::cout << "peek: " << (container->peek()==newValue?"OK":"ERROR") << std::endl;
		std::cout << "pop: " << (container->pop()==newValue?"OK":"ERROR") << std::endl;
		container->clear();
		std::cout << "clear & isEmpty: " << (container->isEmpty()?"OK":"ERROR") << std::endl;
	}

	void testQueue(Container<char*>* container) {
		StringListGenerator slg(2000);
		std::vector<char*> items = slg.getList();
		for(auto it = items.begin(); it!=items.end(); ++it) {
			container->push(*it);
		}

		char* newValue = strdup("0");
		std::size_t size = 2000;
		std::cout << "size: " << (container->size()==size?"OK":"ERROR") << std::endl;
		std::cout << "peek: " << (strcmp(container->peek(),newValue)==0?"OK":"ERROR") << std::endl;
		std::cout << "pop: " << (strcmp(container->pop(),newValue)==0?"OK":"ERROR") << std::endl;
		container->clear();
		std::cout << "clear & isEmpty: " << (container->isEmpty()?"OK":"ERROR") << std::endl;
		free(newValue);
	}
};



#endif /* UNIT_TESTS_CONTAINERUNITTEST_H_ */
