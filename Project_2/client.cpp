// Khai Nguyen
// TUID: 915552057
// Assignment: HW2
// Course: CIS 4307 - Spring 2020

// Usage: tcp_client server_host server_port file_name directory
#include "header.h"

using namespace std;
//Client side
int main(int argc, char *argv[])
{
    //we need 2 things: ip address and port number, in that order
    if(argc < 5){
        cerr << "Usage: server_ip port file local_dir_to_store" << endl; exit(0); 
    } //grab the IP address and port number 
    char *serverIp = argv[1]; int port = atoi(argv[2]); char* fileName = argv[3]; char* dirName = argv[4];
    //create a message buffer 
    char msg[READ_BUFF_SIZE]; 
    //setup a socket and connection tools 
    struct hostent* host = gethostbyname(serverIp); 
    sockaddr_in sendSockAddr;   
    bzero((char*)&sendSockAddr, sizeof(sendSockAddr)); 
    sendSockAddr.sin_family = AF_INET; 
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    int clientSd = socket(AF_INET, SOCK_STREAM, 0);
    //try to connect...
    int status = connect(clientSd,
                         (sockaddr*) &sendSockAddr, sizeof(sendSockAddr));
    if(status < 0)
    {
        cout<<"Error connecting to socket!"<<endl; 
        exit(0);
    }
    cout << "Connected to the server!" << endl;
    int bytesRead, bytesWritten = 0;
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);

    /*--------------send file name to search ------------*/
    send(clientSd, (char*)fileName, strlen(fileName), 0);
    memset(&msg, 0, sizeof(msg));//clear the buffer


    dirName = strcat(dirName,"/");
    char * filePath = strcat(dirName ,fileName);
    FILE * myfile = fopen(filePath, "w"); 
    while(recv(clientSd, (char*)&msg, sizeof(msg), 0) != 0){
        if (strcmp(msg," ") == 0){
            break;
        }
        fprintf(myfile, msg);
        fprintf(myfile, "\n");    
        memset(&msg, 0, sizeof(msg));
    }
    fclose(myfile);
    // while(1)
    // {
    //     // cout << ">";
    //     // // get input from client
    //     // string data;
    //     // getline(cin, data);
    //     // memset(&msg, 0, sizeof(msg));//clear the buffer
    //     // strcpy(msg, data.c_str());
    //     // if(data == "exit")
    //     // {
    //     //     send(clientSd, (char*)&msg, strlen(msg), 0);
    //     //     break;
    //     // }
    //     // bytesWritten += send(clientSd, (char*)&msg, strlen(msg), 0);
    //     // cout << "Awaiting server response..." << endl;
    //     // memset(&msg, 0, sizeof(msg));//clear the buffer
        

    //     // stopped at this recv syscall
    //     bytesRead += recv(clientSd, (char*)&msg, sizeof(msg), 0);
    //     if(!strcmp(msg, "exit")){
    //         cout << "Server has quit the session" << endl;
    //         break;
    //     }
    //     cout << "Server: " << msg << endl;
    // }

    
    gettimeofday(&end1, NULL);
    close(clientSd);
    cout << "********Session********" << endl;
    cout << "Bytes written: " << bytesWritten << 
    " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec- start1.tv_sec) 
      << " secs" << endl;
    cout << "Connection closed" << endl;
    return 0;    
}