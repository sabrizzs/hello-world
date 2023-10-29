using namespace std;
#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <strings.h>
#include <arpa/inet.h>

#define OCUPADO true
#define LIVRE false 

class Address {
  public:
    in_addr_t ip;
    in_port_t port;

    Address();
    Address(sockaddr_in address);

    static bool compare(const Address a, const Address b);
};

class User {
  public:
    string username;
    string password;
    int session;
    bool status;
    int score;
    Address address;
    in_port_t p2pPort;

    User(string input);
    User(string input, sockaddr_in address);
    User(string input, sockaddr_in address, in_port_t p2p);
    User(string username, bool status, Address address);
};
#endif