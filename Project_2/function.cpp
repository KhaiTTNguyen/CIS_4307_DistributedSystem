// Khai Nguyen
// TUID: 915552057
// Assignment: HW1
// Course: CIS 4307 - Spring 2020
// Filename: function.cpp
// Usage: to build functions

#include "header.h"

// Declare the size 
Cache::Cache(int n) 
{ 
    cache_size = n; 
} 
  
// Refers key x with in the LRU cache 
void Cache::refer(string fileName) 
{ 
    cout<< "Got in refer" << endl;
    int fileSize = getFileSize(fileName);
    /*-------------------NOT IN CACHE-----------------*/ 
    if (cache_map.find(fileName) == cache_map.end() && cache_map.size() != 0) { // and map not empty
        // search thru dir (fileName)
        // if not - report to client
        // if yes - update cache...........
        cout << "Checking cache size" << endl;
        // cache is full 
        if (cache_size + fileSize >= MAX_CACHE_SIZE) { 
            // delete least recently used element 
            string last = LRU_Queue.back(); 
                    cout << "about to pop" << endl;
            // Pops the last elmeent 
            LRU_Queue.pop_back(); 
                    cout << "poped" << endl;
            // Erase "last" in map
            cache_map.erase(last);
        }
    } 
  
    /*-------------------IN CACHE-----------------*/
    else {
                cout << "Adding to cache queue" << endl;
        // delete at that position
        LRU_Queue.remove(fileName);
    }
    // push to front of queue 
    LRU_Queue.push_front(fileName); 

    // add file content to Map
    cache_map.insert({ fileName, "mmmmmmmmmmmmmm" }); 

    // increase cache_size record
    cache_size += fileSize;
    cout<< "Current siuze is" << cache_size << endl;
    // transfer file to client
    //.......................
} 
  
// Function to display contents of cache 
void Cache::display() 
{ 
  
    // Iterate in the deque and print 
    // all the elements in it 
    for (auto it = LRU_Queue.begin(); it != LRU_Queue.end();it++){ 
        cout << (*it) << "-"; 
    }
    cout << endl; 
} 


int getFileSize (string fileName){
    char filePath[fileName.size() + 1];
	strcpy(filePath, fileName.c_str());

    FILE *fp = fopen(filePath, "r");
    int len = 0;
    if( fp == NULL )  {
        perror ("Error opening file");
        return(-1);
    }
    fseek(fp, 0, SEEK_END);

    len = ftell(fp);
    fclose(fp);

    return len;
}