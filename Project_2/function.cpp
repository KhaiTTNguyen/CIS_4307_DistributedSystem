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
/*
return -1 if fails - file too big or no file found in cache & specified dir
return 0 on success, cache updated
*/
int Cache::refer(string fileName) 
{ 
    cout<< "Got in refer" << endl;
    int fileSize = getFileSize(fileName);
    
    /* file too large */
    if (fileSize > MAX_CACHE_SIZE){
        return -1;
    }

    /*-------------------NOT IN CACHE-----------------*/ 
    // first element
    if (cache_map.find(fileName) == cache_map.end() && cache_map.size() == 0){
        cache_map.insert({ fileName, "mmmmmmmmmmmmmm" }); 
        cache_size += fileSize;
    }
    else if (cache_map.find(fileName) == cache_map.end() && cache_map.size() != 0) { // and map not empty
        // search thru dir (fileName)

        // if not - report to client - return -1 ---> no files
        // if yes - update cache...........
        cout << "Checking cache size" << endl;
        // cache is full 
        while (cache_size + fileSize > MAX_CACHE_SIZE) { 
            // delete least recently used element 
            string last = LRU_Queue.back();
             
            LRU_Queue.pop_back(); 
            cache_map.erase(last);
            cache_size -= getFileSize(last);
        }

        // increase cache_size record
        cache_size += fileSize;
         // add file content to Map EDITTING
        cache_map.insert({ fileName, "mmmmmmmmmmmmmm" }); 
    } 
  
    /*-------------------IN CACHE-----------------*/
    else {
                cout << "Adding to cache queue" << endl;
        // delete at that position
        LRU_Queue.remove(fileName);
    }
    // push to front of queue 
    LRU_Queue.push_front(fileName);
    cout<< "Current siuze after adding "<< fileName << " is " << cache_size << endl; 
    return 1;

    // transfer file to client transferFile(fileName, )
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