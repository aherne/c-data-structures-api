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
inline std::size_t hash(const T& item) {
	return 0;
}

template<>
inline std::size_t hash(const long& item) {
	return item;
}

template<>
inline std::size_t hash(char* const& item) {
	unsigned long hash = 5381;
	int c;
	char* temp  = item;

	while ((c = *temp++)) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

#endif /* SRC_HASHING_H_ */
