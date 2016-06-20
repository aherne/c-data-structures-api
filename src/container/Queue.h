/*
 * Queue.h
 *
 *  Created on: May 23, 2016
 *      Author: aherne
 */

#ifndef CONTAINER_QUEUE_H_
#define CONTAINER_QUEUE_H_

#include <deque>
#include "Container.h"
#include "CapacityExceededException.h"

template<typename T>
class Queue: public Container<T> {
public:
	Queue(){
		capacity = 0;
	}

	Queue(const std::size_t& capacity){
		this->capacity = capacity;
	}

	~Queue(){}

	void clear() {
		contents.clear();
	}

	std::size_t size() const {
		return contents.size();
	}

	bool isEmpty() const {
		return contents.empty();
	}

	const T& peek() const {
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
		contents.push_back(item);
	}
private:
	std::deque<T> contents;
	std::size_t capacity;
};



#endif /* CONTAINER_QUEUE_H_ */
