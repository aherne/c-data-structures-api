/*
 * test.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: lucian p
 */
#include <iostream>

#include "benchmarks/MapBenchmark.h"
#include "benchmarks/SetBenchmark.h"
#include "benchmarks/ListBenchmark.h"

int main() {
	MapBenchmark mapBenchmark;
	mapBenchmark.execute();

	SetBenchmark setBenchmark;
	setBenchmark.execute();

	ListBenchmark listBenchmark;
	listBenchmark.execute();
	return 1;
}

