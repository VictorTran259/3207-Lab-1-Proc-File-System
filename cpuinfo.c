#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Calculate the number of CPUs within /proc/cpuinfo and then returns that number.
int getNumCPUs() {
    //Initialize the number of CPUs to 0.
    int numCPUs = 0;
    
    FILE *file;
    char *line = NULL;
    size_t length = 0;

    file = fopen("/proc/cpuinfo", "r");

    //Throw an error if /proc/cpuinfo was unable to be opened.
    if(file == NULL) {
        printf("cpuinfo: failed to open /proc/cpuinfo.\n");
        exit(1);
    }

    //Scans through every line of /proc/cpuinfo
    while(getline(&line, &length, file) != -1) {
        //Increment numCPUs if the string "processor" is present within the current line."
        if(strstr(line, "processor") != NULL) {
            numCPUs++;
        }
    }

    fclose(file);

    return numCPUs;
}

//Prints out the amount of cache in each CPU.
void getAmountOfCacheInCPUs(){
    FILE *file;
    char *line = NULL;
    size_t length = 0;
    int processorNum;
    int cacheSize;

    file = fopen("/proc/cpuinfo", "r");

    //Throw an error if /proc/cpuinfo was unable to be opened.
    if(file == NULL) {
        printf("cpuinfo: failed to open /proc/cpuinfo.\n");
        exit(1);
    }

    //Scans through every line of /proc/cpuinfo.
    while(getline(&line, &length, file) != -1) {
        //Retrieve the processor number if the current line contains the string "processor"
        //for use in printing later.
        if(strstr(line, "processor") != NULL) {
            sscanf(line, "processor       : %d", &processorNum);
        }

        //Retrieve the amount of cache in the processor and then print out the amount of cache in
        //the processor.
        if(strstr(line, "cache size") != NULL) {
            sscanf(line, "cache size      : %d", &cacheSize);
            printf("Amount of cache in CPU #%d: %d KB\n", processorNum, cacheSize);
        }
    }

    fclose(file);
}