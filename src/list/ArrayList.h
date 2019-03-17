/*
 * ArrayList.h
 *
 *  Created on: Apr 17, 2016
 *      Author: aherne
 */

#ifndef LIST_ARRAYLIST_H_
#define LIST_ARRAYLIST_H_

#include "List.h"
#include <stdexcept>

template<typename T>
class ArrayListIterator;

template<typename T>
class ArrayList: public List<T> {
	friend class ArrayListIterator<T>;
public:
	typedef ArrayListIterator<T> iterator;

	ArrayList() {
		maximum_size = 8;
		contents = (T*) malloc(maximum_size*sizeof(T));
		count = 0;
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	ArrayList(const std::size_t& reservedSize) {
		maximum_size = reservedSize;
		contents = (T*) malloc(maximum_size*sizeof(T));
		count = 0;
		internalIteratorStart = nullptr;
		internalIteratorEnd = nullptr;
	}

	~ArrayList() {
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			delete internalIteratorEnd;
		}
		free(contents);
	}

	const T& operator[](const size_t& index) const {
		return contents[index];
	}

	void clear() {
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
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

	const T& get(const size_t& index) const {
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

	bool isEmpty() const {
		return count==0;
	}

	const std::size_t& size() const {
		return count;
	}

	bool containsIndex(const size_t& index) const {
		return (index>=count?false:true);
	}

	bool containsValue(const T& value, int (*comparator)(const T&, const T&)) const {
		for(std::size_t i=0; i<count; ++i) {
			if(comparator(contents[i], value)==0) {
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

	void removeValue(const T& value, int (*comparator)(const T&, const T&)) {
		int reduce = 0;
		for(std::size_t j=0; j< count; ++j) {
			if(comparator(contents[j], value)==0) {
				reduce ++;
			} else {
				if(reduce>0) {
					contents[j-reduce] = contents[j];
				}
			}
		}
		if(reduce==0) throw std::out_of_range("Value not found!");
		count -= reduce;
	}

	void sort(bool (*comparator) (const T&, const T&)) {
		std::sort(&contents[0], &contents[count], comparator);
	}

	ListIterator<T>* begin() {
		if(internalIteratorStart!=nullptr) {
			delete internalIteratorStart;
			internalIteratorStart = nullptr;
			delete internalIteratorEnd;
			internalIteratorEnd = nullptr;
		}
		internalIteratorStart = new iterator(this);
		return internalIteratorStart;
	}

	ListIterator<T>* end() {
		if(internalIteratorEnd!=nullptr){
			return internalIteratorEnd;
		} else {
			internalIteratorEnd = new iterator(count);
			return internalIteratorEnd;
		}
	}
private:
	void resize() {
		maximum_size = 2*maximum_size;
		contents = (T*) realloc(contents, maximum_size*sizeof(T));
	}

	std::size_t maximum_size;
	std::size_t count;
	T* contents;
	ListIterator<T>* internalIteratorStart;
	ListIterator<T>* internalIteratorEnd;
};

template<typename T>
class ArrayListIterator : public ListIterator<T> {
	public:
		ArrayListIterator(ArrayList<T>* list){
			content = list;
			this->offset = 0;
			this->total = list->count;
		}

		ArrayListIterator(std::size_t total){
			content = nullptr;
			this->offset = total;
			this->total = total;
		}

		~ArrayListIterator() {}

		const T& operator*(){
			return content->contents[this->offset];
		}

		void operator++() {
			if(content->count!=this->total) {
				this->offset = this->total;
			} else {
				++this->offset;
			}
			return;
		}

	private:
		ArrayList<T>* content;
		std::size_t total;
};

#endif /* LIST_ARRAYLIST_H_ */
