#include "unit_tests/MapUnitTest.h"
#include "unit_tests/SetUnitTest.h"
#include "unit_tests/ListUnitTest.h"
#include "unit_tests/ContainerUnitTest.h"
#include "unit_tests/TreeUnitTest.h"
#include "unit_tests/GraphUnitTest.h"

int main() {
	MapUnitTest mapUnitTest;
	mapUnitTest.execute();

	SetUnitTest setUnitTest;
	setUnitTest.execute();

	ListUnitTest listUnitTest;
	listUnitTest.execute();

	ContainerUnitTest containerUnitTest;
	containerUnitTest.execute();

	TreeUnitTest treeUnitTest;
	treeUnitTest.execute();

	GraphUnitTest graphUnitTest;
	graphUnitTest.execute();
	return 1;
}

