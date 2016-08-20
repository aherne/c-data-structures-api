/*
 * test.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: lucian p
 */
#include <iostream>

#include "unit_tests/MapUnitTest.h"
#include "benchmarks/MapBenchmark.h"
#include "unit_tests/SetUnitTest.h"
#include "benchmarks/SetBenchmark.h"
#include "unit_tests/ListUnitTest.h"
#include "benchmarks/ListBenchmark.h"
#include "unit_tests/ContainerUnitTest.h"
#include "map/TreeMap.h"

int main() {
	MapUnitTest mapUnitTest;
	mapUnitTest.execute();

//	MapBenchmark mapBenchmark;
//	mapBenchmark.execute();

//	SetUnitTest setUnitTest;
//	setUnitTest.execute();

//	SetBenchmark setBenchmark;
//	setBenchmark.execute();

//	ListUnitTest listUnitTest;
//	listUnitTest.execute();

//	ListBenchmark listBenchmark;
//	listBenchmark.execute();

//	ContainerUnitTest containerUnitTest;
//	containerUnitTest.execute();

	return 1;
}

