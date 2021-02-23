## Client Server Communication Using TCP and UDP Protocol

### Introduction
**Transmission Control Protocol (TCP):** Establishes a two-way connection between a server and a single client. Provides reliable byte stream transmission of data with error checking and correction, and message acknowledgement. <br>
**User Datagram Protocol (UDP):** Provides two-way message transfer between a server and a large number of clients. UDP is not connection-based; each data packet transmission is an independent event. Provides fast and lightweight data transmission for local packet broadcasts and remote multicasting. Inherently less reliable than TCP. Does not provide message acknowledgement.<br>
**Socket:** A socket is a programming interface and communication endpoint that is used for connecting to other computers, sending, and receiving data from them.

### How to Run
First clone this repo to your local machine using `git clone https://github.com/saurabhhere/Client-Server-Communication-TCP-UDP.git`

**For TCP**:
Go the corresponding folder
```
cd Client-Server-Communication-TCP-UDP
cd UsingTCP
```
Compile and Run `server.cpp` and `client.cpp` using:
```
g++ -o server server.cpp
./server 2000
```
```
g++ -o client client.cpp
./client localhost 2000
```

**For UDP**:
Go the corresponding folder
```
cd Client-Server-Communication-TCP-UDP
cd UsingUDP
```
Compile and Run `server.cpp` and `client.cpp` using:
```
g++ -o server server.cpp
./server 2000
```
```
g++ -o client client.cpp
./client 2000
```
Now you can send messages from client to server

### Important Logic
TCP does Flow Control and requires three packets to set up a socket connection, before any user data can be sent. In UDP, the client does not form a connection with the server like in TCP and instead just sends a datagram. 


### Additions to Project
- Added Client-Server-Communication using UDP
- Now we can send messages with spaces also


### Working Preview

***TCP***
![TCP](https://user-images.githubusercontent.com/60233336/108828956-8c829880-75ed-11eb-993c-c6f9e73bdede.gif)


***UDP***
![UDP](https://user-images.githubusercontent.com/60233336/108828959-8db3c580-75ed-11eb-9f77-e5752e4f0037.gif)
