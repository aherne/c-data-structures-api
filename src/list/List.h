/*
 * List.h
 *
 *  Created on: Apr 17, 2016
 *      Author: aherne
 */

#ifndef LIST_LIST_H_
#define LIST_LIST_H_

#include <stdlib.h>
#include <algorithm>

template<typename T>
class List {
public:
	virtual ~List() {}

	virtual void clear()=0;
	virtual void addToTop(const T& value)=0;
	virtual void addToBottom(const T& value)=0;
	virtual T& get(const size_t& index)=0;
	virtual void set(const size_t& index, const T& value)=0;
	virtual void emplace(const size_t& index, const T& value)=0;
	virtual bool isEmpty() = 0;
	virtual std::size_t size() = 0;
	virtual bool containsIndex(const size_t& index) = 0;
	virtual bool containsValue(const T& value) = 0;
	virtual void removeIndex(const size_t& index) = 0;
	virtual void removeValue(const T& value) = 0;
	virtual void sort(bool (*comparator) (const T&, const T&)) = 0;
};

#endif /* LIST_LIST_H_ */
