library:
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"library.d" -MT"library.o" -o "library.o" "src/library.cpp"
test:
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"ContainerUnitTest.d" -MT"ContainerUnitTest.o" -o "ContainerUnitTest.o" "src/unit_tests/ContainerUnitTest.cpp"
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"GraphUnitTest.d" -MT"GraphUnitTest.o" -o "GraphUnitTest.o" "src/unit_tests/GraphUnitTest.cpp"
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"ListUnitTest.d" -MT"ListUnitTest.o" -o "ListUnitTest.o" "src/unit_tests/ListUnitTest.cpp"
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"MapUnitTest.d" -MT"MapUnitTest.o" -o "MapUnitTest.o" "src/unit_tests/MapUnitTest.cpp"
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"SetUnitTest.d" -MT"SetUnitTest.o" -o "SetUnitTest.o" "src/unit_tests/SetUnitTest.cpp"
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"TreeUnitTest.d" -MT"TreeUnitTest.o" -o "TreeUnitTest.o" "src/unit_tests/TreeUnitTest.cpp"
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"test.d" -MT"test.o" -o "test.o" "src/test.cpp"
	g++ -o "CDA"  ContainerUnitTest.o GraphUnitTest.o ListUnitTest.o MapUnitTest.o SetUnitTest.o TreeUnitTest.o test.o
benchmark:
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"ListBenchmark.d" -MT"ListBenchmark.o" -o "ListBenchmark.o" "src/benchmarks/ListBenchmark.cpp"
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"MapBenchmark.d" -MT"MapBenchmark.o" -o "MapBenchmark.o" "src/benchmarks/MapBenchmark.cpp"
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"SetBenchmark.d" -MT"SetBenchmark.o" -o "SetBenchmark.o" "src/benchmarks/SetBenchmark.cpp"
	g++ -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"benchmark.d" -MT"benchmark.o" -o "benchmark.o" "src/benchmark.cpp"
	g++  -o "CDA"  ListBenchmark.o MapBenchmark.o SetBenchmark.o  benchmark.o
clean:
	rm -rf *.o
	rm -rf *.d
	rm CDA