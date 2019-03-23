/*
 * Comparator.h
 *
 *  Created on: Mar 3, 2016
 *      Author: lucian
 */

#ifndef SRC_COMPARATOR_H_
#define SRC_COMPARATOR_H_
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <typeinfo>

template<typename T>
inline int comparator(const T& left, const T& right) {
	return 1;
}

template<>
inline int comparator(const long& left, const long& right) {
	if(left<right) return -1;
	else if (left>right) return 1;
	else return 0;
}

template<>
inline int comparator(char* const& left, char* const& right) {
	return strcmp(left, right);
}

template<typename T>
bool compareAsc(const T& left, const T& right) {
	return (comparator(left, right)<0?true:false);
}

template<typename T>
bool compareDesc(const T& left, const T& right) {
	return (comparator(right, left)<0?true:false);
}

#endif /* SRC_COMPARATOR_H_ */
