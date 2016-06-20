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
struct comparator {
	int operator()(T& left, T& right) const {

		std::cout << typeid(left).name() << std::endl;
		std::cout << typeid(right).name() << std::endl;
		throw std::out_of_range("No key/value comparator defined for this type:");
		return 0;
	}
};

template<>
struct comparator<char> {
	int operator()(const char& left, const char& right) const {
		if(left<right) return -1;
		else if (left>right) return 1;
		else return 0;
	}
};

template<>
struct comparator<long> {
	int operator()(const long& left, const long& right) const {
		if(left<right) return -1;
		else if (left>right) return 1;
		else return 0;
	}
};

template<>
struct comparator<double> {
	int operator()(const double& left, const double& right) const {
		if(left<right) return -1;
		else if (left>right) return 1;
		else return 0;
	}
};

template<>
struct comparator<char*> {
	int operator()(char* const& left, char* const& right) const {
		return strcmp(left, right);
	}
};

template<typename T>
bool compareAsc(const T& left, const T& right) {
	comparator<T> comp;
	return (comp(left, right)<0?true:false);
}

template<typename T>
bool compareDesc(const T& left, const T& right) {
	comparator<T> comp;
	return (comp(right, left)<0?true:false);
}

static inline
bool compareAscCI(char* const& left, char* const& right) {
	return (strcasecmp(left, right)<0?true:false);
}

static inline
bool compareDescCI(char* const& left, char* const& right){
	return (strcasecmp(right, left)<0?true:false);
}

struct stringKeyComparator {
   bool operator()(char* const& a, char* const& b) const {
	   return (strcasecmp(a, b)<0?true:false);
   }
};


#endif /* SRC_COMPARATOR_H_ */
