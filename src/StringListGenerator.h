/*
 * StringCreator.h
 *
 *  Created on: May 7, 2016
 *      Author: aherne
 */

#ifndef UNIT_TESTS_STRINGLISTGENERATOR_H_
#define UNIT_TESTS_STRINGLISTGENERATOR_H_

#include <vector>

class StringListGenerator {
public:
	StringListGenerator(const long& size) {
		for(long i=0; i<size; ++i) {
			char* temp = (char*) malloc(20*sizeof(char));
			sprintf(temp, "%ld", i);
			list.push_back(temp);
		}
	}

	~StringListGenerator() {
		for(char* item: list) {
			free(item);
		}
	}

	std::vector<char*>& getList() {
		return list;
	}

private:
	std::vector<char*> list;
};



#endif /* UNIT_TESTS_STRINGLISTGENERATOR_H_ */
