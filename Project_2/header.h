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
#include <sys/stat.h> 
#include <stdlib.h>
#include <ctype.h> // for size_t
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <unordered_set>
#include <map>
#include <numeric>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <bits/stdc++.h> 
#include <dirent.h>
#include <errno.h>


using namespace std;

#define READ_BUFF_SIZE 1500
#define MAX_CACHE_SIZE 30
// 6.4e+7

class Cache{
    list<string> LRU_Queue; 
    int cache_size;
    std::map<std::string, string > cache_map;
public: 
    Cache(int); 
    int refer(string, string); 
    void display(); 
}; 
  
int refer(string fileName, string dirName); 
void display(); 
int getFileSize (string fileName);
string readFileContent(string fileName);
int searchDir(string dir, string file);

#endif