/*
 * ArrayList.h
 *
 *  Created on: Apr 17, 2016
 *      Author: aherne
 */

#ifndef LIST_ARRAYLIST_H_
#define LIST_ARRAYLIST_H_

#include "List.h"
#include "../Comparator.h"

template<typename T>
class ArrayList: public List<T> {
public:
	ArrayList() {
		maximum_size = 8;
		contents = (T*) malloc(maximum_size*sizeof(T));
		count = 0;
	}

	~ArrayList() {
		free(contents);
	}

	void clear() {
		free(contents);

		maximum_size = 8;
		contents = (T*) malloc(maximum_size*sizeof(T));
		count = 0;

	}

	void addToBottom(const T& value) {
		if(count == maximum_size) {
			resize();
		}
		contents[count] = value;
		++count;
	}

	void addToTop(const T& value) {
		if(count == maximum_size) {
			resize();
		}
		for(std::size_t i = count; i>0; --i) {
			contents[i]=contents[i-1];
		}
		contents[0] = value;
		++ count;
	}

	T& get(const size_t& index) {
		if(index>=count) throw std::out_of_range("Index must already exist!");
		return contents[index];
	}

	void set(const size_t& index, const T& value) {
		if(index>=count) throw std::out_of_range("Index must already exist!");
		contents[index] = value;
	}

	void emplace(const size_t& index, const T& value) {
		if(index>count) throw std::out_of_range("Index cannot exceed list length!");
		if(count == maximum_size) {
			resize();
		}
		for(std::size_t i = count; i>index; --i) {
			contents[i]=contents[i-1];
		}
		contents[index] = value;
		++ count;
	}

	bool isEmpty() {
		return count==0;
	}

	std::size_t size() {
		return count;
	}

	bool containsIndex(const size_t& index) {
		return (index>=count?false:true);
	}

	bool containsValue(const T& value) {
		for(std::size_t i=0; i<count; ++i) {
			if(valueComparator(contents[i], value)==0) {
				return true;
			}
		}
		return false;
	}

	void removeIndex(const size_t& index) {
		if(index>=count) throw std::out_of_range("Index must already exist!");
		for(std::size_t j=index; j< count; ++j) {
			if((j+1)!=count) {
				contents[j] = contents[j+1];
			}
		}
		--count;
	}

	void removeValue(const T& value) {
		int reduce = 0;
		for(std::size_t j=0; j< count; ++j) {
			if(valueComparator(contents[j], value)==0) {
				reduce ++;
			} else {
				if(reduce>0) {
					contents[j-reduce] = contents[j];
				}
			}
		}
		if(reduce==0) throw std::out_of_range("Value must already exist!");
		count -= reduce;
	}

	void sort(bool (*comparator) (const T&, const T&)) {
		std::sort(begin(), end(), comparator);
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

	comparator<T> valueComparator;
};



#endif /* LIST_ARRAYLIST_H_ */
