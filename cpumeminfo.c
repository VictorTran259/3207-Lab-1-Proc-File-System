#include "cpuinfo.h"
#include "meminfo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    printf("Amount of free memory in the system: %d kB\n", getAmountFreeMem());
    printf("Number of memory buffers: %d kB\n", getNumMemBufs());

    printf("Number of CPUs: %d\n", getNumCPUs());
    getAmountOfCacheInCPUs();
    
}