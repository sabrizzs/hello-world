#include <user.hpp>

Address::Address() {
   bzero(&ip, sizeof(ip));
   bzero(&port, sizeof(port));
}

Address::Address(sockaddr_in address) {
   bzero(&ip, sizeof(ip));
   bzero(&port, sizeof(port));

   ip = address.sin_addr.s_addr;
   port = address.sin_port;
}

User::User(string input) {
   username = input.substr(0, input.find(" "));
   password = input.substr(input.find(" ") + 1, input.size());
   session = 0;
   score = 0;
   status = LIVRE;
}

User::User(string input, sockaddr_in networkAddress) {
   username = input.substr(0, input.find(" "));
   password = input.substr(input.find(" ") + 1, input.size());
   address = Address(networkAddress);
   session = 0;
   score = 0;
   status = LIVRE;
}

User::User(string input, sockaddr_in networkAddress, in_port_t p2p) {
   username = input.substr(0, input.find(" "));
   password = input.substr(input.find(" ") + 1, input.size());
   address = Address(networkAddress);
   p2pPort = p2p;
   session = 0;
   score = 0;
   status = LIVRE;   
}

User::User(string username, bool status, Address address) {
   this->username = username;
   this->status = status;
   this->address = address;
}

bool Address::compare(const Address a, const Address b) {
    if (a.ip != b.ip) return a.ip > b.ip;
    return a.port < b.port;
}