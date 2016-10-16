/*
 * Map.h
 *
 *  Created on: Mar 18, 2016
 *      Author: lucian
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

#include <utility>
#include "MapEntry.h"

template<typename _KEY, typename _VALUE>
class MapIterator {
	public:
		MapIterator() {
			offset = 0;
		}
		virtual ~MapIterator() {}
		virtual const std::pair<_KEY, _VALUE> operator*() = 0;
		virtual void operator++() = 0;

		bool operator!=(const MapIterator<_KEY,_VALUE>& it) {
			return offset != it.offset;
		}
	protected:
		std::size_t offset;
};

template<typename _KEY, typename _VALUE>
class Map {
public:
	virtual ~Map(){}

	virtual void clear()=0;
	virtual bool containsKey(const _KEY&) const=0;
	virtual bool containsValue(const _VALUE&, int (*compare)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&)=compareByValue) const=0;
	virtual bool isEmpty() const=0;
	virtual const std::size_t& size() const=0;
	virtual const _VALUE& get(const _KEY&) const=0;
	virtual void set(const _KEY&, const _VALUE&)=0;
	virtual void removeKey(const _KEY&)=0;
	virtual void removeValue(const _VALUE&, int (*compare)(const MapEntry<_KEY,_VALUE>&, const MapEntry<_KEY,_VALUE>&)=compareByValue)=0;
	virtual MapIterator<_KEY,_VALUE>* begin() = 0;
	virtual MapIterator<_KEY,_VALUE>* end() = 0;
};

#endif /* SRC_MAP_H_ */
