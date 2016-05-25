/*
 * Bucket.h
 *
 *  Created on: Feb 26, 2016
 *      Author: lucian p
 */

#ifndef HASHMAPENTRY_H_
#define HASHMAPENTRY_H_

#include "MapEntry.h"

template<typename _KEY, typename _VALUE>
struct HashMapEntry {
	std::size_t hash;
	MapEntry<_KEY,_VALUE> data;
	HashMapEntry<_KEY, _VALUE>* next;
};

#endif /* HASHMAPENTRY_H_ */
