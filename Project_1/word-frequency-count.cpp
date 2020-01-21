// Khai Nguyen
// TUID: 915552057
// Assignment: HW1
// Course: CIS 4307 - Spring 2020
// Filename: word-frequency-count.cpp
// Usage: build main program

/*
a program to count the frequency of words in a plaintext file. 
The text file is segmented into N segments. 
Each segment is processed by a separate thread the outputs the intermediate frequency count for its segment. 
The main process waits until threads complete, then computes the word frequency for the entire file based on the results of the individual threads.

Freq = count/total words

Main accept two parameters as command line arguments. 
The first parameter, in_filename, should be the full path name of a text file that will be used as input to your program. 
The second parameter, N, should be the number of text file segments that will be examined in parallel.

Your program should write the number of threads (N), 
the input file name (in_filename), 
and the elapsed execution time of the program, 
and a list of words with their frequency of occurrence in the input text to a file named hw1_out.txt in the local directory.  
*/

#include "header.h"


long file_length;
long num_segments;
char* fileName;
pthread_mutex_t mutex_conn;


int main (int argc, char *argv[]){  
    /*---------Parsing arguments----------*/
    if (argc < 2) {
        cout << "Not enough arguments" <<endl;
        return 1;
    }
    
    num_segments = atoi(argv[2]);
    char * fileName = (char*) alloca(sizeof(char));
    fileName = argv[1];
    
    cout << "\nNum Segments are " << num_segments<< endl;
    //cout << "\nFilename is " << fileName << endl;
    // printf("Value of filename %s\n", fileName); // not *filename

    /*------Get total lines of file--------*/ 
    int count = 0;  // Line counter (result) 
    char c;  // To store a character read from file 

    // Open the file 
    FILE *fp = fopen(fileName, "r"); 
  
    // Check if file exists 
    if (fp == NULL) { 
        printf("Could not open file %s", fileName); 
        return 0; 
    } 
  
    // Extract characters from file and store in character c 
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            count = count + 1; 
  
    // Close the file 
    fclose(fp); 
    printf("The file %s has %d lines\n", fileName, count); 

    file_length = count;

    /*---------Creating threads----------*/
    // array which holds worker threads
    pthread_t threads[num_segments];
    // init array of worker_thread_maps
    // mapVector.resize(num_segments);

    vector<Arguments*> args_vec;

    for (int i = 0; i < num_segments; ++i){
        std::map<std::string, int> wordMap;
        
        Arguments *section_arg = (Arguments* )malloc(sizeof(Arguments));
        
        section_arg->fileName = fileName;
        section_arg->section_num = i;
        section_arg->map = &wordMap;
        
        args_vec.push_back(section_arg);

        if(pthread_create(&threads[i],NULL,workerThread,(void *)section_arg) != 0){
            printf("Error: Failed to create thread\n");
            exit(1);
        }
    }

    printf("Spawning done\n");

    for (int i = 0; i < num_segments; i++){
        pthread_join(threads[i], NULL);
    }    
    printf("Joining done\n");

    for (int i = 0; i < args_vec.size(); i++) {
        cout << args_vec[i]->map->size() << endl;
    }
    /*----------------Feeding large map----------------*/


    return 0;
}