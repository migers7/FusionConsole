//
//  main.cpp
//  FusionConsole
//
//  Created by WangSam on 12/25/15.
//  Copyright © 2015 migme. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for socket functions
#include <netdb.h>      // Needed for socket functions
#include "FusionPackets.h"
#include "DataBuffer.h"
#include "Sha1.h"
#include "ConsoleColors.h"
#include <pthread.h>

using namespace migme;

// --------------------------------
int transactionId = 0, exitApplication = 0;
std::string password;

struct RecevingThreadParameters
{
    int socketfd;
    DataBuffer *dataBuffer;
};

void SendPacket(int socketfd, FusionPacket *packet);
void HandleReceivedPackets(int socketfd, FusionPacket *packet);
void Dispatch_FusionPacketError(FusionPacket *packet);
void Dispatch_FusionLoginChallenge(int socketfd, FusionPacket *packet);
ssize_t ReceivePacket(int socketfd);
FusionPacket *SignIn(const std::string username);
// --------------------------------

static inline unsigned ByteSwap(unsigned a)
{
    unsigned char b0 = a & 0xff;
    unsigned char b1 = (a >> 8) & 0xff;
    unsigned char b2 = (a >> 16) & 0xff;
    unsigned char b3 = (a >> 24) & 0xff;
    
    return b3 | (b2 << 8) | (b1 << 16) | (b0 << 24);
}

unsigned int CalculateSha1Hash(const std::string& s)
{
    Sha1 hash(s.c_str(), s.size());
    const unsigned* v = (const unsigned*) &hash;
    return ByteSwap(v[0] ^ v[1] ^ v[2] ^ v[3] ^ v[4]);
}

unsigned int CalculateJavaHash(const std::string& s)
{
    const unsigned char* p = (const unsigned char*) s.c_str();
    unsigned int sum = 0;
    while(*p) sum = sum * 31 + *p++;
    return sum;
}

// ----------------------------------------
// Socket command
int Connect(const std::string host, int port, int *socketfd, addrinfo *host_info_list)
{
    int status;
    struct addrinfo host_info;              // The struct that getaddrinfo() fills up with data.
    char *portStr;
    
    // Convert int port to char *.
    asprintf(&portStr, "%d", port);
    
    // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
    // to by hints must contain either 0 or a null pointer, as appropriate." When a struct
    // is created in C++, it will be given a block of memory. This memory is not necessary
    // empty. Therefor we use the memset function to make sure all fields are NULL.
    memset(&host_info, 0, sizeof(host_info));
    
    host_info.ai_family = AF_UNSPEC;        // IP version not specified. Can be both.
    host_info.ai_socktype = SOCK_STREAM;    // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
    
    // Now fill up the linked list of host_info structs with google's address information.
    status = getaddrinfo(host.c_str(), portStr, &host_info, &host_info_list);
    if (status != 0 || host_info_list == NULL)
    {
        std::cout << RED << "Retrieve socket address infomation...(error): \n\t" << gai_strerror(status) << RESET << std::endl;
        return -1;
    }
    
    *socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);
    if (*socketfd == -1) std::cout << RED << "Generating socket...(error)" << RESET;
    
    std::cout << std::endl;
    status = connect(*socketfd, host_info_list->ai_addr, host_info_list->ai_addrlen);
    if (status == -1)
    {
        std::cout << RED << "Connecting to fusion service...(connect error)" << RESET;
    }
    else
    {
        std::cout << GREEN << "Connecting to fusion service...(success)" << RESET;
    }
    std::cout << std::endl;
    
    return status;
}

void Dispatch_FusionPacketError(FusionPacket *packet)
{
    FusionPacket_Error error = FusionPacket_Error(*packet);
    int errorNumber = error.errorNumber.GetWithDefault(0);
    std::string description = error.description;
    std::cout << RED << "fusion response error: " << description << errorNumber << RESET << std::endl;
}

void Dispatch_FusionLoginChallenge(int socketfd, FusionPacket *packet)
{
    FusionPacket_LoginChallenge loginChallenge(*packet);
    std::string challenge = loginChallenge.challenge;
    std::string sessionId = loginChallenge.sessionId;
    std::string result = challenge + password;
    
    unsigned int hash = CalculateSha1Hash(result);
    FusionPacketBuilder_LoginResponse response;
    response.passwordHash = hash;
    
    SendPacket(socketfd, response.CreatePacket());
}

void HandleReceivedPackets(int socketfd, FusionPacket *packet)
{
    FusionEnum::PacketType type = packet->GetType();
    std::cout << "\t> received packet type: " << (int)packet->type << " " << packet->GetTypeString() << std::endl;
    switch (type)
    {
        case FusionEnum::PacketType::ERROR:
            Dispatch_FusionPacketError(packet);
            break;
        case FusionEnum::PacketType::LOGIN_CHALLENGE:
            Dispatch_FusionLoginChallenge(socketfd, packet);
            break;
        case FusionEnum::PacketType::LOGIN_OK:
            std::cout << BOLDGREEN << "Login successed at " __DATE__ " " __TIME__ "." << RESET << std::endl;
            break;
        default:
            break;
    }
}

