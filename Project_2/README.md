# Khai_Nguyen_Network Caching
Project 2: Network Caching

## Introduction
A tool for caching file over a TCP network

## Design
The network cache tool is divided into
- server.cpp
- client.cpp
- function.cpp
- header.h
- Makefile

Program flow:
- Initiate server (folder to search is specified)
- Initiate client (file to search & folder to save are specified)
- server searches in cache if the file exist, else it searches in the local directory
- server send file content buffer by buffer or report file error back to client
- client creates directory to store file 
- client read file content buffer by buffer and save file

## Test cases
- requesting a valid file
- requesting an invalid file not in directory
- requesting file larger than cache
- requesting from a dead server

## Guide 

```bash
$ make 
$ ./tcp_server 9089 .
Client 127.0.0.1 is requesting file khai.txt
Cache miss. khai.txt sent to the client
```
Open another bash window and do
```bash
$ ./tcp_client 127.0.0.1 9089 khai.txt
khai.txt saved
```

## Contributors
Khai Nguyen: khainguyen@temple.edu
