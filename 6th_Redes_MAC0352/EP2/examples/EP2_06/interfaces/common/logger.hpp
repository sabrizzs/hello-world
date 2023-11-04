using namespace std;
#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <util.hpp>
#include <config.hpp>

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>

#define EXIT_LOGGER 5

class Logger {
    private:
        ofstream log;
        string connectionType;

        string getDatetime(); 
    public:
        Logger();
        Logger(string typeOfConnection, string logName);
        void write(string title, string message);
};

#endif