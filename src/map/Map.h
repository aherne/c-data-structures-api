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
#include "MapUtilities.h"

template<typename KEY, typename VALUE>
class MapIterator {
	public:
		MapIterator() {
			offset = 0;
		}
		virtual ~MapIterator() {}
		virtual const std::pair<KEY, VALUE> operator*() = 0;
		virtual void operator++() = 0;

		bool operator!=(const MapIterator<KEY,VALUE>& it) {
			return offset != it.offset;
		}
	protected:
		std::size_t offset;
};

template<typename KEY, typename VALUE>
class Map {
public:
	virtual ~Map(){}

	virtual void clear()=0;
	virtual bool containsKey(const KEY&) const=0;
	virtual bool containsValue(const VALUE&) const=0;
	virtual bool isEmpty() const=0;
	virtual const std::size_t& size() const=0;
	virtual const VALUE& get(const KEY&) const=0;
	virtual void set(const KEY&, const VALUE&)=0;
	virtual void removeKey(const KEY&)=0;
	virtual void removeValue(const VALUE&)=0;
	virtual MapIterator<KEY,VALUE>* begin() = 0;
	virtual MapIterator<KEY,VALUE>* end() = 0;
};

#endif /* SRC_MAP_H_ */
