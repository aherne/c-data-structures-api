/*
 * Set.h
 *
 *  Created on: Mar 19, 2016
 *      Author: aherne
 */

#ifndef SET_H_
#define SET_H_

#include <cstring>

template<typename T>
class SetIterator {
	public:
		SetIterator() {
			offset = 0;
		}
		virtual ~SetIterator() {}
		virtual const T& operator*() = 0;
		virtual void operator++() = 0;


		bool operator!=(const SetIterator<T>& it) {
			return offset != it.offset;
		}
	protected:
		std::size_t offset;
};

template<typename T>
class Set {
public:
	virtual ~Set(){}

	virtual void clear() = 0;
	virtual bool contains(const T& value) const = 0;
	virtual bool isEmpty() const = 0;
	virtual const std::size_t& size() const = 0;
	virtual void add(const T& value) = 0;
	virtual void remove(const T& value) = 0;
	virtual SetIterator<T>* begin() = 0;
	virtual SetIterator<T>* end() = 0;
};

#endif /* SET_H_ */
