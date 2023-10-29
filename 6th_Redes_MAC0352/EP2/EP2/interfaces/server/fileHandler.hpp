using namespace std;
#ifndef FILE_HANDLER_CPP
#define FILE_HANDLER_CPP
#include <user.hpp>
#include <util.hpp>
#include <config.hpp>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <dirent.h>

#define EXIT_DB 3

class FileHandler {
    public:
        FileHandler();
        /* createNewUser
        Creates the user file. On success, returns 0.
        Returns -1 if the user already exists.
        */
        int createNewUser(User user, vector<string> content);
        /* connectNewUser
        Creates a new connected file for the user.
        Returns -1 if the user is already connected, 0 otherwise.
        */
        int connectNewUser(User user, vector<string> content);
        /* writeFile
        Overwrite the content of the file pointed by the file path.
        */
        void writeFile(string filePath, vector<string> newContent);
        vector<string> getFileContent(string filename);
        vector<string> getFilenamesInDirectory(string directory);
};

#endif