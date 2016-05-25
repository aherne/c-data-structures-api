/*
 * Set.h
 *
 *  Created on: Mar 19, 2016
 *      Author: aherne
 */

#ifndef SET_H_
#define SET_H_

template<typename T>
class Set {
public:
	virtual ~Set(){}

	virtual void clear() = 0;
	virtual bool contains(const T& value) = 0;
	virtual bool isEmpty() = 0;
	virtual std::size_t size() = 0;
	virtual std::vector<T> getValues() = 0;
	virtual void add(const T& value) = 0;
	virtual void remove(const T& value) = 0;
};

#endif /* SET_H_ */
