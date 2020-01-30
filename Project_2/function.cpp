// Khai Nguyen
// TUID: 915552057
// Assignment: HW2
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
return 1 on success, cache updated
*/
int Cache::refer(string fileName, string dirName) 
{ 
    int fileSize = getFileSize(fileName);
    
    /* file too large - still transfer but not put in cache */
    if (fileSize > MAX_CACHE_SIZE){
        return 1;
    }

    /*-------------------NOT IN CACHE-----------------*/ 
    // first element
    if (cache_map.find(fileName) == cache_map.end() && cache_size == 0){
        cout << "Cache miss. ";
        cache_map.insert({ fileName, readFileContent(fileName) }); 
        cache_size += fileSize;
    }
    else if (cache_map.find(fileName) == cache_map.end() && cache_size != 0) { // and map not empty
        cout << "Cache miss. ";
        // search thru dir (fileName)
        if (searchDir(dirName, fileName) != 1){
            // cout << "Searched in dir" << endl;
            return -1; //report to client ---> no files
        }
        // if yes - update cache
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
        cache_map.insert({ fileName, readFileContent(fileName) }); 
    } 
  
    /*-------------------IN CACHE-----------------*/
    else {
        cout << "Cache hit. ";
        // delete at that position
        LRU_Queue.remove(fileName);
    }
    // push to front of queue 
    LRU_Queue.push_front(fileName);
    //cout<< "Current size after adding "<< fileName << " is " << cache_size << endl; 
    return 1;
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

// return file size
int getFileSize (string fileName){
    char filePath[fileName.size() + 1];
	strcpy(filePath, fileName.c_str());

    FILE *fp = fopen(filePath, "r");
    int len = 0;
    if( fp == NULL )  {
        perror ("Error opening file when getting fileSize");
        return(-1);
    }
    fseek(fp, 0, SEEK_END);

    len = ftell(fp);
    fclose(fp);

    return len;
}

// read a whole file into a string
string readFileContent(string fileName){
    std::ifstream file;
    file.open(fileName);
    std::string buffer;
    std::string line;
    while(file){
    std::getline(file, line);
        buffer.append(line);
        buffer.append("\n");
    }
    file.close();
    return buffer;
}


// search in directory
// return 1 if succes OR errno if fail
int searchDir(string dir, string file){
    DIR *dp;
    struct dirent *dirp;

    if((dp = opendir(dir.c_str())) == NULL){
      cout << "Error(" << errno << ") opening " << dir << endl;
      return errno;
    }
    while ((dirp = readdir(dp)) != NULL){      
        if (file.compare(dirp->d_name)){
            closedir(dp);
            return 1;
        }
    }
    closedir(dp);
    return -1;
}