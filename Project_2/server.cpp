// Khai Nguyen
// TUID: 915552057
// Assignment: HW2
// Course: CIS 4307 - Spring 2020

#include "header.h"

//Server side
int main(int argc, char *argv[])
{
    //for the server, we only need to specify a port number
    if(argc != 3)
    {
        cerr << "Usage: ./tcp_server port file_directory" << endl;
        exit(0);
    }
    //grab the port number
    int port = atoi(argv[1]); char * dirName = argv[2];

   /*--------------Data structure for cache-------------*/

    Cache file_cache(0); 

    //buffer to send and receive messages with
    char msg[READ_BUFF_SIZE];
     
    //setup a socket and connection tools
    sockaddr_in servAddr;
    bzero((char*)&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(port);
 
    //open stream oriented socket with internet address
    //also keep track of the socket descriptor
    int serverSd = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSd < 0)
    {
        cerr << "Error establishing the server socket" << endl;
        exit(0);
    }

    // in case there is an existing server socket - reuse it
    // if not, when recreating socket with same code, bind error happens, only after 30-60 seconds a new socket is created successfully.
    int yes=1;
    if (setsockopt(serverSd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    //bind the socket to its local address
    int bindStatus = bind(serverSd, (struct sockaddr*) &servAddr, 
        sizeof(servAddr));
    if(bindStatus < 0)
    {
        cerr << "Error binding socket to local address" << endl;
        exit(0);
    }
    cout << "Waiting for a client to connect..." << endl;
    //listen for up to 5 requests at a time
    listen(serverSd, 5);
    //receive a request from client using accept
    //we need a new address to connect with the client
    sockaddr_in newSockAddr;
    socklen_t newSockAddrSize = sizeof(newSockAddr);

    //lets keep track of the session time
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    //also keep track of the amount of data sent as well
    int bytesRead, bytesWritten = 0;
    while(1)
    {
      //
            //accept, create a new socket descriptor to 
        //handle the new connection with client
        int newSd = accept(serverSd, (sockaddr *)&newSockAddr, &newSockAddrSize);
    
        if(newSd < 0)
        {
            cerr << "Error accepting request from client!" << endl;
            exit(1);
        }
         //receive a message from the client (listen)
        memset(&msg, 0, sizeof(msg));//clear the buffer
        bytesRead += recv(newSd, (char*)&msg, sizeof(msg), 0);
        cout <<  "Client " << inet_ntoa(newSockAddr.sin_addr) << " is requesting file " << msg << endl;
        
        string fileName = std::string(msg);
        if (file_cache.refer(fileName,dirName) == 1){
            file_cache.display();
            cout << msg << " sent to the client" << endl;
            memset(&msg, 0, sizeof(msg)); //clear the buffer
            
            /* ------------transfer file to client ------------*/
            char filePath[fileName.size() + 1];
	        strcpy(filePath, fileName.c_str());
            FILE *fp = fopen(filePath, "r");
            while(fgets(msg, sizeof(msg), fp) != NULL){
                send(newSd, (char*)msg, strlen(msg), 0);
                memset(&msg, 0, sizeof(msg)); //clear the buffer
            }

        } else {
            memset(&msg, 0, sizeof(msg)); //clear the buffer
            strcpy(msg, "File not found!"); 
            send(newSd, (char*)msg, strlen(msg), 0);
            memset(&msg, 0, sizeof(msg));
        }

        close(newSd);
    }
    //we need to close the socket descriptors after we're all done
    gettimeofday(&end1, NULL);
    close(serverSd);
    cout << "********Session********" << endl;
    cout << " Bytes read: " << bytesRead << endl;
    cout << "Elapsed time: " << (end1.tv_sec - start1.tv_sec) 
        << " secs" << endl;
    cout << "Connection closed..." << endl;
    return 0;   
}