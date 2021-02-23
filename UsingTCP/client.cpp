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

int main(int argc, char* argv[]){
    
    //get the arguments
    if (argc != 3){
        cout<<"Missing hostname and port number";
        exit(0);
    }
    char *serverName = argv[1];
    int port = atoi(argv[2]);   //atoi - array to integer function

    char message[1500];

    //declare client socket and retrieve details of host
    struct hostent* host = gethostbyname(serverName);
    sockaddr_in clientSocket;
    clientSocket.sin_family = AF_INET;  //IPv4
    clientSocket.sin_port = htons(port);
    clientSocket.sin_addr = ** (struct in_addr **) host->h_addr_list;   //** - derefrencing


    //socket() call to get file descriptor
    int clientSocketID = socket(AF_INET, SOCK_STREAM, 0);

    //connect() to the remote address
    //int status = connect(socketID, &serverAddress, addressLen)
    // Return 0 for successful connection
    int status = connect(clientSocketID, (sockaddr *)&clientSocket, sizeof(clientSocket));
    if (status < 0){
        cout<<"Error connecting";
        exit(0);
    }
    
    cout<<"Successful Connection!\n";


    //start sending and receiving messages
    while(1){
        string data;
        cout<<"Client: ";
        getline(cin, data);
        strcpy(message, data.c_str());
        if (data == "exit"){
            cout<<"Connection terminated"<<endl;
            break;
        }
        send(clientSocketID, message, sizeof(message), 0);
        cout<<"Server: ";
        recv(clientSocketID, message, sizeof(message), 0);
        if (!strcmp(message, "exit")){
            cout<<"Connection terminated"<<endl;
            break;
        }
        cout<<message<<endl;
    }

    //close() the socket
    close(clientSocketID);
}