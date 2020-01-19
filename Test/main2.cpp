
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

    FILE *fptr1 = fopen(fileName, "r"); // scan thru file
    FILE *fptr2 = fopen(fileName, "r"); // scan thru section

    int count = 0;
    if ( fptr1 == NULL){
        cout << "Thread" << section_num << "cannot open file" << endl;
        exit;
    }

    char line[MAXSTRING]; /* or other suitable maximum line size */
    char line2[MAXSTRING];            

    char * word = NULL;
    char * word2 = NULL;
    
    int turn = 0;

    // scan words from start of file
    while(fgets(line,sizeof line,fptr1) != NULL){
        word = strtok(line," ");
        while(word != NULL){
            printf("Current word is %s \n",word); /* your word */
            
            // locate fptr2
            while (fgets(line2, sizeof line2, fptr2) != NULL) /* read a line */{
                if (count == start_line - 1){
                    printf("At start line: %s\n", line2);            
                    break; // fptr2 at line startline
                }else{
                    count++;
                }
            }
            
            turn++;
            cout << "Turn is " << turn << endl;
            if (turn == 10){
                exit(0);
            }
            
            // scan through section for line2
            while(fgets(line2,sizeof line2,fptr2) != NULL){

                printf("Current line is %s\n", line2);
                word2 = strtok(line2," ");
                while(word2 != NULL){
                    printf("Word in line2 is %s\n", word2);
                    
                    // add to map    
                    if(strcmp(word,word2) == 0){
                        printf("Matching word is %s\n", word2);
                    }
                    word2 = strtok(NULL," ");
                }
                
                // check if endline reached
                if (count == end_line){
                    printf("End line reached: %s\n", line2);            
                    break; // fptr2 at line endline
                }else{
                    count++;
                }
            }
            printf("Got out here to close fptr2\n");
            rewind(fptr2);
            word = strtok(NULL," ");
            printf("Current word is %s \n",word); /* your word */
        }
    }

    printf("Position of ptr1: %s\n", line2);

    //rewind(fptr1);
    fclose(fptr1);

    return 0;

}