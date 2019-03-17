CC = g++
CFLAGS = -O2 -g3 -Wall -c
all:
	$(CC) $(CFLAGS) "src/library.cpp"
	$(CC) -shared -o CDS.so library.o
test:
	$(CC) $(CFLAGS) "src/unit_tests/MapUnitTest.cpp"
	$(CC) $(CFLAGS) "src/unit_tests/ContainerUnitTest.cpp"
	$(CC) $(CFLAGS) "src/unit_tests/GraphUnitTest.cpp"
	$(CC) $(CFLAGS) "src/unit_tests/ListUnitTest.cpp"
	$(CC) $(CFLAGS) "src/unit_tests/SetUnitTest.cpp"
	$(CC) $(CFLAGS) "src/unit_tests/TreeUnitTest.cpp"
	$(CC) $(CFLAGS) "src/test.cpp"
	$(CC) -o "CDS"  ContainerUnitTest.o GraphUnitTest.o ListUnitTest.o MapUnitTest.o SetUnitTest.o TreeUnitTest.o test.o
benchmark:
	$(CC) $(CFLAGS) "src/benchmarks/ListBenchmark.cpp"
	$(CC) $(CFLAGS) "src/benchmarks/MapBenchmark.cpp"
	$(CC) $(CFLAGS) "src/benchmarks/SetBenchmark.cpp"
	$(CC) $(CFLAGS) "src/benchmark.cpp"
	$(CC)  -o "CDS"  ListBenchmark.o MapBenchmark.o SetBenchmark.o  benchmark.o
clean:
	rm -rf *.o
	rm -rf *.so
	rm CDS