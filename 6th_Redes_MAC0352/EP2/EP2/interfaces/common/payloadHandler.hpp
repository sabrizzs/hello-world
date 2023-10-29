using namespace std;
#ifndef PAYLOAD_HANDLER_HPP
#define PAYLOAD_HANDLER_HPP
#include <user.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <sstream>

#define EXIT_PAYLOAD 4

/* processPayload
Processes the payload and returns a space-separeted string.
*/
string processPayload(string payload);
vector<string> payloadToVector(string payload);

string integerPayload(int integer);
string textPayload(string text);
string networkPayload(Address adress);

string aggregatePayloads(vector<string> payloads);
#endif