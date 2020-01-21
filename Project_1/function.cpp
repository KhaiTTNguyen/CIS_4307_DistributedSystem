// Khai Nguyen
// TUID: 915552057
// Assignment: HW1
// Course: CIS 4307 - Spring 2020
// Filename: function.cpp
// Usage: to build functions

#include "header.h"

void * workerThread(void* arg){
    Arguments* arg_sec = (Arguments*) arg;
    int section_num = arg_sec->section_num;
    int start_line = file_length/num_segments * section_num;
    int end_line = file_length/num_segments * (1 + section_num) - 1;

    if (section_num == num_segments - 1){
        end_line = file_length;
    } 

    // cout << "Segment num is " << section_num<< endl;
    // cout << "Start line is " << start_line << endl;
    // cout << "End line is " << end_line << "\n" << endl;

    pthread_mutex_lock(&mutex_conn);

    // get_word_count_in_section
    printf("File name is %s\n", arg_sec->fileName);
    
    FILE *file = fopen(arg_sec->fileName, "r");
    int count = 0;
    if ( file == NULL ){
        cout << "Thread " << section_num << " cannot open file" << endl;
        pthread_mutex_unlock(&mutex_conn);
        pthread_exit(NULL);
    }

    cout << "Thread " << section_num << "parsing words" << endl;

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
                addToMap(word, arg_sec->map);
                word = strtok(NULL, " *!#%&\'/\\()\"\n\r`:,.;?-”");
            }
        }
        count++;
    }
    fclose(file);
    pthread_mutex_unlock(&mutex_conn);
    
}

void addToMap(char* word, map<string,int>* givenMap){
    string str = string(word);
    map<string, int>::iterator iter = (*givenMap).find(str);
    //Not exist, create one
    if (iter != (*givenMap).end()) {
        (*givenMap).at(str) += 1;
    }
    //Already exist, increase count
    else {
        (*givenMap).insert(pair<string, int>(str, 1));
    }
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
