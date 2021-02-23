#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]){
    
    if (argc != 2){
        cerr << "Missing port number"<<endl;
        exit(0);
    }

    // atoi - array to integer
    int port = atoi(argv[1]);
    
    //buffer (storage)
    char message[1500];
    
    //define a sockaddr_in struct for server socket (the socket listening)
    sockaddr_in serverSocket;
    bzero((char *)&serverSocket, sizeof(serverSocket));
    serverSocket.sin_family = AF_INET; //IPv4
    serverSocket.sin_port = htons(port);    //convert host to network   htons -> host to network short
    serverSocket.sin_addr.s_addr = htons(INADDR_ANY); //INADDR_ANY - listen to any interface (accept all connection requests)  

    //socket() for server socket
    //int socketID = socket (Family, Type, Protocol)
    int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketID < 0){
        cerr<<"Not successful socket()"<<endl;
        exit(0);
    }

    //bind() the socket to a port
    //int status = bind(socketID, &addressPort, sizeOfPort)
    int bindStatus = bind(serverSocketID, (struct sockaddr *) &serverSocket, sizeof(serverSocket));
    if (bindStatus < 0){
        //error check
        cerr<< "Not successful bind"<<endl;
        exit(0);
    }

    cout<<"Waiting for client to connect..."<<endl;

    //listen() for any incoming communication
    //int status = listen(socketID, queueLimit)
    //returns 0 if listening else -1
    listen(serverSocketID, 1);


    // define a sockaddr_in struct for the connection socket (the socket sending and receiving data)
    //For connection socket
    sockaddr_in newSocket;
    //store size of the socket 
    socklen_t newSocketLen = sizeof(newSocket);


    //accept() the connection
    //int newID = accept (socketID, &clientAddress, &addressLen)
    int newSocketID = accept(serverSocketID, (sockaddr *) &newSocket, &newSocketLen);

    if (newSocketID < 0){
        //error check
        cerr<<"Not successful accept()"<<endl;;
        exit(0);
    }
    cout<<"Client connected successfully!"<<endl;

    //send() and recv() bytes
    //int data = send(socketID, MSG, MSGLen, flags) ; send return number of bytes sent 
    //int data = recv(socketID, recvBuf, bufLen, flags)
    while(1){
        //keep sending, receiving messages until any one terminate the connection
        cout<<"Waiting for a message from client"<<endl;
        recv(newSocketID, (char *)&message, sizeof(message), 0);
        if (!strcmp(message, "exit")){
            // C library function strcmp return 0 when strings are equal
            cout<<"Session terminated"<<endl;
            break;
        }
        cout<<"Client: ";
        cout<<message<<endl;
        //get data from server
        string data;
        cout<<"Server: ";
        getline(cin, data);
        strcpy(message, data.c_str());
        if (data == "exit"){
            cout<<"Session terminated"<<endl;
            break;            
        }
        send(newSocketID, (char *) &message, sizeof(message), 0);
    }


    //close() the socket
    //int status = close(socketID)
    close(newSocketID);
    close(serverSocketID);
}