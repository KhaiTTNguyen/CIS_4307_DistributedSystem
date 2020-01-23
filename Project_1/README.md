# Khai_Nguyen_Scalability & Concurrency
Project 1: Scalability & Concurrency

## Introduction
This is a basic multithreading software for counting word frequency in a file 

## Design
The spell checker program is broken into 
- word-frequency-count.cpp
- function.cpp
- header.h
- Makefile

Program flow:
- main process takes in cmd line arguments
- main process in word-frequency-count.cpp spawn threads
- threads start with workerThread start routine, locate its section, scan for words, and add to map
- workerThreads joins back to main process
- main process calculate word frequency & output to file 

## Guide 

```bash
$ make 
$ ./myNLP Great_Expectations.txt 5
$ cat hw1_out.txt 
```

## Contributors
Khai Nguyen: khainguyen@temple.edu

