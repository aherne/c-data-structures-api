/*
 * Map.h
 *
 *  Created on: Mar 18, 2016
 *      Author: lucian
 */

#ifndef SRC_MAP_H_
#define SRC_MAP_H_

template<typename _KEY, typename _VALUE>
class Map {
public:
	virtual ~Map(){}

	virtual void clear()=0;
	virtual bool containsKey(const _KEY&)=0;
	virtual bool containsValue(const _VALUE&)=0;
	virtual bool isEmpty()=0;
	virtual std::size_t size()=0;
	virtual std::vector<_KEY> getKeys()=0;
	virtual std::vector<_VALUE> getValues()=0;
	virtual _VALUE& get(const _KEY&)=0;
	virtual void set(const _KEY&, const _VALUE&)=0;
	virtual void removeKey(const _KEY&)=0;
	virtual void removeValue(const _VALUE&)=0;
};



#endif /* SRC_MAP_H_ */
