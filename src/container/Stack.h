/*
 * Stack.h
 *
 *  Created on: May 23, 2016
 *      Author: aherne
 */

#ifndef CONTAINER_STACK_H_
#define CONTAINER_STACK_H_

#include "Container.h"
#include <stdexcept>

template<typename T>
class Stack: public Container<T> {
public:
	Stack(){
		maximum_size = 8;
		contents = (T*) malloc(maximum_size*sizeof(T));
		count = 0;
	}

	~Stack(){
		free(contents);
	}

	void clear() {
		free(contents);

		maximum_size = 8;
		contents = (T*) malloc(maximum_size*sizeof(T));
		count = 0;
	}

	const std::size_t& size() const {
		return count;
	}

	bool isEmpty() const {
		return count==0;
	}

	const T& peek() const {
		if(count==0) throw std::out_of_range("Container is empty!");
		return contents[count-1];
	}

	T pop() {
		if(count==0) throw std::out_of_range("Container is empty!");
		--count;
		return contents[count];
	}

	void push(const T& item) {
		if(count == maximum_size) {
			resize();
		}
		contents[count] = item;
		++count;
	}

	T* begin() {
		if(count==0) return nullptr;
		return &contents[0];
	}

	T* end() {
		return &contents[count];
	}
private:
	void resize() {
		maximum_size = 2*maximum_size;
		contents = (T*) realloc(contents, maximum_size*sizeof(T));
	}

	std::size_t maximum_size;
	std::size_t count;
	T* contents;
};

#endif /* CONTAINER_STACK_H_ */
