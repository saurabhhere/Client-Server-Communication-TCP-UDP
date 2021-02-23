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

    // atoi - array to integer
    int port = atoi(argv[1]);
    
    char message[1500];
    
    sockaddr_in clientSocket;
    clientSocket.sin_family = AF_INET; //IPv4
    clientSocket.sin_port = htons(port);    //convert host to network 
    inet_pton(AF_INET, "127.0.0.1", &clientSocket.sin_addr);

    int clientSocketID = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocketID < 0){
        cerr<<"Not successful socket()"<<endl;
        exit(0);
    }
    

    //start sending and receiving messages
    while(1){
        string data;
        cout<<"Client: ";
        getline(cin, data);
        strcpy(message, data.c_str());
        int sendOk = sendto(clientSocketID, message, sizeof(message), 0, (sockaddr*)&clientSocket, sizeof(clientSocket));
        if (data == "exit"){
            cout<<"Connection terminated"<<endl;
            break;
        }
        if (sendOk < 0 ){
        cout<<"That didn't work"<<endl;
        exit(0);
        }

    }

    

    close(clientSocketID);
}