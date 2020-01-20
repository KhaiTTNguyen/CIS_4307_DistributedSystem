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
    ifstream input;                     // input stream
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
    string line;
    for(line; getline(input,line );){
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
        iss.clear();
    }

//    iterate through set
    cout << "\nThe elements in set are: "; 
    for (auto it = word_dict.begin(); it != word_dict.end(); it++){ 
        cout << *it << "\n"; 
    }

    /*---------------------------Check word in section----------------------------*/
    // reset input stream
    input.clear();
    input.seekg(0,input.beg);
    input.close();

    int turn = 0;
    int count = 0;

    //--------------------------------------------------------------------------------
    for (auto it = word_dict.begin(); it != word_dict.end(); it++){ 
        ifstream input; 
        input.open(filename.c_str());
        while(input.fail()){
            input.clear();
            cout<<"Incorrect filename, please enter again: ";
            cin>>filename;
            input.open(filename.c_str());
        }

        // locate fptr
        string section_line;
        for(section_line; getline(input,section_line );){
            if (count == start_line - 1){
                cout << "At start line: " << section_line << endl;            
                break; // fptr at line startline
            }else{
                count++;
            }
        }
        
        turn++;
        cout << "Turn is " << turn << endl;
        if (turn == 100){
            exit(0);
        }

        string current_word;
        // scan through section for line2
        for(section_line; getline(input,section_line );){
            section_line.erase(remove(section_line.begin(), section_line.end(), ','), section_line.end());
            section_line.erase(remove(section_line.begin(), section_line.end(), '.'), section_line.end());
            section_line.erase(remove(section_line.begin(), section_line.end(), '\"'), section_line.end());
            section_line.erase(remove(section_line.begin(), section_line.end(), '\''), section_line.end());
            section_line.erase(remove(section_line.begin(), section_line.end(), '!'), section_line.end());
            section_line.erase(remove(section_line.begin(), section_line.end(), '?'), section_line.end());
            section_line.erase(remove(section_line.begin(), section_line.end(), '-'), section_line.end());
            section_line.erase(remove(section_line.begin(), section_line.end(), ':'), section_line.end());
            section_line.erase(remove(section_line.begin(), section_line.end(), ';'), section_line.end());
                
            cout << "Current line is " << section_line << endl;
            stringstream section_iss(section_line);

            // Read and print each word. 
            while (section_iss >> current_word){ 
                cout<< "Current word is " << current_word << endl;
                cout<< "Current *it is " << *it << endl;
                // add to map    
                if(current_word.compare(*it) == 0){
                    cout << "Matching word is "<< current_word << endl;
                }                
            }

            section_iss.clear();

            // check if endline reached
            if (count == end_line){
                cout << "End line reached: " << section_line << endl;            
                break; // fptr2 at line endline
            }else{
                count++;
            }
        }
        // reset input stream
        input.clear();
        input.seekg(0,input.beg);
        input.close();
    }    

    //-----------------------------------------------------------------------------------

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
    //     





    //rewind(fptr1);
    // fclose(fptr1);
    // fclose(fptr2);

    return 0;

}