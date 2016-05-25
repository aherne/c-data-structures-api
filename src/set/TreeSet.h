/*
 * TreeSet.h
 *
 *  Created on: Mar 25, 2016
 *      Author: aherne
 */

#ifndef SET_TREESET_H_
#define SET_TREESET_H_

#include <vector>
#include <set>
#include "Set.h"
#include "../Comparator.h"

template<typename T, typename VALUE_COMPARATOR = std::less<T>>
class TreeSet : public Set<T> {
public:
	typedef typename std::set<T, VALUE_COMPARATOR>::iterator iterator;

	TreeSet(){}

	~TreeSet(){}

	void clear(){
		data.clear();
	}

	bool contains(const T& value){
		if(data.size()==0) return false;
		return data.count(value);
	}

	bool isEmpty() {
		return data.empty();
	}

	std::size_t size(){
		return data.size();
	}

	std::vector<T> getValues(){
		std::vector<T> output;
		for(auto it = data.begin(); it != data.end(); ++it) {
			output.push_back(*it);
		}
		return output;
	}

	void add(const T& value){
		data.insert(value);
	}

	void remove(const T& value) {
		if(data.size()==0) throw std::out_of_range("Key not found!");
		std::size_t rowsAffected = data.erase(value);
		if(rowsAffected==0) throw std::out_of_range("Key not found!");
	}

	typename std::set<T,VALUE_COMPARATOR>::iterator  begin() {
		return data.begin();
	}

	typename std::set<T,VALUE_COMPARATOR>::iterator  end() {
		return data.end();
	}
private:
	std::set<T, VALUE_COMPARATOR> data;
};

#endif /* SET_TREESET_H_ */
