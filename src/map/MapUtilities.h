/*
 * MapComparators.h
 *
 *  Created on: Mar 8, 2019
 *      Author: aherne
 */

#ifndef SRC_MAP_MAPUTILITIES_H_
#define SRC_MAP_MAPUTILITIES_H_

template<typename KEY, typename VALUE, int (*comparator)(const KEY&, const KEY&)>
static inline int compareMapKey(const MapEntry<KEY,VALUE>& left, const MapEntry<KEY,VALUE>& right) {
	return comparator(left.key, right.key);
}

template<typename KEY, typename VALUE, int (*comparator)(const VALUE&, const VALUE&)>
static inline int compareMapValue(const MapEntry<KEY,VALUE>& left, const MapEntry<KEY,VALUE>& right) {
	return comparator(left.value, right.value);
}

template<typename KEY, typename VALUE, std::size_t (*hash)(const KEY&)>
static inline std::size_t hashMapKey(const MapEntry<KEY, VALUE>& element) {
	return hash(element.key);
}

#endif /* SRC_MAP_MAPUTILITIES_H_ */
