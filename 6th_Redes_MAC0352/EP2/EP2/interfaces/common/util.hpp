using namespace std;
#ifndef UTIL_HPP
#define UTIL_HPP
#include <iostream>
#include <filesystem>
#include <sys/stat.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <string.h>
#include <ftw.h>

#include <config.hpp>

#define MAX_SIZE pow(2, 8)
#define MAX_IP_SIZE 100

/*
Used to print a byte in binary representation
Usage: printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(foo))
*/
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)     \
  (byte & 0x80 ? '1' : '0'),     \
      (byte & 0x40 ? '1' : '0'), \
      (byte & 0x20 ? '1' : '0'), \
      (byte & 0x10 ? '1' : '0'), \
      (byte & 0x08 ? '1' : '0'), \
      (byte & 0x04 ? '1' : '0'), \
      (byte & 0x02 ? '1' : '0'), \
      (byte & 0x01 ? '1' : '0')

bool isNumber(const string& str);

bool fileExists(string path);

bool isDirectory(string path);

int removeFile(string path);

int removeFolder(string path);

/* printBytes
Receives an string and prints byte 
by byte in binary representation
*/
void printBytes(string src);

/* printNetworkData
Receives the network data and prints it,
converting from network to host conventions
*/
string printNetworkData(sockaddr_in data);

void setCleanUpHook();

void resetCleanUpHook();
#endif