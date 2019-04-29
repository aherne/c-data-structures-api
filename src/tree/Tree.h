/*
 * Tree.h
 *
 *  Created on: Sep 19, 2016
 *      Author: Lucian
 */

#ifndef TREE_H_
#define TREE_H_

template<typename NODE>
class Tree {
	public:
		virtual ~Tree() {}
		virtual NODE* getRoot() = 0;
		virtual const std::size_t& getSize() const = 0;
};

#endif /* TREE_H_ */
