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
int main (int argc, char *argv[]){  
    return 0;
}