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

	TreeSet(){
		count = 0;
	}

	~TreeSet(){}

	void clear(){
		data.clear();
	}

	bool contains(const T& value) const{
		if(data.size()==0) return false;
		return data.count(value);
	}

	bool isEmpty() const {
		return data.empty();
	}

	const std::size_t& size() const{
		count = data.size();
		return count;
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
	mutable std::size_t count;
	std::set<T, VALUE_COMPARATOR> data;
};

#endif /* SET_TREESET_H_ */