void SendPacket(int socketfd, FusionPacket *packet)
{
    // Send packet to fusion.
    packet->transactionId = ++transactionId;
    DataBuffer writeBuffer;
    writeBuffer.WriteBlock(packet, packet->GetPacketSize());
    delete packet;
    
    while (writeBuffer.HasData()) {
        uint8_t buffer[2048];
        size_t bytes_to_write = std::min(writeBuffer.GetCount(), sizeof(buffer));
        writeBuffer.PeekBlock(buffer, bytes_to_write);
        ssize_t bytes_sent = send(socketfd, buffer, bytes_to_write, 0);
        if(bytes_sent > 0)
        {
            std::cout << "\t(sending bytes " << bytes_sent << ")" << std::endl;
            writeBuffer.ReadBlock(buffer, bytes_sent);
        }
    }
}

ssize_t ReceivePacket(int socketfd, DataBuffer *dataBuffer)
{
    ssize_t bytes_received;
    char incoming_data_buffer[2048];
    memset(incoming_data_buffer, 0, 2048);
    if ((bytes_received = recv(socketfd, incoming_data_buffer, sizeof(incoming_data_buffer), 0)) > 0)
    {
        // If no data arrives, the program will just wait here until some data arrives.
        std::cout << "\t(" << bytes_received << " byte received)" << std::endl;
        dataBuffer->WriteBlock(incoming_data_buffer, bytes_received);
        
        while(dataBuffer->HasCount(sizeof(FusionPacket)))
        {
            FusionPacket header;
            dataBuffer->PeekBlock(&header, sizeof(header));
            
            size_t packetSize = header.GetPacketSize();
            if(!dataBuffer->HasCount(packetSize)) break;
            
            FusionPacket* packet = new(header.GetContentSize()) FusionPacket();
            dataBuffer->ReadBlock(packet, packetSize);
            HandleReceivedPackets(socketfd, packet);
            delete packet;
        }
    }
    
    return bytes_received;
}

FusionPacket *SignIn(const std::string username)
{
    // Fusion login packet setup.
    FusionPacketBuilder_Login login;
    login.protocolVersion 	= 1;
    login.clientType		= FusionEnum::ClientType::ANDROID;
    login.clientVersion 	= 400;
    login.username 			= username;
    login.userAgent 		= "migme Console version 0.1a";
    login.deviceName 		= "Console";
    login.initialPresence 	= FusionEnum::PresenceType::OFFLINE;
    login.screenWidth 		= 500;
    login.screenHeight 		= 500;
    login.fontHeight 		= 48;
    login.giftPixelSize		= 64;
    login.stickerPixelSize	= 200;
    login.language 			= "en-US";
    
    return login.CreatePacket();
}
// ----------------------------------------
// Multi-thread control
void *StartReceivingThread(void *context)
{
    ssize_t bytes_received;
    struct RecevingThreadParameters *recevingParams = (RecevingThreadParameters *)context;
    std::cout << "Waiting to receive data from fusion..." << std::endl;
    while ((bytes_received = ReceivePacket(recevingParams->socketfd, recevingParams->dataBuffer)) > 0) {
        // do something.
    }
    std::cout << "Received complete. terminate socket...";
    if (bytes_received == 0) std::cout << RED << "(fusion host shutdown)" << RESET << std::endl;
    if (bytes_received == -1) std::cout << RED << "(socket disconnect)" << RESET << std::endl;
    pthread_exit(NULL);
    return NULL;
}

void *StartSendingThread(void *context)
{
    std::string line;
    while (getline(std::cin, line))
    {
        if (line.compare("exit") == 0) {
            exitApplication = 1;
            break;
        }
        std::cout << "# ";
    }
    pthread_exit(NULL);
    return NULL;
}
// ----------------------------------------

int main(int argc, const char * argv[])
{
    std::cout << "FusionConsole Copyright (C) migme 2015-2016." << std::endl;
    
    int status, socketfd, port;
    struct addrinfo *host_info_list;        // Pointer to the linked list of host_info's.
    std::string host_name, username, command;
    DataBuffer dataBuffer;
    pthread_t receiving_thread, sending_thread;
    struct RecevingThreadParameters receivingParams;
    
    std::cout << GREEN << "<<< Please input fusion service's host & port >>>" << RESET << std::endl;
    std::cout << "host: ";
    std::cin >> host_name;
    std::cout << "port: ";
    std::cin >> port;
    
    if (std::cin.fail())
    {
        std::cout << "please input integer value of port." << std::endl;
        return 0;
    }
    
    status = Connect(host_name, port, &socketfd, host_info_list);
    if (status != 0) return 0;
    
    std::cout << "username: ";
    std::cin >> username;
    std::cout << "password: ";
    std::cin >> password;
    std::cout << std::endl;
    
    SendPacket(socketfd, SignIn(username));
    
    pthread_create(&sending_thread, NULL, StartSendingThread, NULL);
    
    // Starting receive thread
    receivingParams.dataBuffer = &dataBuffer;
    receivingParams.socketfd = socketfd;
    pthread_create(&receiving_thread, NULL, StartReceivingThread, &receivingParams);

    // let main loop handles the lifecycle of this application, not using pthread_join.
    while (!exitApplication) {
        sleep(1);
    }
    
    freeaddrinfo(host_info_list);
    close(socketfd);
    
    return 0;
}
