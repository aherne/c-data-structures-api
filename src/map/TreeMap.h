/*
 * TreeMap.h
 *
 *  Created on: Mar 23, 2016
 *      Author: aherne
 */

#ifndef TREEMAP_H_
#define TREEMAP_H_

#include <vector>
#include <map>
#include "Map.h"
#include "../Comparator.h"

template<typename _KEY, typename _VALUE, typename _KEY_COMPARATOR = std::less<_KEY>>
class TreeMap : public Map<_KEY,_VALUE> {
	typedef typename std::map<_KEY, _VALUE,_KEY_COMPARATOR>::iterator iterator;

	public:
		TreeMap(){
			count=0;
		}
		~TreeMap(){}

		void clear(){
			data.clear();
		}

		bool containsKey(const _KEY& key) const{
			if(data.size()==0) return false;
			return data.count(key);
		}

		bool containsValue(const _VALUE& value) const {
			if(data.size()==0) return false;
			for(auto it = data.begin(); it != data.end(); ++it) {
				if(valueComparator(it->second, value) ==0) {
					return true;
				}
			}
			return false;
		}

		bool isEmpty() const{
			return data.empty();
		}

		const std::size_t& size() const{
			count = data.size(); // TODO: hack to enforce conformity with interface
			return count;
		}

		std::vector<_KEY> getKeys(){
			std::vector<_KEY> output;
			for(auto it = data.begin(); it != data.end(); ++it) {
				output.push_back(it->first);
			}
			return output;
		}

		std::vector<_VALUE> getValues(){
			std::vector<_KEY> output;
			for(auto it = data.begin(); it != data.end(); ++it) {
				output.push_back(it->second);
			}
			return output;
		}

		const _VALUE& get(const _KEY& key) const{
			return data.at(key);
		}

		void set(const _KEY& key, const _VALUE& value){
			data[key] = value;
		}

		void removeKey(const _KEY& key) {
			if(data.size()==0) throw std::out_of_range("Key not found!");
			std::size_t rowsAffected = data.erase(key);
			if(rowsAffected==0) throw std::out_of_range("Key not found!");
		}

		void removeValue(const _VALUE& value) {
			if(data.size()==0) throw std::out_of_range("Value not found!");
			std::size_t oldCount = data.size();
			for(auto it = data.begin(); it != data.end(); ) {
				if(valueComparator(it->second, value)==0) {
					it = data.erase(it);
				} else {
					++it;
				}
			}
			if(oldCount == data.size()) throw std::out_of_range("Value not found!");
		}

		typename std::map<_KEY, _VALUE,_KEY_COMPARATOR>::iterator begin() {
			return data.begin();
		}
		typename std::map<_KEY, _VALUE,_KEY_COMPARATOR>::iterator end() {
			return data.end();
		}
	private:
		mutable std::size_t count;
		std::map<_KEY,_VALUE, _KEY_COMPARATOR> data;
		comparator<_VALUE> valueComparator;
};

#endif /* TREEMAP_H_ */
