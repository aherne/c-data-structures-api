/*
 * Benchmark.h
 *
 *  Created on: Sep 18, 2016
 *      Author: aherne
 */

#ifndef SRC_BENCHMARK_H_
#define SRC_BENCHMARK_H_

#include <sys/time.h>
#include <cstddef>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

static inline std::size_t getTime() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return tp.tv_sec * 1000 + tp.tv_usec / 1000;
}

// http://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
static inline std::size_t getMemory(){
	//Note: this value is in KB!
	FILE* file = fopen("/proc/self/status", "r");
	int result = -1;
	char line[128];

    while (fgets(line, 128, file) != NULL){
        if (strncmp(line, "VmSize:", 7) == 0){
        	// This assumes that a digit will be found and the line ends in " Kb".
			int i = strlen(line);
			const char* p = line;
			while (*p <'0' || *p > '9') p++;
			line[i-3] = '\0';
			result = atoi(p);
            break;
        }
    }
    fclose(file);
    return result;
}

#endif /* SRC_BENCHMARK_H_ */
