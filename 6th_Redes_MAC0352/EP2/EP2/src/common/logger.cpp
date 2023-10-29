#include <logger.hpp>

string Logger::getDatetime() {
    auto end = chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    
    string datetimeWithNewLine = ctime(&end_time);
    string datetimeWithoutNewLine = datetimeWithNewLine.substr(0, datetimeWithNewLine.length() - 1);
    return datetimeWithoutNewLine;
}

Logger::Logger() {}

Logger::Logger(string typeOfConnection, string logName) {
    if(!fileExists(LOG_PATH)) {
        if(mkdir(LOG_PATH, 0777) == -1) {
            perror("mkdir :(\n");
            exit(EXIT_LOGGER);
        }
    }

    string filename = LOG_PATH + string("/") + logName;
    log.open(filename, ios::app);
    if(!log.is_open()) {
        cerr << "[ERROR] Error creating log file! Closing connection." << endl;
        exit(EXIT_LOGGER);
    }

    connectionType = typeOfConnection;
}

void Logger::write(string title, string message) {
    string datetime = getDatetime();
    string header = "[" + datetime + "|" + connectionType + ":" + title + "]";
    string logMessage = header + " " + message;

    log << logMessage << endl;
}

