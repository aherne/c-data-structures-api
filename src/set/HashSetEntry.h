/*
 * HashSet.h
 *
 *  Created on: Mar 4, 2016
 *      Author: lucian
 */

#ifndef SRC_HASHSETENTRY_H_
#define SRC_HASHSETENTRY_H_


template<typename T>
struct HashSetEntry {
	std::size_t hash;
	T value;
	HashSetEntry<T>* next;
};

#endif /* SRC_HASHSETENTRY_H_ */
