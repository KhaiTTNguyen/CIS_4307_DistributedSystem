// Khai Nguyen
// Filename: header.h
// Usage to build class and declare functions

#ifndef HEADER_H
#define HEADER_H


using namespace std;

// Include libraries
#include <iostream>
#include <alloca.h>
#include <fstream> // file opss
#include <set> // for set operations 
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // for size_t
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <unordered_set>
#include <map>
#include <numeric>


#define MAXSTRING 512

extern vector<map<string, int>*> mapVector;
extern char* fileName;
extern long file_length;
extern long num_segments;
extern pthread_mutex_t mutex_conn;

typedef struct Arguments{
    int section_num;
    char* fileName;
    std::map<std::string, int>* map;
}Arguments;


bool isNumber(char * number);
void spawn_worker_threads(int num_threads, pthread_t* threads, char* filename);
void * workerThread(void * arg);
void addToMap(char* word, map<string,int>* givenMap);

#endif