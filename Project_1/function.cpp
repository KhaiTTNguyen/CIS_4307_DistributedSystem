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

    // init individual maps for eacah thread
    for (int i = 0; i < num_segments; i++) {
        mapVector[i] = (map<std::string, int> *) (malloc(sizeof(map<string, int>)));
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

    // get_word_count_in_section
    FILE *file = fopen(fileName, "r");
    int count = 0;
    if ( file == NULL ){
        cout << "Thread" << section_num << "cannot open file" << endl;
        exit;
    }

    char line[MAXSTRING]; /* or other suitable maximum line size */
    char* word;
    while (fgets(line, sizeof line, file) != NULL) /* read a line */{
        if (count == end_line) {
            cout << "Thread " << section_num << " reached end of segment\n";
            break;
        }
        if (count >= start_line && count < end_line) {
            if (count == start_line) {
                cout << "Thread " << section_num << " reached start of segment\n";
            }
            word = strtok(line, " *!#%&\'/\\()\"\n\r`:,.;?-”");
            while (word != NULL) {
                *mapVector[section_num] = addToMap(word, *mapVector[section_num]);
                word = strtok(NULL, " *!#%&\'/\\()\"\n\r`:,.;?-”");
            }
        }
        count++;
    }
    fclose(file);
}

map<string,int> addToMap(char* word, map<string,int> givenMap){
    string str = string(word);
    map<string, int>::iterator iter = givenMap.find(str);
    //Not exist, create one
    if (iter != givenMap.end()) {
        givenMap.at(str) += 1;
    }
    //Already exist, increase count
    else {
        givenMap.insert(pair<string, int>(str, 1));
    }
    return givenMap;
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
