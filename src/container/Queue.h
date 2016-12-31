/*
 * Queue.h
 *
 *  Created on: May 23, 2016
 *      Author: aherne
 */

#ifndef CONTAINER_QUEUE_H_
#define CONTAINER_QUEUE_H_

#include "Container.h"
#include <stdexcept>

template<typename T>
class Queue: public Container<T> {
public:
	Queue(){
		maximum_size = 8;
		contents = (T*) malloc(maximum_size*sizeof(T));
		count = 0;
		position_start = 0;
		position_end = 0;
		load_factor = 0.5;
	}

	~Queue(){
		free(contents);
	}

	void clear() {
		free(contents);

		maximum_size = 8;
		contents = (T*) malloc(maximum_size*sizeof(T));
		count = 0;
		position_start = 0;
		position_end = 0;
	}

	const std::size_t& size() const {
		return count;
	}

	bool isEmpty() const {
		return count==0;
	}

	const T& peek() const {
		if(count==0) throw std::out_of_range("Container is empty!");
		return contents[position_start];
	}

	T pop() {
		if(count==0) throw std::out_of_range("Container is empty!");
		T element = contents[position_start];
		-- count;
		++ position_start;
		return element;
	}

	void push(const T& item) {
		if(position_end == maximum_size) {
			resize();
		}
		contents[position_end] = item;
		++ count;
		++ position_end;
	}

	T* begin() {
		if(count==0) return nullptr;
		return &contents[position_start];
	}

	T* end() {
		return &contents[position_end];
	}
private:
	void resize() {
		if((position_end - position_start) > (maximum_size*load_factor)) {
			maximum_size = 2*maximum_size;	// grow
		}
		T* newArray = (T*) malloc(maximum_size*sizeof(T));
		std::size_t j=0;
		for(std::size_t i=position_start; i<position_end; ++i) {
			newArray[j] = contents[i];
			++j;
		}

		free(contents);
		contents = newArray;
		position_start = 0;
		position_end = count;
	}

	double load_factor; // percentage of maximum size by which array grows
	std::size_t maximum_size;
	std::size_t count;
	std::size_t position_start;
	std::size_t position_end;
	T* contents;
};



#endif /* CONTAINER_QUEUE_H_ */
