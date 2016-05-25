/*
 * Stack.h
 *
 *  Created on: May 23, 2016
 *      Author: aherne
 */

#ifndef CONTAINER_STACK_H_
#define CONTAINER_STACK_H_

#include <deque>
#include "Container.h"
#include "CapacityExceededException.h"

template<typename T>
class Stack: public Container<T> {
public:
	Stack(){
		capacity = 0;
	}

	Stack(const std::size_t& capacity){
		this->capacity = capacity;
	}

	~Stack(){}

	void clear() {
		contents.clear();
	}

	std::size_t size() {
		return contents.size();
	}

	bool isEmpty() {
		return contents.empty();
	}

	T& peek() {
		if(contents.size()==0) throw std::out_of_range("Container is empty!");
		return contents[0];
	}

	T pop() {
		if(contents.size()==0) throw std::out_of_range("Container is empty!");
		T element = contents[0];
		contents.pop_front();
		return element;
	}

	void push(const T& item) {
		if(capacity!=0 && contents.size()==capacity) throw CapacityExceededException();
		contents.push_front(item);
	}
private:
	std::deque<T> contents;
	std::size_t capacity;
};

#endif /* CONTAINER_STACK_H_ */
