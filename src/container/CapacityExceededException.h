/*
 * CapacityExceededException.h
 *
 *  Created on: May 23, 2016
 *      Author: aherne
 */

#ifndef CONTAINER_CAPACITYEXCEEDEDEXCEPTION_H_
#define CONTAINER_CAPACITYEXCEEDEDEXCEPTION_H_

#include <exception>

class CapacityExceededException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Capacity was exceeded!";
  }
};



#endif /* CONTAINER_CAPACITYEXCEEDEDEXCEPTION_H_ */
