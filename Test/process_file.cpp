using namespace std;

// Include libraries
#include <iostream>
#include <alloca.h>
#include <fstream> // file opss
#include <set> // for set operations 
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // for size_t
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#include <unordered_set>
#include <map>
#include<bits/stdc++.h>

#define MAXSTRING 255


int main (int argc, char *argv[]){  
    if (argc < 2) {
        cout << "Not enough arguments" <<endl;
        return 1;
    }
    
    int num_segments = atoi(argv[2]);
    char * fileName = (char*) alloca(sizeof(char));
    fileName = argv[1];
    
    cout << "\nNum Segments are " << num_segments<< endl;
    cout << "\nFilename is " << fileName << endl;
    

    int section_num = 5;
    int start_line = 5;
    int end_line = 10;
    //-----------------------------------
    unordered_set<string> word_dict;    // set name
    ifstream input;                     // stream
    string filename = fileName;         // convert to string type

    input.open(filename.c_str());
    while(input.fail()){
        input.clear();
        cout<<"Incorrect filename, please enter again: ";
        cin>>filename;
        input.open(filename.c_str());
    }

    /*---------------------------Read words to set----------------------------*/
    // get words from file
    for(string line; getline(input,line );){
        // word variable to store word 
        string word; 
        line.erase(remove(line.begin(), line.end(), ','), line.end());
        line.erase(remove(line.begin(), line.end(), '.'), line.end());
        line.erase(remove(line.begin(), line.end(), '\"'), line.end());
        line.erase(remove(line.begin(), line.end(), '\''), line.end());
        line.erase(remove(line.begin(), line.end(), '!'), line.end());
        line.erase(remove(line.begin(), line.end(), '?'), line.end());
        line.erase(remove(line.begin(), line.end(), '-'), line.end());
        line.erase(remove(line.begin(), line.end(), ':'), line.end());
        line.erase(remove(line.begin(), line.end(), ';'), line.end());
        

        // making a string stream 
        stringstream iss(line); 
    
        // Read and print each word. 
        while (iss >> word){ 
            // add word to Set
            word_dict.insert(word);    
        }  
    }

    // iterate through set
    cout << "\nThe elements in set are: "; 
    for (auto it = word_dict.begin(); it != word_dict.end(); it++){ 
        cout << *it << "\n"; 
    }

    /*---------------------------Check word in section----------------------------*/
    // char line[MAXSTRING]; 
    char line2[MAXSTRING];            

    // char * word = NULL;
    char * word2 = NULL;
    
    // FILE *fptr1 = fopen(fileName, "r");
    FILE *fptr2 = fopen(fileName, "r"); // scan thru section

    // int count = 0;
    // if ( fptr1 == NULL){
    //     cout << "Thread" << section_num << "cannot open file" << endl;
    //     exit;
    // }

    /* ----------------------- have to allocate memory for char** & char* -----------------------------*/
    // char* line = (char*) calloc(MAXSTRING, sizeof(char)); /* or other suitable maximum line size */
    // char* line2 = (char*) calloc(MAXSTRING, sizeof(char));            

    // char * word = (char*)calloc(MAXSTRING, sizeof(char));
    // char * word2 = (char*)calloc(MAXSTRING, sizeof(char));



    // //char** head_list = list_of_words;
    // int turn = 0;

    // // scann ALL words in file to list_of_words
    // while(fgets(line,sizeof line,fptr1) != NULL){
    //     word = strtok(line," ");
    //     while(word != NULL){
    //         *list_of_words = (char*)alloca(sizeof(char));
    //         *list_of_words = word;
    //         cout<< "Current word in list of words " << *list_of_words << endl;
    //         word = strtok(NULL," ");
    //         list_of_words++;
    //     }
    // }

    // // reset
    // list_of_words = head_list;
    
    // cout<< "Value at list of word " << *list_of_words << endl;
    // while (list_of_words != NULL){
    //     // scan through section
    //     // locate fptr2
    //     while (fgets(line2, sizeof line2, fptr2) != NULL) /* read a line */{
    //         if (count == start_line - 1){
    //             printf("At start line: %s\n", line2);            
    //             break; // fptr2 at line startline
    //         }else{
    //             count++;
    //         }
    //     }
        
    //     turn++;
    //     cout << "Turn is " << turn << endl;
    //     if (turn == 10){
    //         exit(0);
    //     }

    //     // scan through section for line2
    //     while(fgets(line2,sizeof line2,fptr2) != NULL){

    //         printf("Current line is %s\n", line2);
    //         word2 = strtok(line2," ");
    //         while(word2 != NULL){
    //             printf("Word in line2 is %s\n", word2);
                
    //             // add to map    
    //             if(strcmp(*list_of_words,word2) == 0){
    //                 printf("Matching word is %s\n", word2);
    //             }
    //             word2 = strtok(NULL," ");
    //         }
            
    //         // check if endline reached
    //         if (count == end_line){
    //             printf("End line reached: %s\n", line2);            
    //             break; // fptr2 at line endline
    //         }else{
    //             count++;
    //         }
    //     }
    //     printf("Got out here to rewind fptr2\n");
    //     rewind(fptr2);
    //     list_of_words++;
    // }    

    //rewind(fptr1);
    // fclose(fptr1);
    // fclose(fptr2);

    return 0;

}