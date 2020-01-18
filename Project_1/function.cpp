// Khai Nguyen
// TUID: 915552057
// Assignment: HW1
// Course: CIS 4307 - Spring 2020
// Filename: function.cpp
// Usage: to build functions

#include "header.h"



void spawn_worker_threads(int num_threads, pthread_t* threads){
    // create worker threads
    for (size_t i = 0; i < num_threads; ++i){
        int* section_num = (int*)malloc(sizeof(int));
        *section_num = i;
        if(pthread_create(&threads[i],NULL,workerThread,(void *)section_num) != 0){
            printf("Error: Failed to create thread\n");
            exit(1);
        }
    }
}

void * workerThread(void * arg){
    int section_num = *(int *)arg;
    int start_line = file_length/num_segments * section_num;
    int end_line = file_length/num_segments * (1 + section_num) - 1;

    if (section_num == num_segments - 1){
        end_line = file_length;
    } 

    cout << "Segment num is " << section_num<< endl;
    cout << "Start line is" << start_line << endl;
    cout << "End line is" << end_line << endl;

    get_section_count(start_line, end_line, section_num);    
}

void get_section_count(int start_line, int end_line){

    FILE *file = fopen(fileName, "r");
    int count = 0;
    if ( file == NULL ){
        cout << "Thread" << section_num << "cannot open file" << endl;
        exit;
    }

    char line[256]; /* or other suitable maximum line size */
    while (fgets(line, sizeof line, file) != NULL) /* read a line */{
        if (count == start_line){
            
            //use line or in a function return it
            //in case of a return first close the file with "fclose(file);"
        }else{
            count++;
        }
    }
        fclose(file);
}

bool isNumber(char * number){
    int i = 0;

    //checking for negative numbers
    if (*number == '-'){
        return false;
    }
    for (; *number != 0; number++){
        if (!isdigit(*number)){
            return false;
        }
    }
    return true;
}
