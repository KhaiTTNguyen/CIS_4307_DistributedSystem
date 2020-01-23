# Khai_Nguyen_Network Caching
Project 2: Network Caching

## Introduction
This is a basic multithreading software for counting word frequency in a file 

## Design
The spell checker program is broken into 
- .cpp
- function.cpp
- header.h
- Makefile

Program flow:
- main process takes in cmd line arguments
- main process in word-frequency-count.cpp spawn threads
- threads start with workerThread start routine, locate its section, scan for words, and add to map
- workerThreads joins back to main process
- main process calculate word frequency & output to file 

## Test cases
Different test cases you use to test your program: e.g., requesting an invalid file, requesting from a dead server

## Guide 

```bash
$ make 
$ ./myNLP Great_Expectations.txt 5
$ cat hw1_out.txt 
```

## Contributors
Khai Nguyen: khainguyen@temple.edu
