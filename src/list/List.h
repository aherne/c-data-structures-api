/*
 * List.h
 *
 *  Created on: Apr 17, 2016
 *      Author: aherne
 */

#ifndef LIST_LIST_H_
#define LIST_LIST_H_

#include <algorithm>

template<typename T>
class ListIterator {
	public:
		ListIterator() {
			offset = 0;
		}
		virtual ~ListIterator() {}
		virtual const T& operator*() = 0;
		virtual void operator++() = 0;


		bool operator!=(const ListIterator<T>& it) {
			return offset != it.offset;
		}
	protected:
		std::size_t offset;
};

template<typename T>
class List {
public:
	virtual ~List() {}
	virtual const T& operator[](const size_t& index) const=0;

	virtual void clear()=0;
	virtual void addToTop(const T& value)=0;
	virtual void addToBottom(const T& value)=0;
	virtual const T& get(const size_t& index) const =0;
	virtual void set(const size_t& index, const T& value)=0;
	virtual void emplace(const size_t& index, const T& value)=0;
	virtual bool isEmpty() const = 0;
	virtual const std::size_t& size() const = 0;
	virtual bool containsIndex(const size_t& index) const = 0;
	virtual bool containsValue(const T& value) const = 0;
	virtual void removeIndex(const size_t& index) = 0;
	virtual void removeValue(const T& value) = 0;
	virtual ListIterator<T>* begin() = 0;
	virtual ListIterator<T>* end() = 0;
};

#endif /* LIST_LIST_H_ */
