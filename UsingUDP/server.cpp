#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <bits/stdc++.h>
#include<iostream>
#include<sys/socket.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

using namespace std;

int main(int argc, char *argv[]){
    
    if (argc != 2){
        cerr << "Missing port number"<<endl;
        exit(0);
    }

    // atoi - array to integerc
    int port = atoi(argv[1]);
    
    //buffer (storage)
    char message[1500];
    
    //define a sockaddr_in struct for server socket (the socket listening)
    sockaddr_in serverSocket;
    serverSocket.sin_family = AF_INET; //IPv4
    serverSocket.sin_port = htons(port);    //convert host to network 
    serverSocket.sin_addr.s_addr = htons(INADDR_ANY); //INADDR_ANY - listen to any interface (accept all connection requests)  


    //socket() for server socket
    //int socketID = socket (Family, Type, Protocol)
    int serverSocketID = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocketID < 0){
        cerr<<"Not successful socket()"<<endl;
        exit(0);
    }

    //bind() the socket to a port
    //int status = bind(socketID, &addressPort, sizeOfPort)
    int bindStatus = bind(serverSocketID, (struct sockaddr *) &serverSocket, sizeof(serverSocket));
    if (bindStatus < 0){
        cerr<< "Not successful bind"<<endl;
        exit(0);
    }

    cout<<"Waiting for client to connect..."<<endl;

    sockaddr_in newSocket;
    //store size of the socket 
    socklen_t newSocketLen = sizeof(newSocket);
    
    while(1){
        recvfrom(serverSocketID, (char *)&message, sizeof(message), 0, (sockaddr *)&newSocket, &newSocketLen);
        cout<<"Client: ";
        cout<<message<<endl;
        if (!strcmp(message, "exit")){
            cout<<"Connection terminated"<<endl;
            break;
        }
    }

    //close() the socket
    //int status = close(socketID)
    close(serverSocketID);
}