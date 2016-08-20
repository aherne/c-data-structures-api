/*
 * MapEntry.h
 *
 *  Created on: Mar 25, 2016
 *      Author: aherne
 */

#ifndef MAP_MAPENTRY_H_
#define MAP_MAPENTRY_H_

#include "../Comparator.h"
#include "../Hashing.h"

template<typename _KEY, typename _VALUE>
struct MapEntry {
	_KEY key;
	_VALUE value;
};

template<typename _KEY, typename _VALUE>
int compareByKey(const MapEntry<_KEY,_VALUE>& left, const MapEntry<_KEY,_VALUE>& right) {
	comparator<_KEY> cmp;
	return cmp(left.key, right.key);
}

template<typename _KEY, typename _VALUE>
int compareByValue(const MapEntry<_KEY,_VALUE>& left, const MapEntry<_KEY,_VALUE>& right) {
	comparator<_VALUE> cmp;
	return cmp(left.value, right.value);
}

template<typename _KEY, typename _VALUE>
std::size_t hasher(const MapEntry<_KEY,_VALUE>& element) {
	hash<_KEY> temp;
	return temp(element.key);
}

#endif /* MAP_MAPENTRY_H_ */
