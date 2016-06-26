/*
 * Container.h
 *
 *  Created on: May 23, 2016
 *      Author: aherne
 */

#ifndef CONTAINER_CONTAINER_H_
#define CONTAINER_CONTAINER_H_

template<typename T>
class Container {
public:
	virtual ~Container(){}

	virtual void clear() = 0;
	virtual const std::size_t& size() const = 0;
	virtual bool isEmpty() const = 0;
	virtual const T& peek() const = 0;
	virtual T pop() = 0;
	virtual void push(const T& item) = 0;
};



#endif /* CONTAINER_CONTAINER_H_ */
