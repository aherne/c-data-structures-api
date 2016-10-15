/*
 * Hashing.h
 *
 *  Created on: Mar 2, 2016
 *      Author: lucian p
 */

#ifndef SRC_HASHING_H_
#define SRC_HASHING_H_
#include <stdexcept>

template<typename T>
struct hash {
	std::size_t operator()(T item) const {
		throw std::logic_error("No hashing function found for this type!");
		return 0;
	}
};

template<>
struct hash<long> {
	std::size_t operator()(const long& item) const {
		return item;
	}
};

template<>
struct hash<char*> {
	std::size_t operator()(const char* item) const {
		unsigned long hash = 5381;
		int c;

		while ((c = *item++)) {
			hash = ((hash << 5) + hash) + c;
		}

		return hash;
	}
};

template<typename T>
std::size_t hashByValue(const T& item) {
	hash<T> temp;
	return temp(item);
}


#endif /* SRC_HASHING_H_ */
